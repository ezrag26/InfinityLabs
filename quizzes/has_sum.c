#include <stdio.h>
#include <stddef.h>

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

int HasSum(int *arr, size_t length, int sum);

int main()
{
	int arr[10] = {1, 3, 5, 7, 9, 15, 18, 19, 22, 40};
	size_t length = 10;
	int sum[] = {8, 27, 41, 42, 1, 0, 62, 63, 36};
	int exp_return[] = {1, 1, 1, 0, 0, 0, 1, 0, 0};
	size_t	i = 0;
	
	for (i = 0; i < ARR_SIZE(sum); ++i)
	{
		if (HasSum(arr, length, sum[i]) != exp_return[i])
		{
			printf("Failed at index %lu\n", i);
		}
	} 
	
	return 0;
}

int HasSum(int *arr, size_t length, int sum)
{
	int *left = arr;
	int *right = arr + length - 1;
	
	while (right > left)
	{
		if ((*left + *right) > sum)
		{
			--right;
		}
		else if ((*left + *right) < sum)
		{
			++left;
		}
		else
		{
			return (1);
		}
	}
	
	return (0);
}
