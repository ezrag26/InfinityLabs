/*******************************************************************************
 * Date: 		04/11/2019
 * Developer:	Ezra Gordon
 * Reviewer:
 * Satus: 		S
 ******************************************************************************/
#include <string.h> /* memmove */
#include <assert.h> /* assert  */

#include "advanced_sort.h"

static void SplitArrayInPlace(int *src, int *dest, size_t left, size_t right);
static void MergeInPlace(int *dest, size_t left, size_t middle, size_t right);

/******************************** In Place ************************************/

void MergeSortInPlace(int *src, int *dest, size_t size)
{
    size_t left = 0;
    size_t middle = size / 2 - 1;
    size_t right = size - 1;

    assert(NULL != src);
    assert(NULL != dest);

    SplitArrayInPlace(src, dest, left, middle);
    SplitArrayInPlace(src, dest, middle + 1, right);

    MergeInPlace(dest, left, middle + 1, right);
}

static void SplitArrayInPlace(int *src, int *dest, size_t left, size_t right)
{
    size_t middle = (left + right) / 2;

    if (left >= right)
    {
        dest[left] = src[left];
        return;
    }

    /* "split" into halves until individual elements */
    SplitArrayInPlace(src, dest, left, middle);
    SplitArrayInPlace(src, dest, middle + 1, right);

    /* merge each half sorted */
    MergeInPlace(dest, left, middle + 1, right);
}

static void MergeInPlace(int *dest, size_t left, size_t middle, size_t right)
{
    /* haven't reached both ends */
    while (left < middle && middle <= right)
    {
        /* not sorted */
        if (dest[left] > dest[middle])
        {
            /* insert unsorted number into correct place */
            int tmp = dest[middle];
            memmove(dest + left + 1, dest + left, (middle - left) * sizeof(int));
            dest[left] = tmp;
            ++middle;
        }
        ++left;
    }
}

/****************************** Not In Place **********************************/

static void Merge(int *new_src, int *cur_src, size_t left, size_t middle, size_t right)
{
    size_t i = left;
    const size_t MID = middle;
    const size_t END = right;

    /* haven't reached both ends */
    while (left < MID && middle <= END)
    {
        /* not sorted */
        if (cur_src[left] > cur_src[middle])
        {
            new_src[i] = cur_src[middle];
            ++middle;
        }
        else
        {
            new_src[i] = cur_src[left];
            ++left;
        }
        ++i;
    }

    while (middle <= END)
    {
        new_src[i] = cur_src[middle];
        ++middle;
        ++i;
    }

    while (left < MID)
    {
        new_src[i] = cur_src[left];
        ++left;
        ++i;
    }
}

static void SplitArray(int *src, int *dest, size_t left, size_t right)
{
    size_t middle = (left + right) / 2;

    if (left >= right)
    {
        return;
    }

    /* "split" into halves until individual elements */
    SplitArray(dest, src, left, middle);
    SplitArray(dest, src, middle + 1, right);

    /* merge each half sorted */
    Merge(dest, src, left, middle + 1, right);
}

void MergeSort(int *src, int *dest, size_t size)
{
    size_t left = 0;
    size_t middle = size / 2;
    size_t right = size - 1;

    assert(NULL != src);
    assert(NULL != dest);

    memcpy(dest, src, size * sizeof(int));

    SplitArray(dest, src, left, right);
    Merge(dest, src, left, middle + 1, right);
}
