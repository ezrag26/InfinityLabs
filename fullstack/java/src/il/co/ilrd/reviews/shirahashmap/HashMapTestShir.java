//package il.co.ilrd.reviews.shirahashmap;
//
//import org.junit.Before;
//import org.junit.Rule;
//import org.junit.Test;
//import org.junit.rules.TestName;
//import org.junit.jupiter.api.*;
//
//import java.util.ConcurrentModificationException;
//import java.util.Iterator;
//import java.util.Map;
//import java.util.Set;
//
//import static org.junit.jupiter.api.Assertions.*;
//
//public class HashMapTestShir {
//	private static final int SIZE = 1000;
//	private HashMap<Integer, Integer> hashMap;
//	@Rule
//	public TestName name = new TestName();
//
//	@Before
//	public void setUp() {
//		hashMap = new HashMap<>(200);
//
//		System.out.println("Test " + name.getMethodName() + "():");
//	}
//
//	@Test
//	public void put() {
//		for (int i = 0; i < SIZE; ++i) hashMap.put(i, i);
//	}
//	@Test
//	public void putReplace() {
//		put();
//		for (int i = 0; i < SIZE; ++i){
//			assertEquals(i, hashMap.put(i, 2*i));
//			assertEquals(SIZE, hashMap.size());
//		}
//
//	}
//	@Test
//	public void get() {
//		put();
//		for (int i = 0; i < SIZE; ++i) assertEquals(i, hashMap.get(i));
//		for (int i = SIZE; i < 2*SIZE; ++i) assertEquals(null, hashMap.get(i));
//	}
//
//	@Test
//	public void remove() {
//		put();
//		assertEquals(SIZE, hashMap.size());
//		for (int i = 0; i < SIZE; ++i) {
//			assertEquals(SIZE - i, hashMap.size());
//			assertEquals(i, hashMap.remove(i));
//		}
//		assertEquals(0, hashMap.size());
//		for (int i = 0; i < SIZE; ++i) {
//			assertEquals(null, hashMap.remove(i));
//			assertEquals(0, hashMap.size());
//		}
//		for (int i = 0; i < SIZE; ++i) assertEquals(null, hashMap.get(i));
//	}
//
//	@Test
//	public void putAll() {
//		HashMap<Integer, Integer> hashMap2 = new HashMap<>();
//		for (int i = 0; i < SIZE; ++i) hashMap2.put(i*2, i);
//		assertEquals(SIZE, hashMap2.size());
//		hashMap.putAll(hashMap2);
//		assertEquals(SIZE, hashMap.size());
//	}
//
//	@Test
//	public void clear() {
//		assertEquals(0, hashMap.size());
//		assertTrue(hashMap.isEmpty());
//		put();
//		assertEquals(SIZE, hashMap.size());
//		assertFalse(hashMap.isEmpty());
//		hashMap.clear();
//		assertEquals(0, hashMap.size());
//		assertTrue(hashMap.isEmpty());
//		assertFalse(hashMap.containsKey(1));
//		assertFalse(hashMap.containsValue(1));
//		assertEquals(null, hashMap.get(0));
//		put();
//		assertEquals(SIZE, hashMap.size());
//		assertFalse(hashMap.isEmpty());
//	}
//
//	@Test
//	public void keySet() {
//		double sumK = 0;
//		int i = 0;
//		put();
//		Set<Map.Entry<Integer, Integer>> set = hashMap.entrySet();
//		Iterator<Map.Entry<Integer, Integer>> iter = set.iterator();
//		while (iter.hasNext()) {
//			Map.Entry<Integer, Integer> entry = iter.next();
//			sumK += entry.getKey();
//			++i;
//		}
//
//		assertEquals(SIZE, i);
//		assertEquals(((double)(SIZE-1)/2)*SIZE, sumK);
//
//		hashMap.remove(1);
//		assertThrows(ConcurrentModificationException.class, iter::next);
//		assertThrows(ConcurrentModificationException.class, iter::next);
//		iter = set.iterator();
//		assertTrue(iter.hasNext());
//	}
//
//	@Test
//	public void values() {
//		double sumV = 0;
//		int i = 0;
//		put();
//		Set<Map.Entry<Integer, Integer>> set = hashMap.entrySet();
//		Iterator<Map.Entry<Integer, Integer>> iter = set.iterator();
//		while (iter.hasNext()) {
//			Map.Entry<Integer, Integer> entry = iter.next();
//			sumV += entry.getValue();
//			++i;
//		}
//
//		assertEquals(SIZE, i);
//		assertEquals(((double)( SIZE-1)/2)*SIZE, sumV);
//
//		hashMap.remove(1);
//		assertThrows(ConcurrentModificationException.class, iter::next);
//		assertThrows(ConcurrentModificationException.class, iter::next);
//		iter = set.iterator();
//		assertTrue(iter.hasNext());
//	}
//
//	@Test
//	public void entrySet() {
//		double sumV = 0;
//		double sumK = 0;
//		int i = 0;
//		put();
//		Set<Map.Entry<Integer, Integer>> set = hashMap.entrySet();
//		Iterator<Map.Entry<Integer, Integer>> iter = set.iterator();
//		while (iter.hasNext()) {
//			Map.Entry<Integer, Integer> entry = iter.next();
//			sumV += entry.getValue();
//			sumK += entry.getKey();
//			++i;
//		}
//
//		assertEquals(SIZE, i);
//		assertEquals(((double)( SIZE-1)/2)*SIZE, sumV);
//		assertEquals(((double)(SIZE-1)/2)*SIZE, sumK);
//
//		hashMap.remove(1);
//		assertThrows(ConcurrentModificationException.class, iter::next);
//		assertThrows(ConcurrentModificationException.class, iter::next);
//		iter = set.iterator();
//		assertTrue(iter.hasNext());
//	}
//
//	@Test
//	public void size() {
//		assertEquals(0, hashMap.size());
//		put();
//		assertEquals(SIZE, hashMap.size());
//		hashMap.put(5545435,1);
//		assertEquals(SIZE+1, hashMap.size());
//		assertEquals(1, hashMap.remove(5545435));
//		remove();
//		assertEquals(0, hashMap.size());
//	}
//
//	@Test
//	public void isEmpty() {
//		assertTrue(hashMap.isEmpty());
//		put();
//		assertFalse(hashMap.isEmpty());
//		remove();
//		assertTrue(hashMap.isEmpty());
//	}
//
//	@Test
//	public void containsKey() {
//		for (int i = 0; i < SIZE; ++i) assertFalse(hashMap.containsKey(i));
//		put();
//		for (int i = 0; i < SIZE; ++i) assertTrue(hashMap.containsKey(i));
//		for (int i = 0; i < SIZE; ++i) {
//			hashMap.remove(i);
//			assertFalse(hashMap.containsKey(i));
//		}
//	}
//
//	@Test
//	public void containsValue() {
//		for (int i = 0; i < SIZE; ++i) assertFalse(hashMap.containsValue(i));
//		put();
//		for (int i = 0; i < SIZE; ++i) assertTrue(hashMap.containsValue(i));
//		for (int i = 0; i < SIZE; ++i) hashMap.put(i+2000, i);
//		for (int i = 0; i < SIZE; ++i) {
//			hashMap.remove(i);
//			assertTrue(hashMap.containsValue(i), "value = "+i);
//		}
//		for (int i = 0; i < SIZE; ++i) {
//			hashMap.remove(i);
//			assertFalse(hashMap.containsKey(i));
//		}
//	}
//
//	@Test
//	public void nullKey() {
//		assertEquals(null, hashMap.put(null, 1));
//		assertEquals(1, hashMap.put(null, 2));
//
//	}
//}