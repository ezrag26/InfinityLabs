#ifndef __OL73_SIMPLE_SORT_H__
#define __OL73_SIMPLE_SORT_H__

#include <stddef.h> /* size_t             */

#include "utils.h"

void BubbleSort(int * arr, size_t size);

void InsertionSort(int * arr, size_t size);

void SelectionSort(int * arr, size_t size);

int *CountingSort(int *dest, const int *src, size_t size, int min, int max);

unsigned long *RadixSortBaseTen(unsigned long *dest,
                                const unsigned long *src,
                                size_t size);

unsigned long *RadixSortBits(unsigned long *dest,
                             const unsigned long *src,
                             size_t size,
                             size_t nbits);

#endif /* __OL73_SIMPLE_SORT_H__ */
