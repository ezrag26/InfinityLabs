package il.co.ilrd.worksheets.ws9.ex;

public class Generics <E> {
	public static void main(String[] args) {
		Integer[] ints = {1, 2, 3};
		Double[] doubles = {1.3, 3.4576, 315.1};
		String[] strings = {"This", "is", "a", "test"};

		printArray(ints);
		printArray(doubles);
		printArray(strings);

		FooReference<Integer> integerInstance = new FooReference<>();
		FooReference<Double> doubleInstance = new FooReference<>();
		FooReference<String> stringInstance = new FooReference<>();

		integerInstance.setT(Integer.valueOf(1));
		System.out.println(integerInstance.getT());

		doubleInstance.setT(Double.valueOf(3.2));
		System.out.println(doubleInstance.getT());
		
		stringInstance.setT("some string");
		System.out.println(stringInstance.getT());
		
		System.out.println(integerInstance.getClass());
		System.out.println(integerInstance.getClass());
		System.out.println(doubleInstance.getClass());
		System.out.println(stringInstance.getClass());
		System.out.println(ints.getClass());
	}
	
	public static <E> void printArray(E[] array) {
		System.out.print("[ ");
		for (Object e : array) {
			System.out.print(e + ", ");
		}
		System.out.println("]");
	}
}

class FooReference <T> {
	private T t;
	public FooReference() {
	}

	public T getT() {
		return t;
	}

	public void setT(T t) {
		this.t = t;
	}
}
