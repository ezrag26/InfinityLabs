#include <stdio.h>	/* printf */
#include <stddef.h> /* size_t */

#include "dynamic_vector.h"
#include "utils.h"
#include "tests.h"

#define NEWLINE (printf("\n"))

int TestCreateAndDestroy();
int TestPush();
int TestReserve();
int TestPop();
int TestGetElemAddress();

int main()
{
	size_t failures = 0;

	puts("Testing Dynamic Vector...");
	TEST(TestCreateAndDestroy(), "DVCreateAndDestroy");
/*	TEST(TestPush(), "DVPush");
	TEST(TestReserve(), "DVReserve");
	TEST(TestPop(), "DVPop");
	TEST(TestGetElemAddress(), "DVGetElemAddress");*/

	PRNT_STATUS(failures);

	return (failures);
}

int TestCreateAndDestroy()
{
	size_t capacity = 10;
	size_t element_size = 4;
	size_t failures = 0;

	dv_t *dynamic_vector = DVCreate(capacity, element_size);

	if (DVCapacity(dynamic_vector) != capacity)
	{
		printf("\tDVCreate **FAILED** on capacity\n");
		++failures;
	}

	if (DVSize(dynamic_vector) != capacity)
	{
		printf("\tDVCreate **FAILED** on size\n");
		++failures;
	}

	DVDestroy(dynamic_vector);

	return (failures);
}

int TestPush()
{
	size_t capacity = 10;
	size_t element_size = 4;
	int nums[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28};
	size_t i = 0;
	size_t failures = 0;

	dv_t *dynamic_vector = DVCreate(capacity, element_size);

	for (i = 0; i < ARR_SIZE(nums); ++i)
	{
		DVPush(dynamic_vector, &nums[i]);

		REQUIRE(DVSize(dynamic_vector), !=, (i + 1), %lu, %lu);

		if (DVCapacity(dynamic_vector) != capacity && DVSize(dynamic_vector) > capacity)
		{
			capacity *= 1.5;

			if (DVCapacity(dynamic_vector) != capacity)
			{
				NEWLINE;
				printf("\tDVPush **FAILED** at index %lu\n", i);
				++failures;
			}
		}
	}

	NEWLINE;

	DVDestroy(dynamic_vector);

	return (failures);
}

int TestReserve()
{
	size_t capacity = 10;
	size_t element_size = 4;
	int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	size_t i = 0;
	size_t failures = 0;

	dv_t *dynamic_vector = DVCreate(capacity, element_size);

	DVReserve(dynamic_vector, 10);

	for (i = 0; i < ARR_SIZE(nums); ++i)
	{
		REQUIRE(DVSize(dynamic_vector), !=, 0ul, %lu, %lu);

		if (DVCapacity(dynamic_vector) != capacity + 10)
		{
			NEWLINE;
			printf("\tDVReserve **FAILED** at index %lu\n", i);
			++failures;
		}
	}

	NEWLINE;

	DVDestroy(dynamic_vector);

	return (failures);
}

int TestPop()
{
	size_t capacity = 10;
	size_t element_size = 4;
	int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	size_t i = 0;
	size_t failures = 0;

	dv_t *dynamic_vector = DVCreate(capacity, element_size);

	for (i = 0; i < ARR_SIZE(nums); ++i)
	{
		DVPush(dynamic_vector, &nums[i]);
	}

	for (i = 0; i < ARR_SIZE(nums); ++i)
	{
		DVPop(dynamic_vector);

		REQUIRE(DVSize(dynamic_vector), !=, ARR_SIZE(nums) - i - 1, %lu, %lu);
	}

	NEWLINE;

	DVDestroy(dynamic_vector);

	return (failures);
}

int TestGetElemAddress()
{
	size_t capacity = 10;
	size_t element_size = 4;
	int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	size_t i = 0;
	size_t failures = 0;

	dv_t *dynamic_vector = DVCreate(capacity, element_size);

	for (i = 0; i < ARR_SIZE(nums); ++i)
	{
		DVPush(dynamic_vector, &nums[i]);
	}

	for (i = 0; i < ARR_SIZE(nums); ++i)
	{
		REQUIRE(*(int *)DVGetElemAddress(dynamic_vector, i), !=, nums[i], %d, %d);
	}

	for (i = ARR_SIZE(nums); i > 0; --i)
	{
		DVPop(dynamic_vector);

		REQUIRE(*(int *)DVGetElemAddress(dynamic_vector, i - 1), !=, nums[i - 1], %d, %d);
	}

	NEWLINE;

	DVDestroy(dynamic_vector);

	return (failures);
}
