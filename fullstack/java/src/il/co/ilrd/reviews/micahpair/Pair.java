package il.co.ilrd.reviews.micahpair;

import java.util.Comparator;
import java.util.Map;
import java.util.Objects;
import java.util.function.BiFunction;

public class Pair <K, V> implements Map.Entry<K, V>{
	private K key;
	private V value;

	private Pair(K key, V value) {
		this.key = key;
		this.value = value;
	}

	public static <K, V> Pair<K, V> of(K key, V value) {
		return new Pair<>(key, value);
	}

	public static <K, V> Pair<V, K> swap(Pair<K, V> pair) {
		return new Pair<>(pair.value, pair.key);
	}

	public void setKey(K key) {
		this.key = key;
	}

	public K getKey() {
		return key;
	}

	@Override
	public V setValue(V value) {
		this.value = value;
		return value;
	}

	public V getValue() {
		return value;
	}

	private static <E> Pair<E, E> compare(E[] arr, BiFunction<? super E, ? super E, Integer> c) {
		if (arr.length == 0) throw new NullPointerException("list is empty");

		E min = arr[0];
		E max = arr[0];

		for (int i = arr.length % 2 == 0 ? 1 : 2; i < arr.length; i += 2) {
			E smaller = arr[i - 1];
			E larger = arr[i];

			if ((c.apply(smaller, larger)) > 0) {
				larger = arr[i - 1];
				smaller = arr[i];
			}

			min = c.apply(smaller, min) < 0 ? smaller : min;
			max = c.apply(larger, max) > 0 ? larger : max;
		}

		return new Pair<>(min, max);
	}

	public static <T extends Comparable<? super T>> Pair<T, T> minMax(T[] arr) {
		return compare(arr, T::compareTo);
	}

	public static <T> Pair<T, T> minMax(T[] arr, Comparator<? super T> c) {
		return compare(arr, c::compare);
	}

	@Override
	public String toString() {
		return "(" + key + ", " + value + ")";
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) return true;
		if (!(obj instanceof Pair)) return false;

		Pair<K,V> pair = (Pair<K,V>)obj;

		return ((this.key.equals(pair.key)) &&
				(this.value.equals(pair.value)));
	}

	@Override
	public int hashCode() {
		return Objects.hash(key, value);
	}
}
