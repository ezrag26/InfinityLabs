#include <time.h>   /* time               */
#include <stdio.h>  /* printf             */
#include <stdlib.h> /* alloc family, rand */

#include "sort.h"
#include "utils.h"  /* PRNT_ARRAY         */
#include "tests.h"

#define SMALL_NUM (10)
#define LARGE_NUM (5000)

int TestQuickSortSimple();
int TestQuickSort();

int main()
{
    size_t failures = 0;

    puts("Testing Simple Sort...");
    TEST(TestQuickSortSimple(), "TestQuickSortSimple");
    TEST(TestQuickSort(), "TestQuickSort");

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

int TestQuickSortSimple()
{
    size_t failures = 0;
    size_t i = 0;
    int arr[] = {4, 1, -1, 2, 9, 3, 0, 6, 5, 8};
    int exp_arr[] = {-1, 0, 1, 2, 3, 4, 5, 6, 8, 9};

    /*PRNT_ARRAY(arr);*/

    QuickSort(arr, ARR_SIZE(arr), sizeof(int), Cmp);

    /*PRNT_ARRAY(ret_arr);*/

    for (i = 0; i < SMALL_NUM; ++i)
    {
        REQUIRE(arr[i], !=, exp_arr[i], %d, %d);
    }

    return (failures);
}

int TestQuickSort()
{
    size_t failures = 0;
    size_t i = 0;
    size_t max = 10000;
    size_t min = 1;
    int arr[LARGE_NUM] = {0};

    srand(time(NULL));

    for (i = 0; i < LARGE_NUM; ++i)
    {
        arr[i] = (rand() % max) + min;
    }

    QuickSort(arr, ARR_SIZE(arr), sizeof(int), Cmp);

    /* PRNT_ARRAY(ret_arr); */

    for (i = 1; i < LARGE_NUM; ++i)
    {
        REQUIRE(arr[i], <, arr[i - 1], %d, %d);
    }

    return (failures);
}
