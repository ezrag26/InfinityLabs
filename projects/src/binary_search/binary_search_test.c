#include <stdio.h>  /* printf  */
#include <time.h>   /* clock_t */
#include <stdlib.h> /* rand    */

#include "binary_search.h"
#include "utils.h"
#include "tests.h"

#define LARGE_NUM (100000)

int TestBinarySearch();
int TestBinarySearchSameNum();
int TestBinarySearchSameNumNotFound();
int TestBinarySearchNotFound();
int TestRecBinarySearch();
int TestRecBinarySearchSameNum();
int TestRecBinarySearchSameNumNotFound();
int TestRecBinarySearchNotFound();

int main()
{
	size_t failures = 0;

	puts("Testing Binary Search...");
	TEST(TestBinarySearch(), "TestBinarySearch");
    TEST(TestBinarySearchSameNum(), "TestBinarySearchSameNum");
    TEST(TestBinarySearchSameNumNotFound(), "TestBinarySearchSameNumNotFound");
    TEST(TestBinarySearchNotFound(), "TestBinarySearchNotFound");
    TEST(TestRecBinarySearch(), "TestRecBinarySearch");
    TEST(TestRecBinarySearchSameNum(), "TestRecBinarySearchSameNum");
    TEST(TestRecBinarySearchSameNumNotFound(), "TestRecBinarySearchSameNumNotFound");
    TEST(TestRecBinarySearchNotFound(), "TestRecBinarySearchNotFound");

	PRNT_STATUS(failures);
	return (failures);
}

int Cmp(const void *data1, const void *data2)
{
    if (*(int *)data1 < *(int *)data2)
    {
        return (-1);
    }
    else if (*(int *)data1 > *(int *)data2)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int TestBinarySearch()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	int *ret_data = NULL;
    static int data_to_find[LARGE_NUM] = {0};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = i;
        data_to_find[i] = i;
    }


    for (i = 0; i < LARGE_NUM; ++i)
    {
        ret_data = BinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(*(int *)ret_data, !=, data_to_find[i], %d, %d);
    }

    return (failures);
}

int TestBinarySearchSameNum()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	int *ret_data = NULL;
    static int data_to_find[LARGE_NUM] = {0};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = 1;
        data_to_find[i] = 1;
    }


    for (i = 0; i < LARGE_NUM; ++i)
    {
        ret_data = BinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(*(int *)ret_data, !=, data_to_find[i], %d, %d);
    }

    return (failures);
}

int TestBinarySearchSameNumNotFound()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	void *ret_data = NULL;
    static int data_to_find[LARGE_NUM] = {0};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = 1;
        data_to_find[i] = 2;
    }


    for (i = 0; i < LARGE_NUM; ++i)
    {
        ret_data = BinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(ret_data, !=, NULL, %p, %p);
    }

    return (failures);
}

int TestBinarySearchNotFound()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	void *ret_data = NULL;
    static int data_to_find[] = {-1, LARGE_NUM + 1};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = i;
    }


    for (i = 0; i < ARR_SIZE(data_to_find); ++i)
    {
        ret_data = BinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(ret_data, !=, NULL, %p, %p);
    }

    return (failures);
}

int TestRecBinarySearch()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	int *ret_data = NULL;
    static int data_to_find[LARGE_NUM] = {0};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = i;
        data_to_find[i] = i;
    }


    for (i = 0; i < LARGE_NUM; ++i)
    {
        ret_data = RecBinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(*(int *)ret_data, !=, data_to_find[i], %d, %d);
    }

    return (failures);
}

int TestRecBinarySearchSameNum()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	int *ret_data = NULL;
    static int data_to_find[LARGE_NUM] = {0};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = 1;
        data_to_find[i] = 1;
    }


    for (i = 0; i < LARGE_NUM; ++i)
    {
        ret_data = RecBinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(*(int *)ret_data, !=, data_to_find[i], %d, %d);
    }

    return (failures);
}

int TestRecBinarySearchSameNumNotFound()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	void *ret_data = NULL;
    static int data_to_find[LARGE_NUM] = {0};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = 1;
        data_to_find[i] = 2;
    }


    for (i = 0; i < LARGE_NUM; ++i)
    {
        ret_data = RecBinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(ret_data, !=, NULL, %p, %p);
    }

    return (failures);
}

int TestRecBinarySearchNotFound()
{
	size_t failures = 0;
    size_t i = 0;
    static int arr[LARGE_NUM] = {0};
	void *ret_data = NULL;
    static int data_to_find[] = {-1, LARGE_NUM + 1};

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = i;
    }


    for (i = 0; i < ARR_SIZE(data_to_find); ++i)
    {
        ret_data = RecBinarySearch(data_to_find + i, arr, ARR_SIZE(arr), sizeof(int), Cmp);
        REQUIRE(ret_data, !=, NULL, %p, %p);
    }

    return (failures);
}