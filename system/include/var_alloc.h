#ifndef __OL73_VAR_ALLOC_H__
#define __OL73_VAR_ALLOC_H__

#include <stddef.h> /* size_t */

typedef struct variable_alloc valloc_t;

 /**
 * VAInit initializes an instance of the variable allocator.
 * @param memory Pointer to a memory space to contain the allocator
 * @param seg_size Size of memory given by user, in bytes.
 * @return (valloc_t *) Returns a pointer to a variable allocator. If seg_size
 * in insufficent for initialization, NULL is returned
 * @complexity O(1).
 */
valloc_t *VAInit(void *memory, size_t seg_size);

 /**
 * VAAlloc allocates memory.
 * @param valloc A pointer to a variable allocator
 * @param block_size Number of bytes to allocate from valloc.
 * @return (void *) Returns a pointer to the allocated memory block, or NULL if
 * requested size is unavailable. If block_size is 0, returns a unique pointer
 * value that can be successfully passed to VAFree().
 * @complexity O(n).
 */
void *VAAlloc(valloc_t *valloc, size_t block_size);

/**
 * VAFree frees the memory pointed by block.
 * @param block A pointer previously returned by VAAlloc(). Calling VAFree() on
 * an already freed pointer results in undefined behavior.
 * @complexity O(1).
 */
void VAFree(void *block);

/**
 * VALargestAvailable finds the largest segment available for allocation.
 * @param valloc A pointer to a variable allocator
 * @return Returns size of largest avaiable segment for allocation, in bytes.
 * @complexity O(n).
 */
size_t VALargestAvailable(valloc_t *valloc);

#endif /* __OL73_VAR_ALLOC_H__ */
