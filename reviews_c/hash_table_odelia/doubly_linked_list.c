/*******************************************************************************
 * Date: 		10/9/2019
 * Developer:	Ezra Gordon
 * Reviewer: 	Erez
 * Satus: 		S
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert 		*/

#include "doubly_linked_list.h"

#include "utils.h"

#define ITER(x) ((dll_node_t *)x)

typedef struct dll_node dll_node_t;

struct dll_node {
	void *data;
	dll_node_t *next;
	dll_node_t *prev;
};

struct dll
{
	dll_node_t *begin;
	dll_node_t *end;
};

/******************************** CreateNode **********************************/
static dll_node_t *CreateNode(void *data, dll_node_t *prev, dll_node_t *next)
{
	dll_node_t *dll_node = (dll_node_t *)malloc(sizeof(dll_node_t));

	if (NULL == dll_node)
	{
		PRNT_ERR("Malloc allocation failed");
		return (NULL);
	}

	dll_node->data = data;
	dll_node->next = next;
	dll_node->prev = prev;

	return (dll_node);
}

/********************************* DLLCreate **********************************/
dll_t *DLLCreate()
{
	dll_t *dll = (dll_t *)malloc(sizeof(dll_t));
	dll_node_t *stub_begin = NULL;
	dll_node_t *stub_end = NULL;

	if (NULL == dll)
	{
		PRNT_ERR("Malloc allocation failed");
		return (NULL);
	}

	stub_begin = CreateNode((void *)0xDEADBEEF, NULL, NULL);
	stub_end = CreateNode((void *)0xDEADBEEF, NULL, NULL);

	dll->begin = stub_begin;
	dll->end = stub_end;

	/* stubs point to each other */
	stub_begin->next = stub_end;
	stub_end->prev = stub_begin;

	return (dll);
}

/********************************* DLLDestroy *********************************/
void DLLDestroy(dll_t *dll)
{
	dll_node_t *store_next_addr = NULL;

	if (dll != NULL)
	{
		while (dll->begin->next != NULL)
		{
			/* store begin's next's next */
			store_next_addr = dll->begin->next->next;

			/* begin's next's next and prev point to NULL */
			dll->begin->next->next = NULL;
			dll->begin->next->prev = NULL;

			/* free last node */
			free(dll->begin->next); dll->begin->next = NULL;

			/* begin now points to the next address */
			dll->begin->next = store_next_addr;
		}

		free(dll->begin); dll->begin = NULL;

		free(dll); dll = NULL;
	}
}

/********************************* DLLInsert **********************************/
dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iter, void *data)
{
	dll_node_t *new_node = NULL;

	assert(NULL != iter);

	new_node = CreateNode(data, ITER(iter)->prev, ITER(iter));

	if (NULL == new_node)
	{
		PRNT_ERR("Malloc allocation failed");
		return (DLLEnd(dll));
	}

	/* insert into appropriate position in list */
	new_node->prev->next = (dll_node_t *)new_node;
	new_node->next->prev = (dll_node_t *)new_node;

	return ((dll_iter_t)new_node);
}

/********************************* DLLRemove **********************************/
void DLLRemove(dll_iter_t iter)
{
	dll_node_t *node_prev = NULL;
	dll_node_t *node_next = NULL;

	assert(NULL != iter);

	node_prev = ITER(iter)->prev;
	node_next = ITER(iter)->next;

	/* connect iters next and prev */
	node_prev->next = node_next;
	node_next->prev = node_prev;

	free(iter); iter = NULL;
}

/********************************** DLLFind ***********************************/
dll_iter_t DLLFind(dll_iter_t begin, dll_iter_t end,
					const void *data_to_find,
					is_match_t IsMatch)
{
	dll_iter_t *current_iter = NULL;

	assert(NULL != begin);
	assert(NULL != end);

	/* while haven't reached end iterator, check if the data matches */
	for (current_iter = begin; 1 != DLLIsSameIter(current_iter, end); current_iter = DLLNext(current_iter))
	{
		if (IsMatch(ITER(current_iter)->data, data_to_find))
		{
			return (current_iter);
		}
	}

	return (current_iter);
}

/********************************* DLLForEach *********************************/
int DLLForEach(dll_iter_t begin, dll_iter_t end, act_t Act, void *param)
{
	dll_node_t *current_iter = NULL;
	int act_return = 0;

	assert(NULL != begin);
	assert(NULL != end);

	/* while haven't reached end iterator, perform function on each item */
	for (current_iter = begin; 1 != DLLIsSameIter(current_iter, end); current_iter = DLLNext(current_iter))
	{
		act_return = Act(ITER(current_iter)->data, param);
		if (0 != act_return)
		{
			break;
		}
	}

	return (act_return);
}

/********************************** DLLSize ***********************************/
size_t DLLSize(dll_t *dll)
{
	dll_node_t *current_node = NULL;
	size_t count = 0;

	assert(NULL != dll);

	current_node = dll->begin;

	while (current_node->next != dll->end)
	{
		++count;
		current_node = current_node->next;
	}

	return (count);
}

/********************************** DLLEmpty **********************************/
int DLLIsEmpty(dll_t *dll)
{
	assert(NULL != dll);

	return (dll->begin->next == dll->end);
}

/******************************** DLLPushFront ********************************/
dll_iter_t DLLPushFront(dll_t *dll, void *data)
{
	dll_iter_t node_iter = NULL;

	assert(NULL != dll);

	/* insert to first position */
	node_iter = (dll_iter_t)DLLInsert(dll, DLLBegin(dll), data);
	return (node_iter);
}

/******************************** DLLPopFront *********************************/
void *DLLPopFront(dll_t *dll)
{
	void *data = NULL;

	assert(NULL != dll);

	data = dll->begin->next->data;

	/* remove first */
	DLLRemove(dll->begin->next);

	return (data);
}

/******************************** DLLPushBack *********************************/
dll_iter_t DLLPushBack(dll_t *dll, void *data)
{
	dll_iter_t node_iter = NULL;

	assert(NULL != dll);

	/* insert to last position */
	node_iter = (dll_iter_t)DLLInsert(dll, DLLEnd(dll), data);
	return (node_iter);
}

/******************************** DLLPopBack **********************************/
void *DLLPopBack(dll_t *dll)
{
	void *data = NULL;

	assert(NULL != dll);

	data = dll->end->prev->data;

	/* remove last */
	DLLRemove(dll->end->prev);

	return (data);
}

/********************************** DLLNext ***********************************/
dll_iter_t DLLNext(dll_iter_t iter)
{
	assert(NULL != iter);

	return((dll_iter_t)ITER(iter)->next);
}

/********************************** DLLPrev ***********************************/
dll_iter_t DLLPrev(dll_iter_t iter)
{
	assert(NULL != iter);

	return((dll_iter_t)ITER(iter)->prev);
}

/********************************* DLLGetData *********************************/
void *DLLGetData(dll_iter_t iter)
{
	assert(NULL != iter);

	return (ITER(iter)->data);
}

/********************************** DLLBegin **********************************/
dll_iter_t DLLBegin(const dll_t *dll)
{
	assert(NULL != dll);

	return ((dll_iter_t)dll->begin->next);
}

/*********************************** DLLEnd ***********************************/
dll_iter_t DLLEnd(const dll_t *dll)
{
	assert(NULL != dll);

	return ((dll_iter_t)dll->end);
}

/******************************** DLLIsSameIter *******************************/
int DLLIsSameIter(dll_iter_t i, dll_iter_t j)
{
	assert(NULL != i);
	assert(NULL != j);

	return (i == j);
}

/********************************* DLLSplice **********************************/
void DLLSplice(dll_iter_t dest, dll_iter_t src_first, dll_iter_t src_last)
{
	dll_iter_t tmp_src_last_prev = NULL;

	assert(NULL != dest);
	assert(NULL != src_first);
	assert(NULL != src_last);

	tmp_src_last_prev = ITER(src_last)->prev;

	/* src_last prev points to dest, and src_last point to src_first prev */
	ITER(src_last)->prev->next = ITER(dest);
	ITER(src_last)->prev = ITER(src_first)->prev;

	/* src_first prev point to src_last, and stc_first points to dest prev */
	ITER(src_first)->prev->next = ITER(src_last);
	ITER(src_first)->prev = ITER(dest)->prev;

	/* dest prev points to src_first, and dest points to src_last prev */
	ITER(dest)->prev->next = ITER(src_first);
	ITER(dest)->prev = ITER(tmp_src_last_prev);
}
