package il.co.ilrd.genericlinkedlist;

import java.util.*;

public class GLL <E> implements Iterable<E> {
	private GLLNode<E> head = null;
	private int modCount = 0;

	private static class GLLNode <E> {
		private E data;
		private GLLNode<E> next;

		GLLNode(E data, GLLNode<E> next) {
			this.data = data;
			this.next = next;
		}
	}

	private class GLLIter<E> implements Iterator<E> {
		private GLLNode<E> currentNode;
		private final int modCount;

		public GLLIter(GLLNode<E> node) {
			currentNode = node;
			modCount = GLL.this.modCount;
		}

		private E getData() { return currentNode.data; }

		/**
		 * Increments this Iterator to the next element
		 *
		 * @return the data of the element this Iterator represented before
		 * incrementing to the next element
		 * @throws NoSuchElementException if the iterator has no more elements
		 * @throws ConcurrentModificationException if the list was modified
		 * (pushFront() or popFront() were used) after this Iterator was created
		 */
		@Override
		public E next() {
			if (!hasNext()) throw new NoSuchElementException();

			E data = currentNode.data;
			currentNode = currentNode.next;

			return data;
		}

		/**
		 * Checks if the next call to next() will be successful
		 *
		 * @return true if the next call to next() will be successful, false if
		 * it will not
		 * @throws ConcurrentModificationException if the list was modified
		 * (pushFront() or popFront() were used) after this Iterator was created
		 */
		@Override
		public boolean hasNext() {
			if (GLL.this.modCount != this.modCount) {
				throw new ConcurrentModificationException();
			}

			return currentNode != null;
		}
	}

	public GLL() {}

	/**
	 * Adds the specified data to the head of the list
	 *
	 * @param data the data to insert to this list
	 */
	public void pushFront(E data) {
		++modCount;
		head = new GLLNode<>(data, head);
	}

	/**
	 * Removes the front element of this list
	 *
	 * @return the data of the removed element
	 */
	public E popFront() {
		if (this.isEmpty()) throw new NoSuchElementException();

		++modCount;
		E data = head.data;
		head = head.next;

		return data;
	}

	/**
	 * Calculates the number of elements in this list
	 *
	 * @return total elements in this list
	 */
	public int size() {
		int count = 0;
		for (E e : this) ++count;

		return count;
	}

	/**
	 * Checks if this list is empty
	 *
	 * @return true if this list is empty, false if it is not empty
	 */
	public boolean isEmpty() { return head == null; }

	public Iterator<E> find(E data) {
		GLLIter<E> iter = new GLLIter<>(head);

		while (iter.hasNext()) {
			if (data.equals(iter.getData())) return iter;
			iter.next();
		}

		return null;
	}

	/**
	 * Gets an iterator to the head of this list
	 *
	 * @return an iterator to the head of this list
	 */
	@Override
	public Iterator<E> iterator() { return new GLLIter<>(head); }

	/**
	 * Merges two specified GLL lists
	 *
	 * @param list1 a list to be merged with list2
	 * @param list2 a list to be merged with list1
	 * @param <E>
	 * @return a new list, merged with the data of list1 and list2
	 */
	public static <E> GLL<E> merge(GLL<E> list1, GLL<E> list2) {
		GLL<E> newList = new GLL<>();

		for (E data : list1) newList.pushFront(data);
		for (E data : list2) newList.pushFront(data);

		return GLL.reverse(newList);
	}

	private static <E extends Comparable<E>> GLL<E> sort(GLL<E> newList) {
		List<E> sortList = new ArrayList<>();

		while (!newList.isEmpty()) {
			sortList.add(newList.popFront());
		}

		Collections.sort(sortList);

		for (int i = sortList.size() - 1; i >= 0; --i) {
			newList.pushFront(sortList.remove(i));
		}

		return newList;
	}

	/**
	 * Sorts and merges two GLL lists of the same type which is comparable
	 *
	 * @param list1 a list to be sorted and merged with list2
	 * @param list2 a list to be sorted and merged with list1
	 * @param <E>
	 * @return a new GLL list, sorted and merged into one list
	 */
	public static <E extends Comparable<E>> GLL<E>
	sortMerge(GLL<E> list1, GLL<E> list2) {
		return sort(GLL.merge(list1, list2));
	}

	/**
	 * Reverses the specified GLL list
	 *
	 * @param list the list to be reversed
	 * @param <E>
	 * @return a new GLL list that is the reverse of the specified list
	 */
	public static <E> GLL<E> reverse(GLL<E> list) {
		GLL<E> newList = new GLL<>();
		for (E data : list) newList.pushFront(data);

		return newList;
	}

	/**
	 * Prints the specified GLL list
	 *
	 * @param list the list to be printed
	 * @param <E>
	 */
	public static <E> void print(GLL<E> list) {
		for (E data : list) System.out.print("[ " + data + " ]");
	}

	@Override
	public String toString() {
		return "Generic Linked List with size of " + this.size();
	}
}
