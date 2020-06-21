#ifndef __OL73_QUICKSORT_H__
#define __OL73_QUICKSORT_H__

#include <stddef.h> /* size_t */

void QuickSort(void *base, size_t nel, size_t width, int (*cmp)(const void *, const void *));

#endif /* __OL73_QUICKSORT_H__ */
