package il.co.ilrd.pair;

import org.junit.jupiter.api.Test;

import java.util.Comparator;

import static org.junit.jupiter.api.Assertions.*;

class PairTest {
	@Test
	public void testOf() {
		Pair<Integer, String> integerKeyPair = Pair.of(1, "One");
		Pair<String, String> stringKeyPair = Pair.of("Hi", "Two");
		Pair<Double, String> doubleKeyPair = Pair.of(3.56, "Three");

		assertEquals(1, integerKeyPair.getKey());
		assertEquals("Hi", stringKeyPair.getKey());
		assertEquals(3.56, doubleKeyPair.getKey());


		assertEquals("One", integerKeyPair.getValue());
		assertEquals("Two", stringKeyPair.getValue());
		assertEquals("Three", doubleKeyPair.getValue());
	}

	@Test
	public void testSetKey() {
		Pair<Integer, String> integerKeyPair = Pair.of(1, "One");
		Pair<String, String> stringKeyPair = Pair.of("Hi", "Two");
		Pair<Double, String> doubleKeyPair = Pair.of(3.56, "Three");

		integerKeyPair.setKey(10);
		stringKeyPair.setKey("A new key");
		doubleKeyPair.setKey(1.11);

		assertEquals(10, integerKeyPair.getKey());
		assertEquals("A new key", stringKeyPair.getKey());
		assertEquals(1.11, doubleKeyPair.getKey());
	}

	@Test
	public void testGetKey() {
		Pair<Integer, String> integerKeyPair = Pair.of(1, "One");
		Pair<String, Double> stringKeyPair = Pair.of("Hi", 83.1);
		Pair<Double, Integer> doubleKeyPair = Pair.of(3.56, 6);

		integerKeyPair.setValue("A new value");
		stringKeyPair.setValue(26.6);
		doubleKeyPair.setValue(26);

		assertEquals("A new value", integerKeyPair.getValue());
		assertEquals(26.6, stringKeyPair.getValue());
		assertEquals(26, doubleKeyPair.getValue());
	}

	@Test
	public void testSetValue() {
		Pair<Integer, String> integerKeyPair = Pair.of(1, "One");
		Pair<String, Integer> stringKeyPair = Pair.of("Hi", 5);
		Pair<Double, Double> doubleKeyPair = Pair.of(3.56, 9.91);

		assertEquals("One", integerKeyPair.getValue());
		assertEquals(5, stringKeyPair.getValue());
		assertEquals(9.91, doubleKeyPair.getValue());
	}

	@Test
	public void testGetValue() {
		Pair<Integer, String> integerKeyPair = Pair.of(1, "One");
		Pair<String, Integer> stringKeyPair = Pair.of("Hi", 5);
		Pair<Double, Double> doubleKeyPair = Pair.of(3.56, 9.91);

		assertEquals("One", integerKeyPair.getValue());
		assertEquals(5, stringKeyPair.getValue());
		assertEquals(9.91, doubleKeyPair.getValue());
	}

	@Test
	public void testSwap() {
		Pair<Integer, String> pair = Pair.of(1, "One");
		Pair<String, Integer> swapPair = Pair.swap(pair);

		assertEquals("One", swapPair.getKey());
		assertEquals(1, swapPair.getValue());
	}

	@Test
	public void testToString() {
		Pair<Integer, String> integerKeyPair = Pair.of(1, "One");
		Pair<String, String> stringKeyPair = Pair.of("Hi", "Two");
		Pair<Double, String> doubleKeyPair = Pair.of(3.56, "Three");

		System.out.println(integerKeyPair.toString());
		System.out.println(stringKeyPair.toString());
		System.out.println(doubleKeyPair.toString());
	}

	@Test
	public void testEquals() {
		Pair<Integer, String> integerKeyPair = Pair.of(1, "One");
		Pair<String, String> stringKeyPair = Pair.of("Hi", "Two");
		Pair<Double, String> doubleKeyPair = Pair.of(3.56, "Three");

		assertTrue(integerKeyPair.equals(integerKeyPair));
		assertTrue(stringKeyPair.equals(stringKeyPair));
		assertTrue(doubleKeyPair.equals(doubleKeyPair));

		assertNotEquals(true, integerKeyPair.equals(stringKeyPair));
		assertNotEquals(true, stringKeyPair.equals(doubleKeyPair));
		assertNotEquals(true, integerKeyPair.equals(doubleKeyPair));
	}

	@Test
	public void testMinMaxComparable() {
		Integer[] integers = {4, 2, 7, 1, 3, 6, 10, 4, 5};
		String[] strings = {"e", "b", "test", "zebra", "great", "apple", "this"};

		Pair<Integer, Integer> intPair = Pair.minMax(integers);
		assertEquals(1, intPair.getKey());
		assertEquals(10, intPair.getValue());

		Pair<String, String> stringPair = Pair.minMax(strings);
		assertEquals("apple", stringPair.getKey());
		assertEquals("zebra", stringPair.getValue());
	}

	@Test
	public void testMinMaxComparator() {
		Integer[] integers = {4, 2, 7, 1, 3, 6, 10, 4, 11};
		Comparator<Integer> comparator = (a, b) -> {
			if (a.compareTo(b) > 0) return -1;
			if (a.compareTo(b) < 0) return 1;
			return 0;
		};
		Pair<Integer, Integer> intPair = Pair.minMax(integers, comparator);
		assertEquals(11, intPair.getKey());
		assertEquals(1, intPair.getValue());

		String[] strings = {"e", "b", "test", "zebra", "great", "apple", "this"};
//		Pair<String, String> stringPair = Pair.minMax(strings);
//		assertEquals("apple", stringPair.getKey());
//		assertEquals("zebra", stringPair.getValue());
	}

}