#ifndef __OL73_FIXED_ALLOC_H__
#define __OL73_FIXED_ALLOC_H__

#include <stddef.h> /* size_t */

typedef struct fixed_allocater falloc_t;

 /**
 * FASuggestSize calculates the total size of memory required for
 * an instance of the fixed allocator.
 * @param num_of_blocks Number of elements that the allocator can contain.
 * @param block_size Size of each element in the allocator.
 * @return size_t Returns total size of the required memory.
 * @complexity O(1).
 */
size_t FASuggestSize(size_t num_of_blocks, size_t block_size);

 /**
 * FAInit initializes an instance of the fixed allocator.
 * @param ptr Pointer to a memory space to contain the allocator, in a total
 * size suggested by FASuggestSize().
 * @param seg_size Size of memory allocated by malloc
 * @param block_size Size of each element in the allocator.
 * @return (falloc_t *) Returns a pointer to a fixed allocator. If seg_size is
 * not large enough for initialization or block_size is 0, then FAInit() returns
 * NULL.
 * @complexity O(n).
 */
falloc_t *FAInit(void *memory, size_t seg_size, size_t block_size);


 /**
 * FAAlloc allocates memory for a single element.
 * @param falloc A pointer to a fixed allocator in which to allocate memory.
 * @return (void *) Returns a pointer to the allocated memory.
 * @complexity O(1).
 */
void *FAAlloc(falloc_t *falloc);

 /**
 * FAFree frees the memory pointed by ptr.
 * @param block A pointer previously returned by FAAlloc(). If ptr is NULL,
 * no operation is performed.
 * @complexity O(1).
 */
void FAFree(void *block);

 /**
 * FACountFree counts the free element-sized blocks in falloc.
 * @param falloc A pointer to a fixed allocator to count its free space.
 * @complexity O(n).
 */
size_t FACountFree(const falloc_t *falloc);

#endif /* __OL73_FIXED_ALLOC_H__ */
