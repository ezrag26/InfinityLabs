#ifndef __OL73_DS_HEAPIFY_H__
#define __OL73_DS_HEAPIFY_H__

#include <stddef.h>					/* size_t	 */

/**
 * type of function-pointer accepted by HeapCreate().
 * Functions of type heapify_cmp_t can use param to compare data, and return an
 * int less than, equal to, or greater than zero if data1 is found,
 * respectively, to have lower, same or higher priority than data2.
 */
typedef int (*heapify_cmp_t)(const void *data1, const void *data2, void *param);


void HeapSiftUp(void *arr, size_t elem_size, size_t index, heapify_cmp_t cmp, void *param);
void HeapSiftDown(void *arr, size_t elem_size, size_t arr_size, size_t index, heapify_cmp_t cmp, void *param);

#endif /* __OL73_DS_HEAPIFY_H__ */
