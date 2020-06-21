#ifndef __OL73_VAR_ALLOC_H__
#define __OL73_VAR_ALLOC_H__

#include <stddef.h>		/* size_t */

typedef struct var_allocator valloc_t;

/**
 *@brief Creates an instance of a variable memory allocator
 *@param memory Pointer to the malloc'd memory to be managed by the allocator
 *@param seg_size The total size in bytes of the memory to be managed
 *@return (valloc_t *) Returns a pointer to the memory allocator or NULL if
 *		 seg_size is insufficient
 *@complexity O(1)
 */
valloc_t *VAInit(void *memory, size_t seg_size);

/**
 *@brief Gets an available block of memory of the given block_size from the
 *		 given memory allocator.
 *@param valloc Pointer to the allocator from which to get a block of memory
 *@param block_size The desired size in bytes of the block to be allocated
 *@return Returns a pointer to an available block of memory or NULL if
 *		  requested size is unavailable
 *@complexity O(n)
 */
void *VAAlloc(valloc_t *valloc, size_t block_size);

/**
 *@brief Releases the the given block of memory. Can be alloc'd again later
 *@param block Pointer to the block of memory to be released. If block is NULL,
 *		 no operation is performed. Behavior is undefined if block is already
 *		 free
 *@complexity O(1)
 */
void VAFree(void *block);

/**
 *@brief Calculates the size of the largest available block of memory
 *@param valloc Pointer to the allocator to check
 *@return Returns the size of the largest available block of memory
 *@complexity O(n)
 */
size_t VALargestAvailable(valloc_t *valloc);

#endif /* __OL73_VAR_ALLOC_H__ */
