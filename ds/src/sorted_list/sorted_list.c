/*******************************************************************************
 * Date: 		11/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Lazy
 * Satus: 		S
 ******************************************************************************/

#include <stddef.h> /* size_t  		*/
#include <stdio.h>	/* fprintf 		*/
#include <stdlib.h> /* malloc, free */
#include <assert.h>	/* assert		*/

#include "doubly_linked_list.h"
#include "sorted_list.h"
#include "utils.h"

#define DLL (sl->dll)

struct sorted_list
{
    dll_t *dll;
    void *param;
    is_before_t is_before;
};

/**************************** SortedListCreateNode ****************************/
sol_t *SortedListCreate(is_before_t is_before, void *param)
{

	sol_t *sl = (sol_t *)malloc(sizeof(sol_t));

	if (NULL == sl)
	{
		PRNT_ERR("Malloc allocation failed");
		return (NULL);
	}

	/* create doubly linked list */
	DLL = DLLCreate();

	if (NULL == DLL)
	{
		PRNT_ERR("Malloc allocation failed");

		free(sl);

		return (NULL);
	}

	sl->param = param;
	sl->is_before = is_before;

	return (sl);
}

/****************************** SortedListDestroy *****************************/
void SortedListDestroy(sol_t *sl)
{
	assert(NULL != sl);

	DLLDestroy(DLL);

	free(sl); sl = NULL;
}
/*############################ forward_is_before #############################*/
static sol_iter_t forward_is_before(sol_t *sl, const void *data,
                                    sol_iter_t start_iter,
                                    sol_iter_t end_iter)
{
	sol_iter_t current_iter = start_iter;

	/* while not at end of range and current iter is before data */
	while (!SortedListIsSameIterator(end_iter, current_iter) &&
		   sl->is_before(SortedListGetData(current_iter), data, sl->param))
	{
		current_iter = SortedListNext(current_iter);
	}

	return (current_iter);
}

/****************************** SortedListInsert ******************************/
sol_iter_t SortedListInsert(sol_t *sl, void *data)
{
	sol_iter_t current_iter = NULL;
	sol_iter_t end_iter = NULL;

	assert(NULL != sl);

	current_iter = SortedListBegin(sl);
	end_iter = SortedListEnd(sl);

	/* find correct position to insert data based on user's is_before function*/
	current_iter = forward_is_before(sl, data, current_iter, end_iter);

	return ((sol_iter_t)DLLInsert(DLL, current_iter, data));
}

/****************************** SortedListRemove ******************************/
sol_iter_t SortedListRemove(sol_iter_t iter)
{
	sol_iter_t next_node = NULL;

	assert(NULL != iter);

	next_node = SortedListNext(iter);

	DLLRemove(iter);

	return (next_node);
}

/***************************** SortedListPopFront *****************************/
void *SortedListPopFront(sol_t *sl)
{
	assert(NULL != sl);

	return(DLLPopFront(DLL));
}

/****************************** SortedListPopBack *****************************/
void *SortedListPopBack(sol_t *sl)
{
	assert(NULL != sl);

	return(DLLPopBack(DLL));
}

/******************************* SortedListSize *******************************/
size_t SortedListSize(const sol_t *sl)
{
	assert(NULL != sl);

	return (DLLSize(DLL));
}

/****************************** SortedListIsEmpty *****************************/
int SortedListIsEmpty(const sol_t *sl)
{
	assert(NULL != sl);

	return (DLLIsEmpty(DLL));
}

/******************************* SortedListBegin ******************************/
sol_iter_t SortedListBegin(const sol_t *sl)
{
	assert(NULL != sl);

	return (DLLBegin(DLL));
}

/******************************** SortedListEnd *******************************/
sol_iter_t SortedListEnd(const sol_t *sl)
{
	assert(NULL != sl);

	return (DLLEnd(DLL));
}

/******************************* SortedListNext *******************************/
sol_iter_t SortedListNext(sol_iter_t iter)
{
	assert(NULL != iter);

	return (DLLNext(iter));
}

/******************************* SortedListPrev *******************************/
sol_iter_t SortedListPrev(sol_iter_t iter)
{
	assert(NULL != iter);

	return (DLLPrev(iter));
}

/************************** SortedListIsSameIterator **************************/
int SortedListIsSameIterator(sol_iter_t i, sol_iter_t j)
{
	assert(NULL != i);
	assert(NULL != j);

	return (DLLIsSameIter(i, j));
}

/***************************** SortedListGetData ******************************/
void *SortedListGetData(sol_iter_t iter)
{
	assert(NULL != iter);

	return (DLLGetData(iter));
}


/*############################ backward_is_before ############################*/
static int backward_is_before(sol_t *sl,
                              const void *data,
                              sol_iter_t current_iter)
{
	return (sl->is_before(data, SortedListGetData(current_iter), sl->param));
}

/******************************* SortedListFind *******************************/
sol_iter_t SortedListFind(sol_t *sl,
						 sol_iter_t start,
						 sol_iter_t finish,
						 const void *data_to_find)
{
	sol_iter_t current_iter = NULL;

	assert(NULL != sl);
	assert(NULL != start);
	assert(NULL != finish);

	current_iter = forward_is_before(sl, data_to_find, start, finish);

	/* haven't reached end of range */
	if (!SortedListIsSameIterator(current_iter, finish))
	{
		if (0 == backward_is_before(sl, data_to_find, current_iter))
		{
			return (current_iter);
		}
	}

	return (finish);
}

/****************************** SortedListFindIf ******************************/
sol_iter_t SortedListFindIf(is_findif_t is_findif,
						   void *param,
						   sol_iter_t start,
						   sol_iter_t finish)
{
	sol_iter_t current_iter = NULL;

	assert(NULL != start);
	assert(NULL != finish);

	current_iter = start;

	/* while not at end of range, check if data matches is_findif condition */
	while (1 != SortedListIsSameIterator(current_iter, finish) &&
		 1 != is_findif(SortedListGetData(current_iter), param))
	{
		current_iter = SortedListNext(current_iter);
	}

	return (current_iter);
}

/***************************** SortedListForEach ******************************/
int SortedListForEach(sol_iter_t start,
					  sol_iter_t finish,
					  sol_act_t act,
					  void *param)
{
    assert(NULL != start);
    assert(NULL != finish);

    return(DLLForEach(start, finish, act, param));
}

/*############################ find_splice_chunk #############################*/
static sol_iter_t find_splice_chunk(sol_t *sl,
                                    sol_iter_t current_iter,
                                    sol_iter_t before_check,
                                    sol_iter_t list_end)
{
	/* while current_iter is not at end and is before the before_check */
    while (!SortedListIsSameIterator(current_iter, list_end) &&
    	   sl->is_before(SortedListGetData(current_iter),
                         SortedListGetData(before_check),
                         sl->param))
    {
    	/* go to next iter */
        current_iter = SortedListNext(current_iter);
    }

    return (current_iter);
}

/****************************** SortedListMerge *******************************/
sol_t *SortedListMerge(sol_t *sl1, sol_t *sl2)
{
    sol_iter_t splice_dest = NULL;
    sol_iter_t splice_start = NULL;
    sol_iter_t splice_end = NULL;

    assert(NULL != sl1);
    assert(NULL != sl2);

    splice_dest = SortedListBegin(sl1);
    splice_start = SortedListBegin(sl2);
    splice_end = SortedListBegin(sl2);

	/* while sl2 has not reached the end */
    while (!SortedListIsSameIterator(splice_start, SortedListEnd(sl2)))
    {
        splice_dest = find_splice_chunk(sl1,
                                 	    splice_dest,
                                 	    splice_start,
                                 	    SortedListEnd(sl1));

		/* if sl1 is at the end, splice the rest of sl2 to sl1 */
        if (SortedListIsSameIterator(splice_dest, SortedListEnd(sl1)))
        {
            DLLSplice(splice_dest, splice_start, SortedListEnd(sl2));
            break;
        }

        splice_end = find_splice_chunk(sl1,
                                   	   splice_end,
                                   	   splice_dest,
                                   	   SortedListEnd(sl2));

		/*
			* if they are the same values, it will create an endless loop if one
			* of the lists is not incremented
		*/
		while (!SortedListIsSameIterator(splice_end, SortedListEnd(sl2)) &&
			   sl1->is_before(SortedListGetData(splice_end),
			   				  SortedListGetData(splice_dest),
			   				  sl1->param) 								 ==
			   sl1->is_before(SortedListGetData(splice_dest),
			   				  SortedListGetData(splice_end),
			   				  sl1->param))
		{
			splice_end = SortedListNext(splice_end);
		}

		/* Splice correct items of sl2 to sl1 */
        DLLSplice(splice_dest, splice_start, splice_end);

        /* new sl2 start is last item not copied */
        splice_start = splice_end;
    }

    return (sl1);
}
