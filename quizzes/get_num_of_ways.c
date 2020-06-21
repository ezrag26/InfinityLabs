#include <stdio.h>

/**
 * Gets the number of ways that add up to @param sum using the values in @param
 * coins array as many times as needed
 */
int GetNumOfWays(int arr[], int len, int sum);

int main ()
{
	int coins[] = {1, 2, 5, 10};
	int len = sizeof(coins)/sizeof(coins[0]);
	int sum = 10;

	printf("Ways: %d\n", GetNumOfWays(coins, len, sum));
	return (0);
}

int GetNumOfWays(int arr[], int len, int sum)
{
	int ways = 0;

	if (0 == len) return 0;

	if (0 == sum) return 1;

	if (*arr <= sum)
	{
		ways += GetNumOfWays(arr, len, sum - *arr);
	}

	ways += GetNumOfWays(arr + 1, len - 1, sum);

	return (ways);
}
