#include <stdlib.h>

#include "var_alloc.h"
#include "tests.h"
#include "utils_micah.h"

#define WORD (sizeof(size_t))

int InitNotEnough();

int InitEnough();

int AllocOne();

int AllocMore();

int AllocAll();

int LargestTest();

int FreeOne();

int FreeAll();

int AllocFreeAlloc();

int WordAligned();

int TwoAllocators();

int main()
{
	int errors = 0;

	RUNTEST(InitNotEnough);
	RUNTEST(InitEnough);
	RUNTEST(AllocOne);
	RUNTEST(AllocMore);
	RUNTEST(AllocAll);
	RUNTEST(LargestTest);
	RUNTEST(FreeOne);
	RUNTEST(FreeAll);
	RUNTEST(AllocFreeAlloc);
	RUNTEST(WordAligned);
	RUNTEST(TwoAllocators);

	return errors;
}

int InitNotEnough()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	size_t i = 0;
	size_t seg_sizes[] = { 10, 15, 0, 7, 16 };

	for (i = 0; i < ARR_SIZE(seg_sizes); ++i)
	{
		valloc_t *valloc = VAInit(memory, seg_sizes[i]);
		REQUIRE(NULL == valloc);
	}
	free(memory);
	return status;
}

int InitEnough()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	size_t i = 0;
	size_t seg_sizes[] = { 33, 50, 75, 200 };

	for (i = 0; i < ARR_SIZE(seg_sizes); ++i)
	{
		valloc_t *valloc = VAInit(memory, seg_sizes[i]);
		REQUIRE(NULL != valloc);
	}

	free(memory);
	return status;
}

int AllocOne()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	size_t i = 0;
	size_t seg_sizes[] = 			{ 33, 60, 40, 200 };
	size_t block_sizes[] = 			{ 1,  8, 8,  100 };
	size_t expected_free_space[] = 	{ 0,  8,  0,  48  };
	for (i = 0; i < ARR_SIZE(seg_sizes); ++i)
	{
		valloc_t *valloc = VAInit(memory, seg_sizes[i]);
		VAAlloc(valloc, block_sizes[i]);
		REQUIRE(expected_free_space[i] == VALargestAvailable(valloc));
	}

	free(memory);
	return status;
}

int AllocMore()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	valloc_t *valloc = VAInit(memory, 200);

	VAAlloc(valloc, 20);

	REQUIRE(128 == VALargestAvailable(valloc));

	VAAlloc(valloc, 20);
	REQUIRE(88 == VALargestAvailable(valloc));

	VAAlloc(valloc, 16);
	REQUIRE(56 == VALargestAvailable(valloc));

	free(memory);
	return status;
}

int AllocAll()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	valloc_t *valloc = VAInit(memory, 112);

	VAAlloc(valloc, 20);
	REQUIRE(40 == VALargestAvailable(valloc));

	VAAlloc(valloc, 8);
	REQUIRE(16 == VALargestAvailable(valloc));

	VAAlloc(valloc, 1);
	REQUIRE(0 == VALargestAvailable(valloc));

	free(memory);
	return status;
}

int LargestTest()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	valloc_t *valloc = VAInit(memory, 80);
	VAAlloc(valloc, 20);

	REQUIRE(8 == VALargestAvailable(valloc));

	free(memory);
	return status;
}

int FreeOne()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	valloc_t *valloc = VAInit(memory, 80);
	size_t *block1 = VAAlloc(valloc, 20);

	VAFree(block1);

	REQUIRE(48 == VALargestAvailable(valloc));

	free(memory);
	return status;
}

int FreeAll()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	valloc_t *valloc = VAInit(memory, 160);
	size_t* block1 = VAAlloc(valloc, 20);
	size_t* block2 = NULL;
	size_t* block3 = NULL;

	REQUIRE(88 == VALargestAvailable(valloc));

	block2 = VAAlloc(valloc, 16);
	REQUIRE(56 == VALargestAvailable(valloc));

	block3 = VAAlloc(valloc, 56);
	REQUIRE(0 == VALargestAvailable(valloc));

	VAFree(block1);
	REQUIRE(24 == VALargestAvailable(valloc));

	VAFree(block2);
	REQUIRE(56 == VALargestAvailable(valloc));

	VAFree(block3);
	REQUIRE(128 == VALargestAvailable(valloc));

	free(memory);
	return status;
}

int AllocFreeAlloc()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	valloc_t *valloc = VAInit(memory, 160);
	size_t *block1 = VAAlloc(valloc, 8);
	size_t *block2 = NULL;
	size_t *block3 = NULL;

	VAFree(block1);

	block2 = VAAlloc(valloc, 8);
	REQUIRE(104 == VALargestAvailable(valloc));

	block3 = VAAlloc(valloc, 8);

	VAFree(block2);
	REQUIRE(80 == VALargestAvailable(valloc));

	block1 = VAAlloc(valloc, 20);

	REQUIRE(40 == VALargestAvailable(valloc));

	VAFree(block3);

	REQUIRE(40 == VALargestAvailable(valloc));

	free(memory);
	return status;
}

int WordAligned()
{
	int status = SUCCESS;
	void *memory = malloc(200);
	valloc_t *valloc = VAInit(memory, 160);
	size_t *block1 = VAAlloc(valloc, 20);
	size_t *block2 = VAAlloc(valloc, 16);
	size_t *block3 = VAAlloc(valloc, 1);

	int is_aligned = (0 == (size_t)(block1) % WORD);
	REQUIRE(is_aligned);

	is_aligned = (0 == (size_t)(block2) % WORD);
	REQUIRE(is_aligned);

	is_aligned = (0 == (size_t)(block3) % WORD);
	REQUIRE(is_aligned);

	free(memory);
	return status;
}

int TwoAllocators()
{
	int status = SUCCESS;
	void *memory1 = malloc(200);
	void *memory2 = malloc(200);
	valloc_t *valloc1 = VAInit(memory1, 160);
	valloc_t *valloc2 = VAInit(memory2, 160);
	size_t* block1 = VAAlloc(valloc1, 20);
	size_t* block2 = NULL;
	size_t* block3 = NULL;
	size_t* block4 = VAAlloc(valloc2, 20);
	size_t* block5 = NULL;
	size_t* block6 = NULL;

	REQUIRE(88 == VALargestAvailable(valloc1));
	REQUIRE(88 == VALargestAvailable(valloc2));

	block2 = VAAlloc(valloc1, 16);
	block5 = VAAlloc(valloc2, 16);
	REQUIRE(56 == VALargestAvailable(valloc1));
	REQUIRE(56 == VALargestAvailable(valloc2));

	block3 = VAAlloc(valloc1, 56);
	block6 = VAAlloc(valloc2, 56);
	REQUIRE(0 == VALargestAvailable(valloc1));
	REQUIRE(0 == VALargestAvailable(valloc2));

	VAFree(block1);
	REQUIRE(24 == VALargestAvailable(valloc1));
	VAFree(block4);
	REQUIRE(24 == VALargestAvailable(valloc2));

	VAFree(block2);
	VAFree(block5);
	REQUIRE(56 == VALargestAvailable(valloc1));
	REQUIRE(56 == VALargestAvailable(valloc2));

	VAFree(block3);
	VAFree(block6);
	REQUIRE(128 == VALargestAvailable(valloc1));
	REQUIRE(128 == VALargestAvailable(valloc2));

	free(memory1);
	free(memory2);
	return status;
}
