package il.co.ilrd.crud;

import java.io.Serializable;

public interface Crud <K extends Serializable, V extends Serializable> extends AutoCloseable {
	public K create(V data);

	public V read(K key);

	public V update(K key, V data);

	public V delete(K key);
}
