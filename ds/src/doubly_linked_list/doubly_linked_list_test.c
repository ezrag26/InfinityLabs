#include <stdio.h> /* printf */

#include "doubly_linked_list.h"
#include "utils.h"
#include "tests.h"

int TestDLLCreate();
int TestDLLSizeEmpty();
int TestDLLIsEmptyEmpty();
int TestDLLSizeNotEmpty();
int TestDLLIsEmptyNotEmpty();
int TestDLLInsert();
int TestDLLRemove();
int TestDLLFind();
int TestDLLForEach();
int TestDLLPushFront();
int TestDLLPopFront();
int TestDLLPushBack();
int TestDLLPopBack();
int TestDLLNext();
int TestDLLPrev();
int TestDLLSpliceMiddleToMiddle();
int TestDLLSpliceMiddleToStart();
int TestDLLSpliceStartEndToStart();
int TestDLLSpliceStartEndToEnd();

size_t failures = 0;

int main()
{
	puts("Testing Doubly Linked List...");
	TEST(TestDLLCreate(), "DLLCreate");
	TEST(TestDLLSizeEmpty(), "DLLSizeEmpty");
	TEST(TestDLLIsEmptyEmpty(), "DLLIsEmptyEmpty");
	TEST(TestDLLSizeNotEmpty(), "DLLSizeNotEmpty");
	TEST(TestDLLIsEmptyNotEmpty(), "DLLIsEmptyNotEmpty");
	TEST(TestDLLInsert(), "DLLInsert");
	TEST(TestDLLRemove(), "DLLRemove");
	TEST(TestDLLFind(), "DLLFind");
	TEST(TestDLLForEach(), "DLLForEach");
	TEST(TestDLLPushFront(), "DLLPushFront");
	TEST(TestDLLPopFront(), "DLLPopFront");
	TEST(TestDLLPushBack(), "DLLPushBack");
	TEST(TestDLLPopBack(), "DLLPopBack");
	TEST(TestDLLNext(), "DLLNext");
	TEST(TestDLLPrev(), "DLLPrev");
	TEST(TestDLLSpliceMiddleToMiddle(), "DLLSpliceMiddleToMiddle");
	TEST(TestDLLSpliceMiddleToStart(), "DLLSpliceMiddleToStart");
	TEST(TestDLLSpliceStartEndToStart(), "DLLSpliceStartEndToStart");
	TEST(TestDLLSpliceStartEndToEnd(), "DLLSpliceStartEndToEnd");

	PRNT_STATUS(failures);

	return (failures);
}

int TestDLLCreate()
{
	dll_t *dll = NULL;


	dll = DLLCreate();


	DLLDestroy(dll);

	return (failures);
}

int TestDLLSizeEmpty()
{
	dll_t *dll = DLLCreate();
	size_t exp_return = 0;


	if (DLLSize(dll) != exp_return)
	{
		printf("\tFailed on line %d\n", __LINE__);
		printf("\t\tExpected %lu\n", exp_return);
		printf("\t\tReturned %lu\n", DLLSize(dll));
		++failures;
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLIsEmptyEmpty()
{
	dll_t *dll = DLLCreate();
	int exp_return = 1;


	if (DLLIsEmpty(dll) != exp_return)
	{
		printf("\tFailed on line %d\n", __LINE__);
		printf("\t\tExpected %d\n", exp_return);
		printf("\t\tReturned %d\n", DLLIsEmpty(dll));
		++failures;
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLSizeNotEmpty()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	size_t exp_size[] = {1, 2, 3, 4, 5, 6, 7};


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
		if (DLLSize(dll) != exp_size[i])
		{
			printf("\tFailed at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected %lu\n", exp_size[i]);
			printf("\t\tReturned %lu\n", DLLSize(dll));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLIsEmptyNotEmpty()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	int exp_return[] = {0, 0, 0, 0, 0, 0, 0};


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
		if (DLLIsEmpty(dll) != exp_return[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %d\n", exp_return[i]);
			printf("\t\tReturned %d\n", DLLIsEmpty(dll));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLInsert()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	size_t exp_size[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t current_node = NULL;

	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLInsert(dll, DLLEnd(dll), &push_data[i]);
		if (DLLSize(dll) != exp_size[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %lu\n", exp_size[i]);
			printf("\t\tReturned %lu\n", DLLSize(dll));
			++failures;
		}

	}

	current_node = DLLBegin(dll);

	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		if (*(int *)DLLGetData(current_node) != push_data[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %d\n", push_data[i]);
			printf("\t\tReturned %d\n", *(int *)DLLGetData(current_node));
			++failures;
		}

		current_node = DLLNext(current_node);
	}
	DLLDestroy(dll);

	return (failures);
}

int TestDLLRemove()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t *push_data_p[7] = {0};
	size_t exp_size[] = {6, 5, 4, 3, 2, 1, 0};


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		push_data_p[i] = DLLPushFront(dll, &push_data[i]);
	}

	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLRemove(push_data_p[i]);
		if (DLLSize(dll) != exp_size[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %lu\n", exp_size[i]);
			printf("\t\tReturned %lu\n", DLLSize(dll));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int IsMatch(const void *current_data, const void *data_to_find)
{
	return(*(int *)current_data == *(int *)data_to_find);
}

int TestDLLFind()
{
	dll_t *dll = DLLCreate();

	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t push_data_p[8] = {0}; /* 1, 2, 3, 4, 5, 6, 7, until */
	dll_iter_t from = NULL;
	dll_iter_t until = NULL;
	int find_array[] = {4, 2, 1, 6, 2, 4, 7, 7, -1, 0};
	int exp_iter_index[] = {3, 1, 0, 5, 1, 3, 6, 6, 7, 7};
	void *find_return = NULL;


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		push_data_p[i] = DLLInsert(dll, DLLEnd(dll), &push_data[i]);
	}

	from = DLLBegin(dll);
	until = DLLEnd(dll);
	push_data_p[7] = until;

	for (i = 0; i < ARR_SIZE(find_array); ++i)
	{
		find_return = DLLFind(from, until, &find_array[i], IsMatch);
		if (find_return != push_data_p[exp_iter_index[i]])
		{
			printf("\tFailed at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected %p\n", (void *)push_data_p[exp_iter_index[i]]);
			printf("\t\tReturned %p\n", find_return);
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int ForEach(void *current_data, void *param)
{
	if (6 == *(int *)param)
	{
		return (*(int *)param);
	}

	*(int *)current_data += *(int *)param;

	return (0);
}

int TestDLLForEach()
{
	dll_t *dll = DLLCreate();

	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t from = NULL;
	dll_iter_t until = NULL;
	int param_array[] = {4, 2, 1, 6, 2, 4, 7, 7, -1, 0};
	int exp_return[] = {0, 0, 0, 6, 0, 0, 0, 0, 0, 0};
	int for_each_return = 0;


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	from = DLLBegin(dll);
	until = DLLEnd(dll);

	for (i = 0; i < ARR_SIZE(param_array); ++i)
	{
		for_each_return = DLLForEach(from, until, ForEach, &param_array[i]);
		if (for_each_return != exp_return[i])
		{
			printf("\tFailed at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected %d\n", exp_return[i]);
			printf("\t\tReturned %d\n", for_each_return);
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLPushFront()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	size_t exp_size[] = {1, 2, 3, 4, 5, 6, 7};


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
		if (DLLSize(dll) != exp_size[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %lu\n", exp_size[i]);
			printf("\t\tReturned %lu\n", DLLSize(dll));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLPopFront()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	size_t exp_size[] = {6, 5, 4, 3, 2, 1, 0};


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPopFront(dll);
		if (DLLSize(dll) != exp_size[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %lu\n", exp_size[i]);
			printf("\t\tReturned %lu\n", DLLSize(dll));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLPushBack()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	size_t exp_size[] = {1, 2, 3, 4, 5, 6, 7};


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushBack(dll, &push_data[i]);
		if (DLLSize(dll) != exp_size[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %lu\n", exp_size[i]);
			printf("\t\tReturned %lu\n", DLLSize(dll));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLPopBack()
{
	dll_t *dll = DLLCreate();
	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	size_t exp_size[] = {6, 5, 4, 3, 2, 1, 0};


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushBack(dll, &push_data[i]);
	}

	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPopBack(dll);
		if (DLLSize(dll) != exp_size[i])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %lu\n", exp_size[i]);
			printf("\t\tReturned %lu\n", DLLSize(dll));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLNext()
{
	dll_t *dll = DLLCreate();

	size_t i = 0;
	size_t j = 6;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t current_node = NULL;

	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	current_node = DLLBegin(dll);


	for (i = 0; i < ARR_SIZE(push_data); ++i, --j)
	{
		if (*(int *)DLLGetData(current_node) != push_data[j])
		{
			printf("\tFailed at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected %d\n", push_data[j]);
			printf("\t\tReturned %d\n", *(int *)DLLGetData(current_node));
			++failures;
		}
		current_node = DLLNext(current_node);
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLPrev()
{
	dll_t *dll = DLLCreate();

	size_t i = 0;
	size_t j = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t current_node = NULL;

	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	current_node = DLLEnd(dll);


	for (i = 0; i < ARR_SIZE(push_data); ++i, ++j)
	{
		current_node = DLLPrev(current_node);
		if (*(int *)DLLGetData(current_node) != push_data[j])
		{
			printf("\tFailed at index %lu on line %d\n", i, __LINE__);
			printf("\t\tExpected %d\n", push_data[j]);
			printf("\t\tReturned %d\n", *(int *)DLLGetData(current_node));
			++failures;
		}
	}

	DLLDestroy(dll);

	return (failures);
}

int TestDLLSpliceMiddleToMiddle()
{
	dll_t *dll = DLLCreate();
	dll_t *dll2 = DLLCreate();

	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	int push_data2[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t from = NULL;
	dll_iter_t until = NULL;
	int data_returned = 0;


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	for (i = 0; i < ARR_SIZE(push_data2); ++i)
	{
		DLLPushFront(dll2, &push_data2[i]);
	}

	from = DLLNext(DLLBegin(dll));
	until = DLLPrev(DLLEnd(dll));

	DLLSplice(DLLNext(DLLBegin(dll2)), from, until);

	data_returned = *(int *)DLLGetData(DLLNext(DLLNext(DLLBegin(dll2))));
	if (data_returned != push_data[4])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %d\n", push_data[4]);
			printf("\t\tReturned %d\n", data_returned);
			++failures;
		}

	DLLDestroy(dll);
	DLLDestroy(dll2);

	return (failures);
}

int TestDLLSpliceMiddleToStart()
{
	dll_t *dll = DLLCreate();
	dll_t *dll2 = DLLCreate();

	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	int push_data2[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t from = NULL;
	dll_iter_t until = NULL;
	int data_returned = 0;


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	for (i = 0; i < ARR_SIZE(push_data2); ++i)
	{
		DLLPushFront(dll2, &push_data2[i]);
	}

	from = DLLNext(DLLBegin(dll));
	until = DLLPrev(DLLEnd(dll));

	DLLSplice(DLLBegin(dll2), from, until);

	data_returned = *(int *)DLLGetData(DLLNext(DLLBegin(dll2)));
	if (data_returned != push_data[4])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %d\n", push_data[4]);
			printf("\t\tReturned %d\n", data_returned);
			++failures;
		}

	DLLDestroy(dll);
	DLLDestroy(dll2);

	return (failures);
}

int TestDLLSpliceStartEndToStart()
{
	dll_t *dll = DLLCreate();
	dll_t *dll2 = DLLCreate();

	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5, 6, 7};
	int push_data2[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t from = NULL;
	dll_iter_t until = NULL;
	int data_returned = 0;


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	for (i = 0; i < ARR_SIZE(push_data2); ++i)
	{
		DLLPushFront(dll2, &push_data2[i]);
	}

	from = DLLBegin(dll);
	until = DLLPrev(DLLEnd(dll));

	DLLSplice(DLLBegin(dll2), from, until);

	data_returned = *(int *)DLLGetData(DLLBegin(dll2));
	if (data_returned != push_data[6])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %d\n", push_data[6]);
			printf("\t\tReturned %d\n", data_returned);
			++failures;
		}

	DLLDestroy(dll);
	DLLDestroy(dll2);

	return (failures);
}

int TestDLLSpliceStartEndToEnd()
{
	dll_t *dll = DLLCreate();
	dll_t *dll2 = DLLCreate();

	size_t i = 0;
	int push_data[] = {1, 2, 3, 4, 5};
	int push_data2[] = {1, 2, 3, 4, 5, 6, 7};
	dll_iter_t from = NULL;
	dll_iter_t until = NULL;
	int data_returned = 0;


	for (i = 0; i < ARR_SIZE(push_data); ++i)
	{
		DLLPushFront(dll, &push_data[i]);
	}

	for (i = 0; i < ARR_SIZE(push_data2); ++i)
	{
		DLLPushFront(dll2, &push_data2[i]);
	}

	from = DLLBegin(dll);
	until = DLLEnd(dll);

	DLLSplice(DLLEnd(dll2), from, until);

	data_returned = *(int *)DLLGetData(DLLPrev(DLLEnd(dll2)));
	if (data_returned != push_data[0])
		{
			printf("\tFailed on line %d\n", __LINE__);
			printf("\t\tExpected %d\n", push_data[0]);
			printf("\t\tReturned %d\n", data_returned);
			++failures;
		}

	DLLDestroy(dll);
	DLLDestroy(dll2);

	return (failures);
}
