#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h>

#include "singly_linked_list.h"


#ifndef NDEBUG
#include <stdio.h>  /* PRINT_ERROR */
#define PRINT_ERROR(x)\
fprintf(stderr, "file name:%s | line:%d | error:%s\n", __FILE__, __LINE__, x);
#else
#define PRINT_ERROR(x)
#endif /* NDEBUG */



/*******************************************************************
 **********************  SLLCreateNode  ****************************
 *******************************************************************/

/* create new node */
sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *node = (sll_node_t *)malloc(sizeof(sll_node_t));

	if(!node)
	{
		PRINT_ERROR("malloc failed")

		return NULL;
	}

	node->data = data;
	node->next = next;

	return node;
}



/*******************************************************************
 *************************  SLLFreeAll  ****************************
 *******************************************************************/

/* destroy all nodes! */
void SLLFreeAll(sll_node_t* root)
{
	sll_node_t *current = root;
	sll_node_t *next = NULL;


	while(current)
	{
		next = current->next;

		free(current); current = NULL;

		current = next;
	}
}



/*******************************************************************
 *************************  SLLInsertAfter  ************************
 *******************************************************************/

/* put new node after dest */
sll_node_t *SLLInsertAfter(sll_node_t* where, sll_node_t *node)
{
	assert(NULL != where);
	assert(NULL != node);

	node->next = where->next;
	where->next = node;

	return node;
}



/*******************************************************************
 *************************  SLLInsert  *****************************
 *******************************************************************/

/* put new node before dest */
sll_node_t *SLLInsert(sll_node_t* where, sll_node_t* node)
{
	void *temp_data = NULL;
	sll_node_t *temp_next = NULL;

	assert(NULL != where);
	assert(NULL != node);

	temp_data =  where->data;
	temp_next = where->next;

	where->data = node->data;
	where->next = node;

	node->next = temp_next;
	node->data = temp_data;

	return where;
}



/*******************************************************************
 *************************  SLLRemoveAfter  ************************
 *******************************************************************/

/* remove following node, returns removed node */
sll_node_t *SLLRemoveAfter(sll_node_t* node)
{
	sll_node_t *remove_node = NULL;

	assert(NULL != node);

	remove_node = node->next;

	node->next = node->next->next;

	remove_node->next = NULL;

	return remove_node;
}



/*******************************************************************
 *************************  SLLRemove  *****************************
 *******************************************************************/

/* remove sent node, except last */
sll_node_t *SLLRemove(sll_node_t *node)
{
	void *r_node_data = NULL;
	sll_node_t *node_replace = NULL;

	assert(NULL != node);

	r_node_data = node->data;
	node_replace = node->next;

	node->data = (node->next)->data;
	node->next = (node->next)->next;

	node_replace->data = r_node_data;
	node_replace->next = NULL;

	return node_replace;
}



/*******************************************************************
 *************************  SLLFind  *******************************
 *******************************************************************/

/* find node with same data, cmp must return seccess returns */
sll_node_t *SLLFind(const sll_node_t *root, const void *data_to_find, cmp_t cmp)
{
	const sll_node_t *current_node = root;

	assert(NULL != data_to_find);
	assert(NULL != cmp);

	while(current_node)
	{
		if(!cmp(current_node->data, data_to_find))
		{
			return (sll_node_t *)current_node; /* found the data */
		}

		current_node = current_node->next;
	}

	return NULL;
}



/*******************************************************************
 *************************  SLLForEach  ****************************
 *******************************************************************/

/* act on each node, act must be a function that returns seccess returns */
int SLLForEach(sll_node_t *root, act_t act, void *param)
{
	sll_node_t *current_node = root;
	int status = 0;

	assert(NULL != param);
	assert(NULL != act);

	while((current_node) && (0 == status))
	{
		status = act(current_node->data, param);

		current_node = current_node->next;
	}

	return status;
}



/*******************************************************************
 *************************  SLLCount  ******************************
 *******************************************************************/

/* return number of connected nodes */
size_t SLLCount(const sll_node_t *root)
{
	size_t count = 0;

	assert(NULL != root);

	while(root)
	{
		++count;
		root = root->next;
	}

	return count;
}



/*******************************************************************
 *************************  SLLFlip  *******************************
 *******************************************************************/

/* flip all the nodes */
sll_node_t *SLLFlip(sll_node_t *root)
{
	sll_node_t *current = root;
	sll_node_t *next =  NULL;
	sll_node_t *prev = NULL;

	assert(NULL != root);

	next = root->next;

	while(next)
	{
		current->next = prev;
		prev = current;
		current = next;
		next = current->next;
	}

	current->next = prev;

	return current; /* now current is the new root after the flip */
}



/*******************************************************************
 *********************  SLLFindIntersection  ***********************
 *******************************************************************/

/* return node that is an intersection between roots */
sll_node_t *SLLFindIntersection(const sll_node_t *root1,
                           const sll_node_t *root2)
{
	const sll_node_t *big_list = root1;
	const sll_node_t *small_list = root2;
	size_t count_r1 = 0;
	size_t count_r2 = 0;
	size_t run_count = 0;

	assert(NULL != root1);
	assert(NULL != root2);

	count_r1 = SLLCount(root1);
	count_r2 = SLLCount(root2);
	run_count = count_r1 - count_r2;

	if(count_r1 < count_r2)
	{
		run_count = count_r2 - count_r1;
		big_list = root2;
		small_list = root1;
	}

	while(run_count)
	{
		big_list = big_list->next;
		--run_count;
	}

	while(big_list != small_list)
	{
		big_list = big_list->next;
		small_list = small_list->next;
	}

	/* return null if there is no intersection */
	return ((sll_node_t *)small_list);
}


/*******************************************************************
 *************************  SLLHasLoop  ****************************
 *******************************************************************/

/* returns 1 if has loop */
int SLLHasLoop(const sll_node_t *root)
{
	const sll_node_t *slow = root;
	const sll_node_t *fast = root;

	assert(NULL != root);

	while(slow && fast && fast->next)
	{
		slow = slow->next;
		fast = (fast->next)->next;

		if(slow == fast)
		{
			return 1;
		}
	}

	return 0;
}
