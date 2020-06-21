#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define THREADS (6 + 1)

typedef struct range
{
	int first;
	int last;
} range_t;

void *ThreadFunc(void *param);

int main(int argc, char *argv[])
{
	/*pthread_t *thread = NULL;*/
	pthread_t thread[THREADS] = {0};
	int user_num = atoi(argv[1]); /* convert user input to int */
	void *result = NULL;
	range_t *range = NULL;
	int final_result = 0;
	int i = 0;
	int chunk_size = user_num / THREADS;
	(void)argc;

	if (0 > user_num)
	{
		return (-1);
	}

	if (1 >= user_num)
	{
		printf("Number of factors: %d\n", user_num);
		return user_num;
	}


	/*for (chunk_size = 0; chunk_size < user_num; ++chunk_size)
	{
		if ((THREADS = user_num % chunk_size) == 0)
		{
			break;
		}
	}*/

	/* create all threads but the last, as it needs to take on leftovers */
	for (i = 0; i < THREADS - 1; ++i)
	{
		range = (range_t *)malloc(sizeof(range_t));

		range->first = (i * chunk_size) + 1;
		range->last = (i + 1) * chunk_size;

		if (0 != pthread_create(&thread[i], NULL, ThreadFunc, (void *)range))
		{
			printf("pthread_create error");
		}

	}

	/* last thread has to take on any leftovers */
	range = (range_t *)malloc(sizeof(range_t));
	range->first = (i * chunk_size) + 1;
	range->last = user_num;
	if (0 != pthread_create(&thread[i], NULL, ThreadFunc, (void *)range))
	{
		printf("pthread_create error");
	}

	/* join and get final result */
	for (i = 0; i < THREADS; ++i)
	{
		if (0 != pthread_join(thread[i], &result))
		{
			perror("pthread_join error");
		}
		final_result += ((range_t *)result)->first;
		free((range_t *)result);
	}

	printf("Number of factors: %d\n", final_result);

	return final_result;
}

void *ThreadFunc(void *param)
{
	range_t *range = (range_t *)param;
	int current = range->first;
	int last = range->last;
	int divisor = 0;

	/* don't need the value anymore, store the result here */
	range->first = 0;

	for (; current < last + 1; ++current)
	{
		for (divisor = 1; divisor <= current; ++divisor)
		{
			if (current % divisor == 0)
			{
				range->first += 1;
			}
		}
	}

	printf("Thread result: %d\n", range->first);

	pthread_exit(range);
}
