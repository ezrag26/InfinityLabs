#ifndef __OL73_HEAP_H__
#define __OL73_HEAP_H__

#include <stddef.h> /* size_t */

#include "dynamic_vector.h"

typedef struct heap_s heap_t;

/*
 * Checks if data satisifes a condition with a given param
 * Should return 1 upon a successful match, 0 upon a failure
 */
typedef int (*heap_is_match_t)(const void *data, void *param);

/*
 * Compare function for the heap's order
 * With a given param, it should return a negative number if data1 has less
 * 		priority over data2 with a given given param, 0 if they they are the
 * 		same, and a positive number if data1 has more priority over data2
 */
typedef int (*heap_cmp_t)(const void *data1, const void *data2, void *param);

/**
 * Creates a heap according to the heap_cmp function
 * @param heap_cmp, compare function according to the guidelines above
 * @param param, paramter that can be used in the heap_cmp function
 * Returns pointer to the heap, or NULL upon a memory allocation failure
 * @complexity O(1) amortized
 */
heap_t *HeapCreate(heap_cmp_t heap_cmp, void *param);

/**
 * Destroys and frees memory of a given heap
 * @param heap, the heap to be destroyed
 * No return
 * @complexity O(1)
 */
void HeapDestroy(heap_t *heap);

/**
 * Pushes a given data into the heap according to the heap_cmp function
 * @param heap, the heap to push to
 * @data heap, the data to be pushed
 * Returns 0 upon a successful push, 1 upon memory error
 * @complexity O(log(n))
 */
int HeapPush(heap_t *heap, void *data);

/**
 * Pops the data with the highest priority according to the heap_cmp function
 * @param heap, the heap to pop the data from
 * Returns a pointer to the popped data
 * HeapPop() on an empty heap will result in undefined behavior
 * @complexity O(log(n))
 */
void *HeapPop(heap_t *heap);

/**
 * Looks at the data with the highest priority accoring to the heap_cmp function
 * @param heap, the heap to peek from
 * Returns a pointer to the peeked data
 * HeapPeek() on an empty heap will result in undefined behavior
 * @complexity O(1)
 */
void *HeapPeek(const heap_t *heap);

/**
 * Removes any element within the heap according to the is_match function and
 * a paramater
 * @param heap, the heap to remove the data from
 * @param is_match, function according to the guidelines above
 * @param param, additional parameter that can be used in the is_match function
 * Returns a pointer to the removed data, or NULL if the data could not be found
 * @complexity O(n)
 */
void *HeapRemove(heap_t *heap, heap_is_match_t is_match, void *param);

/**
 * Finds the size of a given heap
 * @param heap, the desired heap
 * Returns total number of elements in the heap
 * @complexity O(1)
 */
size_t HeapSize(const heap_t *heap);

/**
 * Checks if a given heap is empty
 * @param heap, the heap to check
 * Returns 1 if the heap is empty, 0 if not
 * @complexity O(1)
 */
int HeapIsEmpty(const heap_t *heap);

#endif /* __OL73_HEAP_H__ */
