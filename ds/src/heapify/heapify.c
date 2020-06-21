#include <stddef.h> /* size_t       */
#include <stdlib.h> /* alloc family */
#include <string.h> /* memcpy       */
#include <assert.h> /* assert       */

#include "heapify.h"
#include "utils.h"

static int HeapifySwap(void *data1, void *data2, size_t element_size)
{
    void *tmp = malloc(element_size);

    if (NULL == tmp)
    {
        PRNT_ERR("Memory allocation error");
        return (1);
    }

    memcpy(tmp, data1, element_size);
    memcpy(data1, data2, element_size);
    memcpy(data2, tmp, element_size);

    free(tmp); tmp = NULL;
	return (0);
}

int HeapSiftUp(void *arr, size_t index, size_t element_size, heapify_cmp_t heap_cmp, void *param)
{
	size_t parent_index = (index - 1) / 2;
    void *parent_data_ptr = (char *)arr + (parent_index * element_size);
    void *inserted_data_ptr = (char *)arr + (index * element_size);
    int cmp = 0;

    assert(NULL != arr);

    /* root index */
    if (index < 1)
    {
        return (0);
    }

    cmp = heap_cmp(parent_data_ptr, inserted_data_ptr, param);

    /* inserted_data has more priority than its parent */
    if (0 > cmp)
    {
        if (1 == HeapifySwap(parent_data_ptr, inserted_data_ptr, element_size))
		{
			return (1);
		}

        HeapSiftUp(arr, parent_index, element_size, heap_cmp, param);
    }

	return (0);
}


int HeapSiftDown(void *arr, size_t arr_size, size_t index, size_t element_size, heapify_cmp_t heap_cmp, void *param)
{
    size_t left_child_index = (index * 2) + 1;
    size_t right_child_index = (index * 2) + 2;
    size_t swap_child_index = left_child_index;
    size_t heap_size = arr_size;
    void *current_ptr = (char *)arr + (index * element_size);
    void *swap_child_ptr = (char *)arr + (left_child_index * element_size);
    void *left_child_ptr = swap_child_ptr;
    void *right_child_ptr = (char *)arr + (right_child_index * element_size);
    int cmp = 0;

    /* has no children */
    if (left_child_index >= heap_size)
    {
        return (0);
    }

    /* has a left child but no right child */
    if (right_child_index < heap_size)
    {
		cmp = heap_cmp(left_child_ptr, right_child_ptr, param);

        /* the left child has less priority than the right child */
        if (0 > cmp)
        {
            swap_child_ptr = right_child_ptr;
			swap_child_index = right_child_index;
        }
    }

    cmp = heap_cmp(current_ptr, swap_child_ptr, param);

    /* current_ptr has less priority than one of its children */
    if (0 > cmp)
    {
		if (1 == HeapifySwap(current_ptr, swap_child_ptr, element_size))
		{
			return (1);
		}

        HeapSiftDown(arr, arr_size, swap_child_index, element_size, heap_cmp, param);
    }

	return (0);
}
