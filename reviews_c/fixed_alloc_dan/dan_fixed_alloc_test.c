#include <stdio.h>
#include <stdlib.h>

#include "fixed_alloc.h"

int TestTooSmallSegSize();
int TestAllocThenSize();
int TestFullAllocFullFree();
int TestDiffSBlockSize();
int TestFullAllocFullFreeCalloc();
int TestTwoAllocator();

int main()
{
	int counter = 0;

	counter += TestTooSmallSegSize();
	counter += TestAllocThenSize();
	counter += TestFullAllocFullFree();
	counter += TestDiffSBlockSize();
	counter += TestFullAllocFullFreeCalloc();
	counter += TestTwoAllocator();

	return (counter);
}


int TestTooSmallSegSize()
{
	int counter = 0;

	size_t seg_size = 1;
	size_t block_size = 5;
	void *memory = NULL;

	falloc_t *result = NULL;

	memory = malloc(10);
	result = FAInit(memory, seg_size, block_size);

	if (NULL != result)
	{
		++counter;
		printf("TestTooSmallSegSize: not aprroved - line: %d\n", __LINE__);
	}

	free(memory);

	return (counter);
}


int TestAllocThenSize()
{
	int counter = 0;

	size_t suggested_seg_size = 0;
	size_t block_size = 5;
	size_t number_of_blocks = 10;

	size_t result_count_before_alloc = 0;
	size_t result_count_after_alloc = 0;

	void *memory = NULL;
	falloc_t *falloc = NULL;

	suggested_seg_size = FASuggestSize(number_of_blocks, block_size);

	memory = malloc(suggested_seg_size);
	falloc = FAInit(memory, suggested_seg_size, block_size);

	result_count_before_alloc = FACountFree(falloc);

	if (10 != result_count_before_alloc)
	{
		++counter;
		printf("TestAllocThenSize: not aprroved - line: %d\n", __LINE__);
	}

	if (NULL == falloc)
	{
		++counter;
		printf("TestAllocThenSize: not aprroved - line: %d\n", __LINE__);
	}

	FAAlloc(falloc);
	result_count_after_alloc = FACountFree(falloc);
	if (result_count_before_alloc - 1 != result_count_after_alloc)
	{
		++counter;
		printf("TestAllocThenSize: not aprroved - line: %d\n", __LINE__);
	}

	free(memory);

	return (counter);
}


int TestFullAllocFullFree()
{
	int counter = 0;
	size_t i = 0;

	size_t suggested_seg_size = 0;
	size_t block_size = 5;
	size_t number_of_blocks = 10;

	void *allocated_mem[10] = {NULL};
	void *memory = NULL;
	falloc_t *falloc = NULL;

	suggested_seg_size = FASuggestSize(number_of_blocks, block_size);

	memory = malloc(suggested_seg_size);
	falloc = FAInit(memory, suggested_seg_size, block_size);

	for (i = 0; i < 10; ++i)
	{
		if (10 - i != FACountFree(falloc))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, FACountFree(falloc));
		}
		allocated_mem[i] = FAAlloc(falloc);
	}

	for (i = 0; i < 10; ++i)
	{
		if (i != FACountFree(falloc))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, i);
		}
		FAFree(allocated_mem[i]);
	}

	FAAlloc(falloc);
	if (9 != FACountFree(falloc))
	{
		++counter;
		printf("TestFullAllocFullFree: not aprroved - line: %d\n", __LINE__);
	}

	free(memory);

	return (counter);
}


int TestFullAllocFullFreeCalloc()
{
	int counter = 0;
	size_t i = 0;

	size_t suggested_seg_size = 0;
	size_t block_size = 5;
	size_t number_of_blocks = 10;

	void *allocated_mem[10] = {NULL};
	void *memory = NULL;
	falloc_t *falloc = NULL;

	suggested_seg_size = FASuggestSize(number_of_blocks, block_size);

	memory = calloc(suggested_seg_size, 1);
	falloc = FAInit(memory, suggested_seg_size, block_size);

	for (i = 0; i < 10; ++i)
	{
		if (10 - i != FACountFree(falloc))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, FACountFree(falloc));
		}
		allocated_mem[i] = FAAlloc(falloc);
	}

	for (i = 0; i < 10; ++i)
	{
		if (i != FACountFree(falloc))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, i);
		}
		FAFree(allocated_mem[i]);
	}

	FAAlloc(falloc);
	if (9 != FACountFree(falloc))
	{
		++counter;
		printf("TestFullAllocFullFree: not aprroved - line: %d\n", __LINE__);
	}

	free(memory);

	return (counter);
}


int TestDiffSBlockSize()
{
	int counter = 0;
	size_t word_size = sizeof(size_t);
	size_t i = 0;

	size_t suggested_seg_size = 0;
	size_t block_size[3] = {0};
	size_t number_of_blocks = 10;

	void *allocated_mem = NULL;
	void *memory = NULL;
	falloc_t *falloc = NULL;

	for (i = 0; i < 3; ++i)
	{
		block_size[i] = word_size - 1 + i;
	}

	for (i = 0; i < 3; ++i)
	{
		suggested_seg_size = FASuggestSize(number_of_blocks, block_size[i]);
		memory = malloc(suggested_seg_size);

		falloc = FAInit(memory, suggested_seg_size, block_size[i]);
		if (10 != FACountFree(falloc))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d\n", __LINE__);
		}

		allocated_mem = FAAlloc(falloc);
		if (0 != (size_t)allocated_mem % word_size)
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d\n", __LINE__);
		}

		free(memory);
	}

	return (counter);
}


int TestTwoAllocator()
{
	int counter = 0;
	size_t i = 0;

	size_t suggested_seg_size = 0;
	size_t block_size = 5;
	size_t number_of_blocks = 10;

	void *allocated_mem1[10] = {NULL};
	void *allocated_mem2[10] = {NULL};
	void *memory1 = NULL;
	void *memory2 = NULL;
	falloc_t *falloc1 = NULL;
	falloc_t *falloc2 = NULL;

	suggested_seg_size = FASuggestSize(number_of_blocks, block_size);

	memory1 = malloc(suggested_seg_size);
	memory2 = malloc(suggested_seg_size);
	falloc1 = FAInit(memory1, suggested_seg_size, block_size);
	falloc2 = FAInit(memory2, suggested_seg_size, block_size);

	for (i = 0; i < 5; ++i)
	{
		if (10 - i != FACountFree(falloc1))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, FACountFree(falloc1));
		}
		allocated_mem1[i] = FAAlloc(falloc1);
	}

	for (i = 0; i < 3; ++i)
	{
		if (10 - i != FACountFree(falloc2))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, i);
		}
		allocated_mem2[i] = FAAlloc(falloc2);
	}

	for (i = 0; i < 3; ++i)
	{
		if (5 + i != FACountFree(falloc1))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, i);
		}
		FAFree(allocated_mem1[i]);
	}

	for (i = 0; i < 3; ++i)
	{
		if (7 + i != FACountFree(falloc2))
		{
			++counter;
			printf("TestFullAllocFullFree: not aprroved - line: %d  i:%lu\n",
				   __LINE__, i);
		}
		FAFree(allocated_mem2[i]);
	}

	FAAlloc(falloc1);
	if (7 != FACountFree(falloc1))
	{
		++counter;
		printf("TestFullAllocFullFree: not aprroved - line: %d\n", __LINE__);
	}

	FAAlloc(falloc2);
	if (9 != FACountFree(falloc2))
	{
		++counter;
		printf("TestFullAllocFullFree: not aprroved - line: %d\n", __LINE__);
	}

	free(memory1);
	free(memory2);

	return (counter);
}
