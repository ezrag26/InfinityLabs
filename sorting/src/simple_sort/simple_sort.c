/*******************************************************************************
 * Date: 		10/10/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Liron
 * Satus: 		S
 ******************************************************************************/
#include <stdio.h>  /* fprintf            */
#include <stdlib.h> /* alloc family, rand */
#include <assert.h> /* assert             */

#include "simple_sort.h"

/*############################# Helper Functions #############################*/

static void Swap(int *num1, int *num2)
{
    int tmp = 0;

    tmp = *num1;
    *num1 = *num2;
    *num2 = tmp;
}

static size_t FindInsertPosition(int *arr, int swap_num, size_t i)
{
    while (swap_num > arr[i])
    {
        ++i;
    }

    return (i);
}

static size_t ShiftOneRight(int *arr, size_t index)
{
    arr[index] = arr[index - 1];

    return (--index);
}

static void ShiftAllRight(int *arr, size_t current_index, size_t stop_index)
{
    while (current_index > stop_index)
    {
        /* shift last number one space */
        current_index = ShiftOneRight(arr, current_index);
    }
}

static size_t Power(size_t base, size_t exponent)
{
    size_t result = 1;
    while (exponent)
    {
        result = result * base;
        --exponent;
    }

    return (result);
}

static size_t FindLargestLength(const unsigned long int *src, size_t size)
{
    size_t i = 0;
    size_t largest_num = 0;
    size_t length = 0;

    for (i = 0; i < size; ++i)
    {
        unsigned long int current_num = src[i];

        largest_num = (current_num > largest_num) ? current_num : largest_num;
    }

    while (0 < largest_num)
    {
        largest_num /= 10;
        ++length;
    }

    return length;
}

/*############################# Sorting Functions ############################*/

void BubbleSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    int was_swapped = 1;

    assert(NULL != arr);

    while (was_swapped)
    {
        was_swapped = 0;
        for (j = 1; j < size - i; j++)
        {
            if (arr[j - 1] > arr[j])
            {
                Swap((arr + j), (arr + (j - 1)));
                was_swapped = 1;
            }
        }
        ++i;
    }
}

void InsertionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t insert_index = 0;
    int swap_num = 0;

    assert(NULL != arr);

    for (i = 1; i < size; ++i)
    {
        insert_index = 0;
        if (arr[i - 1] > arr[i])
        {
            swap_num = arr[i];

            insert_index = FindInsertPosition(arr, swap_num, insert_index);

            ShiftAllRight(arr, i, insert_index);

            /* insert saved number */
            arr[insert_index] = swap_num;
        }
    }
}


void SelectionSort(int *arr, size_t size)
{
    size_t i = 0;
    size_t check_index = 0;
    size_t swap_index = 0;

    assert(NULL != arr);

    for (i = 0; i < size; i++)
    {
        swap_index = i;
        for (check_index = (i + 1); check_index < size; check_index++)
        {
            if (arr[check_index] < arr[swap_index])
            {
                swap_index = check_index;
            }
        }
        Swap((arr + i), (arr + swap_index));
    }
}

int *CountingSort(int *dest, const int *src, size_t size, int min, int max)
{
    size_t i = 0;
    size_t freq_arr_size = max - min + 1;
    int *freq_arr = (int *)calloc(freq_arr_size, sizeof(int));

    if (NULL == freq_arr)
    {
        PRNT_ERR("Memory allocation error");
        return (NULL);
    }

    assert(NULL != dest);
    assert(NULL != src);

    /* count number of times each number appears in src */
    for (i = 0; i < size; ++i)
    {
        freq_arr[src[i] - min] += 1;
    }

    /* calculate the index the number is next placed in */
    for (i = 1; i < freq_arr_size; ++i)
    {
        freq_arr[i] += freq_arr[i - 1];
    }

    /* write to dest the appropriate number */
    for (i = size; i > 0; --i)
    {
        size_t index = src[i - 1] - min;
        size_t dest_location = freq_arr[index] - 1;

        dest[dest_location] = src[i - 1];
        --freq_arr[index];
    }

    free(freq_arr); freq_arr = NULL;

    return (dest);
}

static unsigned long int *RadixCountBaseTen(unsigned long int *dest,
                                        const unsigned long int *src,
                                        size_t size,
                                        size_t exponent)
{
    size_t i = 0;
    size_t base = 10;
    size_t divisor = Power(base, exponent);
    size_t index = 0;
    size_t *freq_arr = (size_t *)calloc(base, sizeof(size_t));
    size_t *tmp_dest = (unsigned long int *)calloc(size, sizeof(unsigned long int));

    if (NULL == freq_arr)
    {
        PRNT_ERR("Memory allocation error");
        return NULL;
    }

    if (NULL == tmp_dest)
    {
        PRNT_ERR("Memory allocation error");
        return NULL;
    }

    /* count number of times each digit appears in src */
    for (i = 0; i < size; ++i)
    {
        index = (src[i] / divisor) % base;                   /* current digit */
        freq_arr[index] += 1;
    }

    /* accumulative sum */
    for (i = 1; i < base; ++i)
    {
        freq_arr[i] += freq_arr[i - 1];
    }

    /* write to tmp_dest the current sorted array */
    for (i = size; i > 0; --i)
    {
        size_t index = (src[i - 1] / divisor) % base;/* current digit to sort */
        size_t dest_location = freq_arr[index] - 1;

        tmp_dest[dest_location] = src[i - 1];
        --(freq_arr[index]);
    }

    /* copy to real dest */
    for (i = 0; i < size; ++i)
    {
        dest[i] = tmp_dest[i];
    }

    free(freq_arr); freq_arr = NULL;
    free(tmp_dest); tmp_dest = NULL;

    return (dest);
}

unsigned long int *RadixSortBaseTen(unsigned long int *dest,
                                const unsigned long int *src,
                                size_t size)
{
    size_t largest_length = 0;
    size_t exponent = 0;
    const unsigned long int *new_src = src;

    assert(NULL != dest);
    assert(NULL != src);

    largest_length = FindLargestLength(new_src, size);

    for (exponent = 0; exponent < largest_length; ++exponent)
    {
        new_src = RadixCountBaseTen(dest, new_src, size, exponent);

        if (NULL == new_src)
        {
            PRNT_ERR("Memory allocation error");
            return (NULL);
        }
    }

    return (dest);
}

static unsigned long int *RadixCountBits(unsigned long int *dest,
                                     const unsigned long int *src,
                                     size_t size,
                                     size_t nbits,
                                     size_t bits_sorted)
{
    size_t i = 0;
    size_t base = 2;
    size_t range = Power(base, nbits);
    size_t flag = (1 << nbits) - 1;  /* the bits to be sorted will all be set */
    size_t index = 0;
    size_t *freq_arr = (size_t *)calloc(range, sizeof(size_t));
    size_t *tmp_dest = (unsigned long int *)calloc(size, sizeof(unsigned long int));
    size_t shift = bits_sorted;

    if (NULL == freq_arr)
    {
        PRNT_ERR("Memory allocation error");
        return NULL;
    }

    if (NULL == tmp_dest)
    {
        PRNT_ERR("Memory allocation error");
        return NULL;
    }

    /* count number of times each group of bits appear in src */
    for (i = 0; i < size; ++i)
    {
        index = (src[i] >> shift) & flag;             /* current bits to sort */
        freq_arr[index] += 1;
    }

    /* accumulative sum */
    for (i = 1; i < range; ++i)
    {
        freq_arr[i] += freq_arr[i - 1];
    }

    /* write to tmp_dest the current sorted array */
    for (i = size; i > 0; --i)
    {
        size_t index = (src[i - 1] >> shift) & flag;
        size_t dest_location = freq_arr[index] - 1;

        tmp_dest[dest_location] = src[i - 1];
        --(freq_arr[index]);
    }

    /* copy to real dest */
    for (i = 0; i < size; ++i)
    {
        dest[i] = tmp_dest[i];
    }

    free(freq_arr); freq_arr = NULL;
    free(tmp_dest); tmp_dest = NULL;

    return (dest);
}

unsigned long int *RadixSortBits(unsigned long int *dest,
                             const unsigned long int *src,
                             size_t size,
                             size_t nbits)
{
    size_t bits_sorted = 0;
    size_t total_bits = sizeof(unsigned long int) * 8;
    const unsigned long int *new_src = src;

    assert(NULL != dest);
    assert(NULL != src);

    for (bits_sorted = 0; bits_sorted < total_bits; bits_sorted += nbits)
    {
        new_src = RadixCountBits(dest, new_src, size, nbits, bits_sorted);

        if (NULL == new_src)
        {
            PRNT_ERR("Memory allocation error");
            return (NULL);
        }
    }

    return (dest);
}
