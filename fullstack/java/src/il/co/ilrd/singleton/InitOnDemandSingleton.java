package il.co.ilrd.singleton;

public class InitOnDemandSingleton {
	private static class SingletonHolder {
		private static final InitOnDemandSingleton singleton = new InitOnDemandSingleton();
	}

	private InitOnDemandSingleton() {}

	public static InitOnDemandSingleton getSingleton() {
		return SingletonHolder.singleton;
	}
}
