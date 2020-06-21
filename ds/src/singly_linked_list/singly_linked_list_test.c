

#include <stdio.h>

#include "singly_linked_list.h"
#include "utils.h"
#include "tests.h"

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
int TestSLLRecFlip();
int TestSLLFindIntersectionTrue();
int TestSLLFindIntersectionFalse();
int TestSLLFindIntersectionNodes();
int TestSLLIsLoop();
int TestSLLHasLoopTrue();
int TestSLLHasLoopFalse();
int TestSLLHasLoopNode();

size_t failures = 0;

int main()
{

	puts("Testing Singly Linked List...");
	TEST(TestSLLCreateFreeNode(), "SLLCreateFreeNode");
	TEST(TestSLLCreateFreeSLL(), "SLLCreateFreeSLL");
	TEST(TestSLLInsertAfterHead(), "SLLInsertAfterHead");
	TEST(TestSLLInsertAfter(), "SLLInsertAfter");
	TEST(TestSLLInsertAfterTail(), "SLLInsertAfterTail");
	TEST(TestSLLInsertHead(), "SLLInsertHead");
	TEST(TestSLLInsert(), "SLLInsert");
	TEST(TestSLLRemoveAfterHead(), "SLLRemoveAfterHead");
	TEST(TestSLLRemoveAfter(), "SLLRemoveAfter");
	TEST(TestSLLRemoveHead(), "SLLRemoveHead");
	TEST(TestSLLRemove(), "SLLRemove");
	TEST(TestSLLFindTrue(), "SLLFindTrue");
	TEST(TestSLLFindFalse(), "SLLFindFalse");
	TEST(TestSLLForEachSuccess(), "SLLForEachSuccess");
	TEST(TestSLLForEachFailure(), "SLLForEachFailure");
	TEST(TestSLLCount(), "SLLCount");
	TEST(TestSLLFlip(), "SLLFlip");
	TEST(TestSLLRecFlip(), "TestSLLRecFlip");
	TEST(TestSLLFindIntersectionTrue(), "SLLFindIntersectionTrue");
	TEST(TestSLLFindIntersectionFalse(), "SLLFindIntersectionFalse");
	TEST(TestSLLFindIntersectionNodes(), "SLLFindIntersectionNodes");
	TEST(TestSLLIsLoop(), "SLLIsLoop");
	TEST(TestSLLHasLoopTrue(), "SLLHasLoopTrue");
	TEST(TestSLLHasLoopFalse(), "SLLHasLoopFalse");
	TEST(TestSLLHasLoopNode(), "SLLHasLoopNode");

	PRNT_STATUS(failures);

	return (failures);
}


int TestSLLCreateFreeNode()
{

	int data = 16;

	sll_node_t *node = SLLCreateNode(&data, NULL);
	if (NULL == node)
	{
		++failures;
	}

	if (data != *(int *)(node->data))
	{
		++failures;
	}

	SLLFreeAll(node);

	return (failures);
}

int TestSLLCreateFreeSLL()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLInsertAfterHead()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLInsertAfter()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLInsertAfterTail()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLInsertHead()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLInsert()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLRemoveAfterHead()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLRemoveAfter()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLRemoveHead()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLRemove()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

static int SLLIntCmp(const void *current_data, const void *data_to_find)
{
	return (*(int *)current_data != *(int *)data_to_find);
}

int TestSLLFindTrue()
{

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
		++failures;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLFindFalse()
{

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
		++failures;
	}

	SLLFreeAll(head);

	return (failures);
}

static int SLLNodeComplement(void *data, void *param)
{
	int comp = 0;

	return ((comp = *(int *)param - *(int *)data) < 0);
}

int TestSLLForEachSuccess()
{

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
		++failures;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLForEachFailure()
{

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
		++failures;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLCount()
{

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
		++failures;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLFlip()
{

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
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLRecFlip()
{

	size_t i = 0;
	int data[] = {2, 4, 8, 16, 32, 64};

	sll_node_t *head = NULL;
	sll_node_t *node = NULL;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		node = SLLCreateNode(&data[i], node);
	}

	node = SLLRecFlip(node);
	head = node;

	for (i = 0; ARR_SIZE(data) > i; ++i)
	{
		if (*(int *)node->data != data[i])
		{
			++failures;
		}
		node = node->next;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLFindIntersectionTrue()
{

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
		++failures;
	}

	while (node->next != intersection)
	{
		node = node->next;
	}
	node->next = NULL;

	SLLFreeAll(head1);
	SLLFreeAll(head2);

	return (failures);
}

int TestSLLFindIntersectionFalse()
{

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
		++failures;
	}

	SLLFreeAll(head1);
	SLLFreeAll(head2);

	return (failures);
}

int TestSLLFindIntersectionNodes()
{

	int data1 = 16;
	int data2 = 8;

	sll_node_t *node1 = NULL;
	sll_node_t *node2 = NULL;

	node1 = SLLCreateNode(&data1, NULL);
	node2 = SLLCreateNode(&data2, NULL);

	if (NULL != SLLFindIntersection(node1, node2))
	{
		++failures;
	}

	SLLFreeAll(node1);
	SLLFreeAll(node2);

	return (failures);
}

int TestSLLIsLoop()
{

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
		++failures;
	}
	tail->next = NULL;

	SLLFreeAll(head);

	return (failures);
}

int TestSLLHasLoopTrue()
{

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
		++failures;
	}
	tail->next = NULL;

	SLLFreeAll(head);

	return (failures);
}

int TestSLLHasLoopFalse()
{

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
		++failures;
	}

	SLLFreeAll(head);

	return (failures);
}

int TestSLLHasLoopNode()
{

	int data = 16;
	sll_node_t *node = SLLCreateNode(&data, NULL);

	if (0 != SLLHasLoop(node))
	{
		++failures;
	}

	SLLFreeAll(node);

	return (failures);
}
