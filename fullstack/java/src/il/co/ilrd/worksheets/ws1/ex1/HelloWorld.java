package il.co.ilrd.worksheets.ws1.ex1;

public class HelloWorld {
	public HelloWorld() {
	}

	public static void main(String[] var0) {
		System.out.println("Hello, World!");

		MySecondClass var1 = new MySecondClass();

		MySecondClass.foo1();

		var1.foo2("This is an instance of Foo2");
	}
}
