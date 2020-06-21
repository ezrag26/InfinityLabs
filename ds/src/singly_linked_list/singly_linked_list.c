/*
*	Developer: Ezra
*	Reviewer: Lazy
*	Date: 4/9/2019
*	Status: A
*/

#include <stdlib.h> /* malloc  */
#include <assert.h> /* assert  */
#include <stdio.h> /* fprintf */

#include "singly_linked_list.h"

#ifndef NDEBUG
#define PRNT_ERR(x) (fprintf(stderr, x"\n"))
#else
#define PRNT_ERR(x)
#endif

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{
	sll_node_t *node = (sll_node_t *)malloc(sizeof(sll_node_t));

	if (NULL == node)
	{
		PRNT_ERR("Memory Allocation Error");
		return (NULL);
	}

	node->data = data;
	node->next = next;

	return (node);
}

void SLLFreeAll(sll_node_t *root)
{
	sll_node_t *tmp = NULL;

	while (NULL != root)
	{
		tmp = root->next;

		free(root); root = NULL;

		root = tmp;
	}
}

sll_node_t *SLLInsertAfter(sll_node_t *where, sll_node_t *node)
{
	node->next = where->next; 			   /* node's new next is where's next */
	where->next = node; 				/* where's new next is node's address */

	return (node);
}


sll_node_t *SLLInsert(sll_node_t *where, sll_node_t *node)
{
	sll_node_t *temp_next = NULL;
	void *temp_data = NULL;

	assert(NULL != where);
	assert(NULL != node);

	/* save where's data and next in temps */
	temp_next = where->next;
	temp_data = where->data;

	/* where's original data and next becomes node's new data and its address */
	where->data = node->data;
	where->next = node;

	/* node's new data and next become where's original data and next */
	node->data = temp_data;
	node->next = temp_next;

	return (where);						  /* returns where's original address */
}

sll_node_t *SLLRemoveAfter(sll_node_t *node)
{
	sll_node_t *tmp_remove_addr = NULL;

	assert(NULL != node);

	/* save the node's address that will be removed */
	tmp_remove_addr = node->next;

	node->next = node->next->next;	   /* node now points to node's next next */

	tmp_remove_addr->next = NULL; 	 /* removed node should now point to NULL */

	return (tmp_remove_addr);				 /* return removed node's address */
}

sll_node_t *SLLRemove(sll_node_t *node)
{
	sll_node_t *tmp_remove_next = NULL;
	void *tmp_remove_data = NULL;

	assert(NULL != node);

	if (NULL == node->next)
	{
		return (NULL);
	}

	/* save the node's data and next that will be removed */
	tmp_remove_next = node->next;
	tmp_remove_data = node->data;

	/* node's new data and new next is node->next's data and next */
	node->data = node->next->data;
	node->next = node->next->next;

	/* node that will be removed should point to NULL, but save the orig data */
	tmp_remove_next->next = NULL;
	tmp_remove_next->data = tmp_remove_data;

	return (tmp_remove_next);

}

sll_node_t *SLLFind(sll_node_t *root, void *data_to_find, compare_t Compare)
{
	sll_node_t *current_data = root;
	int was_not_found = 1;

	assert(NULL != root);
	assert(NULL != data_to_find);

	/* data wasn't found and there is another node to check */
	while (0 != was_not_found && NULL != current_data)
	{
		/* compare next data */
		was_not_found = Compare(current_data->data, data_to_find);

		/* found the data */
		if (0 == was_not_found)
		{
			return (current_data);
		}

		current_data = current_data->next; 				   /* go to next node */
	}

	return (current_data);
}

int SLLForEach(sll_node_t *root, action_t ActionFunction, void *param)
{
	sll_node_t *current_data = root;
	int func_return = 0;

	assert(NULL != root);
	assert(NULL != param);

	/* while function is successful and there is another node */
	while (0 == func_return && NULL != current_data)
	{
		func_return = ActionFunction(current_data->data, param);

		/* function wasn't successful */
		if (1 == func_return)
		{
			return (1);
		}

		current_data = current_data->next;				   /* go to next node */
	}

	return (0);

}

size_t SLLCount(const sll_node_t *root)
{
	sll_node_t *current_node = (sll_node_t *)root;
	size_t count = 0;

	while (NULL != current_node)			   /* while there is another node */
	{
		++count;
		current_node = current_node->next; 				   /* go to next node */
	}

	return (count);
}

sll_node_t *SLLFlip(sll_node_t *root)
{
	sll_node_t *tmp_next = NULL;
	sll_node_t *actual_next = NULL;
	sll_node_t *new_root = NULL;
	sll_node_t *current_node = NULL;

	assert(NULL != root);

	current_node = root;

	while (NULL != current_node)
	{
		new_root = current_node; 						/* save the last node */

		tmp_next = current_node->next;					 /* next node to flip */
		current_node->next = actual_next; 			   /* flipped node's next */
		actual_next = current_node;				  /* next flipped node's next */

		current_node = tmp_next;						 /* next node to flip */
	}

	return (new_root);
}

static sll_node_t *FlipWithNext(sll_node_t *root, sll_node_t *prev)
{
	sll_node_t *new_root = NULL;

	if (NULL != root->next)
	{
		new_root = root->next;					   /* next node to be flipped */
		root->next = prev;					  /* root points to previous node */
		return (FlipWithNext(new_root, root));
	}

	root->next = prev;			   /* last node points to second to last node */

	return (root);
}

sll_node_t *SLLRecFlip(sll_node_t *root)
{
	sll_node_t *prev = NULL;

	assert(NULL != root);

	return (FlipWithNext(root, prev));
}

sll_node_t *SLLFindIntersection(const sll_node_t *root1, const sll_node_t *root2)
{
	sll_node_t *temp_node1 = (sll_node_t *)root1;
	sll_node_t *temp_node2 = (sll_node_t *)root2;
	size_t root1_len = 0;
	size_t root2_len = 0;
	size_t len_difference = 0;

	assert(NULL != root1);
	assert(NULL != root2);

	/* find lengths of each linked list */
	root1_len = SLLCount(temp_node1);
	root2_len = SLLCount(temp_node2);

	/* find difference in length */
	len_difference = MAX(root1_len, root2_len) - MIN(root1_len, root2_len);

	/* remove difference in length */
	if (root1_len > root2_len)
	{
		while (len_difference--)
		{
			temp_node1 = temp_node1->next;
		}
	}
	else
	{
		while (len_difference--)
		{
			temp_node2 = temp_node2->next;
		}
	}

	/* while nodes are not the same, go to next node in each list */
	while (temp_node1 != temp_node2)
	{
		temp_node1 = temp_node1->next;
		temp_node2 = temp_node2->next;
	}

	return (temp_node1);
}

int SLLHasLoop(const sll_node_t *root)
{
	sll_node_t *slow_p = (sll_node_t *)root;
	sll_node_t *fast_p = NULL;

	assert(NULL != root);

	fast_p = (sll_node_t *)root->next;		   /* start fast_p one node ahead */

	/* the ptrs not on the same node, fast_p and fast_p->next are not NULL */
	while (slow_p != fast_p && fast_p != NULL && fast_p->next != NULL)
	{
		slow_p = slow_p->next;							   /* go to next node */
		fast_p = fast_p->next->next;						 /* skip one node */
	}

	/* if they are on the same node, it's a loop */
	if (slow_p == fast_p)
	{
		return (1);
	}

	return (0);
}
