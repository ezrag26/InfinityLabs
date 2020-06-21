package il.co.ilrd.quizzes.primorial;

import java.math.BigInteger;
import java.util.Arrays;

public class Primorial {
	public static void main(String[] args) {
		System.out.println(numPrimorial(3));
		System.out.println(numPrimorial(5));

	}

	public static int numPrimorial(int n) {
		int[] nums = new int[n];

		for (int num = 2, i = 0; num < Integer.MAX_VALUE && i < n; ++num) {
			if (isPrime(num)) nums[i++] = num;
		}

		return calcResult(nums);
	}

	private static boolean isPrime(int num) {
		for (int factor = 2; factor < num; ++factor) {
			if (num % factor == 0) {
				return false;
			}
		}
		return true;
	}

	private static int calcResult(int[] nums) {
		int result = nums[0];

		for (int i = 1; i < nums.length; ++i) {
			result *= nums[i];
		}

		return result;
	}
}
