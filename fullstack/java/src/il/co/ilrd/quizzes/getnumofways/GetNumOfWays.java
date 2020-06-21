package il.co.ilrd.quizzes.getnumofways;

import java.util.Arrays;

public class GetNumOfWays {
	public static void main(String[] args) {
		int[] coins = {1, 2, 5, 10};
		int sum = 9;

		System.out.println(GetNumOfWays(coins, sum));
	}

	static int GetNumOfWays(int[] arr, int sum)
	{
		int ways = 0;

		if (0 == arr.length) return 0;

		if (0 == sum) return 1;

		if (arr[0] <= sum)
		{
			ways += GetNumOfWays(arr, sum - arr[0]);
		}

		int[] copy = Arrays.copyOfRange(arr, 1, arr.length);

		ways += GetNumOfWays(copy, sum);

		return ways;
	}
}
