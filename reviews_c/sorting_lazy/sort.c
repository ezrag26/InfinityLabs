/*******************************************************************************
*																			   *
*	DataStructures - Sorting Algorithms - Source Code						   *
*	Developer: Lazy Frid						  							   *
*	Reviewer: Ezra															   *
*	Status: S 15.10.2019													   *
*	Date: 07.10.2019														   *
*																			   *
*******************************************************************************/
#include <stdlib.h>			/* malloc		 */
#include <stdio.h>			/* DBG_PRT		 */
#include <assert.h>			/* assert		 */
#include <string.h>			/* memcpy		 */

#include "utils_lazy.h"			/* DBG_PRT		 */
#include "heapify.h"		/* siftup/down	 */

static void SwapInt(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;

	return;
}

static int CmpInt(const void *n1, const void *n2, void *param)
{
	(void)param;

	return (*(int *)n1 - *(int *)n2);
}

/***************** Comparison sorting algorithms ******************************/

void BubbleSort(int *arr, size_t size)
{
	size_t i = 0, j = 0, swapped = 1;

	assert(arr);

	while (swapped)
	{
		swapped = 0;
		/* Last i elements are already in place */
		for (j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				SwapInt(arr + j, arr + j + 1);
				swapped = 1;		/* keep bubbling only if swap happened */
			}
		}
		++i;
	}
	return;
}

void InsertionSort(int *arr, size_t size)
{
	size_t i = 0, j = 0;
	int temp = 0;

	assert(arr);

	for (i = 1; i < size; ++i)
	{
		temp = arr[i];
		for (j = i; (j > 0) && arr[j - 1] > temp; --j)
		{
			arr[j] = arr[j - 1];
		}
		arr[j] = temp;
	}
	return;
}

void SelectionSort(int *arr, size_t size)
{
	size_t i = 0, j = 0;

	assert(arr);

	for (i = 0; i < size - 1; ++i)
	{
		for (j = i; j < size; ++j)
		{
			if (arr[j] < arr[i])
			{
				SwapInt(arr + i, arr + j);
			}
		}
	}
	return;
}

/***************** Distribution sort algorithms *******************************/

int *CountingSort(int *dest, const int *src, size_t size, int min, int max)
{
	size_t *counters = NULL, i = 0;
	size_t range_size = max - min + 1;
	int key = 0;

	assert(dest);
	assert(src);

	if ((min > max) || size == 0)
	{
		DBG_PRT("arguments failed to meet the requirements");
		return NULL;
	}

	counters = (size_t *)calloc(range_size, sizeof(size_t));
	if (!counters)
	{
		DBG_PRT("malloc failed");
		return NULL;
	}
	/* Store count of each key */
	for (i = 0; i < size; ++i)
	{
		++counters[src[i] - min];
	}
	/* accumulate counts to represent key's top index */
	for (i = 1; i < range_size; ++i)
	{
		counters[i] += counters[i - 1];
	}
	/* cpy 'src' elements to 'dest' according to indexes in 'counters' */
	for (i = size; i > 0; --i)
	{
		key = src[i - 1];
		dest[counters[key - min] - 1] = key;
		--counters[key - min];
	}

	free(counters);

	return dest;
}

unsigned int *RadixSortFlex(unsigned int *dest, const unsigned int *src,
												size_t size, unsigned int base)
{
	unsigned int *help_arr = NULL, *from_handle = NULL, *to_handle = NULL;
	unsigned int key = 0, exp = 1;
	size_t *counters = NULL;
	size_t i = 0, j = 0, digits = 0;

	assert(dest);
	assert(src);

	help_arr = (unsigned int *)calloc(size, sizeof(unsigned int));
	if (!help_arr)
	{
		DBG_PRT("malloc failed");
		return NULL;
	}

	/* get number of digits of largest key */
	for (i = 0; i < size; ++i)
	{
		key = (src[i] > key) ? src[i] : key;
	}
	while (key)
	{
		key /= base;
		++digits;
	}

	counters = (size_t *)calloc(base * digits, sizeof(size_t));
	if (!counters)
	{
		DBG_PRT("malloc failed");
		return NULL;
	}

	/* Store count of each digit for all digits */
	for (i = 0; i < size; ++i)
	{
		key = src[i];
		for (j = 0; j < digits; ++j)
		{
			++counters[(base * j) + (key % base)];
			key /= base;
		}
	}
	/* accumulate counts to represent key's top index */
	for (i = 1; i < base; ++i)
	{
		for (j = 0; j < digits; ++j)
		{
			counters[(j * base) + i] += counters[(j * base) + i - 1];
		}
	}

	/* set initial handlers */
	from_handle = (unsigned int *)src;
	to_handle = (digits % 2 == 0) ? help_arr : dest;

	/* count sort for every digit */
	for (j = 0, exp = 1; j < digits; ++j, exp *= base)
	{
		for (i = size; i > 0; --i)
		{
			key = (from_handle[i - 1] / exp) % base;
			to_handle[counters[(j * base) + key] - 1] = from_handle[i - 1];
			--counters[(j * base) + key];
		}

		/* flip between the arrays after every digit sort */
		if ((digits - j) % 2 == 0)
		{
			from_handle = help_arr;
			to_handle = dest;
		}
		else
		{
			from_handle = dest;
			to_handle = help_arr;
		}
	}

	free(counters);
	free(help_arr);

	return dest;
}

unsigned int *RadixSort2Powers(unsigned int *dest, const unsigned int *src,
											size_t size, unsigned int base_exp)
{
	unsigned int *help_arr = NULL, *from_handle = NULL, *to_handle = NULL;
	unsigned int key = 0, base = 0, mask = 0;
	size_t *counters = NULL;
	size_t i = 0, j = 0, digits = 0;

	assert(dest);
	assert(src);

	base = (1 << base_exp);
	mask = base - 1;

	help_arr = (unsigned int *)calloc(size, sizeof(unsigned int));
	if (!help_arr)
	{
		DBG_PRT("malloc failed");
		return NULL;
	}

	/* get number of digits of largest key */
	for (i = 0; i < size; ++i)
	{
		key = (src[i] > key) ? src[i] : key;
	}
	while (key)
	{
		key >>= base_exp;
		++digits;
	}

	counters = (size_t *)calloc(base * digits, sizeof(size_t));
	if (!counters)
	{
		DBG_PRT("malloc failed");
		return NULL;
	}

	/* Store count of each digit for all digits */
	for (i = 0; i < size; ++i)
	{
		key = src[i];
		for (j = 0; j < digits; ++j)
		{
			++counters[(base * j) + (key & mask)];
			key >>= base_exp;
		}
	}
	/* accumulate counts to represent key's top index */
	for (i = 1; i < base; ++i)
	{
		for (j = 0; j < digits; ++j)
		{
			counters[(base * j) + i] += counters[(base * j) + i - 1];
		}
	}

	/* set initial handlers */
	from_handle = (unsigned int *)src;
	to_handle = (digits % 2 == 0) ? help_arr : dest;

	/* count sort for every digit */
	for (j = 0; j < digits; ++j)
	{
		for (i = size; i > 0; --i)
		{
			key = (from_handle[i - 1] >> (j * base_exp)) & mask;
			to_handle[counters[(j * base) + key] - 1] = from_handle[i - 1];
			--counters[(j * base) + key];
		}

		/* flip between the arrays after every digit sort */
		if ((digits - j) % 2 == 0)
		{
			from_handle = help_arr;
			to_handle = dest;
		}
		else
		{
			from_handle = dest;
			to_handle = help_arr;
		}
	}

	free(counters);
	free(help_arr);

	return dest;
}

int IsIntBefore (int a, int b)
{
	return (a < b);
}

static void RecMergeSort(int *dest, int *src, size_t size)
{
	/* recursively splits the array in the middle into sub-arrays */
	const size_t half = size / 2;
	size_t i = 0, j = half;

	/* Base case. A list of one elements is sorted, by definition */
	if (1 == size) return;

	/* alternating the direction of the merge with each level of recursion */
	RecMergeSort(src, dest, half);
	RecMergeSort(src + half, dest + half, size - half);

	/* merge 2 sorted sub-arrays using IsBefore func */
	while ((i < half) && (j < size))
	{
		if (IsIntBefore(*(src + i), *(src + j)))
		{
			*(dest++) = *(src + i);
			++i;
		}
		else
		{
			*(dest++) = *(src + j);
			++j;
		}
	}

	/* if only one sub-array left, spill it all to dest, no need to compare */
	while (i < half)
	{
		*(dest++) = *(src + i);
		++i;
	}
	while (j < size)
	{
		*(dest++) = *(src + j);
		++j;
	}

	return;
}

void MergeSort(int *dest, int *src, size_t size)
{
	assert(dest);
	assert(src);

	/* sub-array sorting can start from dest too */
	memcpy(dest, src, size * sizeof(int));

	RecMergeSort(dest, src, size);

	return;
}

void HeapSort(int *arr, size_t size)
{
	size_t i = 0;

	/* Floyd's heap construction */
	for (i = 0; i <= ((size / 2) - 1); ++i)
	{
		/* sift down all sub trees (excluding leaves) */
		HeapSiftDown(arr, sizeof(int), size, ((size / 2) - 1) - i, CmpInt, NULL);
	}

	/* sort element by element */
	for (i = 0; i < size - 1; ++i)
	{
		/* swap heap top (largest element) with the end */
		SwapInt(arr, arr + (size - 1 - i));

		/* sift new top down a --sized heap since last element is in place */
		HeapSiftDown(arr, sizeof(int), size - 1 - i, 0, CmpInt, NULL);
	}

	return;
}
