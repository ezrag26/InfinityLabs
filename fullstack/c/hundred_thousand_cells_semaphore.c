#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define ARR_SIZE (100000)
int arr_g[ARR_SIZE] = {0};

void *ThreadFunc(void *param);
void CreateThreads(pthread_t thread_arr[], size_t arr_size);
void CheckArray(int *arr, size_t arr_size);

int main()
{
	pthread_t thread_arr[ARR_SIZE] = {0};

	CreateThreads(thread_arr, ARR_SIZE);

	CheckArray(arr_g, ARR_SIZE);

	return 0;
}

void *ThreadFunc(void *param)
{
	arr_g[(*(int *)param)] = *(int *)param + 1;
	free(param); param = NULL;

	return param;
}

void CreateThreads(pthread_t thread_arr[], size_t arr_size)
{
	size_t i = 0;
	int create_ret = 0;

	for (i = 0; i < arr_size; ++i)
	{
		int *param = (int *)malloc(sizeof(int));
		*param = i;

		if (0 != (create_ret = pthread_create(&thread_arr[i], NULL, ThreadFunc, (void *)param)))
		{
			printf("Threads created before fail: %lu\n", i);
			break;
		}


		if (pthread_detach(thread_arr[i]) != 0)
		{
			printf("pthread_detach error");
		}
	}
}

void CheckArray(int *arr, size_t arr_size)
{
	size_t i = 0;

	for (i = 0; i < arr_size; ++i)
	{
		if ((int)(i + 1) != arr[i])
		{
			printf("Failed: %lu, ", i + 1);
		}
	}
	printf("\n");
}
