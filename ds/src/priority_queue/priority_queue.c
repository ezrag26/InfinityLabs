/*******************************************************************************
 * Date: 		15/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Erez
 * Satus: 		S
 ******************************************************************************/

#include <assert.h> /* assert 	    */
#include <stdlib.h> /* malloc, free */

#include "utils.h"
#include "sorted_list.h"
#include "priority_queue.h"

typedef struct param_s
{
	pq_cmp_t cmp;
	void *param;
} param_t;

struct p_queue
{
	sol_t *sl;
	param_t param_s;
};

/**
 * Returns 1 if the user's compare function returns 1 or 0, meaning that data1
 * has more priority over data2, otherwise data2 has more priority over data1
 */
static int AdjustIsBefore(const void *data1, const void *data2, void *param_s)
{
	return ((((param_t *)param_s)->cmp(data1, data2, ((param_t *)param_s)->param))
									 >= 0);
}

pq_t *PQCreate(pq_cmp_t compare, void *param)
{
	pq_t *pq = (pq_t *)malloc(sizeof(pq_t));

	if (NULL == pq)
	{
		PRNT_ERR("Malloc allocation failed");
		return (NULL);
	}

	pq->param_s.cmp = compare;
	pq->param_s.param = param;

	pq->sl = SortedListCreate(AdjustIsBefore, &(pq->param_s));

	if (NULL == pq->sl)
	{
		PRNT_ERR("Malloc allocation failed");

		free(pq); pq = NULL;

		return (NULL);
	}

	return (pq);
}

void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);

	SortedListDestroy(pq->sl);

	free(pq); pq = NULL;
}

int PQPush(pq_t *pq, void *data)
{
	assert(NULL != pq);

	/**
	 * if the insert was successful, the new element and end will not be the
	 * same
	 */
	return (SortedListIsSameIterator(SortedListEnd(pq->sl),
			SortedListInsert(pq->sl, data)));
}

void *PQPop(pq_t *pq)
{
	assert(NULL != pq);

	return (SortedListPopFront(pq->sl));
}

void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);

	return (SortedListGetData(SortedListBegin(pq->sl)));
}

size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);

	return (SortedListSize(pq->sl));
}

int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);

	return (SortedListIsEmpty(pq->sl));
}

void PQClear(pq_t *pq)
{
	assert(NULL != pq);

	while (!PQIsEmpty(pq))
	{
		SortedListPopFront(pq->sl);
	}
}

void *PQErase(pq_t *pq, pq_is_match_t is_match, void *param)
{
	void *result = NULL;
	sol_iter_t iter = NULL;

	assert(NULL != pq);

	/**
	 * find where the condition is satisfied in the list, or the end
	 * otherwise
	 */
	iter = SortedListFindIf((is_findif_t)is_match,
							 param,
							 SortedListBegin(pq->sl),
							 SortedListEnd(pq->sl));

	/* condition wasn't satisfied within the entire queue */
	if (iter == SortedListEnd(pq->sl))
	{
		return (NULL);
	}

	/* Store pointer to the data*/
	result = SortedListGetData(iter);

	/* Remove the element */
	SortedListRemove(iter);

	return (result);
}
