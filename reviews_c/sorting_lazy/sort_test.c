#include <time.h>   /* time               */
#include <stdio.h>  /* printf             */
#include <stdlib.h> /* alloc family, rand */

#include "sort.h"
#include "utils.h"  /* PRNT_ARRAY         */
#include "tests.h"

#define SMALL_NUM (10)
#define LARGE_NUM (5000)

int TestMergeSortSimple();
int TestMergeSort();

int main()
{
    size_t failures = 0;

    puts("Testing Simple Sort...");
    TEST(TestMergeSortSimple(), "TestMergeSortSimple");
    TEST(TestMergeSort(), "TestMergeSort");

    PRNT_STATUS(failures);

    return (failures);
}

int TestMergeSortSimple()
{
    size_t failures = 0;
    size_t i = 0;
    int arr[] = {4, 1, 7, 2, 9, 3, 0, 6, 5, 8};
    int exp_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int ret_arr[SMALL_NUM] = {0};

    /*PRNT_ARRAY(arr);*/

    MergeSort(ret_arr, arr, SMALL_NUM);

    /*PRNT_ARRAY(ret_arr);*/

    for (i = 0; i < SMALL_NUM; ++i)
    {
        REQUIRE(ret_arr[i], !=, exp_arr[i], %d, %d);
    }

    return (failures);
}

int TestMergeSort()
{
    size_t failures = 0;
    size_t i = 0;
    size_t max = 10000;
    size_t min = 1;
    int arr[5000] = {0};
    int ret_arr[5000] = {0};

    srand(time(NULL));

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = (rand() % max) + min;
    }

    MergeSort(ret_arr, arr, LARGE_NUM);

    /* PRNT_ARRAY(ret_arr); */

    for (i = 1; i < LARGE_NUM; ++i)
    {
        REQUIRE(ret_arr[i], <, ret_arr[i - 1], %d, %d);
    }

    return (failures);
}
