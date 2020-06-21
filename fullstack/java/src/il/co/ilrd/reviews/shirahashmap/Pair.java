package il.co.ilrd.reviews.shirahashmap;

import java.util.Comparator;
import java.util.Map;

public class Pair <K, V> implements Map.Entry<K, V>{
	private K key;
	private V value;

	private Pair(K key, V value) {
		this.key = key;
		this.value = value;
	}



	public static <K, V> Pair<K, V> of(K key, V value) {
		return new Pair<K, V>(key, value);
	}

	public static <K, V> Pair<V, K> swap(Pair<K, V> pair) {
		return new Pair<V, K>(pair.getValue(), pair.getKey());
	}

	public void setKey(K key) {
		this.key = key;
	}

	public K getKey() {
		return key;
	}

	@Override
	public V setValue(V value) {
		V retVal = this.value;
		this.value = value;
		return retVal;
	}

	@Override
	public V getValue() {
		return value;
	}


	public static <T extends Comparable<? super T>> Pair<T, T> minMax(T[] arr) {

		return minMax(arr, new Comparator<T>() {
			@Override
			public int compare(T t1, T t2) {
				return t1.compareTo(t2);
			}
		});
	}


	public static <T> Pair<T, T> minMax(T[] arr, Comparator<? super T> c) {
		T min = arr[0];
		T max = arr[0];

		for (int i = 0; i < arr.length - 1; i += 2) {
			T lower = arr[i];
			T higher = arr[i + 1];
			if (c.compare(arr[i], arr[i+1]) > 0) {
				lower = arr[i + 1];
				higher = arr[i];
			}
			if (c.compare(lower, min) < 0) min = lower;
			if (c.compare(higher, max) > 0) max = higher;

		}

		if (arr.length % 2 != 0) {
			if (c.compare(arr[arr.length-1], min) < 0) min = arr[arr.length-1];
			if (c.compare(arr[arr.length-1], max) > 0) max = arr[arr.length-1];
		}

		return new Pair<>(min, max);
	}
	
	@Override
	public String toString() {
		StringBuilder str = new StringBuilder();
		str.append(key);
		str.append(value);

		return str.toString();
	}

	@Override
	public boolean equals(Object obj) {
		if (obj == this) return true;
		if (!(obj instanceof Pair)) return false;
		if (this.value.equals(((Pair<?, ?>)obj).value)) return false;
		if (this.key .equals(((Pair<?, ?>)obj).key)) return false;

		return true;
	}


	@Override
	public int hashCode() {
		return (this.key.hashCode() + this.value.hashCode());
	}
}

