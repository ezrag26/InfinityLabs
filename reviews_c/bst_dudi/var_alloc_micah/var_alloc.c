#include <stdlib.h>		/* labs */
#include <assert.h>

#include "var_alloc.h"
#include "utils.h"

struct var_allocator
{
	long int offset;
#ifndef NDEBUG
	size_t magic_number;
#endif
};

#define TRUE (1)
#define FALSE (0)
#define WORD (sizeof(size_t))
#define METADATA_SPACE (sizeof(valloc_t))
#define MAGIC_NUMBER (66)

static const size_t MIN_SEG_SIZE = ((2 * METADATA_SPACE) + WORD);
static const size_t WORDS_PER_METADATA = METADATA_SPACE / WORD;

static size_t GetBlockSize(size_t requested_block_size)
{
	/*
	*	if the requested block size is not word aligned, add the necessary
	*	number of bytes until word alignment, otherwise do not add anything
	*/
	return  requested_block_size
			+ ((WORD - (requested_block_size % WORD)) % WORD);

}

static size_t GetSpaceRequired(size_t requested_block_size)
{
	size_t user_space = GetBlockSize(requested_block_size);
	/*
	 *	each block is the size that the user gets plus the space for metadata
	 *	divide by word to get the total number of words
	 */
	return (user_space + METADATA_SPACE) / WORD;
}

static long int DefragmentFreeSpace(valloc_t *metadata)
{

	valloc_t *next_metadata = NULL;

	if (metadata->offset <= 0)
	{
		return 0;
	}

	next_metadata = (valloc_t *)((size_t *)(metadata) + metadata->offset);
	if (next_metadata->offset > 0)
	{
		metadata->offset += next_metadata->offset;
	}

	return next_metadata->offset;
}

valloc_t *VAInit(void *memory, size_t seg_size)
{
	valloc_t *valloc = NULL;
	valloc_t *end = NULL;

	assert(NULL != memory);

	valloc = (valloc_t *)(memory);
#ifndef NDEBUG
	valloc->magic_number = MAGIC_NUMBER;
#endif

	seg_size = GetBlockSize(seg_size);

	if (seg_size < MIN_SEG_SIZE)
	{
		return NULL;
	}

	seg_size /= WORD;
	valloc->offset = seg_size - WORDS_PER_METADATA;
	end = (valloc_t*)((size_t*)(memory) + (seg_size - WORDS_PER_METADATA));
	end->offset = 0;

	return valloc;
}

static valloc_t *GetFirstFit(valloc_t *valloc, long int space_required)
{
	long int offset = 0;

	assert(NULL != valloc);

	offset = valloc->offset;

	while(offset)
	{
		if (offset < 0)
		{
			valloc = (valloc_t*)((size_t*)(valloc) + labs(offset));
			offset = valloc->offset;
			continue;
		}

		while ((offset < space_required) && (DefragmentFreeSpace(valloc) > 0))
		{
			offset = valloc->offset;
		}

		if (offset >= space_required)
		{
			return valloc;
		}

		valloc = (valloc_t*)((size_t*)(valloc) + labs(offset));
		offset = valloc->offset;
	}

	return NULL;
}

void *VAAlloc(valloc_t *valloc, size_t block_size)
{
	long int space_required = (long int)(GetSpaceRequired(block_size));
	long int offset = 0;
	valloc_t *new_metadata = NULL;

	valloc = GetFirstFit(valloc, space_required);

	if (NULL == valloc)
	{
		return NULL;
	}

	offset = valloc->offset;

	if (space_required <= (offset - (long int)(WORDS_PER_METADATA)))
	{
		new_metadata = (valloc_t*)((size_t*)(valloc) + space_required);
		new_metadata->offset = offset - space_required;
#ifndef NDEBUG
		new_metadata->magic_number = MAGIC_NUMBER;
#endif
	}
	else if (space_required < offset)
	{
		space_required = offset;
	}

	valloc->offset = -space_required;

	return (valloc + 1);
}

void VAFree(void *block)
{
	valloc_t *metadata = NULL;

	assert(NULL != block);

	metadata = (valloc_t *)(block) - 1;

#ifndef NDEBUG
	if (metadata->offset > 0)
	{
		fprintf(stderr, "Error: Invalid pointer, pointer already free\n");
		fprintf(stderr,"	in file %s, line: %d\n", __FILE__, __LINE__);

		return;
	}
	if (MAGIC_NUMBER != metadata->magic_number)
	{
		fprintf(stderr, "Error: Invalid pointer, pointer does not match \
pointer received by VAAlloc\n");
		fprintf(stderr,"	in file %s, line: %d\n", __FILE__, __LINE__);

		return;
	}
#endif

	metadata->offset *= -1;
}

size_t VALargestAvailable(valloc_t *valloc)
{
	long int offset = 0;
	long int largest_offset = 0;

	assert(NULL != valloc);

	offset = valloc->offset;

	while(offset)
	{
		while (DefragmentFreeSpace(valloc) > 0)
		{
			;
		}

		offset = valloc->offset;

		if ((offset - (long int)(WORDS_PER_METADATA)) > largest_offset)
		{
			largest_offset = offset - (long int)(WORDS_PER_METADATA);
		}

		valloc = (valloc_t*)((size_t*)(valloc) + labs(offset));
		offset = valloc->offset;
	}

	return (largest_offset * WORD);
}
