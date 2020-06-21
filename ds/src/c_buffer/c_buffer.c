/*******************************************************************************
 * Date: 		8/9/2019
 * Developer:	Ezra Gordon
 * Reviewer: 	Odelia
 * Satus: 		A
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <stdio.h>  /* fprintf		*/
#include <errno.h>	/* errno		*/
#include <assert.h> /* assert		*/
#include <string.h> /* memcpy		*/

#include "c_buffer.h"

struct c_buffer {
	size_t read_i;
	size_t write_i; 	 /* current occupied bytes */
	size_t capacity; 	 /* total size of buffer   */
	char buffer[1];		 /* Enables to see if the buffer is full or empty */
};

const size_t OFFSET = sizeof(c_buffer_t);
size_t CBufferCapacity(const c_buffer_t *c_buffer);

/******************************* CBufferCreate ********************************/

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *c_buffer = (c_buffer_t *)malloc(sizeof(c_buffer_t) + capacity);

	if (NULL == c_buffer)
	{
		PRNT_ERR("Malloc Allocation Error");
		return (NULL);
	}

	c_buffer->read_i = 0;
	c_buffer->write_i = 0;
	c_buffer->capacity = capacity;

	return (c_buffer);
}

/******************************* CBufferDestroy *******************************/

void CBufferDestroy(c_buffer_t *c_buffer)
{
	if (NULL != c_buffer)
	{
		free(c_buffer); c_buffer = NULL;
	}
}

/******************************** CBufferRead *********************************/

ssize_t CBufferRead(c_buffer_t *c_buffer, void *buf, size_t count)
{
	size_t bytes_allowed_to_read = 0;
	size_t remaining_bytes = 0;
	size_t read_to_end = (CBufferCapacity(c_buffer) + 1) - c_buffer->read_i;
	size_t first_copy_bytes = 0;
	char *buf_pos = NULL;

	assert(NULL != c_buffer);
	assert(NULL != buf);

	bytes_allowed_to_read = (CBufferCapacity(c_buffer) -
							 CBufferFreeSpace(c_buffer));
	buf_pos = (char *)buf;

	if (0 == bytes_allowed_to_read)					  /* if c_buffer is empty */
	{
		errno = ENODATA;
		return (-1);
	}

	/* find total bytes to actually read */
	count = MIN(count, bytes_allowed_to_read);

	/* copy remaining bytes or until end of buffer */
	first_copy_bytes = MIN(count, read_to_end);
	buf_pos = memcpy(buf_pos,
					 c_buffer->buffer + c_buffer->read_i,
					 first_copy_bytes);

	c_buffer->read_i += first_copy_bytes;   /* incremement read_i accordingly */

	/* subtract number of bytes already copied */
	remaining_bytes = count - first_copy_bytes;

	if (remaining_bytes > 0)				 /* there are still bytes to copy */
	{
		c_buffer->read_i = 0;		   /* read returns to beginning of buffer */

		memcpy(buf_pos + first_copy_bytes, c_buffer->buffer, remaining_bytes);

		c_buffer->read_i += remaining_bytes;/* incremement read_i accordingly */
	}

	return ((ssize_t)count);

}

/******************************** CBufferWrite ********************************/

ssize_t CBufferWrite(c_buffer_t *c_buffer, const void *buf, size_t count)
{
	size_t bytes_allowed_to_write = 0;
	size_t remaining_bytes = 0;
	size_t write_to_end = (CBufferCapacity(c_buffer) + 1) - c_buffer->write_i;
	size_t first_write_bytes = 0;
	char *buf_pos = NULL;

	assert(NULL != c_buffer);
	assert(NULL != buf);

	bytes_allowed_to_write = CBufferFreeSpace(c_buffer);
	buf_pos = (char *)buf;

	if (0 == bytes_allowed_to_write)				   /* if c_buffer is full */
	{
		errno = ENOBUFS;
		return (-1);
	}

	/* find total bytes to actually write */
	count = MIN(count, bytes_allowed_to_write);

	/* copy remaining bytes or until end of buffer */
	first_write_bytes = MIN(count, write_to_end);
	memcpy(c_buffer->buffer + c_buffer->write_i, buf_pos, first_write_bytes);

	c_buffer->write_i += first_write_bytes;  /* increment write_i accordingly */

	/* subtract number of bytes already copied */
	remaining_bytes = count - first_write_bytes;

	if (remaining_bytes > 0)				 /* there are still bytes to copy */
	{
		c_buffer->write_i = 0;		  /* write returns to beginning of buffer */

		memcpy(c_buffer->buffer + c_buffer->write_i,
			   buf_pos + first_write_bytes,
			   remaining_bytes);

		c_buffer->write_i += remaining_bytes;/* increment write_i accordingly */
	}

	return ((ssize_t)count);
}

/****************************** CBufferFreeSpace ******************************/

size_t CBufferFreeSpace(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	if (c_buffer->write_i >= c_buffer->read_i)
	{
		return (CBufferCapacity(c_buffer) -
			   (c_buffer->write_i - c_buffer->read_i));
	}
	else
	{
		/* c_buffer->read_i is one position after c_buffer->write_i */
		return (c_buffer->read_i - c_buffer->write_i - 1);
	}
}

/****************************** CBufferCapacity *******************************/

size_t CBufferCapacity(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	return (c_buffer->capacity);
}

/******************************* CBufferIsEmpty *******************************/

int CBufferIsEmpty(const c_buffer_t *c_buffer)
{
	assert(NULL != c_buffer);

	return (c_buffer->write_i == c_buffer->read_i);
}
