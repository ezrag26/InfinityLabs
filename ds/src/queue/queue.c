/*******************************************************************************
 * Date: 		8/9/2019
 * Developer:	Ezra Gordon
 * Reviewer: 	Dan
 * Satus: 		A
 ******************************************************************************/

#include <stddef.h>	/* size_t */
#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */
#include <stdio.h>	/* fprintf */

#include "queue.h"
#include "singly_linked_list.h"

#define LAST_IN_P (queue_p->node)

#ifndef NDEBUG
#define PRNT_ERR(x) (fprintf(stderr, x"\n"))
#else
#define PRNT_ERR(x)
#endif

struct queue
{
	sll_node_t *node;
};

queue_t *QueueCreate()
{

	queue_t *queue_p = (queue_t *)malloc(sizeof(queue_t));

	if (NULL == queue_p)
	{
		PRNT_ERR("Memory Allocation Failed");
		return (NULL);
	}

	LAST_IN_P = SLLCreateNode(NULL, NULL);

	LAST_IN_P->data = (void *)LAST_IN_P;
	LAST_IN_P->next = (sll_node_t *)LAST_IN_P;

	return (queue_p);

}

void QueueDestroy(queue_t *queue_p)
{
	if (NULL != queue_p)
	{	
		sll_node_t *tmp = LAST_IN_P->next;
		LAST_IN_P->next = NULL;
	
		SLLFreeAll(tmp); tmp = NULL;
		free(queue_p); queue_p = NULL;
	}
}

void QueueDequeue(queue_t *queue_p)
{
	assert(NULL != queue_p);

	SLLFreeAll(SLLRemoveAfter(LAST_IN_P));
}

void QueueEnqueue(queue_t *queue_p, void *data)
{
	sll_node_t *new_node = NULL;

	assert(NULL != queue_p);
	assert(NULL != data);

	/* create a new node pointing to NULL */
	new_node = SLLCreateNode(data, NULL);

	/* Insert the new node where LAST_IN_P is located */
	LAST_IN_P = SLLInsert(LAST_IN_P->next, new_node);
}

size_t QueueSize(const queue_t *queue_p)
{
	sll_node_t *next_addr = NULL;
	size_t size = 0;

	assert(NULL != queue_p);

	next_addr = LAST_IN_P->next;

	while (next_addr != LAST_IN_P)
	{
		++size;
		next_addr = next_addr->next;
	}

	return (size);
}

int QueueIsEmpty(const queue_t *queue_p)
{
	assert(NULL != queue_p);

	return (!QueueSize(queue_p));
}

queue_t *QueueAppend(queue_t *queue_p1, queue_t *queue_p2)
{
	sll_node_t *end1 = NULL;
	sll_node_t *end2 = NULL;

	assert(NULL != queue_p1);
	assert(NULL != queue_p2);

	/* ends of respective queues */
	end1 = queue_p1->node->next;
	end2 = queue_p2->node->next;

	/* queue_p1 next should point to first in of of queue_p2 */
	queue_p1->node->next = end2->next;
	/* end of queue_p2 should point to first in of queue_p1 */
	end2->next = end1->next;

	/* queue_p1 now points to last in from queue_p2 */
	queue_p1->node = queue_p2->node;
	queue_p2->node = end1;			/* queue_p2 now points to end of queue_p1 */
	end1->next = queue_p2->node;				 /* queue_p2 points to itself */

	return (queue_p1);
}

void *QueuePeek(const queue_t *queue_p)
{
	assert(NULL != queue_p);
	
	return((void *)LAST_IN_P->next->next->data);
}
