/*******************************************************************************
 *	Developer: Ezra Gordon
 *	Reviewer: Dan
 *	Status:
 *	Date: 5/9/2019
 ******************************************************************************/

#include <stdio.h> /* printf */

#include "queue.h"
#include "utils.h"
#include "tests.h"

#define NUM_OF_NODES (3)

int TestQueueEnqueue();
int TestQueueDequeue();
int TestQueueSize();
int TestQueueAppend();

size_t failures = 0;
int data[] = {1, 2, 3};
int data2[] = {4, 5, 6};

int main()
{
	size_t failures = 0;
	puts("Testing Queue...");
	TEST(TestQueueEnqueue(), "QueueEnqueue");
	TEST(TestQueueDequeue(), "QueueDequeue");
	TEST(TestQueueSize(), "QueueSize");
	TEST(TestQueueAppend(), "QueueAppend");

	PRNT_STATUS(failures);

	return (failures);
}

int TestQueueEnqueue()
{
	size_t i = 0;
	queue_t *queue_p = QueueCreate();


	for (i = 0; i < NUM_OF_NODES; ++i)
	{
		QueueEnqueue(queue_p, &data[i]);
		if (QueueSize(queue_p) != (i + 1))
		{
			printf("Size FAILED at index %lu\n", i);
			printf("Expected: %lu\n", (i + 1));
			printf("Returned: %lu\n", QueueSize(queue_p));
		}

		if (QueueIsEmpty(queue_p) != 0)
		{
			printf("\tIsEmpty FAILED at index %lu\n", i);
			printf("\t\tExpected: %d\n", 0);
			printf("\t\tReturned: %d\n", QueueIsEmpty(queue_p));
		}

		if (*(int *)QueuePeek(queue_p) != data[0])
		{
			printf("\tPeek FAILED at index %lu\n", i);
			printf("\t\tExpected: %d\n", data[0]);
			printf("\t\tReturned: %d\n", *(int *)QueuePeek(queue_p));
		}
	}


/*	QueueDequeue(queue_p);*/
/*	printf("Peek: %d\n", *(int *)QueuePeek(queue_p));*/
/*	QueueDequeue(queue_p);*/
/*	QueueDequeue(queue_p);*/
/*	printf("Size: %lu\n", QueueSize(queue_p));*/
/*	printf("Empty? %s\n", QueueIsEmpty(queue_p) == 1 ? "Empty" : "Not Empty");*/

/*	printf("Peek: %d\n", *(int *)QueuePeek(queue_p));*/

	QueueDestroy(queue_p);

	return (failures);
}

int TestQueueDequeue()
{
	size_t i = 0;
	queue_t *queue_p = QueueCreate();


	QueueEnqueue(queue_p, &data[0]);
	QueueEnqueue(queue_p, &data[1]);
	QueueEnqueue(queue_p, &data[2]);

	for (i = NUM_OF_NODES; i > 0; --i)
	{

		if (QueueSize(queue_p) != (i))
		{
			printf("Size FAILED at index %lu\n", i);
			printf("Expected: %lu\n", (i));
			printf("Returned: %lu\n", QueueSize(queue_p));
		}

		if (QueueIsEmpty(queue_p) != (i == 0))
		{
			printf("\tIsEmpty FAILED at index %lu\n", i);
			printf("\t\tExpected: %d\n", 0);
			printf("\t\tReturned: %d\n", QueueIsEmpty(queue_p));
		}

		if (*(int *)QueuePeek(queue_p) != data[3 - i])
		{
			printf("\tPeek FAILED at index %lu\n", (3 - i));
			printf("\t\tExpected: %d\n", data[3 - i]);
			printf("\t\tReturned: %d\n", *(int *)QueuePeek(queue_p));
		}

		QueueDequeue(queue_p);
	}

	QueueDestroy(queue_p);

	return (failures);
}

int TestQueueSize()
{
	size_t i = 0;
	queue_t *queue_p = QueueCreate();


	if (0 == QueueIsEmpty(queue_p))
	{
		printf("\tFAILED on index %lu\n", i);
		printf("\t\tExpected: 1\n");
		printf("\t\tActual: %d\n", QueueIsEmpty(queue_p));
		++failures;
	}

	for (i = 0; i < NUM_OF_NODES; ++i)
	{
		QueueEnqueue(queue_p, &data[i]);
		if ((i + 1) != QueueSize(queue_p))
		{
			printf("\tFAILED on index %lu\n", i);
			printf("\t\tExpected: %lu\n", (i + 1));
			printf("\t\tActual: %lu\n", QueueSize(queue_p));
			++failures;
		}

		if (0 != QueueIsEmpty(queue_p))
		{
			printf("\tFAILED on index %lu\n", i);
			printf("\t\tExpected: 0\n");
			printf("\t\tActual: %d\n", QueueIsEmpty(queue_p));
			++failures;
		}
	}

	for (i = NUM_OF_NODES; i > 0; --i)
	{
		QueueDequeue(queue_p);
		if ((i - 1) != QueueSize(queue_p))
		{
			printf("\tFAILED on index %lu\n", i);
			printf("\t\tExpected: %lu\n", (i - 1));
			printf("\t\tActual: %lu\n", QueueSize(queue_p));
			++failures;
		}
	}

	if (0 == QueueIsEmpty(queue_p))
	{
		printf("\tFAILED on index %lu\n", i);
		printf("\t\tExpected: 1\n");
		printf("\t\tActual: %d\n", QueueIsEmpty(queue_p));
		++failures;
	}

	QueueDestroy(queue_p);

	return (failures);
}

int TestQueueAppend()
{
	size_t i = 0;
	int peek_return = 0;
	queue_t *queue_p1 = QueueCreate();
	queue_t *queue_p2 = QueueCreate();


	for (i = 0; i < NUM_OF_NODES; ++i)
	{
		QueueEnqueue(queue_p1, &data[i]);
	}

	for (i = 0; i < NUM_OF_NODES; ++i)
	{
		QueueEnqueue(queue_p2, &data2[i]);
	}

	peek_return = *(int *)QueuePeek(QueueAppend(queue_p1, queue_p2));

	if (peek_return != data[0])
	{
		printf("\tFAILED\n");
		printf("\t\tExpected: %d\n", data[0]);
		printf("\t\tActual: %d\n", peek_return);
	}

	QueueDestroy(queue_p1);
	QueueDestroy(queue_p2);

	return (failures);
}
