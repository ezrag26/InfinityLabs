package il.co.ilrd.reviews.shirahashmap;

import il.co.ilrd.pair.Pair;
import java.util.*;

/**
 * Hashmap to store pairs<K, V>
 * @param <K> represent the key of the elements
 * @param <V> represent the value of the elements
 */
public class HashMap<K, V> implements Map<K, V> {
	private static final int DEFAULT_CAPACITY = 16;
	private final int capacity;
	private int size;
	private List<List<Entry<K, V>>> hashMap;
	private int modCount;

	/**
	 * a set to the user
	 * the set is traversed using iterator
	 */
	private class EntrySet extends AbstractSet<Map.Entry<K, V>> {
		private class EntrySetIter implements Iterator<Map.Entry<K, V>> {
			private int modCount;
			private Iterator<Entry<K, V>> iter;
			private int bucket;

			/**
			 * entryset iterator Ctor.
			 * contains the modCount, in order to be a fail-fast
			 */
			public EntrySetIter() {
				bucket = 0;
				iter = getNextIter();
				modCount = HashMap.this.modCount;
			}

			/**
			 * check if the iterator return data on the next() call
			 * @return true if next() return value
			 */
			@Override
			public boolean hasNext() {
				if (HashMap.this.modCount != this.modCount) throw new ConcurrentModificationException("Iter not valid");
				return iter != null;
			}

			/**
			 * private function that return the next iterator
			 * @return new iterator to the next available entry in the map
			 */
			private Iterator<Entry<K, V>> getNextIter() {
				while (bucket < capacity && hashMap.get(bucket) == null) {
					++bucket;
				}

				if (bucket >= capacity) return null;

				if (hashMap.get(bucket).isEmpty()) {
					++bucket;
					return getNextIter();
				}
				return hashMap.get(bucket).iterator();
			}

			/**
			 * go to the next iterator
			 * @return the value in the iterator
			 */
			@Override
			public Map.Entry<K, V> next() {
				if(HashMap.this.modCount != this.modCount) throw new ConcurrentModificationException("Iter not valid");
				if(!hasNext()) throw new NoSuchElementException();

				Entry<K,V> ret = iter.next();

				if(!iter.hasNext()) {
					++bucket;
					iter = getNextIter();
				}
				return ret;
			}
		}

		/**
		 * Method that call the Ctor
		 * @return new iterator
		 */
		@Override
		public Iterator<Map.Entry<K, V>> iterator() {
			return new EntrySetIter();
		}

		/**
		 *
		 * @return the size of the set
		 */
		@Override
		public int size() {return size;}
	}

	/**
	 * use the EntrySet iterator and logic
	 */
	private class KeySet extends AbstractSet<K> {

		private class KeySetIter implements Iterator<K> {
			private Iterator<Entry<K, V>> iter;

			public KeySetIter() {
				iter = entrySet().iterator();
			}

			@Override
			public boolean hasNext() {
				return iter.hasNext();
			}

			@Override
			public K next() {
				return  iter.next().getKey();
			}
		}

		@Override
		public Iterator<K> iterator() {return new KeySetIter();}

		@Override
		public int size() {return size;}
	}

	/**
	 * use the EntrySet iterator and logic
	 */
	private class ValueCollection extends AbstractCollection<V> {
		private class ValueCollectionIter implements Iterator<V> {
			private Iterator<Entry<K, V>> iter;

			public ValueCollectionIter() {
				iter = entrySet().iterator();
			}

			@Override
			public boolean hasNext() {
				return iter.hasNext();
			}

			@Override
			public V next() {
				return iter.next().getValue();
			}

		}

		@Override
		public Iterator<V> iterator() {return new ValueCollectionIter();}

		@Override
		public int size() {return size;}
	}

	/**
	 * Default HashMap Ctor
	 * call the HashMap(int capacity) Ctor, with default capacity of 16
	 */
	public HashMap() { this(DEFAULT_CAPACITY); }

	/**
	 * HashMap Ctor, accept an initial capacity
	 * @param capacity the size of the hashMap.
	 */
	public HashMap(int capacity) {
		this.capacity = capacity;
		size = 0;
		hashMap = new ArrayList<>(capacity);
		modCount = 0;
		for (int i = 0; i < capacity; ++i) {
			hashMap.add(null);
		}

	}

	/**
	 * private method that convert the key to the index in the hashtable
	 * @param key
	 * @return index
	 */
	private int keyToIndex(Object key){
		if (key == null) return 0;
		return (key.hashCode() < 0 ? -(key.hashCode() % capacity): key.hashCode() % capacity);
	}

	/**
	 * get an key and value (new Pair) and insert it in the hashmap
	 * @param key the key og the pair
	 * @param value
	 * @return the previously data that was stored in that key, or null
	 */
	@Override
	public V put(K key, V value) {
		int idx = keyToIndex(key);
		++modCount;
		if (hashMap.get(idx) == null ) {
			hashMap.set(idx, new LinkedList<>());
		}

		for (Entry<K, V> pair : hashMap.get(idx)) {
			if (key.equals(pair.getKey())) {
				return pair.setValue(value);
			}
		}

		hashMap.get(idx).add(Pair.of(key, value));
		++size;
		return null;
	}

	/**
	 * get the data of a specific key
	 * @param key
	 * @return data
	 */
	@Override
	public V get(Object key) {
		int idx = keyToIndex(key);
		List<Map.Entry<K, V>> current = hashMap.get(idx);
		if (current == null) return null;


		for (Entry<K, V> elm : current) {
			if (key.equals(elm.getKey())) {
				return elm.getValue();
			}
		}

		return null;
	}

	/**
	 * remove pair
	 * @param key
	 * @return the data
	 */
	@Override
	public V remove(Object key) {
		++modCount;
		int idx = keyToIndex(key);

		List<Map.Entry<K, V>> current = hashMap.get(idx);
		if (current == null) return null;

		for (int i = 0; i < current.size(); ++i) {
			if (key.equals(current.get(i).getKey())) {
				--size;
				return current.remove(i).getValue();
			}
		}

		return null;
	}

	/**
	 * insert one map to another
	 * @param m - map to insert to the current map
	 */
	@Override
	public void putAll(Map<? extends K, ? extends V> m) {
		m.forEach(this::put);
	}

	/**
	 * remove all pairs from the map
	 */
	@Override
	public void clear() {

		for (int i = 0; i < capacity; ++i) { hashMap.set(i, null); }

		++modCount;
		size = 0;
	}

	/**
	 *
	 * @return a key set
	 */

	@Override
	public Set<K> keySet() {
		return new KeySet();
	}

	/**
	 * return a value collection
	 * @return a value collection
	 */

	@Override
	public Collection<V> values() {
		return new ValueCollection();
	}

	/**
	 *
	 * @return a entry set
	 */

	@Override
	public Set<Map.Entry<K, V>> entrySet() {
		return new EntrySet();
	}

	/**
	 *
	 * @return the size of the map
	 */
	@Override
	public int size() {
		return size;
	}

	/**
	 * boolean method
	 * @return true if the map is empty
	 */
	@Override
	public boolean isEmpty() {
		return size == 0;
	}

	/**
	 * boolean method for check if a specific key is in the map
	 * @param key for the checking
	 * @return true if the key in the map
	 */
	@Override
	public boolean containsKey(Object key) {
		int idx = keyToIndex(key);

		List<Map.Entry<K, V>> current = hashMap.get(idx);
		if (current == null) return false;

		for (Entry<K, V> elm : current) {
			if (Objects.equals(key, elm.getKey())) {
				return true;
			}
		}
		return false;
	}

	/**
	 * boolean method for check if a specific value is in the map
	 * @param value for the checking
	 * @return true if the value in the map
	 */
	@Override
	public boolean containsValue(Object value) {
		for (V val : values()) {
			if (Objects.equals(val, value)) return true;
		}

		return false;
	}
}