/************************************************
 * date: 4.9.19				                    *
						                        *
 * developr: Tom			                	*
 * reviewer: Naama	                        *
 * status: S				                 	*
 ***********************************************/
/*/*/

#include <stdio.h>  /* for the printf */
#include <stddef.h> /* for the size_t */
#include <stdlib.h> /* for the malloc */
#include <assert.h> /* for the assert */
#include <string.h> /* for the memcpy */

#include "doubly_linked_list.h"
#include "utils.h"


#ifndef NDEBUG
#define DBPRINT(x) fprintf(stderr,x)
#else
#define DBPRINT(x)
#endif

#define DLL_ITER_T(x)	((dll_node_t *)(x))

typedef struct dll_node dll_node_t;

struct dll_node
{
	void *data;
	dll_node_t *next;
	dll_node_t *prev;
};


struct dll
{
	dll_node_t *begin;
	dll_node_t *end;
};

/*****************************************************************************/
dll_t *DLLCreate()
{
	dll_node_t *end = NULL;
	dll_node_t *begin = NULL;
	dll_t *node = (dll_t *)malloc (sizeof(dll_t));
	if (NULL == node)
	{
		DBPRINT("Error in Malloc\n");
		return NULL;
	}

	end = (dll_node_t *)malloc (sizeof(dll_node_t));

	if (NULL == end)
	{
		DBPRINT("Error in Malloc\n");
		free (node);
		return NULL;
	}

	begin = (dll_node_t *)malloc (sizeof(dll_node_t));

	if (NULL == begin)
	{
		DBPRINT("Error in Malloc\n");
		free (node);
		return NULL;
	}

	node->begin = begin;
	begin->next = end;
	begin->prev = NULL;
	begin->data = NULL;

	node->end = end;
	end->prev = begin;
	end->next = NULL;
	end->data = NULL;

	return node;
}

/*****************************************************************************/
void DLLDestroy(dll_t *dll)
{
	dll_node_t *next_node_free = NULL;

	if (NULL != dll)
	{
		next_node_free = dll->begin;

		while (NULL != next_node_free->next)
		{
			next_node_free = next_node_free->next;
			free (next_node_free->prev);next_node_free->prev= NULL;
		}
		free(next_node_free); next_node_free = NULL;
		free(dll); dll = NULL;

	}
	return;
}

/*****************************************************************************/
dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iter, void *data)
{

	dll_node_t *NewNode = (dll_node_t *)malloc(sizeof(dll_node_t));

	if (NULL == NewNode)
	{
		DBPRINT("Error in Malloc\n");
		return (dll->end);
	}

	NewNode->next = DLL_ITER_T(iter);
	NewNode->prev = DLL_ITER_T(iter)->prev;
	NewNode->data = data;

	DLL_ITER_T(iter)->prev->next = NewNode;
	DLL_ITER_T(iter)->prev = NewNode;

	return NewNode;
}

/*****************************************************************************/
void DLLRemove(dll_iter_t iter)
{

	dll_node_t *temp_next = DLL_ITER_T(iter)->next;
	dll_node_t *temp_prev = DLL_ITER_T(iter)->prev;

	temp_prev->next = temp_next;
	temp_next->prev = temp_prev;

	DLL_ITER_T(iter)->prev = NULL;
	DLL_ITER_T(iter)->next = NULL;

	free (iter);
}

/*****************************************************************************/
dll_iter_t DLLFind(dll_iter_t begin, dll_iter_t end,
					const void *data_to_find,
					is_match_t is_match)
{
	dll_iter_t i = NULL;

	assert(NULL != begin);
	assert(NULL != end);
	assert(NULL != is_match);

	for (i = begin; !DLLIsSameIter(i, end); i = DLLNext(i))
	{
		if (is_match(((dll_node_t *)i)->data, data_to_find))
		{
			break;
		}
	}

	return (i);
}

/*****************************************************************************/
int DLLIsEmpty(dll_t *dll)
{
	assert(NULL != dll);


	return (dll->begin->next == dll->end && dll->end->prev == dll->begin);


}

/*****************************************************************************/

size_t DLLSize(dll_t *dll)
{
	size_t size = 0;
	dll_iter_t i = NULL;

	assert(NULL != dll);

	i = DLLBegin(dll);

	while (DLLEnd(dll) != i)
	{
		i = DLLNext(i);
		++size;
	}
	return	(size);
}

/*****************************************************************************/
dll_iter_t DLLPushFront(dll_t *dll, void *data) /* front = start */
{
	assert(NULL != dll);
	assert(NULL != data);

 	DLLInsert(dll ,dll->begin->next, data);

 	return (dll->begin->next);
}

/*****************************************************************************/
void *DLLPopBack(dll_t *dll) /* back = end */
{

	void * temp = dll->end->prev->data;

	assert(NULL != dll);

	DLLRemove(dll->end->prev);

	return temp;
}

/*****************************************************************************/
void *DLLPopFront(dll_t *dll)
{

	void *temp = dll->begin->next->data;

	assert(NULL != dll);

	DLLRemove(dll->begin->next);

	return temp;
}

/*****************************************************************************/
dll_iter_t DLLPushBack(dll_t *dll, void *data)
{
	assert(NULL != dll);
	assert(NULL != data);

	DLLInsert(dll, dll->end, data);

	return (dll->end->prev);
}

/*****************************************************************************/

dll_iter_t DLLNext(dll_iter_t iter)
{
	assert(NULL != iter);

	iter = DLL_ITER_T(iter)->next;
	return iter;
}

/*****************************************************************************/
dll_iter_t DLLPrev(dll_iter_t iter)
{
	assert(NULL != iter);

	iter = DLL_ITER_T(iter)->prev;
	return iter;
}
/*****************************************************************************/

void *DLLGetData(dll_iter_t iter)
{
	assert(NULL != iter);

	return DLL_ITER_T(iter)->data;
}

/*****************************************************************************/
dll_iter_t DLLBegin(const dll_t *dll)
{
	assert(NULL != dll);

	return (dll->begin->next);
}


/*****************************************************************************/
dll_iter_t DLLEnd(const dll_t *dll)
{
	assert(NULL != dll);

	return (dll->end);
}

/*****************************************************************************/
int DLLIsSameIter(dll_iter_t i, dll_iter_t j)
{
	assert(NULL != i);
	assert(NULL != j);

	return (i == j);
}

/*****************************************************************************/
void DLLSplice(dll_iter_t *dest, dll_iter_t *src_first, dll_iter_t *src_last)
{

	dll_node_t *temp1 = DLL_ITER_T(src_first)->prev;
	dll_node_t *temp2 = DLL_ITER_T(src_last);
	dll_node_t *temp3 = DLL_ITER_T(dest)->prev;

	assert(NULL != dest);
	assert(NULL != src_first);
	assert(NULL != src_last);

	DLL_ITER_T(dest)->prev = DLL_ITER_T(src_last)->prev;
	DLL_ITER_T(src_last)->prev->next = DLL_ITER_T(dest);

	temp1->next = temp2;
	temp2->prev = temp1;
	temp3->next = DLL_ITER_T(src_first);
	DLL_ITER_T(src_first)->prev = temp3;
}

/*****************************************************************************/
int DLLForEach(dll_iter_t start, dll_iter_t finish,
			   act_t act, void *param)
{
	dll_iter_t i = NULL;
	int result = 0;

	assert(NULL != start);
	assert(NULL != finish);
	assert(NULL != act);

	for (i = start; !DLLIsSameIter(i, finish); i = DLLNext(i))
	{
		result = act(((dll_node_t *)i)->data, param);
		if(0 != result)
		{
			break;
		}
	}

	return result;
}
