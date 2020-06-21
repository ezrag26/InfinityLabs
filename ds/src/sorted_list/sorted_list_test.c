/*******************************************************************************
 * Date: 		11/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Lazy
 * Satus: 		S
 ******************************************************************************/
#include <stdio.h> /* printf */

#include "sorted_list.h"
#include "utils.h"
#include "tests.h"

int TestSLCreateAndDestroy();
int TestSLInsert();
int TestSLRemoveReturn();
int TestSLRemoveSize();
int TestSLPopFront();
int TestSLPopBack();
int TestSLBegin();
int TestSLFind();
int TestSLFindValid();
int TestSLMergeSize();
int TestSLMergeValuesSL2Greater();
int TestSLMergeValuesSL1Greater();
int TestSLFindIf();
int TestSLForEach();

size_t failures = 0;

int main()
{
	puts("Testing Sorted List...");
	TEST(TestSLCreateAndDestroy(), "SLCreateAndDestroy");
	TEST(TestSLInsert(), "SLInsert");
	TEST(TestSLRemoveReturn(), "SLRemoveReturn");
	TEST(TestSLRemoveSize(), "SLRemoveSize");
	TEST(TestSLPopFront(), "SLPopFront");
	TEST(TestSLPopBack(), "SLPopBack");
	/*TEST(TestSLBegin(), "SLBegin");*/
	TEST(TestSLFind(), "SLFind");
	TEST(TestSLFindValid(), "SLFindValid");
	TEST(TestSLMergeSize(), "SLMergeSize");
	TEST(TestSLMergeValuesSL2Greater(), "SLMergeValuesSL2Greater");
	TEST(TestSLMergeValuesSL1Greater(), "SLMergeValuesSL1Greater");
	TEST(TestSLFindIf(), "SLFindIf");
	TEST(TestSLForEach(), "SLForEach");

	PRNT_STATUS(failures);

	return (failures);
}

int IsBefore(const void *data1, const void *data2, void *param)
{
	(void)(param);

	if (*(int *)data1 < *(int *)data2)
	{
		return (1);
	}
	return (0);
}

int TestSLCreateAndDestroy()
{
	int param = 1;

	sol_t *sl = NULL;


	sl = SortedListCreate(IsBefore, &param);


	SortedListDestroy(sl);

	return (failures);
}

int TestSLInsert()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {5, 1, 2, 6, 3, -1, 4, 7, 0};
	int exp_return[] = {-1, 0, 1, 2, 3, 4, 5, 6, 7};
	int returned_data = 0;
	sol_iter_t current_iter = NULL;


	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
	}

	current_iter = SortedListBegin(sl);
	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		returned_data = *(int *)SortedListGetData(current_iter);
		if (returned_data != exp_return[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_return[i]);
			printf("\t\tReturned: %d\n", returned_data);
			++failures;
		}
		current_iter = SortedListNext(current_iter);
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLRemoveReturn()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {5, 1, 2, 6, 3, -1, 4, 7, 0};
	sol_iter_t current_iter = NULL;
	sol_iter_t removed_iter_next = NULL;
	sol_iter_t removed_iter_prev = NULL;
	sol_iter_t returned_iter_next = NULL;


	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
	}

	current_iter = SortedListPrev(SortedListEnd(sl));
	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		removed_iter_next = SortedListNext(current_iter);
		removed_iter_prev = SortedListPrev(current_iter);
		returned_iter_next = SortedListRemove(current_iter);
		if (!SortedListIsSameIterator(returned_iter_next, removed_iter_next))
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %p\n", (void *)removed_iter_next);
			printf("\t\tReturned: %p\n", (void *)returned_iter_next);
			++failures;
		}
		current_iter = removed_iter_prev;
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLRemoveSize()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {5, 1, 2, 6, 3, -1, 4, 7, 0};
	size_t exp_size[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
	sol_iter_t current_iter = NULL;
	sol_iter_t removed_iter_prev = NULL;


	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
	}

	current_iter = SortedListPrev(SortedListEnd(sl));
	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		removed_iter_prev = SortedListPrev(current_iter);
		SortedListRemove(current_iter);
		if (SortedListSize(sl) != exp_size[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %lu\n", exp_size[i]);
			printf("\t\tReturned: %lu\n", SortedListSize(sl));
			++failures;
		}
		current_iter = removed_iter_prev;
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLPopFront()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {5, 1, 2, 6, 3, -1, 4, 7, 0};
	int exp_return[] = {-1, 0, 1, 2, 3, 4, 5, 6, 7};
	size_t exp_size[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
	int returned_data = 0;


	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
	}

	if (SortedListIsEmpty(sl) != 0)
	{
		printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
		printf("\t\tExpected: %d\n", 0);
		printf("\t\tReturned: %d\n", SortedListIsEmpty(sl));
		++failures;
	}

	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		returned_data = *(int *)SortedListPopFront(sl);
		if (returned_data != exp_return[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_return[i]);
			printf("\t\tReturned: %d\n", returned_data);
			++failures;
		}

		if (SortedListSize(sl) != exp_size[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %lu\n", exp_size[i]);
			printf("\t\tReturned: %lu\n", SortedListSize(sl));
			++failures;
		}
	}

	if (SortedListIsEmpty(sl) != 1)
	{
		printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
		printf("\t\tExpected: %d\n", 1);
		printf("\t\tReturned: %d\n", SortedListIsEmpty(sl));
		++failures;
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLPopBack()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {5, 1, 2, 6, 3, -1, 4, 7, 0};
	int exp_return[] = {7, 6, 5, 4, 3, 2, 1, 0, -1};
	size_t exp_size[] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
	int returned_data = 0;


	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
	}

	if (SortedListIsEmpty(sl) != 0)
	{
		printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
		printf("\t\tExpected: %d\n", 0);
		printf("\t\tReturned: %d\n", SortedListIsEmpty(sl));
		++failures;
	}

	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		returned_data = *(int *)SortedListPopBack(sl);
		if (returned_data != exp_return[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_return[i]);
			printf("\t\tReturned: %d\n", returned_data);
			++failures;
		}

		if (SortedListSize(sl) != exp_size[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %lu\n", exp_size[i]);
			printf("\t\tReturned: %lu\n", SortedListSize(sl));
			++failures;
		}
	}

	if (SortedListIsEmpty(sl) != 1)
	{
		printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
		printf("\t\tExpected: %d\n", 1);
		printf("\t\tReturned: %d\n", SortedListIsEmpty(sl));
		++failures;
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLBegin()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {5, 1, 2, 6, 3, -1, 4, 7, 0, -4};
	int exp_begin[] = {5, 1, 1, 1, 1, -1, -1, -1, -1, -4};
	sol_iter_t start = NULL;
	sol_iter_t finish = NULL;


	SortedListInsert(sl, &insert_data[0]);

	start = SortedListPrev(SortedListEnd(sl));
	finish = SortedListEnd(sl);

	for (i = 1; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
		if (SortedListBegin(sl) != SortedListFind(sl, start, finish, &exp_begin[i]))
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %p\n", (void *)SortedListFind(sl, start, finish, &exp_begin[i]));
			printf("\t\tReturned: %p\n", (void *)SortedListBegin(sl));
			++failures;
		}
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLFind()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {1, 2, 6, 3, 4, 7};
	int find_data[] = {5, 3, 8, 6, 0, -1, 1};
	sol_iter_t find_data_p[8] = {0}; /* 1, 2, 3, 4, 5, 6, 7, until */
	sol_iter_t start = NULL;
	sol_iter_t finish = NULL;

	int exp_return[] = {7, 3, 7, 2, 7, 7, 0};
	void *returned_p = NULL;

	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		find_data_p[i] = SortedListInsert(sl, &insert_data[i]);
	}

	start = SortedListBegin(sl);
	finish = SortedListEnd(sl);
	find_data_p[7] = finish;


	for (i = 0; i < ARR_SIZE(find_data); ++i)
	{
		returned_p = SortedListFind(sl, start, finish, &find_data[i]);
		if (returned_p != find_data_p[exp_return[i]])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %p\n", (void *)find_data_p[exp_return[i]]);
			printf("\t\tReturned: %p\n", returned_p);
			++failures;
		}
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLFindValid()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {1, 2, 6, 3, 4, 7};
	int find_data[] = {3, 6, 1, 4, 7};
	sol_iter_t find_data_p[6] = {0}; /* 1, 2, 3, 4, 5 */
	sol_iter_t start = NULL;
	sol_iter_t finish = NULL;

	int exp_return[] = {3, 2, 0, 4, 5};
	void *returned_p = NULL;
	int returned_data = 0;
	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		find_data_p[i] = SortedListInsert(sl, &insert_data[i]);
	}

	start = SortedListBegin(sl);
	finish = SortedListEnd(sl);


	for (i = 0; i < ARR_SIZE(find_data); ++i)
	{
		returned_p = SortedListFind(sl, start, finish, &find_data[i]);
		if (returned_p != find_data_p[exp_return[i]])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %p\n", (void *)find_data_p[exp_return[i]]);
			printf("\t\tReturned: %p\n", returned_p);
			++failures;
		}
	}

	for (i = 0; i < ARR_SIZE(find_data); ++i)
	{
		returned_data = *(int *)SortedListGetData(SortedListFind(sl, start, finish, &find_data[i]));
		if (returned_data != *(int *)SortedListGetData(find_data_p[exp_return[i]]))
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", *(int *)SortedListGetData(find_data_p[exp_return[i]]));
			printf("\t\tReturned: %d\n", returned_data);
			++failures;
		}
	}

	SortedListDestroy(sl);

	return (failures);
}

int TestSLMergeSize()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl1 = SortedListCreate(IsBefore, &param);
	sol_t *sl2 = SortedListCreate(IsBefore, &param);

	int insert_data1[] = {3, 1, 6, 5, 7, 4, -3, 4}; /* -3, 1, 3, 4, 5, 6, 7 */
	int insert_data2[] = {-1, 6, 4, 6, 0, 4, 9}; /* -1, 0, 4, 4, 6, 6, 9 */

								/* -3, -1, 0, 1, 3,  */
	for (i = 0; i < ARR_SIZE(insert_data1); ++i)
	{
		SortedListInsert(sl1, &insert_data1[i]);
	}

	for (i = 0; i < ARR_SIZE(insert_data2); ++i)
	{
		SortedListInsert(sl2, &insert_data2[i]);
	}


	sl1 = SortedListMerge(sl1, sl2);

	if (SortedListSize(sl1) != (ARR_SIZE(insert_data1) + ARR_SIZE(insert_data2)))
	{
		printf("\tFAILED on LINE %d\n", __LINE__);
		printf("\t\tExpected: %lu\n", (ARR_SIZE(insert_data1) + ARR_SIZE(insert_data2)));
		printf("\t\tReturned: %lu\n", SortedListSize(sl1));
		++failures;
	}

	if (SortedListSize(sl2) != 0)
	{
		printf("\tFAILED on LINE %d\n", __LINE__);
		printf("\t\tExpected: %d\n", 0);
		printf("\t\tReturned: %lu\n", SortedListSize(sl2));
		++failures;
	}

	SortedListDestroy(sl1);
	SortedListDestroy(sl2);

	return (failures);

}

int TestSLMergeValuesSL2Greater()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl1 = SortedListCreate(IsBefore, &param);
	sol_t *sl2 = SortedListCreate(IsBefore, &param);

	int insert_data1[] = {3, 1, 6, 5, 7, 4, -3}; /* -3, 1, 3, 4, 5, 6, 7 */
	int insert_data2[] = {-1, 6, 4, 6, 0, 4, 9}; /* -1, 0, 4, 4, 6, 6, 9 */
	int returned_value = 0;
	int exp_value[] = {-3, -1, 0, 1, 3, 4, 4, 4, 5, 6, 6, 6, 7, 9};
	sol_iter_t current_iter = NULL;

	for (i = 0; i < ARR_SIZE(insert_data1); ++i)
	{
		SortedListInsert(sl1, &insert_data1[i]);
	}

	for (i = 0; i < ARR_SIZE(insert_data2); ++i)
	{
		SortedListInsert(sl2, &insert_data2[i]);
	}


	sl1 = SortedListMerge(sl1, sl2);

	current_iter = SortedListBegin(sl1);

	for (i = 0; i < SortedListSize(sl1); ++i)
	{
		returned_value = *(int *)SortedListGetData(current_iter);
		if (returned_value != exp_value[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_value[i]);
			printf("\t\tReturned: %d\n", returned_value);
			++failures;
		}
		current_iter = SortedListNext(current_iter);
	}

	SortedListDestroy(sl1);
	SortedListDestroy(sl2);

	return (failures);

}

int TestSLMergeValuesSL1Greater()
{
	int param = 1;
	size_t i = 0;

	sol_t *sl1 = SortedListCreate(IsBefore, &param);
	sol_t *sl2 = SortedListCreate(IsBefore, &param);

	int insert_data1[] = {3, 1, 6, 5, 7, 10, -3}; /* -3, 1, 3, 5, 6, 7, 10 */
	int insert_data2[] = {-1, 6, 4, 6, 0, 4, 9}; /* -1, 0, 4, 4, 6, 6, 9 */
	int returned_value = 0;
	int exp_value[] = {-3, -1, 0, 1, 3, 4, 4, 5, 6, 6, 6, 7, 9, 10};
	sol_iter_t current_iter = NULL;

	for (i = 0; i < ARR_SIZE(insert_data1); ++i)
	{
		SortedListInsert(sl1, &insert_data1[i]);
	}

	for (i = 0; i < ARR_SIZE(insert_data2); ++i)
	{
		SortedListInsert(sl2, &insert_data2[i]);
	}


	sl1 = SortedListMerge(sl1, sl2);

	current_iter = SortedListBegin(sl1);

	for (i = 0; i < SortedListSize(sl1); ++i)
	{
		returned_value = *(int *)SortedListGetData(current_iter);
		if (returned_value != exp_value[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_value[i]);
			printf("\t\tReturned: %d\n", returned_value);
			++failures;
		}
		current_iter = SortedListNext(current_iter);
	}

	SortedListDestroy(sl1);
	SortedListDestroy(sl2);

	return (failures);

}

int IsFindIf(void *data, void *param)
{
	return ((*(int *)data + 3) ==  *(int *)param);
}

int TestSLFindIf()
{
	int param[] = {4, 5, 6, 7, 9, 10, 1};
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {1, 2, 6, 3, 4, 7};
	sol_iter_t start = NULL;
	sol_iter_t finish = NULL;
	sol_iter_t current_iter = NULL;

	void *returned_p = NULL;

	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
	}

	start = SortedListBegin(sl);
	finish = SortedListEnd(sl);

	current_iter = start;



	for (i = 0; i < ARR_SIZE(param); ++i)
	{
		returned_p = SortedListFindIf(IsFindIf, &param[i], start, finish);
		if (returned_p != current_iter)
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %p\n", (void *)current_iter);
			printf("\t\tReturned: %p\n", returned_p);
			++failures;
		}
		current_iter = SortedListNext(current_iter);
	}

	SortedListDestroy(sl);

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

int TestSLForEach()
{
	int param[] = {4, 5, 7, 6, 9, 10, 1};
	size_t i = 0;

	sol_t *sl = SortedListCreate(IsBefore, &param);
	int insert_data[] = {1, 2, 6, 3, 4, 7, 4};
	int exp_return[] = {0, 0, 0, 6, 0, 0, 0};
	sol_iter_t start = NULL;
	sol_iter_t finish = NULL;

	int returned = 0;

	for (i = 0; i < ARR_SIZE(insert_data); ++i)
	{
		SortedListInsert(sl, &insert_data[i]);
	}

	start = SortedListBegin(sl);
	finish = SortedListEnd(sl);


	for (i = 0; i < ARR_SIZE(param); ++i)
	{
		returned = SortedListForEach(start, finish, ForEach, &param[i]);
		if (returned != exp_return[i])
		{
			printf("\tFAILED at index %lu on LINE %d\n", i, __LINE__);
			printf("\t\tExpected: %d\n", exp_return[i]);
			printf("\t\tReturned: %d\n", returned);
			++failures;
		}
	}

	SortedListDestroy(sl);

	return (failures);
}
