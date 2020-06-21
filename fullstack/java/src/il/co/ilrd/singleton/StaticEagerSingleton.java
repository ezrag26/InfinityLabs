package il.co.ilrd.singleton;

public class StaticEagerSingleton {

	/* instantiate upon class loading */
	private static final StaticEagerSingleton singleton = new StaticEagerSingleton();

	/* private constructor so no instances can be made */
	private StaticEagerSingleton() {}

	public static StaticEagerSingleton getSingleton() {
		return singleton;
	}
}
