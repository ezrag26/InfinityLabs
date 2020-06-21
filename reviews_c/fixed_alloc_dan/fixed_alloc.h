/*******************************************************************************
 * Date: 24/9/19 
 * Developer: Dan 
 * Reviewer: Ezra 
 ******************************************************************************/

#ifndef __OL73_FIXED_ALLOC_H__
#define __OL73_FIXED_ALLOC_H__

#include <stddef.h>

typedef struct fixed_allocator falloc_t;

/**
 * FASuggestSize calculates the total size of memory required for
 * an instance of the fixed allocator.
 * @param nmemb Max number of elements that the allocator can contain.
 * @param size Size of each element in the allocator.
 * @return size_t Returns total size of the required memory.
 * @compelxity O(1).
 */
size_t FASuggestSize(size_t number_of_blocks, size_t block_size);

/**
 * FAInit initializes an instance of the fixed allocator.
 * @param ptr Pointer to a memory space to contain the allocator, in a total
 * size suggested by FASuggestSize().
 * @param number_of_blocks Max number of elements that the allocator can contain.
 * @param block_size Size of each element in the allocator.
 * @return (falloc_t *) Returns a pointer to a fixed allocator. If block_size or
 * number_of_blocks are 0, then FAInit() returns NULL.
 * @compelxity O(1).
 */
falloc_t *FAInit(void *memory, size_t seg_size, size_t block_size);


/**
 * FAAlloc allocates memory for a single element.
 * @param falloc A pointer to a fixed allocator in which to allocate memory.
 * @return (void *) Returns a pointer to the allocated memory.
 * @compelxity O(1).
 */
void *FAAlloc(falloc_t *falloc);

/**
 * FAFree frees the memory pointed by ptr.
 * @param ptr A pointer previously returned by FAAlloc(). If ptr is NULL,
 * no operation is performed.
 * @compelxity O(1).
 */
void FAFree(void* block);

/**
 * FACountFree counts the free element-sized blocks in falloc.
 * @param falloc A pointer to a fixed allocator to count its free space.
 * @compelxity O(n).
 */
size_t FACountFree(const falloc_t *falloc);


#endif /* __OL73_FIXED_ALLOC_H__ */
