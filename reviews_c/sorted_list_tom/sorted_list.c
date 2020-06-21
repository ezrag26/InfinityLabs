/************************************************
 * date: 15.9.19				                *
						                        *
 * developr: Tom			                	*
 * reviewer: Ezra		                        *
 * status: S				                 	*
 ***********************************************/

#include <stdio.h>  /* for the printf */
#include <stddef.h> /* for the size_t */
#include <stdlib.h> /* for the malloc */
#include <assert.h> /* for the assert */
#include <string.h> /* for the memcpy */

#include "doubly_linked_list.h"
#include "sorted_list.h"
#include "utils.h"

struct sorted_list
{
	dll_t *dll;
	is_before_t is_before;
	void *param;
};

/******************************************************************************/
sol_t *SortedListCreate(is_before_t is_before, void *param)
{

	sol_t *sorted_list = (sol_t *)malloc (sizeof(sol_t));
	if (NULL == sorted_list)
	{
		DBPRINT("Error in Malloc\n");
		return NULL;
	}

	sorted_list->dll = DLLCreate();

	if (NULL == sorted_list->dll)
	{
		DBPRINT("Error in Malloc\n");
		free(sorted_list);
		return NULL;
	}

	sorted_list->is_before = is_before;
	sorted_list->param = param;

	return sorted_list;
}
/******************************************************************************/
void SortedListDestroy(sol_t *list)
{
	if (NULL != list)
	{
		DLLDestroy(list->dll);

		free(list); list = NULL;
	}
}
/******************************************************************************/
sol_iter_t SortedListInsert(sol_t *list, void *data)
{

	sol_iter_t current_iter = DLLBegin(list->dll);

	if (0 == DLLIsEmpty((list->dll)))
	{
		while(list->is_before(DLLGetData(current_iter), data, list->param))
		{
			current_iter = DLLNext(current_iter);

			if (current_iter == SortedListEnd(list))
			{
				break;
			}
		}

	}
	return  (DLLInsert(list->dll,current_iter, data));
}
/******************************************************************************/
size_t SortedListSize(const sol_t *list)
{
	return DLLSize(list->dll);
}
/******************************************************************************/
int SortedListIsEmpty(const sol_t *list)
{
	return DLLIsEmpty(list->dll);
}
/******************************************************************************/
sol_iter_t SortedListBegin(const sol_t *list)
{
	return DLLBegin(list->dll);
}
/******************************************************************************/
sol_iter_t SortedListEnd(const sol_t *list)
{
	return DLLEnd(list->dll);
}
/******************************************************************************/
sol_iter_t SortedListNext(sol_iter_t iter)
{
	return DLLNext(iter);
}
/******************************************************************************/
sol_iter_t SortedListPrev(sol_iter_t iter)
{
	return DLLPrev(iter);
}
/******************************************************************************/
int SortedListIsSameIterator(sol_iter_t iter1, sol_iter_t iter2)
{
	return DLLIsSameIter(iter1, iter2);
}
/******************************************************************************/
void *SortedListGetData(sol_iter_t iter)
{
	return DLLGetData(iter);
}
/******************************************************************************/
sol_iter_t SortedListRemove(sol_iter_t iter)
{
	sol_iter_t iter2 = DLLNext(iter);
	DLLRemove(iter);
	return iter2;
}
/******************************************************************************/
void *SortedListPopFront(sol_t *list)
{
	return DLLPopFront(list->dll);
}
/******************************************************************************/
void *SortedListPopBack(sol_t *list)
{
	return DLLPopBack(list->dll);
}
/******************************************************************************/
int SortedListForEach(sol_iter_t start, sol_iter_t end, sol_act_t act,
	void *param)
{
	return DLLForEach(start, end, act, param);
}
/******************************************************************************/
sol_iter_t SortedListFind(sol_t *list, sol_iter_t start, sol_iter_t end,
						 const void *data_to_find)
{
	sol_iter_t iter = start;

	assert(NULL != list);
	assert(NULL != start);
	assert(NULL != end);
	assert(NULL != data_to_find);

	while ( 1 == (list->is_before(DLLGetData(iter), data_to_find, list->param)))
	{

		iter =	DLLNext(iter);
	}

	if (0 == (list->is_before(data_to_find, DLLGetData(iter), list->param)))
	{
		return iter;
	}
	return end;
}
/******************************************************************************/
sol_iter_t SortedListFindIf(is_findif_t is_findif, void *param,
							sol_iter_t start, sol_iter_t end)
{

	assert(NULL != is_findif);
	assert(NULL != param);
	assert(NULL != start);
	assert(NULL != end);

	while ( 1 != SortedListIsSameIterator(start,end))
	{
		if (is_findif(param,DLLGetData(start)))
		{
			return start;
		}
		else
		{
		 	start = DLLNext(start);
		}
	}
	return end;
}
/******************************************************************************/
sol_t *SortedListMerge(sol_t *list1, sol_t *list2)
{

	dll_iter_t list2_end = NULL;
	dll_iter_t list1_end = NULL;
	dll_iter_t list2_splice_end = NULL;
	dll_iter_t list2_splice_start = NULL;
	dll_iter_t list1_run = NULL;

	list1_end = SortedListEnd(list1);
	list2_end = SortedListEnd(list2);

	list1_run = SortedListBegin(list1);
	list2_splice_start = SortedListBegin(list2);
	list2_splice_end = list2_splice_start;

	while(!(SortedListIsSameIterator(list2_splice_end, list2_end)) &&
	      !(SortedListIsSameIterator(list1_run, list1_end)))
	{

		while (!(SortedListIsSameIterator(list1_run, list1_end)) &&
		       !(SortedListIsSameIterator(list2_splice_end, list2_end)))
		{
			if(!(list1->is_before) (SortedListGetData(list2_splice_end),
			   SortedListGetData(list1_run), list1->param))
			{
				break;
			}

			list2_splice_end = SortedListNext(list2_splice_end);
		}

		if(!(SortedListIsSameIterator(list2_splice_end, list2_splice_start)))
		{
			DLLSplice(list1_run, list2_splice_start, list2_splice_end);
			list2_splice_start = list2_splice_end;
		}
		list1_run = SortedListNext(list1_run);
	}

	if (!(SortedListIsSameIterator(list2_splice_end, list2_end)))
	{
		DLLSplice(list1_end, list2_splice_start, list2_end);
	}
	return list1;

}
