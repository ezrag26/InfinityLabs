#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

int *SortZeroOne(int *arr, size_t size);

int main()
{
    size_t failures = 0;
    size_t i = 0;
    int arr[] = {0, 1, 1, 0, 0, 1, 0, 1, 0};
    int exp[] = {0, 0, 0, 0, 0, 1, 1, 1, 1};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    int *return_arr = NULL;

    return_arr = SortZeroOne(arr, size);

    for (i = 0; i < size; ++i)
    {
        if (return_arr[i] != exp[i])
        {
            printf("Failed\n");
            printf("\tExpected: %d\n", exp[i]);
            printf("\tReturned: %d\n", return_arr[i]);
            ++failures;
        }
    }

    if (failures == 0)
    {
        printf("Passed\n");
    }
    return 0;
}

int *SortZeroOne(int *arr, size_t size)
{
    size_t left_i = 0;
    size_t right_i = size - 1;
    int tmp = 0;

    assert(NULL != arr);

    while (left_i < right_i)
    {
        while (arr[left_i] != 1 && left_i <= right_i)
        {
            ++left_i;
        }

        while (arr[right_i] != 0 && left_i <= right_i)
        {
            --right_i;
        }

        if (left_i >= right_i)
        {
            return arr;
        }
        else
        {
            tmp = arr[left_i];
            arr[left_i] = arr[right_i];
            arr[right_i] = tmp;
        }
    }
    return arr;
}
