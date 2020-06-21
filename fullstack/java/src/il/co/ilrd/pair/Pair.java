package il.co.ilrd.pair;

import java.util.Comparator;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.function.ToIntBiFunction;

public class Pair<K, V> implements Map.Entry<K, V> {
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
		if (pair == null) throw new NullPointerException();
		return Pair.of(pair.value, pair.key);
	}

	public void setKey(K key) { this.key = key; }

	@Override
	public K getKey() { return key; }

	@Override
	public V setValue(V value) {
		V retVal = this.value;
		this.value = value;
		return retVal;
	}

	@Override
	public V getValue() { return value; }

	public static <T extends Comparable<? super T>> Pair<T, T> minMax(T[] arr) {
		return minMaxIMP(arr, T::compareTo); // same as: (a, b) -> { return a.compareTo(b); };
	}

	public static <T> Pair<T, T> minMax(T[] arr, Comparator<? super T> c) {
		if (c == null) throw new NullPointerException();
		return minMaxIMP(arr, c::compare); // same as (a, b) -> { return c.compare(a, b); }
	}

	private static <T> Pair<T, T> minMaxIMP(T[] arr, ToIntBiFunction<T, T> action) {
		if (arr == null) throw new NullPointerException();
		if (arr.length == 0) throw new NoSuchElementException();

		T key = arr[0];
		T value = arr[0];

		for (int i = arr.length % 2; i < arr.length; i += 2) {
			T min = arr[i + 1];
			T max = arr[i];

			if (action.applyAsInt(min, max) > 0) {
				min = arr[i];
				max = arr[i + 1];
			}

			key = action.applyAsInt(key, min) < 0 ? key : min;
			value = action.applyAsInt(value, max) > 0 ? value : max;
		}

		return (Pair.of(key, value));
	}

	@Override
	public String toString() {
		return "Key: " + getKey() + ", Value: " + getValue();
	}

	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof Pair)) return false;

		Pair<?, ?> pair = (Pair<?, ?>)obj;

		return Objects.equals(key, pair.key) &&
			   Objects.equals(value, pair.value);
	}

	@Override
	public int hashCode() { return Objects.hash(key, value); }
}
