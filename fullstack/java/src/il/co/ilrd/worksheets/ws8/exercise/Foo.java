package il.co.ilrd.worksheets.ws8.exercise;

import java.io.IOException;

public class Foo {
	static void throwException() throws IOException {
		throw new IOException();
	}

	static void throwNullPointerException() {
		throw new NullPointerException();
	}

	static void throwMyException1() throws MyException1 {
		throw new MyException1();
	}

	static void throwMyException2() throws MyException2 {
		throw new MyException2("MyException2 message");
	}

	public static void main(String[] args) {
		try {
			throwException();
		} catch (IOException ignored) {}

//		throwNullPointerException();
//		throwMyException1();

		try {
			throwMyException2();
		} catch (MyException2 ignored) {}

		byte[] arr = new byte[100];
		
		System.out.println(arr[100]);
	}
}
