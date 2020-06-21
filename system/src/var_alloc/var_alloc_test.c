#include <stdio.h>  /* printf 		*/
#include <stdlib.h> /* malloc, free */

#include "var_alloc.h"
#include "utils.h"
#include "tests.h"

int TestVAInitShortSegment();
int TestVAInitGoodSegment();
int TestVAAllocFull();
int TestVAAllocOver();
int TestVAAllocMore();
int TestVAAllocLargestAvail();
int TestVAFreeOne();

size_t failures = 0;

int main()
{
	puts("Testing Variable Alloc...");
	TEST(TestVAInitShortSegment(), "TestVAInitShortSegment");
	TEST(TestVAInitGoodSegment(), "TestVAInitGoodSegment");
	TEST(TestVAAllocFull(), "TestVAAllocFull");
	TEST(TestVAAllocOver(), "TestVAAllocOver");
	TEST(TestVAAllocMore(), "TestVAAllocMore");
	TEST(TestVAAllocLargestAvail(), "TestVAAllocLargestAvail");
	TEST(TestVAFreeOne(), "TestVAFreeOne");

	PRNT_STATUS(failures);

	return (failures);
}

int TestVAInitShortSegment()
{
	size_t failures = 0;
	size_t i = 0;
	size_t seg_size[] = {0, 1, 7, 8, 9, 15, 16, 17/*, 39, 40, 41*/};
	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	failures = 0;

	for (i = 0; i < ARR_SIZE(seg_size); ++i)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);

		REQUIRE((void *)init_ptrs[i], !=, NULL, %p, %p);

		free(buffer);
	}

	return (failures);
}

int TestVAInitGoodSegment()
{
	size_t failures = 0;
	size_t i = 0;
#ifdef NDEBUG
	size_t seg_size[] = {39, 40, 41, 100, 101, 102};
#else
	size_t seg_size[] = {40, 40, 41, 100, 101, 102};
#endif /* NDEBUG */
	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	failures = 0;

	for (i = 0; i < ARR_SIZE(seg_size); ++i)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);

		REQUIRE((void *)init_ptrs[i], ==, NULL, %p, %p);

		free(buffer);
	}

	return (failures);
}

int TestVAAllocFull()
{
	size_t failures = 0;
	size_t i = 0;
#ifdef NDEBUG
	size_t seg_size[] = {40, 49, 100, 101, 102};
#else
	size_t seg_size[] = {40, 41, 89, 90, 91};
#endif /* NDEBUG */
	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	int *block_ptrs[20] = {NULL};
	failures = 0;

	for (i = 0; i < ARR_SIZE(seg_size); ++i)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);

		block_ptrs[i] = VAAlloc(init_ptrs[i], VALargestAvailable(init_ptrs[i]));
		REQUIRE((void *)block_ptrs[i], ==, NULL, %p, %p);

		free(buffer);
	}

	return (failures);
}

int TestVAAllocOver()
{
	size_t failures = 0;
	size_t i = 0;
#ifdef NDEBUG
	size_t seg_size[] = {40, 49, 100, 101, 102};
	size_t block_size[] = {25, 33, 89, 89, 89};
#else
	size_t seg_size[] = {68, 86, 100, 101, 102};
#endif /* NDEBUG */

	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	int *block_ptrs[20] = {NULL};
	failures = 0;

	for (i = 1; i < ARR_SIZE(seg_size); ++i)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);
		block_ptrs[i] = VAAlloc(init_ptrs[i], VALargestAvailable(init_ptrs[i]) + 10);
		REQUIRE((void *)block_ptrs[i], !=, NULL, %p, %p);

		free(buffer);
	}

	return (failures);
}

int TestVAAllocMore()
{
	size_t failures = 0;
	size_t i = 0;
	size_t j = 0;
	size_t seg_size[] = {40, 49, 100, 101, 102};
	size_t block_size[] = {0, 0, 0, 8, 8, 16, 16, 16, 16, 8};
	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	int *block_ptrs[20] = {NULL};
	failures = 0;

	for (i = 1; i < ARR_SIZE(seg_size); ++i)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);

		for (j = 0; j < 2; ++j)
		{
			block_ptrs[i] = VAAlloc(init_ptrs[i], block_size[i]);
		}

		REQUIRE((void *)block_ptrs[i], ==, NULL, %p, %p);

		free(buffer);
	}

	return (failures);
}

int TestVAAllocLargestAvail()
{
	size_t failures = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
#ifdef NDEBUG
	size_t seg_size[] = {56, 65, 112};
	size_t block_size[] = {0, 1, 7, 8, 0};
	long int largest_avail[] = {32, 16, 0, 0, 0, 40, 24, 8, 0, 0, 88, 72, 56, 40, 32};
#else
	size_t seg_size[] = {56, 65, 112};
	size_t block_size[] = {0, 1, 7, 8, 0};
	long int largest_avail[] = {8, 0, 0, 0, 0, 16, 0, 0, 0, 0, 64, 40, 16, 0, 0};
#endif /* NDEBUG */
	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	failures = 0;

	for (i = 0; i < ARR_SIZE(seg_size); ++i)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);

		for (j = 0; j < ARR_SIZE(block_size); ++j, ++k)
		{
			VAAlloc(init_ptrs[i], block_size[j]);
			REQUIRE((long int)VALargestAvailable(init_ptrs[i]), !=, largest_avail[k], %lu, %lu);
		}

		free(buffer);
	}

	return (failures);
}

int TestVAFreeOne()
{
	size_t failures = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
#ifdef NDEBUG
	size_t seg_size[] = {40, 49, 100};
	size_t block_size[] = {0, 1, 7, 8, 9};
	long int largest_avail[] = {16, 8, 8};
#else
	size_t seg_size[] = {56, 65, 112};
	size_t block_size[] = {0, 1, 7, 8, 0};
	long int largest_avail[] = {8, 8, 8};
#endif /* NDEBUG */
	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	int *block_ptrs[20] = {NULL};
	failures = 0;

	for (i = 0; i < ARR_SIZE(seg_size); ++i, ++k)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);

		for (j = 0; j < ARR_SIZE(block_size); ++j)
		{
			block_ptrs[j] = VAAlloc(init_ptrs[i], block_size[j]);
		}

		VAFree(block_ptrs[1]);
		REQUIRE((long int)VALargestAvailable(init_ptrs[i]), !=, largest_avail[k], %lu, %lu);

		free(buffer);
	}

	return (failures);
}

int TestVAFreeAll()
{
	size_t failures = 0;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
#ifdef NDEBUG
	size_t seg_size[] = {40, 49, 100};
	size_t block_size[] = {0, 1, 7, 8, 9};
	long int largest_avail[] = {16, 8, 8};
#else
	size_t seg_size[] = {56, 65, 112};
	size_t block_size[] = {0, 1, 7, 8, 0};
	long int largest_avail[] = {8, 8, 8};
#endif /* NDEBUG */
	int *buffer = NULL;
	valloc_t *init_ptrs[20] = {NULL};
	int *block_ptrs[20] = {NULL};
	failures = 0;

	for (i = 0; i < ARR_SIZE(seg_size); ++i)
	{
		buffer = (int *)malloc(seg_size[i]);
		init_ptrs[i] = VAInit(buffer, seg_size[i]);

		for (j = 0; j < ARR_SIZE(block_size); ++j)
		{
			block_ptrs[j] = VAAlloc(init_ptrs[i], block_size[j]);
		}

		VAFree(block_ptrs[j]);
		REQUIRE((long int)VALargestAvailable(init_ptrs[i]), !=, largest_avail[k], %lu, %lu);
		free(buffer);
	}

	return (failures);
}
