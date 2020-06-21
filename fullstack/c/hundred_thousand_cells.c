#include <stdio.h>
#include <stddef.h>
#include <pthread.h>

#define ARR_SIZE (100000)
int arr_g[ARR_SIZE] = {0};

void *ThreadFunc(void *param);
void CreateThreads(size_t arr_size);
void PrintArray(int *arr, size_t arr_size);

int main()
{
	size_t i = 0;

	CreateThreads(ARR_SIZE);

	PrintArray(arr_g, ARR_SIZE);

	return 0;
}

void *ThreadFunc(void *param)
{
	arr_g[(*(int *)param)] = *(int *)param + 1;

	return param;
}

void CreateThreads(size_t arr_size)
{
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		pthread_t thread = 0;
		pthread_create(&thread, NULL, &ThreadFunc, &i);
		pthread_join(thread, NULL);
	}
}

void PrintArray(int *arr, size_t arr_size)
{
	size_t i = 0;

	printf("[");
	for (i = 0; i < arr_size - 1; ++i)
	{
		printf("%d, ", arr[i]);
	}
	printf("%d]\n", arr[i]);
}
