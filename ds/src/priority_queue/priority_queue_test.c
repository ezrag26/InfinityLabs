#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "utils.h"
#include "tests.h"
#include "priority_queue.h"

int TestPQCreateAndDestroy();
int TestPQPushReturn();
int TestPQPushPeekPop();
int TestPQSizeAfterPush();
int TestPQSizeAfterPop();
int TestPQIsEmpty();
int TestPQClear();
int TestPQEraseFound();
int TestPQEraseNotFound();

size_t failures = 0;

int main()
{
	puts("Testing Priority Queue...");
	TEST(TestPQCreateAndDestroy(), "PQCreateAndDestroy");
	TEST(TestPQPushReturn(), "PQPushReturn");
	TEST(TestPQPushPeekPop(), "PQPushPeekPop");
	TEST(TestPQSizeAfterPush(), "PQSizeAfterPush");
	TEST(TestPQSizeAfterPop(), "PQSizeAfterPop");
	TEST(TestPQIsEmpty(), "PQIsEmpty");
	TEST(TestPQClear(), "PQClear");
	TEST(TestPQEraseFound(), "PQEraseFound");
	TEST(TestPQEraseNotFound(), "PQEraseNotFound");

	PRNT_STATUS(failures);

	return (failures);
}

int compare(const void *data1, const void *data2, void *param)
{
	(void)(param);
	if (*(int *)data1 > *(int *)data2)
	{
		return (1);
	}
	else if (*(int *)data1 == *(int *)data2)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}

int TestPQCreateAndDestroy()
{
	int param = 1;
	pq_t *pq = PQCreate(compare, &param);

	if (NULL == pq)
	{
		puts("\tMalloc failed");
		++failures;
	}

	PQDestroy(pq);

	return (failures);
}

int TestPQPushReturn()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	int exp_return[] = {0, 0, 0, 0, 0, 0, 0};
	int actual_return[7] = {0};

	pq_t *pq = PQCreate(compare, &param);

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		actual_return[i] = PQPush(pq, &data_arr[i]);
	}

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		if (actual_return[i] != exp_return[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_return[i]);
			printf("\t\tReturned: %d\n", actual_return[i]);
			++failures;
		}
	}

	PQDestroy(pq);

	return (failures);
}

int TestPQPushPeekPop()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	int exp_data[] = {300, 4, 4, 1, 0, -1, -1};
	int peek_return[7] = {0};
	int pop_return[7] = {0};

	pq_t *pq = PQCreate(compare, &param);


	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		PQPush(pq, &data_arr[i]);
	}

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		peek_return[i] = *(int *)PQPeek(pq);
		pop_return[i] = *(int *)PQPop(pq);
	}

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		if (peek_return[i] != exp_data[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected Peek: %d\n", exp_data[i]);
			printf("\t\tReturned: %d\n", peek_return[i]);
			++failures;
		}
	}

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		if (pop_return[i] != exp_data[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected Pop: %d\n", exp_data[i]);
			printf("\t\tReturned: %d\n", pop_return[i]);
			++failures;
		}
	}

	PQDestroy(pq);

	return (failures);
}

int TestPQSizeAfterPush()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};

	pq_t *pq = PQCreate(compare, &param);

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{

		if (PQSize(pq) != i)
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected: %lu\n", i);
			printf("\t\tReturned: %lu\n", PQSize(pq));
			++failures;
		}

		PQPush(pq, &data_arr[i]);
	}

	PQDestroy(pq);

	return (failures);
}

int TestPQSizeAfterPop()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};

	pq_t *pq = PQCreate(compare, &param);

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		PQPush(pq, &data_arr[i]);
	}

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{

		if (PQSize(pq) != ARR_SIZE(data_arr) - i)
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected: %lu\n", ARR_SIZE(data_arr) - i);
			printf("\t\tReturned: %lu\n", PQSize(pq));
			++failures;
		}

		PQPop(pq);
	}

	PQDestroy(pq);

	return (failures);
}

int TestPQIsEmpty()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	int exp_is_empty[] = {1, 0, 0, 0, 0, 0, 0, 0};

	pq_t *pq = PQCreate(compare, &param);

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		if (PQIsEmpty(pq) != exp_is_empty[i])
		{
			printf("\tFAILED at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_is_empty[i]);
			printf("\t\tReturned: %d\n", PQIsEmpty(pq));
			++failures;
		}

		PQPush(pq, &data_arr[i]);
	}

	PQDestroy(pq);

	return (failures);
}

int TestPQClear()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};

	pq_t *pq = PQCreate(compare, &param);

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		PQPush(pq, &data_arr[i]);
	}

	PQClear(pq);

	if (PQIsEmpty(pq) != 1)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", 1);
		printf("\t\tReturned: %d\n", PQIsEmpty(pq));
		++failures;
	}

	PQDestroy(pq);

	return (failures);
}

int is_match(const void *data, void *param)
{
	return (*(int *)data + *(int *)param == 301);
}

int TestPQEraseFound()
{
	int param = 1;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	void *erase_return = NULL;

	pq_t *pq = PQCreate(compare, &param);

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		PQPush(pq, &data_arr[i]);
	}

	erase_return = PQErase(pq, is_match, &param);

	if (*(int *)erase_return != data_arr[6])
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", data_arr[6]);
		printf("\t\tReturned: %d\n", *(int *)erase_return);
		++failures;
	}

	PQDestroy(pq);

	return (failures);
}

int TestPQEraseNotFound()
{
	int param = 2;
	size_t i = 0;
	int data_arr[] = {4, 1, 0, -1, 4, -1, 300};
	void *erase_return = NULL;

	pq_t *pq = PQCreate(compare, &param);

	for (i = 0; i < ARR_SIZE(data_arr); ++i)
	{
		PQPush(pq, &data_arr[i]);
	}

	erase_return = PQErase(pq, is_match, &param);

	if (erase_return != NULL)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %p\n", NULL);
		printf("\t\tReturned: %p\n", erase_return);
		++failures;
	}

	PQDestroy(pq);

	return (failures);
}
