package il.co.ilrd.worksheets.ws8.trycatchfinallytest;

public class TryCatchFinallyTest {
	public static void main(String[] args) {
		int result = 0;
		try {
			result = nonCatchingMethod(2, 0);
		} catch (ArithmeticException e) {
			System.out.println("In Main catch block - caught ArithmeticException");
		} finally {
			System.out.println("In Main finally block");
		}
		
		System.out.println(result);
	}

	static int nonCatchingMethod (int num, int divideBy) {
		int result = 0;
		try {
			result = num / divideBy;
		} finally {
			System.out.println("nonCatchingMethod Finally: Should see this even though ArithmeticException not caught");
		}
		System.out.println("Should not see this");
		return result;
	}
}
