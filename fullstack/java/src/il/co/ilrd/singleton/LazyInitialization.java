package il.co.ilrd.singleton;

public class LazyInitialization {
	private static LazyInitialization lazySingleton;

	/* private constructor so no instances can be made */
	private LazyInitialization() {}

	public static LazyInitialization getLazySingleton() {

		/* instantiate if not already instantiated */
		if (lazySingleton == null) {
			lazySingleton = new LazyInitialization();
		}
		return lazySingleton;
	}
}
