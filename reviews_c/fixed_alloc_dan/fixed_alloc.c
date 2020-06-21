/*******************************************************************************
 * Date: 24/9/19
 * Developer: Dan
 * Reviewer: Ezra
 ******************************************************************************/

#include <assert.h>

#include "fixed_alloc.h"

static size_t word_size = sizeof(size_t);

struct fixed_allocator
{
	void *first_free;
};

static size_t FAWordAllinedChunkSizeCal(size_t block_size);


size_t FASuggestSize(size_t number_of_blocks, size_t block_size)
{
	size_t suggest_size = 0;
	size_t chunk_size = 0;

	chunk_size = FAWordAllinedChunkSizeCal(block_size);

	suggest_size = sizeof(falloc_t) + chunk_size * number_of_blocks;

	return (suggest_size);
}


falloc_t *FAInit(void *memory, size_t seg_size, size_t block_size)
{
	size_t chunk_size = 0;
	falloc_t *next_free = NULL;
	falloc_t *falloc = NULL;

	assert(NULL != memory);

	chunk_size = FAWordAllinedChunkSizeCal(block_size);

	if (seg_size < chunk_size)
	{
		return (NULL);
	}

	falloc = (falloc_t *)memory;
	falloc->first_free = falloc + 1;
	next_free = falloc + 1;

	seg_size -= sizeof(falloc_t);

	while (chunk_size <= seg_size)
	{
		next_free->first_free = (char *)next_free + chunk_size;
		next_free = next_free->first_free;

		seg_size -= chunk_size;
	}

	next_free = (falloc_t *)((char *)next_free - chunk_size);
	next_free->first_free = NULL;

	return (falloc);
}


static size_t FAWordAllinedChunkSizeCal(size_t block_size)
{
	size_t chunk_size = 0;
	size_t block_size_word_allined = 0;

	block_size_word_allined = block_size + (word_size - block_size % word_size)
					          % word_size;

	chunk_size = block_size_word_allined + sizeof(falloc_t);

	return (chunk_size);
}


void *FAAlloc(falloc_t *falloc)
{
	falloc_t *tmp = NULL;

	assert(NULL != falloc);

	tmp = falloc->first_free;
	falloc->first_free = tmp->first_free;
	tmp->first_free = falloc;

/*	((falloc_t *)(tmp->first_free))->first_free*/

	return (tmp + 1);
}


void FAFree(void* block)
{
	falloc_t *tmp = NULL;
	falloc_t *falloc_block = (falloc_t *)block;
	falloc_t *falloc_block_data = falloc_block - 1;

	assert(NULL != block);

	tmp = falloc_block_data->first_free;
	falloc_block_data->first_free = tmp->first_free;
	tmp->first_free = falloc_block_data;
}


size_t FACountFree(const falloc_t *falloc)
{
	size_t counter = 0;
	falloc_t *next_free = NULL;

	assert(NULL != falloc);

	next_free = falloc->first_free;

	while (NULL != next_free)
	{
		++counter;
		next_free = next_free->first_free;
	}

	return (counter);
}
