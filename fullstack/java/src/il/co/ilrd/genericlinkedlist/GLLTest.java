package il.co.ilrd.genericlinkedlist;

import org.junit.jupiter.api.Test;

import java.util.ConcurrentModificationException;
import java.util.Iterator;

import static org.junit.jupiter.api.Assertions.*;

class GLLTest {
	@Test
	public void testSize() {
		GLL<Integer> list = new GLL<>();
		Integer[] insert = {1, 5, -1, 3, 0};

		for (Integer integer : insert) {
			list.pushFront(integer);
		}

		assertEquals(insert.length, list.size());

		for (int i = 0; i < insert.length; ++i) {
			list.popFront();
		}

		assertEquals(0, list.size());
	}

	@Test
	public void testIsEmpty() {
		GLL<Integer> list = new GLL<>();
		Integer[] insert = {1, 5, -1, 3, 0};

		assertTrue(list.isEmpty());

		for (Integer integer : insert) {
			list.pushFront(integer);
			assertFalse(list.isEmpty());
		}


		for (int i = 0; i < insert.length; ++i) {
			assertFalse(list.isEmpty());
			list.popFront();
		}

		assertTrue(list.isEmpty());
	}

	@Test
	public void testFind() {
		GLL<Integer> list = new GLL<>();
		Integer[] insert = {1, 5, -1, 3, 0};
		Integer[] notInserted = {10, -4, 2, 40};

		for (Integer integer : insert) {
			list.pushFront(integer);
		}

		for (Integer integer : insert) {
			assertNotNull(list.find(integer));
		}

		for (Integer integer : notInserted) {
			assertNull(list.find(integer));
		}
	}

	@Test
	public void testHasNext() {
		GLL<Integer> list = new GLL<>();
		Integer[] insert = {1, 5, -1, 3, 0};

		for (Integer integer : insert) {
			list.pushFront(integer);
		}

		Iterator<Integer> iter = list.iterator();
		for (int i = 0, j = insert.length - 1; i < insert.length; ++i, --j) {
			assertTrue(iter.hasNext());
			assertEquals(insert[j], iter.next());
		}

		assertFalse(iter.hasNext());
		assertThrows(NullPointerException.class, iter::next); //iter::next is the same as () -> iter.next()
	}

	@Test
	public void testReverse() {
		GLL<Integer> list = new GLL<>();
		Integer[] insert = {1, 5, -1, 3, 0};

		for (Integer integer : insert) {
			list.pushFront(integer);
		}

		GLL<Integer> newList = GLL.reverse(list);
		Iterator<Integer> iter = newList.iterator();

		for (Integer integer : insert) {
			assertEquals(integer, iter.next());
		}
	}

	@Test
	public void testMerge() {
		GLL<Integer> list1 = new GLL<>();
		GLL<Integer> list2 = new GLL<>();
		Integer[] insert1 = {1, 2, 3, 4, 5};
		Integer[] insert2 = {6, 7, 8, 9, 10};

		for (Integer integer : insert1) {
			list1.pushFront(integer);
		}

		for (Integer integer : insert2) {
			list2.pushFront(integer);
		}

		GLL<Integer> newList = GLL.merge(list1, list2);
		Iterator<Integer> iter = newList.iterator();

		for (int i = insert1.length - 1; i >= 0; --i) {
			assertEquals(insert1[i], iter.next());
		}

		for (int i = insert2.length - 1; i >= 0; --i) {
			assertEquals(insert2[i], iter.next());
		}

		GLL.print(newList);
	}

	@Test
	public void testIterator() {
		GLL<Integer> list = new GLL<>();
		Integer[] insert = {1, 5, -1, 3, 0};
		Integer[] ret = {0, 3, -1, 5, 1};

		for (Integer integer : insert) {
			list.pushFront(integer);
		}

		Iterator<Integer> iter = list.iterator();

		for (Integer integer : ret) {
			assertEquals(integer,iter.next());
		}

		for (Integer integer : insert) {
			list.pushFront(integer);
		}

		assertThrows(ConcurrentModificationException.class, iter::next);
	}

	@Test
	public void testFindString() {
		GLL<String> list = new GLL<>();
		String[] insert = {"This", "is", "a", "string", "test"};
		String[] notInserted = {"not", "in", "the", "list"};

		for (String string : insert) {
			list.pushFront(string);
		}

		for (String string : insert) {
			assertNotNull(list.find(string));
		}

		for (String string : notInserted) {
			assertNull(list.find(string));
		}
	}

	@Test
	public void testReverseString() {
		GLL<String> list = new GLL<>();
		String[] insert = {"This", "is", "a", "reversed", "string", "test"};

		for (String string : insert) {
			list.pushFront(string);
		}

		GLL<String> newList = GLL.reverse(list);
		Iterator<String> iter = newList.iterator();

		for (String string : insert) {
			assertEquals(string, iter.next());
		}

		GLL.print(GLL.reverse(list));
	}

	@Test
	public void testToString() {
		GLL<String> list = new GLL<>();
		String[] insert = {"This", "is", "a", "reversed", "string", "test"};

		for (String string : insert) {
			list.pushFront(string);
		}

		GLL<String> newList = GLL.reverse(list);
		Iterator<String> iter = newList.iterator();

		System.out.println(list.toString());
	}

	@Test
	public void testSortMerge() {
		GLL<Integer> list1 = new GLL<>();
		GLL<Integer> list2 = new GLL<>();
		Integer[] insert1 = {1, 2, 3, 4, 5};
		Integer[] insert2 = {6, 7, 8, 9, 10};

		for (Integer integer : insert1) {
			list1.pushFront(integer);
		}

		for (Integer integer : insert2) {
			list2.pushFront(integer);
		}

		GLL<Integer> newList = GLL.sortMerge(list1, list2);
		Iterator<Integer> iter = newList.iterator();

//		for (int i = insert1.length - 1; i >= 0; --i) {
//			assertEquals(insert1[i], iter.next());
//		}
//
//		for (int i = insert2.length - 1; i >= 0; --i) {
//			assertEquals(insert2[i], iter.next());
//		}

		GLL.print(newList);
	}

}