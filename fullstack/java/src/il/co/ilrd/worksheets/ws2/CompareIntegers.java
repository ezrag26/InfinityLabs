package il.co.ilrd.worksheets.ws2;

public class CompareIntegers {
	public static void main(String[] args) {

		System.out.println("Integer.valueOf(1):");

		Integer one = Integer.valueOf(1);
		Integer anotherOne = Integer.valueOf(1);

		if (one == anotherOne) {
			System.out.println("both one are equal");
		} else {
			System.out.println("Both one are not equal");
		}

		System.out.println("--------------------------------");
		System.out.println("new Integer(1):");

		Integer againOne = new Integer(1);
		Integer anotherAgainOne = new Integer(1);

		if (againOne == anotherAgainOne) {
			System.out.println("both one are equal");
		} else {
			System.out.println("Both one are not equal");
		}
	}
}
