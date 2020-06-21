#include <stdio.h>  /* printf 		*/
#include <stdlib.h> /* malloc, free */


#include "fixed_alloc.h"
#include "utils.h"
#include "tests.h"

int TestSuggestSize();
int TestFATooShortSegSize();
int TestFACountFreeOnInit();
int TestFACountFree();
int TestFAFree();
int TestFAAllocAfterFree();
int TestFAWordAligned();

size_t failures = 0;

int main()
{
	puts("Testing Fixed Alloc...");
	TEST(TestSuggestSize(), "TestSuggestSize");
	TEST(TestFATooShortSegSize(), "TestFATooShortSegSize");
	TEST(TestFACountFreeOnInit(), "TestFACountFreeOnInit");
	TEST(TestFACountFree(), "TestFACountFree");
	TEST(TestFAFree(), "TestFAFree");
	TEST(TestFAAllocAfterFree(), "TestFAAllocAfterFree");
	TEST(TestFAWordAligned(), "TestFAWordAligned");

	PRNT_STATUS(failures);
	return (0);
}

int TestSuggestSize()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {0, 1, 5, 3, 2, 8, 3, 5};
	size_t block_size[] = {4, 0, 1, 8, 15, 16, 17, 20};
	size_t exp_size[] = {8, 16, 88, 56, 56, 200, 104, 168};
	size_t suggested_size = 0;
	size_t i = 0;

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		suggested_size = FASuggestSize(num_of_blocks[i], block_size[i]);
		REQUIRE(suggested_size, !=, exp_size[i], %lu, %lu);
	}

	return (failures);
}

int TestFATooShortSegSize()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {0, 4};
	size_t block_size[] = {4, 0};
	size_t i = 0;
	size_t seg_size = 0;
	int *buffer = NULL;
	falloc_t *falloc = NULL;

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		seg_size = FASuggestSize(num_of_blocks[i], block_size[i]);

		buffer = (int *)malloc(seg_size);
		falloc = FAInit(buffer, seg_size, block_size[i]);

		REQUIRE((void *)falloc, !=, NULL, %p, %p);

		free(buffer);
	}

	return (failures);
}

int TestFAZeroInitialized()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {0, 4};
	size_t block_size[] = {4, 0};
	size_t i = 0;
	size_t seg_size = 0;
	int *buffer = NULL;
	falloc_t *falloc = NULL;

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		seg_size = FASuggestSize(num_of_blocks[i], block_size[i]);

		buffer = (int *)calloc(num_of_blocks[i], seg_size);
		falloc = FAInit(buffer, seg_size, block_size[i]);

		REQUIRE((void *)falloc, !=, NULL, %p, %p);

		free(buffer);
	}

	return (failures);
}

int TestFACountFreeOnInit()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {5, 3, 2, 8, 3, 5};
	size_t block_size[] = {1, 8, 15, 16, 17, 20};
	size_t i = 0;
	size_t seg_size = 0;
	int *buffer = NULL;
	falloc_t *falloc = NULL;

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		seg_size = FASuggestSize(num_of_blocks[i], block_size[i]);

		buffer = (int *)malloc(seg_size);
		falloc = FAInit(buffer, seg_size, block_size[i]);

		REQUIRE(FACountFree(falloc), !=, num_of_blocks[i], %lu, %lu);

		free(buffer);
	}

	return (failures);
}

int TestFACountFree()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {5, 3, 2, 8, 3, 5};
	size_t block_size[] = {1, 8, 15, 16, 17, 20};
	size_t i = 0;
	size_t j = 0;
	size_t seg_size = 0;
	int *buffer = NULL;
	falloc_t *falloc = NULL;

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		seg_size = FASuggestSize(num_of_blocks[i], block_size[i]);

		buffer = (int *)malloc(seg_size);
		falloc = FAInit(buffer, seg_size, block_size[i]);
		for (j = 0; j < num_of_blocks[i]; ++j)
		{
			FAAlloc(falloc);
			REQUIRE(FACountFree(falloc), !=, (num_of_blocks[i] - j - 1), %lu, %lu);
		}
		free(buffer);
	}

	return (failures);
}

int TestFAFree()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {5, 3, 2, 8, 3, 5};
	size_t block_size[] = {1, 8, 15, 16, 17, 20};
	size_t i = 0;
	size_t k = 0;
	size_t j = 0;
	size_t seg_size = 0;
	int *buffer = NULL;
	falloc_t *falloc = NULL;
	int *block_ptrs[10] = {0};

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		seg_size = FASuggestSize(num_of_blocks[i], block_size[i]);

		buffer = (int *)malloc(seg_size);
		falloc = FAInit(buffer, seg_size, block_size[i]);

		for (k = 0; k < num_of_blocks[i]; ++k)
		{
			block_ptrs[k] = FAAlloc(falloc);
		}

		for (j = 0; j < num_of_blocks[i]; ++j)
		{
			FAFree(block_ptrs[j]);
			REQUIRE(FACountFree(falloc), !=, (j + 1), %lu, %lu);
		}
		free(buffer);
	}

	return (failures);
}

int TestFAAllocAfterFree()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {5, 3, 2, 8, 3, 5};
	size_t block_size[] = {1, 8, 15, 16, 17, 20};
	size_t i = 0;
	size_t k = 0;
	size_t j = 0;
	size_t seg_size = 0;
	int *buffer = NULL;
	falloc_t *falloc = NULL;
	int *block_ptrs[10] = {0};

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		seg_size = FASuggestSize(num_of_blocks[i], block_size[i]);

		buffer = (int *)malloc(seg_size);
		falloc = FAInit(buffer, seg_size, block_size[i]);

		for (k = 0; k < num_of_blocks[i]; ++k)
		{
			block_ptrs[k] = FAAlloc(falloc);
		}

		for (j = 0; j < num_of_blocks[i]; ++j)
		{
			FAFree(block_ptrs[j]);
			REQUIRE(FACountFree(falloc), !=, (j + 1), %lu, %lu);
		}

		for (k = 0; k < num_of_blocks[i]; ++k)
		{
			block_ptrs[k] = FAAlloc(falloc);
		}

		for (j = 0; j < num_of_blocks[i]; ++j)
		{
			FAFree(block_ptrs[j]);
			REQUIRE(FACountFree(falloc), !=, (j + 1), %lu, %lu);

		}

		free(buffer);
	}

	return (failures);
}

int TestFAWordAligned()
{
	size_t failures = 0;
	size_t num_of_blocks[] = {5, 3, 2, 8, 3, 5};
	size_t block_size[] = {1, 8, 15, 16, 17, 20};
	size_t i = 0;
	size_t seg_size = 0;
	int *buffer = NULL;
	falloc_t *falloc = NULL;
	void *block_ptrs[10] = {0};

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		seg_size = FASuggestSize(num_of_blocks[i], block_size[i]);

		buffer = (int *)malloc(seg_size);
		falloc = FAInit(buffer, seg_size, block_size[i]);

		block_ptrs[i] = FAAlloc(falloc);
		REQUIRE((int)((size_t)block_ptrs[i] % sizeof(size_t)), !=, 0, %d, %d);

		free(buffer);
	}

	return (failures);
}
