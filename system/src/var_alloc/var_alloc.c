/*******************************************************************************
 * Date: 		24/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Dan
 * Satus: 		S
 ******************************************************************************/
#include <assert.h> /* assert  */
#include <stdio.h>  /* fprintf */

#include "var_alloc.h"

#define FLIP_SIGN(x) (-x)
#define ABS(x) (x < 0 ? FLIP_SIGN(x) : x)

struct variable_alloc
{
	long int size;
#ifndef NDEBUG
	size_t magic_number;
#endif /* NDEBUG */
};

static const size_t STRUCT_SIZE = sizeof(valloc_t);
static const size_t WORD_SIZE = sizeof(size_t);
static const size_t DEADBEEF = 0xDEADBEEF;

/*----------------------------- Helper Functions -----------------------------*/

static size_t CalculateOffset(size_t size)
{
	return (size % WORD_SIZE);
}

static valloc_t *GoToNextMeta(valloc_t *current_meta)
{
	return ((valloc_t *)((char *)(current_meta)
						+ ABS(current_meta->size)));
}

static int Defrag(valloc_t *current_meta)
{
	valloc_t *next_meta_data = GoToNextMeta(current_meta);

	assert(NULL != current_meta);

	if (current_meta->size > 0 && next_meta_data->size > 0)
	{
		return (current_meta->size += next_meta_data->size);
	}

	return (1);
}

static size_t AlignBlock(size_t block_size)
{
	return (block_size
					+ ((WORD_SIZE - CalculateOffset(block_size)) % WORD_SIZE)
					+ STRUCT_SIZE);
}

static size_t SegSizeIsLargeEnough(size_t seg_size)
{
	return (seg_size >= ((2 * STRUCT_SIZE) + WORD_SIZE) ? 1 : 0);
}

static valloc_t *FindNextPossibleAlloc(valloc_t *valloc, size_t block_size)
{
	valloc_t *current_meta = valloc;

	assert(NULL != valloc);

	/* block is already allocated */
	while (0 > current_meta->size)
	{
		current_meta = GoToNextMeta(current_meta);
	}

	/* not enough room to allocate block */
	while (current_meta->size < (long int)block_size)
	{
		/* reached the end, there wasn't enough space to allocate */
		if ((long int)STRUCT_SIZE >= current_meta->size)
		{
			return (NULL);
		}

		/* Nothing to Defrag */
		if (1 == Defrag(current_meta))
		{
			current_meta = GoToNextMeta(current_meta);
		}
	}

	return (current_meta);
}

static valloc_t *AllocWithNewMeta(valloc_t *current_meta, size_t block_size)
{
	valloc_t *new_meta = (valloc_t *)((char *)(current_meta)
					+ block_size);

	assert(NULL != current_meta);

	new_meta->size = (long int)(current_meta->size
						  - (long int)block_size);

	current_meta->size = (long int)FLIP_SIGN(block_size);

	return (current_meta);
}

static valloc_t *AllocWithoutNewMeta(valloc_t *current_meta, size_t block_size)
{
	current_meta->size = (long int)FLIP_SIGN(block_size);

	return (current_meta);
}

/*----------------------------- User's Functions -----------------------------*/

/*********************************** VAInit ***********************************/

valloc_t *VAInit(void *memory, size_t seg_size)
{
 	valloc_t *current_meta = (valloc_t *)memory;
	size_t current_seg_size = seg_size;

	current_seg_size -= CalculateOffset(current_seg_size);

 	if (!SegSizeIsLargeEnough(current_seg_size))
 	{
 		return (NULL);
 	}

 	/* first meta_data's size */
 	current_meta->size = (long int)(current_seg_size - STRUCT_SIZE);

 	/* NULL meta_data */
 	current_meta = GoToNextMeta(current_meta);
 	current_meta->size = 0;

 	return ((valloc_t *)memory);
}

/********************************** VAAlloc ***********************************/

void *VAAlloc(valloc_t *valloc, size_t block_size)
{
	const size_t aligned_block = AlignBlock(block_size);
	valloc_t *current_meta = NULL;

	assert(NULL != valloc);

	current_meta = FindNextPossibleAlloc(valloc, aligned_block);
	if (NULL == current_meta)
	{
		return (NULL);
	}

	/* More than enough space to allocate */
	if (current_meta->size >= (long int)(aligned_block + STRUCT_SIZE))
	{
		current_meta = AllocWithNewMeta(current_meta, aligned_block);

    }/* enough room to allocate without new meta_data */
	else if (current_meta->size >= (long int)aligned_block)
    {
		current_meta = AllocWithoutNewMeta(current_meta, aligned_block);
    }

#ifndef NDEBUG
	current_meta->magic_number = DEADBEEF;
#endif /* NDEBUG */

	return (current_meta + 1);
}

/*********************************** VAFree ***********************************/

void VAFree(void *block)
{
	valloc_t *block_meta_data = NULL;

	assert(NULL != block);

	block_meta_data = (valloc_t *)((char *)block - STRUCT_SIZE);

#ifndef NDEBUG
	if (DEADBEEF != block_meta_data->magic_number)
	{
		fprintf(stderr, "Bad pointer\n");
	}
#endif /* NDEBUG */

	block_meta_data->size = FLIP_SIGN(block_meta_data->size);
}

/***************************** VALargestAvailable *****************************/

size_t VALargestAvailable(valloc_t *valloc)
{
	valloc_t *current_meta = NULL;
	long int largest_avail = 0;

	assert(NULL != valloc);

	current_meta = valloc;

	while (0 != current_meta->size)
	{
		if (largest_avail < (current_meta->size - (long int)STRUCT_SIZE))
		{
			largest_avail = current_meta->size - (long int)STRUCT_SIZE;
		}
		if (1 == Defrag(current_meta))
		{
			current_meta = GoToNextMeta(current_meta);
		}
	}

	return (largest_avail);
}
