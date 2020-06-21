#ifndef __OL73_C_BUFFER_H__
#define __OL73_C_BUFFER_H__

#include <unistd.h>	/* ssize_t */
#include <stddef.h> /* size_t  */

#include "utils.h"

typedef struct c_buffer c_buffer_t;

/*
 * Creates an empty circular buffer with given capacity
 * Returns pointer to cicular buffer
 * Time complexity: O(n)
 */
c_buffer_t *CBufferCreate(size_t capacity);

/*
 * Destroy circular buffer c_buffer
 * Returns nothing
 * Time complexity: O(1)
 */
void CBufferDestroy(c_buffer_t *c_buffer);

/*
 * Reads count bytes from cicular buffer c_buffer, and copies to buffer buf
 * Returns number of bytes successfully read and copied to buf
 * If c_buffer is empty at time of function call, -1 is returned and errno is
 		set to ENODATA
 * Time complexity: O(n)
 */
ssize_t CBufferRead(c_buffer_t *c_buffer, void *buf, size_t count);

/*
 * Writes count bytes from buffer buf to circular buffer c_buffer
 * Returns number of bytes successfully written and copied to c_buffer
 * If c_buffer is full at time of function call, -1 is returned and errno is
 		set to ENOBUFS
 * Time complexity: O(n)
 */
ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *buf, size_t count);

/*
 * Checks how much space is available to write to in circular buffer c_buffer
 * Returns total bytes available in c_buffer
 * Time complexity: O(1)
 */
size_t CBufferFreeSpace(const c_buffer_t *c_buffer);

/*
 * Checks total capacity for cicular buffer c_buffer
 * Returns total capacity in bytes
 * Time complexity: O(1)
 */
size_t CBufferCapacity(const c_buffer_t *c_buffer);

/*
 * Checks if buffer c_buffer is empty
 * Returns 1 if c_buffer is empty, 0 otherwise
 * Time complexity: O(1)
 */
int CBufferIsEmpty(const c_buffer_t *c_buffer);

#endif /* __OL73_C_BUFFER_H__ */
