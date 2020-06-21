#ifndef __OL73_HEAPIFY_H__
#define __OL73_HEAPIFY_H__

typedef int (*heapify_cmp_t)(const void *data1, const void *data2, void *param);

int HeapSiftUp(void *arr, size_t index, size_t element_size, heapify_cmp_t heap_cmp, void *param);

int HeapSiftDown(void *arr, size_t arr_size, size_t index, size_t element_size, heapify_cmp_t heap_cmp, void *param);

#endif /* __OL73_HEAPIFY_H__ */
