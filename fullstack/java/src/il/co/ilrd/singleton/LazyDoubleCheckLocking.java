package il.co.ilrd.singleton;

public class LazyDoubleCheckLocking {

	/* needs to be volatile to prevent cache incoherence issues */
	private static volatile LazyDoubleCheckLocking singleton;

	/* private constructor so no instances can be made */
	private LazyDoubleCheckLocking() {}

	public static LazyDoubleCheckLocking getLazyDoubleCheckSingleton() {

		/* instantiate if not already instantiated */
		if (singleton == null) {
			synchronized (LazyDoubleCheckLocking.class) { /* acquire lock */

				/* check again in order to keep the operation atomic */
				if (singleton == null) {
					singleton = new LazyDoubleCheckLocking();
				}
			}
		}
		return singleton;
	}
}
