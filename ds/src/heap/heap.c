#include <assert.h> /* assert */
#include <stdlib.h> /* alloc family */

#include "heap.h"
#include "heapify.h"   /* HeapSiftUp, HeapSiftDown */
#include "utils.h"

struct heap_s
{
    dv_t *dv;
    heap_cmp_t heap_cmp;
    void *param;
};

static const size_t FIRST_ELEM = 1;
static const size_t ELEM_SIZE = sizeof(void *);

static int HeapCmpWrapper(const void *data1, const void *data2, void *param)
{
    heap_t *heap = (heap_t *)param;
    return (heap->heap_cmp(*(void **)data1, *(void **)data2, heap->param));
}

static void HeapSwap(void **data1, void **data2)
{
    void *tmp = *data1;
    *data1 = *data2;
    *data2 = tmp;
}

heap_t *HeapCreate(heap_cmp_t heap_cmp, void *param)
{
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));

    if (NULL == heap)
    {
        PRNT_ERR("Memory allocation failed");
        return (NULL);
    }

    if (NULL == (heap->dv = DVCreate(1, ELEM_SIZE)))
    {
        PRNT_ERR("Memory allocation failed");
        free(heap); heap = NULL;
        return (NULL);
    }

    heap->param = param;
    heap->heap_cmp = heap_cmp;

    return (heap);
}

void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    DVDestroy(heap->dv); heap->dv = NULL;
    free(heap); heap = NULL;
}

int HeapPush(heap_t *heap, void *data)
{
    size_t index = 0;

    assert(NULL != heap);

    if (1 == DVPush(heap->dv, &data))
    {
        PRNT_ERR("Push Error");
        return (1);
    }

    index = HeapSize(heap) - 1;

    HeapSiftUp(
        DVGetElemAddress(heap->dv, 1), index, ELEM_SIZE, HeapCmpWrapper, heap);

    return (0);
}

void *HeapPop(heap_t *heap)
{
    dv_t *dv = NULL;
    void *first_element_ptr = NULL;
    void *last_element_ptr = NULL;
    void *return_data = NULL;
    size_t heap_size = 0;

    assert(NULL != heap);

    dv = heap->dv;
	heap_size = HeapSize(heap);

    first_element_ptr = DVGetElemAddress(dv, FIRST_ELEM);
    last_element_ptr = DVGetElemAddress(dv, heap_size);
    return_data = *(void **)first_element_ptr;

    HeapSwap(first_element_ptr, last_element_ptr);
    DVPop(dv);
	--heap_size;

    if (0 != heap_size)
    {
        if (1 == HeapSiftDown(DVGetElemAddress(dv, FIRST_ELEM),
                     		  heap_size,
							  0,
							  ELEM_SIZE,
							  HeapCmpWrapper,
							  heap))
		{
			return (NULL);
		}
    }

    return (return_data);
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return (*(void **)DVGetElemAddress(heap->dv, 1));
}

void *HeapRemove(heap_t *heap, heap_is_match_t is_match, void *param)
{
    dv_t *dv = NULL;
    void *current = NULL;
    void *last_elem = NULL;
    void *return_data = NULL;
    size_t heap_size = 0;
    size_t i = 1;
    int is_match_ret = 0;

    assert(NULL != heap);

    dv = heap->dv;
    heap_size = HeapSize(heap);

    /* interate through the heap and check for a match */
    while (i <= heap_size && 1 != is_match_ret)
    {
        current = DVGetElemAddress(dv, i);
        is_match_ret = is_match(*(void **)current, param);
        ++i;
    }

    /* data was not found in the heap */
    if (1 != is_match_ret)
    {
        return (NULL);
    }

    last_elem = DVGetElemAddress(dv, heap_size);
    return_data = *(void **)current;

    HeapSwap(current, last_elem);
    DVPop(dv);
	--heap_size;

	/**
	 * i decremented twice, once to take into account extra increment of i for
	 * finding elem address and for to take into account that HeapSiftUp uses
	 * the 0 index
	 */
    i -= 2;

    if (i != 1)
    {
        /* if last element has more priority over its new parent */
        if (1 == HeapSiftUp(DVGetElemAddress(dv, FIRST_ELEM),
							i,
							ELEM_SIZE,
							HeapCmpWrapper,
							heap))
	    {
			return (NULL);
		}
    }

    /* if last element has less priority over its new children */
    if (0 != heap_size)
    {
        if (1 == HeapSiftDown(DVGetElemAddress(dv, FIRST_ELEM),
                     		  heap_size,
							  i,
							  ELEM_SIZE,
							  HeapCmpWrapper,
							  heap))
		{
			return (NULL);
		}
    }

    return (return_data);
}

size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return (DVSize(heap->dv) - 1);   /* first cell is not used in calculation */
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return (0 == HeapSize(heap));
}
