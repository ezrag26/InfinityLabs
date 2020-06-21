#include <time.h>   /* time               */
#include <stdio.h>  /* printf             */
#include <stdlib.h> /* alloc family, rand */

#include "simple_sort.h"
#include "tests.h"

int TestBubbleSort();
int TestInsertionSort();
int TestSelectionSort();
int TestCountingSort();
int TestRadixSortBaseTen();
int TestRadixSortBitsEven();
int TestRadixSortBitsUneven();

int main()
{
    size_t failures = 0;

    puts("Testing Simple Sort...");
    TEST(TestBubbleSort(), "BubbleSort");
    TEST(TestInsertionSort(), "InsertionSort");
    TEST(TestSelectionSort(), "SelectionSort");
    TEST(TestCountingSort(), "CountingSort");
    TEST(TestRadixSortBaseTen(), "RadixSortBaseTen");
    TEST(TestRadixSortBitsEven(), "RadixSortBitsEven");
    TEST(TestRadixSortBitsUneven(), "RadixSortBitsUneven");

    PRNT_STATUS(failures);

    return (failures);
}

int TestBubbleSort()
{
    size_t failures = 0;
    size_t i = 0;
    int arr1[] = {10, 0, -1, -5, 11, 10, 1};
    int exp1[] = {-5, -1, 0, 1, 10, 10, 11};
    int arr2[] = {0};
    int exp2[] = {0};
    int arr3[] = {1, 1, 5, 1, 1, 1};
    int exp3[] = {1, 1, 1, 1, 1, 5};

    BubbleSort(arr1, ARR_SIZE(arr1));
    for (i = 0; i < ARR_SIZE(arr1); ++i)
    {
        REQUIRE(arr1[i], !=, exp1[i], %d, %d);
    }

    BubbleSort(arr2, ARR_SIZE(arr2));
    for (i = 0; i < ARR_SIZE(arr2); ++i)
    {
        REQUIRE(arr2[i], !=, exp2[i], %d, %d);
    }

    BubbleSort(arr3, ARR_SIZE(arr3));
    for (i = 0; i < ARR_SIZE(arr3); ++i)
    {
        REQUIRE(arr3[i], !=, exp3[i], %d, %d);
    }

    return (failures);
}

int TestInsertionSort()
{
    size_t failures = 0;
    size_t i = 0;
    int arr1[] = {0, 13, 12, -5, 11, 10, 1};
    int exp1[] = {-5, 0, 1, 10, 11, 12, 13};
    int arr2[] = {0};
    int exp2[] = {0};
    int arr3[] = {1, 1, 5, 1, 1, 1};
    int exp3[] = {1, 1, 1, 1, 1, 5};

    InsertionSort(arr1, ARR_SIZE(arr1));
    for (i = 0; i < ARR_SIZE(arr1); ++i)
    {
        REQUIRE(arr1[i], !=, exp1[i], %d, %d);
    }

    InsertionSort(arr2, ARR_SIZE(arr2));
    for (i = 0; i < ARR_SIZE(arr2); ++i)
    {
        REQUIRE(arr2[i], !=, exp2[i], %d, %d);
    }

    InsertionSort(arr3, ARR_SIZE(arr3));
    for (i = 0; i < ARR_SIZE(arr3); ++i)
    {
        REQUIRE(arr3[i], !=, exp3[i], %d, %d);
    }

    return (failures);
}


int TestSelectionSort()
{
    size_t failures = 0;
    size_t i = 0;
    int arr1[] = {10, 0, -1, -5, 11, 10, 1};
    int exp1[] = {-5, -1, 0, 1, 10, 10, 11};
    int arr2[] = {0};
    int exp2[] = {0};
    int arr3[] = {1, 1, 5, 1, 1, 1};
    int exp3[] = {1, 1, 1, 1, 1, 5};

    SelectionSort(arr1, ARR_SIZE(arr1));
    for (i = 0; i < ARR_SIZE(arr1); ++i)
    {
        REQUIRE(arr1[i], !=, exp1[i], %d, %d);
    }

    SelectionSort(arr2, ARR_SIZE(arr2));
    for (i = 0; i < ARR_SIZE(arr2); ++i)
    {
        REQUIRE(arr2[i], !=, exp2[i], %d, %d);
    }

    SelectionSort(arr3, ARR_SIZE(arr3));
    for (i = 0; i < ARR_SIZE(arr3); ++i)
    {
        REQUIRE(arr3[i], !=, exp3[i], %d, %d);
    }

    return (failures);
}

int TestCountingSort()
{
    size_t failures = 0;
    size_t i = 0;
    size_t nnumbers = 5000;
    size_t min = 1;
    size_t max = 100;
    int arr1[] = {10, 1, 11, 10};
    int ret_arr1[ARR_SIZE(arr1)] = {0};
    int exp1[] = {1, 10, 10, 11};
    int arr2[] = {0};
    int exp2[] = {0};
    int ret_arr2[ARR_SIZE(arr2)] = {0};
    int arr3[] = {1, 1, 5, 1, 1, 1};
    int exp3[] = {1, 1, 1, 1, 1, 5};
    int ret_arr3[ARR_SIZE(arr3)] = {0};
    int *arr4 = (int *)malloc(nnumbers * sizeof(int));
    int *ret_arr4 = (int *)malloc(nnumbers * sizeof(int));

    srand(time(NULL));

    CountingSort(ret_arr1, arr1, ARR_SIZE(arr1), 1, 11);
    for (i = 0; i < ARR_SIZE(arr1); ++i)
    {
        REQUIRE(ret_arr1[i], !=, exp1[i], %d, %d);
    }

    CountingSort(ret_arr2, arr2, ARR_SIZE(arr2), 0, 0);
    for (i = 0; i < ARR_SIZE(arr2); ++i)
    {
        REQUIRE(ret_arr2[i], !=, exp2[i], %d, %d);
    }

    CountingSort(ret_arr3, arr3, ARR_SIZE(arr3), 1, 5);
    for (i = 0; i < ARR_SIZE(arr3); ++i)
    {
        REQUIRE(ret_arr3[i], !=, exp3[i], %d, %d);
    }

    for (i = 0; i < nnumbers; ++i)
    {
        arr4[i] = (rand() % max) + min;
    /*    printf("%d, ", arr4[i]); */
    }

    CountingSort(ret_arr4, arr4, nnumbers, 1, 100);

    for (i = 1; i < nnumbers; ++i)
    {
        if (ret_arr4[i] < ret_arr4[i - 1])
        {
            printf("\tFailed | %s | Line %d\n", __FILE__, __LINE__);
            printf("\t\tExpected: %d\n", ret_arr4[i - 1]);
            printf("\t\tReturned: %d\n", ret_arr4[i]);
        }
    }

    free(arr4); arr4 = NULL;
    free(ret_arr4); ret_arr4 = NULL;

    return (failures);
}

int TestRadixSortBaseTen()
{
    size_t failures = 0;
    size_t i = 0;
    size_t nnumbers = 5000;
    size_t max = 10000;
    size_t min = 1;
    unsigned long int *arr1 = (unsigned long int *)malloc(nnumbers * sizeof(unsigned long int));
    unsigned long int *ret_arr1 = (unsigned long int *)malloc(nnumbers * sizeof(unsigned long int));

    srand(time(NULL));

    for (i = 0; i < nnumbers; ++i)
    {
        arr1[i] = (rand() % max) + min;
        /*printf("%lu, ", arr1[i]);*/
    }

    ret_arr1 = RadixSortBaseTen(ret_arr1, arr1, nnumbers);

    for (i = 1; i < nnumbers; ++i)
    {
        REQUIRE(ret_arr1[i], <, ret_arr1[i - 1], %lu, %lu);
    }

    free(arr1); arr1 = NULL;
    free(ret_arr1); ret_arr1 = NULL;

    return (failures);
}

int TestRadixSortBitsEven()
{
    size_t failures = 0;
    size_t i = 0;
    size_t nnumbers = 5000;
    size_t max = 10000;
    size_t min = 1;
    size_t bits = 4;
    unsigned long int *arr1 = (unsigned long int *)malloc(nnumbers * sizeof(unsigned long int));
    unsigned long int *ret_arr1 = (unsigned long int *)malloc(nnumbers * sizeof(unsigned long int));

    srand(time(NULL));

    for (i = 0; i < nnumbers; ++i)
    {
        arr1[i] = (rand() % max) + min;
        /*printf("%lu, ", arr1[i]);*/
    }

    ret_arr1 = RadixSortBits(ret_arr1, arr1, nnumbers, bits);

    for (i = 1; i < nnumbers; ++i)
    {
        REQUIRE(ret_arr1[i], <, ret_arr1[i - 1], %lu, %lu);
    }

    free(arr1); arr1 = NULL;
    free(ret_arr1); ret_arr1 = NULL;

    return (failures);
}

int TestRadixSortBitsUneven()
{
    size_t failures = 0;
    size_t i = 0;
    size_t nnumbers = 5000;
    size_t max = 10000;
    size_t min = 1;
    size_t bits = 5;
    unsigned long int *arr1 = (unsigned long int *)malloc(nnumbers * sizeof(unsigned long int));
    unsigned long int *ret_arr1 = (unsigned long int *)malloc(nnumbers * sizeof(unsigned long int));

    srand(time(NULL));

    for (i = 0; i < nnumbers; ++i)
    {
        arr1[i] = (rand() % max) + min;
        /*printf("%lu, ", arr1[i]);*/
    }

    ret_arr1 = RadixSortBits(ret_arr1, arr1, nnumbers, bits);

    for (i = 1; i < nnumbers; ++i)
    {
        REQUIRE(ret_arr1[i], <, ret_arr1[i - 1], %lu, %lu);
    }

    free(arr1); arr1 = NULL;
    free(ret_arr1); ret_arr1 = NULL;

    return (failures);
}
