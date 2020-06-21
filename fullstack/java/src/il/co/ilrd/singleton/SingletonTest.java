package il.co.ilrd.singleton;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

class SingletonTest {
	private static final int ARR_SIZE = 10;

	@Test
	public void testStaticEagerSingleton() {
		List<StaticEagerSingleton> arr = new ArrayList<StaticEagerSingleton>();

		for (int i = 0; i < ARR_SIZE; ++i) {
			arr.add(StaticEagerSingleton.getSingleton());
		}

		for (int i = 0; i < ARR_SIZE - 1; ++i) {
			assertEquals(arr.get(i), arr.get(i + 1));
		}
	}

	@Test
	public void testLazyInitialization() {
		List<LazyInitialization> arr = new ArrayList<LazyInitialization>();

		for (int i = 0; i < ARR_SIZE; ++i) {
			arr.add(LazyInitialization.getLazySingleton());
		}

		for (int i = 0; i < ARR_SIZE - 1; ++i) {
			assertEquals(arr.get(i), arr.get(i + 1));
		}
	}

	@Test
	public void testLazyDoubleCheckLocking() {
		List<LazyDoubleCheckLocking> arr = new ArrayList<LazyDoubleCheckLocking>();

		for (int i = 0; i < ARR_SIZE; ++i) {
			arr.add(LazyDoubleCheckLocking.getLazyDoubleCheckSingleton());
		}

		for (int i = 0; i < ARR_SIZE - 1; ++i) {
			assertEquals(arr.get(i), arr.get(i + 1));
		}
	}

	@Test
	public void testInitOnDemandSingleton() {
		List<InitOnDemandSingleton> arr = new ArrayList<InitOnDemandSingleton>();

		for (int i = 0; i < ARR_SIZE; ++i) {
			arr.add(InitOnDemandSingleton.getSingleton());
		}

		for (int i = 0; i < ARR_SIZE - 1; ++i) {
			assertEquals(arr.get(i), arr.get(i + 1));
		}
	}

	@Test
	public void testEnumSingleton() {
		List<EnumSingleton> arr = new ArrayList<EnumSingleton>();

		for (int i = 0; i < ARR_SIZE; ++i) {
			arr.add(EnumSingleton.SINGLETON);
		}

		for (int i = 0; i < ARR_SIZE - 1; ++i) {
			assertEquals(arr.get(i), arr.get(i + 1));
		}
	}
}