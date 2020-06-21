package il.co.ilrd.worksheets.ws5;

public class OuterClassStaticInner {
	static int i = 0;

	OuterClassStaticInner() {
		System.out.println("Outer Ctor");
	}

	static class StaticInnerClass {
		static int i = 3;

		StaticInnerClass() {
			System.out.println("Inner");
		}

		public static void doThis() {
			System.out.print("Inner doThis() calling ");
			new OuterClassStaticInner().doThis();
		}

		public static void printOuterVariable() {
			System.out.println("OuterClassStaticInner.StaticInnerClass.i = " + OuterClassStaticInner.StaticInnerClass.i);
			System.out.println("OuterClassStaticInner.i = " + OuterClassStaticInner.i);
		}
	}

	public void doThis() {
		System.out.println("Outer doThis()");
	}
}
