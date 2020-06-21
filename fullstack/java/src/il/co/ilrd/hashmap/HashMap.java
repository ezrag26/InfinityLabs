package il.co.ilrd.hashmap;

import il.co.ilrd.pair.Pair;

import java.util.*;

public class HashMap<K, V> implements Map<K, V> {
	private static final int DEFAULT_CAPACITY = 16;
	private final int capacity;
	private int size;
	private List<List<Entry<K, V>>> hashMap;
	private int modCount;

	private void checkFailFast(int mapModCount, int iterModCount) {
		if (mapModCount != iterModCount) {
			throw new ConcurrentModificationException();
		}
	}

	private class EntrySet extends AbstractSet<Entry<K, V>> {

		private class EntrySetIter implements Iterator<Entry<K, V>> {
			private final int modCount;
			private int currentBucket;
			private Iterator<Entry<K, V>> entryIter;

			public EntrySetIter() {
				this.modCount = HashMap.this.modCount;
				currentBucket = 0;
				entryIter = getNextIterator();
			}

			/**
			 * Checks if this Iterator will return data upon its next call to
			 * next()
			 *
			 * @return true if the next call to next() will return data, false
			 * otherwise
			 * @throws ConcurrentModificationException if the HashMap has been
			 * modified during this Iterators iteration over the HashMap
			 */
			@Override
			public boolean hasNext() {
				checkFailFast(HashMap.this.modCount, this.modCount);

				return entryIter != null;
			}

			/**
			 * Increments this Iterator to the next entry in the HashMap
			 *
			 * @return the entry before this Iterator was incremented
			 * @throws NoSuchElementException if this Iterator has reached the
			 * end of the HashMap
			 * @throws ConcurrentModificationException if the HashMap has been
			 * modified during this Iterators iteration over the HashMap
			 */
			@Override
			public Entry<K, V> next() {
				/* no more entries */
				if (!hasNext()) throw new NoSuchElementException();

				Entry<K, V> retVal = entryIter.next();

				/* no more entries in bucket, get iterator of next list */
				if (!entryIter.hasNext()) {
					++currentBucket; /* start checking from next bucket */
					entryIter = getNextIterator();
				}

				return retVal;
			}

			private Iterator<Entry<K, V>> getNextIterator() {
				while (currentBucket < capacity &&
						hashMap.get(currentBucket) == null) {
					++currentBucket;
				}

				/* no more lists */
				if (currentBucket >= capacity) return null;

				/* list exists but is empty, keep looking for non-empty list */
				if (hashMap.get(currentBucket).isEmpty()) {
					++currentBucket;
					return getNextIterator();
				}

				return hashMap.get(currentBucket).iterator();
			}
		}

		/**
		 * Gets an iterator to this Set of entries
		 *
		 * @return an iterator to this Set of entries
		 */
		@Override
		public Iterator<Entry<K, V>> iterator() {
			return new EntrySetIter();
		}

		/**
		 * Gets the number of entries in this Set
		 *
		 * @return the number of entries in this Set
		 */
		@Override
		public int size() { return size; }
	}

	private class KeySet extends AbstractSet<K> {

		private class KeySetIter implements Iterator<K> {
			private Iterator<Entry<K, V>> keyIter;

			public KeySetIter() {
				this.keyIter = entrySet().iterator();
			}

			/**
			 * Checks if this Iterator will return data upon its next call to
			 * next()
			 *
			 * @return true if the next call to next() will return data, false
			 * otherwise
			 * @throws ConcurrentModificationException if the HashMap has been
			 * modified during this Iterators iteration over the HashMap
			 */
			@Override
			public boolean hasNext() {
				return keyIter.hasNext();
			}

			/**
			 * Increments this Iterator to the next entry in the HashMap
			 *
			 * @return the entry before this Iterator was incremented
			 * @throws NoSuchElementException if this Iterator has reached the
			 * end of the HashMap
			 * @throws ConcurrentModificationException if the HashMap has been
			 * modified during this Iterators iteration over the HashMap
			 */
			@Override
			public K next() {
				return keyIter.next().getKey();
			}
		}

		/**
		 * Gets an iterator to this Set of keys
		 *
		 * @return an iterator to this Set of keys
		 */
		@Override
		public Iterator<K> iterator() { return new KeySetIter(); }

		/**
		 * Gets the number of keys in this Set
		 *
		 * @return the number of keys in this Set
		 */
		@Override
		public int size() { return size; }
	}

	private class ValueCollection extends AbstractCollection<V> {

		private class ValueCollectionIter implements Iterator<V> {
			private Iterator<Entry<K, V>> valueIter;

			public ValueCollectionIter() {
				this.valueIter = entrySet().iterator();
			}

			/**
			 * Checks if this Iterator will return data upon its next call to
			 * next()
			 *
			 * @return true if the next call to next() will return data, false
			 * otherwise
			 * @throws ConcurrentModificationException if the HashMap has been
			 * modified during this Iterators iteration over the HashMap
			 */
			@Override
			public boolean hasNext() {
				return valueIter.hasNext();
			}

			/**
			 * Increments this Iterator to the next entry in the HashMap
			 *
			 * @return the entry before this Iterator was incremented
			 * @throws NoSuchElementException if this Iterator has reached the
			 * end of the HashMap
			 * @throws ConcurrentModificationException if the HashMap has been
			 * modified during this Iterators iteration over the HashMap
			 */
			@Override
			public V next() {
				return valueIter.next().getValue();
			}
		}

		/**
		 * Gets an iterator to this Collection of values
		 *
		 * @return an iterator to this Collection of values
		 */
		@Override
		public Iterator<V> iterator() { return new ValueCollectionIter(); }

		/**
		 * Gets the number of values in this Collection
		 *
		 * @return the number of values in this collection
		 */
		@Override
		public int size() { return size; }
	}

	private int calcCapacity(int capacity) {
		if (capacity <= 0) throw new IllegalArgumentException("capacity must be greater than 0");
		if (capacity <= 2) return capacity; /* already squares of 2 */

		/*
		 * will create overflow if second-to-left most bit is set,
		 * so return MAX_VALUE of int
		 */
		if (capacity > (1 << 30)) return 1 << 30;

		int shift = 2;              /* 1 << 2 = 4, the next possible capacity */

		while ((1 << shift) < capacity) { 	/* round up to nearest power of 2 */
			++shift;
		}

		return 1 << shift;
	}

	public HashMap() { this(DEFAULT_CAPACITY); }

	public HashMap(int capacity) {
		this.capacity = calcCapacity(capacity); /* round up to nearest power of 2 */
		size = 0;
		modCount = 0;
		hashMap = new ArrayList<>(this.capacity);
		initializeBuckets();
	}

	/* initialize all buckets to null in order to use List.get() */
	private void initializeBuckets() {
		for (int i = 0; i < this.capacity; ++i) {
			hashMap.add(i, null);
		}
	}

	private int calcIndex(Object key) {
		return Objects.hashCode(key) & (capacity - 1);
	}

	/**
	 * inserts a new entry into this HashMap. If an entry with the same key
	 * already exists, the specified value will replace the existing entry's
	 * value
	 *
	 * @param key the key of the entry to be inserted
	 * @param value the value associated with the specified key
	 * @return null if there was no existing entry with the specified key
	 * already in this HashMap. If there was an existing entry with the
	 * specified key, the old value will be returned
	 */
	@Override
	public V put(K key, V value) {
		int index = calcIndex(key);
		List<Entry<K, V>> bucketList = hashMap.get(index);
		++modCount;

		/* no entries in this bucket */
		if (bucketList == null) hashMap.set(index, new LinkedList<>());
		else {

			/* check bucket if there is already an entry with specified key */
			for (Entry<K, V> entry : bucketList) {
				if (Objects.equals(key, entry.getKey())) { /* replace value */
					return entry.setValue(value);
				}
			}
		}

		/* entirely new entry, insert and update size */
		hashMap.get(index).add(Pair.of(key, value));
		++size;

		return null;
	}

	/**
	 * Gets the value associated with the specified key
	 *
	 * @param key the key for which to find the value for
	 * @return the value associated with the specified key, or null if there is
	 * no entry with the specified key.
	 */
	@Override
	public V get(Object key) {
		int index = calcIndex(key);
		List<Entry<K, V>> bucketList = hashMap.get(index);

		/* no entries in this bucket */
		if (bucketList == null) return null;

		for (Entry<K, V> entry : bucketList) {
			if (Objects.equals(key, entry.getKey())) return entry.getValue();
		}

		return null;
	}

	/**
	 * Removes the entry with the specified key
	 *
	 * @param key the key of the entry to be removed
	 * @return the value of the entry associated with the specified key, or null
	 * if there was no entry with the specified key
	 */
	@Override
	public V remove(Object key) {
		int index = calcIndex(key);
		List<Entry<K, V>> bucketList = hashMap.get(index);

		/* no entries in this bucket's list */
		if (bucketList == null) return null;

		for (Entry<K, V> entry : bucketList) {
			if (Objects.equals(key, entry.getKey())) {
				V value = entry.getValue();
				bucketList.remove(entry);
				++modCount;
				--size;
				return value;
			}
		}

		return null;
	}

	/**
	 * Inserts the entries within the specified Map m. The values of entries
	 * with keys already existing in this HashMap will replace the values of
	 * the entries in this HashMap
	 *
	 * @param m the Map from which to insert its entries into this HashMap
	 * @throws NullPointerException if m is null
	 */
	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		Objects.requireNonNull(m);
		/* put each entry in the hashMap */
		for (Entry<? extends K, ? extends V> entry : m.entrySet()) {
			put(entry.getKey(), entry.getValue());
		}
	}

	/**
	 * Clears the contents of this HashMap, effectively removing all entries.
	 */
	@Override
	public void clear() {
		++modCount;

		/* remove references of all lists */
		for (int i = 0; i < capacity; ++i) hashMap.set(i, null);

		size = 0;
	}

	/**
	 * Gets a new Set of the keys in this HashMap
	 *
	 * @return a Set of the keys in this HashMap
	 */
	@Override
	public Set<K> keySet() { return new KeySet(); }

	/**
	 * Gets a new Collection of the values in this HashMap
	 *
	 * @return a Collection of the values in this HashMap
	 */
	@Override
	public Collection<V> values() { return new ValueCollection(); }

	/**
	 * Gets a new Set of the entries in this HashMap
	 *
	 * @return a Set of the entries in this HashMap
	 */
	@Override
	public Set<Entry<K, V>> entrySet() { return new EntrySet(); }

	/**
	 * Gets the number of entries inserted into this HashMap
	 *
	 * @return the number of entries in this HashMap
	 */
	@Override
	public int size() { return size; }

	/**
	 * Checks if this HashMap is empty
	 *
	 * @return true if this HashMap is empty, false if it is not
	 */
	@Override
	public boolean isEmpty() { return size == 0; }

	/**
	 * Checks if there is an entry in this HashMap with the specified key
	 *
	 * @param key the key to be searched for in this HashMap
	 * @return true if there is an entry with the specified key, false if not
	 */
	@Override
	public boolean containsKey(Object key) {
		int index = calcIndex(key);
		List<Entry<K, V>> bucketList = hashMap.get(index);

		if (bucketList == null) return false;

		for (Entry<K, V> entry : bucketList) {
			if (Objects.equals(key, entry.getKey())) return true;
		}

		return false;
	}

	/**
	 * Checks if there is an entry in this HashMap with the specified value
	 *
	 * @param value the value to be searched for in this HashMap
	 * @return true if there is an entry with the specified key, false if not
	 */
	@Override
	public boolean containsValue(Object value) {
		for (Object currentValue : values()) {
			if (Objects.equals(value, currentValue)) return true;
		}

		return false;
	}
}
