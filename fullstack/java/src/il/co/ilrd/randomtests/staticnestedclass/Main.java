package il.co.ilrd.randomtests.staticnestedclass;

class OuterClass {
	public static void doThis() {
		System.out.println("OuterClass static doThis()");
	}

	static class InnerClass {
		public static void doAnotherThing() {
			System.out.print("doAnotherThing ");
			doThis();
		}
	}

	public static void doSomethingElse() {
		System.out.print("doSomethingElse ");
		doThis();
	}
}

public class Main {
	public static void main(String[] args) {
		OuterClass.doThis();
		OuterClass.InnerClass.doAnotherThing();
		OuterClass.doSomethingElse();
	}
}

