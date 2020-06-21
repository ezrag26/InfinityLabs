package il.co.ilrd.factory;

import il.co.ilrd.hashmap.HashMap;

import java.util.Map;
import java.util.function.Function;

public class Factory<K, T, D> {
	private final Map<K, Function<D, ? extends T>> hashMap;

	public Factory() {
		hashMap = new HashMap<>();
	}

	public Function<D, ? extends T> add(K key, Function<D, ? extends T> action) {
		return hashMap.put(key, action);
	}

	public T create(K key, D data) {
		Function<D, ? extends T> action = hashMap.get(key);

		if (!hashMap.containsKey(key)) throw new IllegalArgumentException();

		return action == null ? null : action.apply(data);
	}
}
