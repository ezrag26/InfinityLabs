package il.co.ilrd.reviews.shirahashmap;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.Map;

import static org.junit.jupiter.api.Assertions.*;

class HashMapTest {
	int[] capacity = {1, 16, 100};
	String[] stringKeys = {"This", "is", "a", "key", "array"};
	String[] keysNot = {"A", "set", "of", "new", "stringKeys"};
	Integer[] intKeys = {-1, 2, 0, -100000, 50000};
	Integer[] intVals = {-10, 2, 1000000, -35000, 0};
	Integer[] expSameKeyPutRet = {null, intVals[0], intVals[1], intVals[2], intVals[3]};
	Integer[] intValsSame = {1, 1, 1, 1, 1};
	Integer[] intKeysSame = {1, 1, 1, 1, 1};
	Integer[] intValsNot = {30, -3, 15, 10000, -40000};
	HashMap<String, Integer> hashMapStrInt;
	int size;

	@BeforeEach
	public void initialization() {
		size = 0;
	}

	@Test
	public void testHashMapInstance() {
		for (int cap : capacity) {
			hashMapStrInt = new HashMap<>(cap);
			assertNotNull(hashMapStrInt);
		}
	}

	@Test
	public void testPutAndGet() {
		for (int cap : capacity) {
			hashMapStrInt = new HashMap<>(cap);
			for (String key : stringKeys) {
				for (Integer val : intVals) {
					hashMapStrInt.put(key, val);
					assertEquals(val, hashMapStrInt.get(key));
				}
			}

			for (String key : keysNot) {
				assertNull(hashMapStrInt.get(key));
			}
		}
	}

	@Test
	public void testSize() {
		for (int cap : capacity) {
			size = 0;
			hashMapStrInt = new HashMap<>(cap);
			for (String key : stringKeys) {
				++size;
				for (Integer val : intVals) {
					hashMapStrInt.put(key, val);
				}
				assertEquals(size, hashMapStrInt.size());
			}
		}
	}

	@Test
	public void testIsEmpty() {
		for (int cap : capacity) {
			hashMapStrInt = new HashMap<>(cap);
			assertTrue(hashMapStrInt.isEmpty());
			for (String key : stringKeys) {
				for (Integer val : intVals) {
					hashMapStrInt.put(key, val);
					assertFalse(hashMapStrInt.isEmpty());
				}
			}
		}
	}

	@Test
	public void testRemove() {
		for (int cap : capacity) {
			size = 0;
			hashMapStrInt = new HashMap<>(cap);
			for (int i = 0; i < stringKeys.length; ++i) {
				++size;
				hashMapStrInt.put(stringKeys[i], intVals[i]);
			}
			for (int i = 0; i < stringKeys.length; ++i) {
				assertEquals(intVals[i], hashMapStrInt.remove(stringKeys[i]));
				assertEquals(--size, hashMapStrInt.size());
			}
		}

	}

	@Test
	public void testRemoveNot() {
		for (int cap : capacity) {
			size = 0;
			hashMapStrInt = new HashMap<>(cap);
			for (int i = 0; i < stringKeys.length; ++i) {
				++size;
				hashMapStrInt.put(stringKeys[i], intVals[i]);
			}
			for (int i = 0; i < keysNot.length; ++i) {
				assertNull(hashMapStrInt.remove(keysNot[i]));
				assertEquals(size, hashMapStrInt.size());
			}
		}
	}

	@Test
	public void testClear() {
		for (int cap : capacity) {
			hashMapStrInt = new HashMap<>(cap);
			assertTrue(hashMapStrInt.isEmpty());
			for (String key : stringKeys) {
				for (Integer val : intVals) {
					hashMapStrInt.put(key, val);
					assertFalse(hashMapStrInt.isEmpty());
				}
			}
			assertFalse(hashMapStrInt.isEmpty());
			hashMapStrInt.clear();
			assertTrue(hashMapStrInt.isEmpty());
		}
	}

	@Test
	public void testPutAll() {
		int capacity = 100;
		hashMapStrInt = new HashMap<>(capacity);
		for (int i = 0; i < stringKeys.length; ++i) {
			hashMapStrInt.put(stringKeys[i], intVals[i]);
		}

		String[] putAllKeys = {"This", "new", "key", "list"};
		Integer[] putAllVals = {6, 7, 8, 9};
		HashMap<String, Integer> putAllHashMap = new HashMap<>(capacity);

		for (int i = 0; i < putAllKeys.length; ++i) {
			putAllHashMap.put(putAllKeys[i], putAllVals[i]);
		}

		hashMapStrInt.putAll(putAllHashMap);
		assertEquals(7, hashMapStrInt.size());

		for (String key : stringKeys) {
			assertTrue(hashMapStrInt.containsKey(key));
		}
		for (String key : putAllKeys) {
			assertTrue(hashMapStrInt.containsKey(key));
		}

		Integer[] expValues = {2, 1000000, 0, 6, 7, 8, 9};
		Integer[] nonExpValue = {-10, -35000};

		for (Integer i : expValues) {
			assertTrue(hashMapStrInt.containsValue(i));
		}

		for (Integer i : nonExpValue) {
			assertFalse(hashMapStrInt.containsValue(i));
		}

	}

	@Test
	public void testSameKeyPut() {
		size = 1;
		HashMap<Integer, Integer> hashMap1Key = new HashMap<>(20);

		for (int i = 0; i < intKeysSame.length; ++i) {
			assertEquals(expSameKeyPutRet[i], hashMap1Key.put(intKeysSame[i], intVals[i]));
		}
		assertEquals(size, hashMap1Key.size());

	}

	@Test
	public void testSameValuePut() {
		HashMap<Integer, Integer> hashMapInts = new HashMap<>(20);

		for (int i = 0; i < intKeys.length; ++i) {
			hashMapInts.put(intKeys[i], intValsSame[i]);
			assertEquals(++size, hashMapInts.size());
		}
	}

	@Test
	public void testContainsKey() {
		hashMapStrInt = new HashMap<>(100);
		for (int i = 0; i < stringKeys.length; ++i) {
			hashMapStrInt.put(stringKeys[i], intVals[i]);
		}

		for (int i = 0; i < stringKeys.length; ++i) {
			assertTrue(hashMapStrInt.containsKey(stringKeys[i]));
		}

		for (int i = 0; i < keysNot.length; ++i) {
			assertFalse(hashMapStrInt.containsKey(keysNot[i]));
		}

		hashMapStrInt.clear();

		for (int i = 0; i < keysNot.length; ++i) {
			assertFalse(hashMapStrInt.containsKey(stringKeys[i]));
		}
	}

	@Test
	public void testContainsNullKey() {
		hashMapStrInt = new HashMap<>(100);
		String[] keys = {"key", "", null, "123", "another key"};
		Integer[] vals = {-100, -1, 0, 1, 100};

		for (int i = 0; i < keys.length; ++i) {
			hashMapStrInt.put(keys[i], vals[i]);
		}

		for (String key : keys) {
			assertTrue(hashMapStrInt.containsKey(key));
		}

		hashMapStrInt.clear();
	}

	@Test
	public void testContainsNullValue() {
		hashMapStrInt = new HashMap<>(100);
		String[] keys = {"null", "key", "", "123", "another key"};
		Integer[] vals = {-100, null, 0, 1, 100};

		for (int i = 0; i < keys.length; ++i) {
			hashMapStrInt.put(keys[i], vals[i]);
		}

		for (Integer val : vals) {
			assertTrue(hashMapStrInt.containsValue(val));
		}

		hashMapStrInt.clear();
	}

	@Test
	public void testContainsValue() {
		hashMapStrInt = new HashMap<>(100);
		for (int i = 0; i < stringKeys.length; ++i) {
			hashMapStrInt.put(stringKeys[i], intVals[i]);
		}

		for (int i = 0; i < stringKeys.length; ++i) {
			assertTrue(hashMapStrInt.containsValue(intVals[i]));
		}

		for (int i = 0; i < intVals.length; ++i) {
			assertFalse(hashMapStrInt.containsValue(intValsNot[i]));
		}

		hashMapStrInt.clear();

		for (Integer integer : intVals) {
			assertFalse(hashMapStrInt.containsValue(integer));
		}
	}

	@Test
	public void testEntrySet() {
		HashMap<Integer, Integer> hashMapInts = new HashMap<>(20);

		for (int i = 0; i < intKeys.length; ++i) {
			hashMapInts.put(intKeys[i], intValsSame[i]);
			assertEquals(++size, hashMapInts.size());
			assertEquals(intValsSame[i], hashMapInts.get(intKeys[i]));
		}

		for (Map.Entry<Integer, Integer> entry : hashMapInts.entrySet()) {
			assertNotNull(entry.getKey());
			assertNotNull(entry.getValue());
		}
	}

	@Test
	public void testKeySet() {
		HashMap<Integer, Integer> hashMapInts = new HashMap<>(20);

		for (int i = 0; i < intKeys.length; ++i) {
			hashMapInts.put(intKeys[i], intValsSame[i]);
			assertEquals(++size, hashMapInts.size());
			assertEquals(intValsSame[i], hashMapInts.get(intKeys[i]));
		}

		for (Integer key : hashMapInts.keySet()) {
			assertTrue(hashMapInts.containsKey(key));
		}
	}

	@Test
	public void testValueSet() {
		HashMap<Integer, Integer> hashMapInts = new HashMap<>(20);

		for (int i = 0; i < intKeys.length; ++i) {
			hashMapInts.put(intKeys[i], intValsSame[i]);
			assertEquals(++size, hashMapInts.size());
			assertEquals(intValsSame[i], hashMapInts.get(intKeys[i]));
		}

		for (Integer value : hashMapInts.values()) {
			assertTrue(hashMapInts.containsValue(value));
		}
	}
}