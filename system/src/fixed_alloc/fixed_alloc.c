/*******************************************************************************
 * Date: 		24/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Micah Gordon
 * Satus: 		S
 ******************************************************************************/
#include <assert.h> /* assert */

#include "fixed_alloc.h"
#include "utils.h"

#define ALIGNED_BLOCK ((WORD_SIZE - (block_size % WORD_SIZE)) % WORD_SIZE)

struct fixed_allocater
{
	void *next;
};

static const size_t STRUCT_SIZE = sizeof(falloc_t);
static const size_t WORD_SIZE = sizeof(size_t);

size_t CalculateChunkSize(size_t block_size)
{
	return (block_size + ALIGNED_BLOCK + STRUCT_SIZE);
}

size_t FASuggestSize(size_t num_of_blocks, size_t block_size)
{
	size_t chunk_size = CalculateChunkSize(block_size);

	size_t suggested_size = num_of_blocks * chunk_size + STRUCT_SIZE;

	return (suggested_size);

}

falloc_t *FAInit(void *memory, size_t seg_size, size_t block_size)
{
	size_t chunk_size = CalculateChunkSize(block_size);
	size_t current_seg_size = seg_size;
	falloc_t *control = (falloc_t *)memory;
	falloc_t *meta_data = NULL;

	assert(NULL != memory);

	/* can't create the allocator as it doesn't fit size requirements */
	if (current_seg_size < FASuggestSize(1, block_size) || block_size == 0)
	{
		return (NULL);
	}

	/* control points to first meta_data */
	control->next = (char *)memory + STRUCT_SIZE;

	/* move to first meta_data position */
	meta_data = (falloc_t *)control->next;

	/**
	 * decrement seg_size accordingly, plus an additional chunk_size to prevent
	 * need for assigning the last meta_data's next twice at segment's end
	 */
	current_seg_size -= (STRUCT_SIZE + chunk_size);

	while (current_seg_size >= chunk_size)
	{
		/* meta_data points to next meta_data */
		meta_data->next = (char *)meta_data + chunk_size;

		current_seg_size -= chunk_size;

		/* move to next meta_data position */
		meta_data = (falloc_t *)meta_data->next;
	}

	/* last meta_data point to NULL */
	meta_data->next = NULL;

	return (control);
}

void *FAAlloc(falloc_t *falloc)
{
	falloc_t *return_block = NULL;
	falloc_t *tmp_next = NULL;

	assert(NULL != falloc);

	/* next avaiable space */
	return_block = (falloc_t *)falloc->next;

	/* save next available space's next */
	tmp_next = return_block->next;

	/* next available space points to control struct */
	return_block->next = falloc;

	/* control points to new next available space */
	falloc->next = tmp_next;

	return (return_block + 1); /* pointer to the block */

}

void FAFree(void *block)
{
	falloc_t *meta_data_of_block = NULL;
	falloc_t *tmp = NULL;

	assert(NULL != block);

	/* block's meta_data */
	meta_data_of_block = (falloc_t *)block - 1;

	/* points to control struct */
	tmp = (falloc_t *)meta_data_of_block->next;

	/* meta_data's next available space is control struct's next */
	meta_data_of_block->next = tmp->next;

	tmp->next = meta_data_of_block;
}

size_t FACountFree(const falloc_t *falloc)
{
	const falloc_t *current_block = NULL;
	size_t count = 0;

	assert(NULL != falloc);

	current_block = (falloc_t *)falloc->next;

	while (NULL != current_block)
	{
		current_block = (falloc_t *)current_block->next;
		++count;
	}

	return (count);
}
