/*
 * Date: 03/09/19
 * Developer: Yossi
 * Reviewer: Shir
 * Status:
 */

#include <stdio.h>

#include "singly_linked_list.h"
#include "utils.h"

int TestSLLCreateFreeNode();
int TestSLLCreateFreeSLL();
int TestSLLInsertAfterHead();
int TestSLLInsertAfter();
int TestSLLInsertAfterTail();
int TestSLLInsertHead();
int TestSLLInsert();
int TestSLLRemoveAfterHead();
int TestSLLRemoveAfter();
int TestSLLRemoveHead();
int TestSLLRemove();
int TestSLLFindTrue();
int TestSLLFindFalse();
int TestSLLForEachSuccess();
int TestSLLForEachFailure();
int TestSLLCount();
int TestSLLFlip();
int TestSLLFindIntersectionTrue();
int TestSLLFindIntersectionFalse();
int TestSLLFindIntersectionNodes();
int TestSLLIsLoop();
int TestSLLHasLoopTrue();
int TestSLLHasLoopFalse();
int TestSLLHasLoopNode();


int main()
{
	int errors = 0;

	fputs("Testing singly linked list...\n", stderr);
	errors += TestSLLCreateFreeNode();
	errors += TestSLLCreateFreeSLL();
	errors += TestSLLInsertAfterHead();
	errors += TestSLLInsertAfter();
	errors += TestSLLInsertAfterTail();
	errors += TestSLLInsertHead();
	errors += TestSLLInsert();
	errors += TestSLLRemoveAfterHead();
	errors += TestSLLRemoveAfter();
	errors += TestSLLRemoveHead();
	errors += TestSLLRemove();
	errors += TestSLLFindTrue();
	errors += TestSLLFindFalse();
	errors += TestSLLForEachSuccess();
	errors += TestSLLForEachFailure();
	errors += TestSLLCount();
	errors += TestSLLFlip();
	errors += TestSLLFindIntersectionTrue();
	errors += TestSLLFindIntersectionFalse();
	errors += TestSLLFindIntersectionNodes();
	errors += TestSLLIsLoop();
	errors += TestSLLHasLoopTrue();
	errors += TestSLLHasLoopFalse();
	errors += TestSLLHasLoopNode();
	fputs("Done.\n", stderr);

	return (errors);
}


int TestSLLCreateFreeNode()
{
	int status = 0;

	int data = 16;

	sll_node_t *node = SLLCreateNode(&data, NULL);
	if (NULL == node)
	{
		status = -1;
	}

	if (data != *(int *)(node->data))
	{
		status = -1;
	}

	SLLFreeAll(node);

	return (status);
}

int TestSLLCreateFreeSLL()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	for (i = ARR_SIZE(data); 0 < i; --i)
	{
		if (*(int *)(node->data) != data[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLInsertAfterHead()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; (ARR_SIZE(data) - 2) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	node = SLLCreateNode(&data[i + 1], node);
	head = node;

	SLLInsertAfter(head, SLLCreateNode(&data[i], NULL));

	for (i = ARR_SIZE(data); 0 < i; --i)
	{
		if (*(int *)(node->data) != data[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLInsertAfter()
{
	int status = 0;

	size_t i = 0;
	size_t j = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; (ARR_SIZE(data) / 2) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	j = i++;

	for (; (ARR_SIZE(data)) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	SLLInsertAfter(head->next, SLLCreateNode(&data[j], NULL));

	for (i = ARR_SIZE(data); 0 < i; --i)
	{
		if (*(int *)(node->data) != data[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLInsertAfterTail()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;
	sll_node_t *tail = NULL;

	for (i = 1; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	head = node;

	tail = node;
	while (NULL != tail->next)
	{
		tail = tail->next;
	}

	SLLInsertAfter(tail, SLLCreateNode(&data[0], NULL));

	for (i = ARR_SIZE(data); 0 < i; --i)
	{
		if (*(int *)(node->data) != data[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLInsertHead()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; (ARR_SIZE(data) - 1) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	head = node;

	SLLInsert(head, SLLCreateNode(&data[i], NULL));

	for (i = ARR_SIZE(data); 0 < i; --i)
	{
		if (*(int *)(node->data) != data[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLInsert()
{
	int status = 0;

	size_t i = 0;
	size_t j = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; (ARR_SIZE(data) / 2) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	j = i++;

	for (; (ARR_SIZE(data)) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	head = node;

	for (i = 0; ((ARR_SIZE(data) - 1) / 2) > i; ++i)
	{
		node = node->next;
	}
	SLLInsert(node, SLLCreateNode(&data[j], NULL));

	node = head;
	for (i = ARR_SIZE(data); 0 < i; --i)
	{
		if (*(int *)(node->data) != data[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLRemoveAfterHead()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};
	int data_after_remove[] = {2, 4, 8, 16, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	SLLFreeAll(SLLRemoveAfter(head));

	for (i = ARR_SIZE(data_after_remove); 0 < i; --i)
	{
		if (*(int *)(node->data) != data_after_remove[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLRemoveAfter()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};
	int data_after_remove[] = {2, 4, 8, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	SLLFreeAll(SLLRemoveAfter(head->next));

	for (i = ARR_SIZE(data_after_remove); 0 < i; --i)
	{
		if (*(int *)(node->data) != data_after_remove[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLRemoveHead()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};
	int data_after_remove[] = {2, 4, 8, 16, 32};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	head = node;

	SLLFreeAll(SLLRemove(node));

	for (i = ARR_SIZE(data_after_remove); 0 < i; --i)
	{
		if (*(int *)(node->data) != data_after_remove[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLRemove()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};
	int data_after_remove[] = {2, 4, 8, 16, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	SLLFreeAll(SLLRemove(head->next));

	for (i = ARR_SIZE(data_after_remove); 0 < i; --i)
	{
		if (*(int *)(node->data) != data_after_remove[i - 1])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

static int SLLIntCmp(const void *current_data, const void *data_to_find)
{
	return (*(int *)current_data != *(int *)data_to_find);
}

int TestSLLFindTrue()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	for (i = 0; ((ARR_SIZE(data)) / 2) > i; ++i)
	{
		node = node->next;
	}

	if (SLLFind(head, &data[(ARR_SIZE(data) - 1) / 2], SLLIntCmp) != node)
	{
		status = -1;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLFindFalse()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 1; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	while (NULL != node)
	{
		node = node->next;
	}

	if (SLLFind(head, &data[0], SLLIntCmp) != node)
	{
		status = -1;
	}

	SLLFreeAll(head);

	return (status);
}

static int SLLNodeComplement(void *data, void *param)
{
	int comp = 0;

	return ((comp = *(int *)param - *(int *)data) < 0);
}

int TestSLLForEachSuccess()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};
	int param = 128;

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	if (0 != SLLForEach(head, SLLNodeComplement, &param))
	{
		status = -1;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLForEachFailure()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};
	int param = 32;

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	if (0 == SLLForEach(head, SLLNodeComplement, &param))
	{
		status = -1;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLCount()
{
	int status = 0;

	size_t i = 0;
	size_t count = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	head = node;

	while (NULL != node)
	{
		node = node->next;
		++count;
	}

	if (ARR_SIZE(data) != count)
	{
		status = -1;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLFlip()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	node = SLLFlip(node);
	head = node;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		if (*(int *)node->data != data[i])
		{
			status = -1;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLFindIntersectionTrue()
{
	int status = 0;

	size_t i = 0;
	int data1[] = {2, 4, 8, 16, 32, 64};
	int data2[] = {3, 9, 27, 81};

	sll_node_t *head1 = NULL;
	sll_node_t *head2 = NULL;
	sll_node_t *intersection = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data1) > i; ++i)
	{
		node = SLLCreateNode(&data1[i], node);
	}
	head1 = node;

	node = head1->next->next;
	for (i = 0; ARR_SIZE(data2) > i; ++i)
	{
		node = SLLCreateNode(&data2[i], node);
	}
	head2 = node;

	intersection = SLLFindIntersection(head1, head2);
	if (intersection != head1->next->next)
	{
		status = -1;
	}

	while (node->next != intersection)
	{
		node = node->next;
	}
	node->next = NULL;

	SLLFreeAll(head1);
	SLLFreeAll(head2);

	return (status);
}

int TestSLLFindIntersectionFalse()
{
	int status = 0;

	size_t i = 0;
	int data1[] = {2, 4, 8, 16, 32, 64};
	int data2[] = {3, 9, 27, 81};

	sll_node_t *head1 = NULL;
	sll_node_t *head2 = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data1) > i; ++i)
	{
		node = SLLCreateNode(&data1[i], node);
	}
	head1 = node;

	node = NULL;
	for (i = 0; ARR_SIZE(data2) > i; ++i)
	{
		node = SLLCreateNode(&data2[i], node);
	}
	head2 = node;

	if (NULL != SLLFindIntersection(head1, head2))
	{
		status = -1;
	}

	SLLFreeAll(head1);
	SLLFreeAll(head2);

	return (status);
}

int TestSLLFindIntersectionNodes()
{
	int status = 0;

	int data1 = 16;
	int data2 = 8;

	sll_node_t *node1 = NULL;
	sll_node_t *node2 = NULL;

	node1 = SLLCreateNode(&data1, NULL);
	node2 = SLLCreateNode(&data2, NULL);

	if (NULL != SLLFindIntersection(node1, node2))
	{
		status = -1;
	}

	SLLFreeAll(node1);
	SLLFreeAll(node2);

	return (status);
}

int TestSLLIsLoop()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *tail = NULL;
	sll_node_t *node = NULL;

	tail = SLLCreateNode(&data[i], NULL);
	node = tail;
	for (i = 1; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	head = node;

	tail->next = head;
	if (1 != SLLHasLoop(head))
	{
		status = -1;
	}
	tail->next = NULL;

	SLLFreeAll(head);

	return (status);
}

int TestSLLHasLoopTrue()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *tail = NULL;
	sll_node_t *node = NULL;

	tail = SLLCreateNode(&data[i], NULL);
	node = tail;
	for (i = 1; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	head = node;

	tail->next = head->next->next;
	if (1 != SLLHasLoop(head))
	{
		status = -1;
	}
	tail->next = NULL;

	SLLFreeAll(head);

	return (status);
}

int TestSLLHasLoopFalse()
{
	int status = 0;

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}
	head = node;

	if (0 != SLLHasLoop(head))
	{
		status = -1;
	}

	SLLFreeAll(head);

	return (status);
}

int TestSLLHasLoopNode()
{
	int status = 0;

	int data = 16;
	sll_node_t *node = SLLCreateNode(&data, NULL);

	if (0 != SLLHasLoop(node))
	{
		status = -1;
	}

	SLLFreeAll(node);

	return (status);
}
