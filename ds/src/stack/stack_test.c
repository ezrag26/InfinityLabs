#include <stdio.h>
#include <stddef.h>

#include "stack.h"
#include "utils.h"
#include "tests.h"

#define NEWLINE (printf("\n"))

int TestStackPush();
int TestStackPop();
int TestSortStack();

int main()
{

	size_t failures = 0;

	puts("Testing Stack...");
	TEST(TestStackPush(), "StackPush");
	TEST(TestStackPop(), "StackPop");
	TEST(TestSortStack(), "TestSortStack");

	PRNT_STATUS(failures);

	return (failures);
}

int TestStackPush()
{
	size_t failures = 0;
	const size_t capacity = 10;
	const size_t element_size = 4;
	mystack_t *test_stack = StackCreate(capacity, element_size);
	int num[] = {0, -2, 5, 9, 3, 7, 1, 8, 4, 7, 3, 2};
	size_t i = 0;

	REQUIRE(StackIsEmpty(test_stack), !=, 1, %d, %d);

	for (i = 0; i < 10; ++i)
	{
		StackPush(test_stack, &num[i]);
		REQUIRE(StackIsEmpty(test_stack), !=, 0, %d, %d);
	}

	StackDestroy(test_stack);

	return (failures);
}

int TestStackPop()
{
	size_t failures = 0;
	const size_t capacity = 10;
	const size_t element_size = 4;
	mystack_t *test_stack = StackCreate(capacity, element_size);
	int num[] = {0, -2, 5, 9, 3, 7, 1, 8, 4, 7, 3, 2};
	size_t i = 0;

	for (i = 0; i < 10; ++i)
	{
		StackPush(test_stack, &num[i]);
	}

	for (i = 0; i < 9; ++i)
	{
		StackPop(test_stack);
		REQUIRE(StackIsEmpty(test_stack), !=, 0, %d, %d);
	}

	StackPop(test_stack);
	REQUIRE(StackIsEmpty(test_stack), !=, 1, %d, %d);

	/*
		NEWLINE;

		StackPop(test_stack);
		printf("Popped Element %lu\n", i--);
		printf("Top element now: %d\n", *(int *)StackPeek(test_stack));
		printf("Total Stack Elements in Stack: %lu\n", StackCount(test_stack));

		NEWLINE;

		if (0 != StackIsEmpty(test_stack))
		{
			printf("Stack is Empty\n");
		}
		else
		{
			printf("Stack is not Empty\n");
		}

	*/

	StackDestroy(test_stack);

	return (failures);
}

int is_before(const void *data1, const void *data2, void *param)
{
	(void)param;
	return (*(int *)data1 < *(int *)data2);
}

int TestSortStack()
{
	size_t failures = 0;
	int data[] = {3, 2, 5, 1, 7, 5, 4, 1};
	int exp[] = {7, 5, 5, 4, 3, 2, 1, 1};
	int param = 0;
	const size_t capacity = 10;
	const size_t element_size = 4;
	mystack_t *stack = StackCreate(capacity, element_size);
	size_t i = 0;

	for (i = 0; i < ARR_SIZE(data); ++i)
	{
		StackPush(stack, &data[i]);
	}

	SortStack(stack, is_before, &param);

	for (i = 0; i < ARR_SIZE(data); ++i)
	{
		REQUIRE(*(int *)StackPeek(stack), !=, exp[i], %d, %d);
		StackPop(stack);
	}

	StackDestroy(stack);

	return (failures);
}
