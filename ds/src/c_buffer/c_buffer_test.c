#include <stdio.h> 	/* printf  */
#include <unistd.h> /* ssize_t */
#include <stddef.h> /* size_t  */

#include "c_buffer.h"
#include "tests.h"

size_t failures = 0;

int TestCBufferCreate();
int TestCBufferWrite();
int TestCBufferEmptyRead();
int TestCBufferRead();
int TestCBufferCapacity();
int TestCBufferFreeSpace();
int TestCBufferIsEmptyWriteOnly();
int TestCBufferIsEmptyReadOnly();
int TestCBufferIsEmptyBoth();

int main()
{
	size_t failures = 0;

	puts("Testing Circular Buffer...");
	TEST(TestCBufferCreate(), "CBufferCreate");
	TEST(TestCBufferWrite(), "CBufferWrite");
	TEST(TestCBufferEmptyRead(), "CBufferEmptyRead");
	TEST(TestCBufferRead(), "CBufferRead");
	TEST(TestCBufferCapacity(), "CBufferCapacity");
	TEST(TestCBufferFreeSpace(), "CBufferFreeSpace");
	TEST(TestCBufferIsEmptyWriteOnly(), "CBufferIsEmptyWriteOnly");
	TEST(TestCBufferIsEmptyReadOnly(), "CBufferIsEmptyReadOnly");
/*	TEST(TestCBufferIsEmptyBoth(), "Testing CBufferIsEmptyBoth...");*/

	PRNT_STATUS(failures);

	return (failures);
}

int TestCBufferCreate()
{
	size_t capacity = 40;

	c_buffer_t *c_buffer = NULL;


	c_buffer = CBufferCreate(capacity);


	CBufferDestroy(c_buffer);

	return (failures);
}

int TestCBufferWrite()
{
	size_t capacity = 100;

	size_t i = 0;

	char buffer[] = "123457890abcdefghijkmnopqrstuvwxyz?.<!@#$%^&*()";
	size_t to_write[] = {-1, 0, 1, 2, 99, 100, 101};
	ssize_t exp_write_return[] = {100, 0, 1, 2, 99, 100, 100};
	ssize_t write_return = 0;

	c_buffer_t *c_buffer = NULL;


	for (i = 0; i < ARR_SIZE(to_write); ++i)
	{
		c_buffer = CBufferCreate(capacity);
		write_return = CBufferWrite(c_buffer, &buffer, to_write[i]);

		if (write_return != exp_write_return[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %lu\n", exp_write_return[i]);
			printf("\t\tReturned: %lu\n", write_return);
			++failures;
		}
		CBufferDestroy(c_buffer);
	}

	return (failures);
}

int TestCBufferEmptyRead()
{
	size_t capacity = 40;

	size_t i = 0;

	int buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ssize_t exp_read_return[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
/*	size_t to_write = 1;*/
/*	ssize_t write_return = 0;*/

	size_t to_read = 4;
	ssize_t read_return = 0;

	c_buffer_t *c_buffer = CBufferCreate(capacity);


	for (i = 0; i < ARR_SIZE(buffer); ++i)
	{
		read_return = CBufferRead(c_buffer, &buffer[i], to_read);

		if (read_return != exp_read_return[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %lu\n", exp_read_return[i]);
			printf("\t\tReturned: %lu\n", read_return);
			++failures;
		}
	}

	CBufferDestroy(c_buffer);

	return (failures);
}

int TestCBufferRead()
{
	size_t capacity = 40;

	size_t i = 0;

	int write_buffer[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	size_t to_write = 4;

	int read_buffer[10] = {0};
	size_t to_read = 24;
	ssize_t exp_read_return[] = {24, 16, -1, -1, -1, -1, -1, -1, -1, -1};
	ssize_t read_return = 0;

	c_buffer_t *c_buffer = CBufferCreate(capacity);


	for (i = 0; i < ARR_SIZE(write_buffer); ++i)
	{
		CBufferWrite(c_buffer, &write_buffer[i], to_write);
	}


	for (i = 0; i < ARR_SIZE(read_buffer); ++i)
	{
		read_return = CBufferRead(c_buffer, &read_buffer[i * (to_read / sizeof(int))], to_read);

		if (read_return != exp_read_return[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %lu\n", exp_read_return[i]);
			printf("\t\tReturned: %lu\n", read_return);
			++failures;
		}

		if (read_buffer[i] != write_buffer[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tWrite Data: %d\n", write_buffer[i]);
			printf("\t\tRead Data: %d\n", read_buffer[i]);
			++failures;
		}
	}

	CBufferDestroy(c_buffer);

	return (failures);
}

int TestCBufferCapacity()
{
	size_t capacity[] = {40, 15, 1, 0, -1};
	size_t i = 0;


	for (i = 0; i < ARR_SIZE(capacity); ++i)
	{
		c_buffer_t *c_buffer = CBufferCreate(capacity[i]);
		if (CBufferCapacity(c_buffer) != capacity[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %lu\n", capacity[i]);
			printf("\t\tReturned: %lu\n", CBufferCapacity(c_buffer));
			++failures;
		}
		CBufferDestroy(c_buffer);
	}

	return (failures);
}

int TestCBufferFreeSpace()
{
	size_t capacity = 100;
	size_t i = 0;

	int write_buffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	size_t to_write[] = {15, 12, 6, 7, 13, 3, 5, 26, 7, 3, 42};
	size_t exp_free_space[] = {85, 73, 67, 60, 47, 44, 39, 13, 6, 3, 0};

	int read_buffer[11] = {0};
	size_t to_read[] = {4, 8, 2, 6, 10, 15, 20, 15, 14, 12, 25};
	size_t exp_free_space2[] = {4, 12, 14, 20, 30, 45, 65, 80, 94, 100, 100};

	size_t exp_free_space3[] = {89, 85, 81, 80, 77, 89, 100, 89, 96, 100, 83};

	c_buffer_t *c_buffer = CBufferCreate(capacity);


	/* write alone */
	for (i = 0; i < ARR_SIZE(write_buffer); ++i)
	{
		CBufferWrite(c_buffer, write_buffer, to_write[i]);

		if (CBufferFreeSpace(c_buffer) != exp_free_space[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %lu\n", exp_free_space[i]);
			printf("\t\tReturned: %lu\n", CBufferFreeSpace(c_buffer));
			++failures;
		}
	}

	/* read alone */
	for (i = 0; i < ARR_SIZE(read_buffer); ++i)
	{
		CBufferRead(c_buffer, read_buffer, to_read[i]);

		if (CBufferFreeSpace(c_buffer) != exp_free_space2[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %lu\n", exp_free_space2[i]);
			printf("\t\tReturned: %lu\n", CBufferFreeSpace(c_buffer));
			++failures;
		}
	}

	/* both write and read */
	for (i = 0; i < ARR_SIZE(write_buffer); ++i)
	{
		CBufferWrite(c_buffer, write_buffer, to_write[i]);
		CBufferRead(c_buffer, read_buffer, to_read[i]);
		if (CBufferFreeSpace(c_buffer) != exp_free_space3[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %lu\n", exp_free_space3[i]);
			printf("\t\tReturned: %lu\n", CBufferFreeSpace(c_buffer));
			++failures;
		}
	}

	CBufferDestroy(c_buffer);

	return (failures);
}

int TestCBufferIsEmptyWriteOnly()
{
	size_t capacity = 100;
	size_t i = 0;

	int write_buffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	size_t to_write[] = {0, 12, 100, 7, 13, 3, 5, 26, 7, 3, 42};
	int exp_is_empty[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	c_buffer_t *c_buffer = CBufferCreate(capacity);


	for (i = 0; i < ARR_SIZE(write_buffer); ++i)
	{
		CBufferWrite(c_buffer, write_buffer, to_write[i]);

		if (CBufferIsEmpty(c_buffer) != exp_is_empty[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %d\n", exp_is_empty[i]);
			printf("\t\tReturned: %d\n", CBufferIsEmpty(c_buffer));
			++failures;
		}
	}

	CBufferDestroy(c_buffer);

	return (failures);
}

int TestCBufferIsEmptyReadOnly()
{
	size_t capacity = 100;
	size_t i = 0;

	int read_buffer[11] = {0};
	size_t to_read[] = {4, 8, 2, 6, 10, 15, 20, 15, 120, 12, 25};
	int exp_is_empty[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	c_buffer_t *c_buffer = CBufferCreate(capacity);


	for (i = 0; i < ARR_SIZE(read_buffer); ++i)
	{
		CBufferRead(c_buffer, read_buffer, to_read[i]);

		if (CBufferIsEmpty(c_buffer) != exp_is_empty[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %d\n", exp_is_empty[i]);
			printf("\t\tReturned: %d\n", CBufferIsEmpty(c_buffer));
			++failures;
		}
	}

	CBufferDestroy(c_buffer);

	return (failures);
}

int TestCBufferIsEmptyBoth()
{
	size_t capacity = 100;
	size_t i = 0;

	int write_buffer[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	size_t to_write[] = {101, 100, 99, 100, 100, -1, 0, 75, 1};

	int read_buffer[9] = {0};
	size_t to_read[] = {101, 100, 98, -1, 50, 101, 100, 25, 120};

	int exp_is_empty[] = {1, 1, 0, 1, 0, 1, 1, 0, 1};

	c_buffer_t *c_buffer = CBufferCreate(capacity);


	for (i = 0; i < ARR_SIZE(write_buffer); ++i)
	{
		CBufferWrite(c_buffer, write_buffer, to_write[i]);
		CBufferRead(c_buffer, read_buffer, to_read[i]);

		if (CBufferIsEmpty(c_buffer) != exp_is_empty[i])
		{
			printf("\tFAILED at index %lu\n", i);
			printf("\t\tExpected: %d\n", exp_is_empty[i]);
			printf("\t\tReturned: %d\n", CBufferIsEmpty(c_buffer));
			++failures;
		}
	}

	CBufferDestroy(c_buffer);

	return (failures);
}
