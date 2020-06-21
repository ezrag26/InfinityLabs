#include <stdio.h>  /* printf 		*/
#include <stdlib.h> /* malloc, free */


#include "fixed_alloc.h"
#include "utils.h"

ret_status_t TestSuggestSize();
ret_status_t TestFATooShortSegSize();
ret_status_t TestFACountFreeOnInit();
ret_status_t TestFACountFree();
ret_status_t TestFAFree();
ret_status_t TestFAAllocAfterFree();
ret_status_t TestFAWordAligned();

size_t failures = 0;

int main()
{
	puts("Testing Fixed Alloc...");
	TEST(TestSuggestSize(), "Message");
	TEST(TestFATooShortSegSize(), "Message");
	TEST(TestFACountFreeOnInit(), "Message");
	TEST(TestFACountFree(), "Message");
	TEST(TestFAFree(), "Message");
	TEST(TestFAAllocAfterFree(), "Message");
	TEST(TestFAWordAligned(), "Message");

	PRNT_STATUS(failures);
}

ret_status_t TestSuggestSize()
{
	size_t num_of_blocks[] = {0, 1, 5, 3, 2, 8, 3, 5};
	size_t block_size[] = {4, 0, 1, 8, 15, 16, 17, 20};
	size_t exp_size[] = {8, 16, 88, 56, 56, 200, 104, 168};
	size_t suggested_size = 0;
	size_t i = 0;

	for (i = 0; i < ARR_SIZE(num_of_blocks); ++i)
	{
		suggested_size = FASuggestSize(num_of_blocks[i], block_size[i]);
		REQUIRE(suggested_size, exp_size[i]);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}

ret_status_t TestFATooShortSegSize()
{
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

		REQUIRE(falloc, NULL);

		free(buffer);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}

ret_status_t TestFAZeroInitialized()
{
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

		REQUIRE(falloc, NULL);

		free(buffer);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}

ret_status_t TestFACountFreeOnInit()
{
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

		REQUIRE(FACountFree(falloc), num_of_blocks[i]);

		free(buffer);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}

ret_status_t TestFACountFree()
{
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
			REQUIRE(FACountFree(falloc), (num_of_blocks[i] - j - 1));
		}
		free(buffer);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}

ret_status_t TestFAFree()
{
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
			REQUIRE(FACountFree(falloc), (j + 1));
		}
		free(buffer);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}

ret_status_t TestFAAllocAfterFree()
{
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
			REQUIRE(FACountFree(falloc), (j + 1));
		}

		for (k = 0; k < num_of_blocks[i]; ++k)
		{
			block_ptrs[k] = FAAlloc(falloc);
		}

		for (j = 0; j < num_of_blocks[i]; ++j)
		{
			FAFree(block_ptrs[j]);
			REQUIRE(FACountFree(falloc), (j + 1));

		}

		free(buffer);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}

ret_status_t TestFAWordAligned()
{
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
		REQUIRE((int)((size_t)block_ptrs[i] % sizeof(size_t)), 0);

		free(buffer);
	}

	if (0 == failures)
	{
		return (SUCCESS);
	}

	return (FAILURE);
}
