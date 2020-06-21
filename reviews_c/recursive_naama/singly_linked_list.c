/*******************************************************************************
*																			   *
*	DataStructurs - Queue - API												   *
*	Developer: Naama													   	   *
*	Reviwer: Erez															   *
*	Status: S													 			   *
*																			   *
*******************************************************************************/

#include "singly_linked_list.h"
#include "utils.h"


#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*malloc*/

sll_node_t *SLLCreateNode(void *data, sll_node_t *next)
{

	sll_node_t *node = (sll_node_t *)(malloc(sizeof(sll_node_t)));

	if (NULL == node)
	{
		PRNT_ERR("Error allocating memory.");
		return (node);
	}

	node->data = data;
	node->next = next;

	return (node);

}

void SLLFreeAll(sll_node_t *root)
{
	sll_node_t *temp = NULL;

	while (NULL != root)
	{
		temp = root->next;
		free(root); root = temp;
	}
}


sll_node_t *SLLInsertAfter(sll_node_t *where, sll_node_t *node)
{
	assert(NULL != where);
	assert(NULL != node);

	node->next = where->next;
	where->next = node;

	return (node);
}

sll_node_t *SLLInsert(sll_node_t *where, sll_node_t *node)
{
	void *temp = NULL;

	assert(NULL != where);
	assert(NULL != node);

	temp = where->data;
	where->data = node->data; /*switch the data pointer between 2 nodes*/
	node->data = temp;

	SLLInsertAfter(where, node); /*insert the new node after the original one*/

	return (where);

}

sll_node_t *SLLRemoveAfter(sll_node_t *node)
{
	sll_node_t *removed_node = NULL;

	assert(NULL != node);

	removed_node = node->next;
	node->next = node->next->next;
	removed_node->next = NULL;

	return (removed_node);
}


sll_node_t *SLLRemove(sll_node_t *node)
{
	void *temp = NULL;

	assert(NULL != node);
	assert(NULL != node->next);

	temp = node->data; /*switch the data pointer between 2 nodes*/
	node->data = node->next->data;
	node->next->data = temp;

	return(SLLRemoveAfter(node)); /*remove unwanted node*/
}

sll_node_t *SLLFind(const sll_node_t *root, const void *data_to_find,
 																cmp_t func_cmp)
{
	unsigned int flag = 1;
	sll_node_t *temp = NULL;

	assert(NULL != root);

	temp = (sll_node_t *)root;

	while(NULL != temp)
	{
		assert(NULL != temp->data);

		flag = func_cmp(temp->data, data_to_find);
		if(0 == flag)
		{
			break;
		}
		temp = temp->next;
	}
	return ((sll_node_t *)temp);
}
int SLLForEach(sll_node_t *root, act_t func_act, void *param)
{
	int flag = 0;
	sll_node_t *temp = NULL;

	assert(NULL != root);

	temp = root;

	while ((NULL != temp) && (1 != flag))
	{

		flag = func_act(temp->data, param);

		temp = temp->next;
	}
	return (flag);
}

size_t SLLCount(const sll_node_t *root)
{
	size_t num_nodes = 0;
	sll_node_t *temp = NULL;

	temp = (sll_node_t *)root;

	while(NULL != temp)
	{
		temp = temp->next;
		++num_nodes;
	}

	return (num_nodes);
}

sll_node_t *SLLFlip(sll_node_t *root)
{
	sll_node_t *temp_prev = NULL;
	sll_node_t *temp_follow = NULL;
	sll_node_t *temp = NULL;

	assert(NULL != root);

	temp = root;

	temp_follow = temp->next;

	while(NULL != temp_follow) /* switching direction of pointers */
	{
		temp->next = temp_prev;
		temp_prev = temp;
		root = temp_follow;
		temp_follow = temp->next;
	}
	temp->next = temp_prev;

	return (root);
}

static sll_node_t *FlipRecAssist(sll_node_t *prev, sll_node_t *current)
{
	sll_node_t *temp = NULL;

	if (NULL == current -> next)
	{
		current->next = prev;
		return current;
	}

	temp = current -> next;
	current->next = prev;
	return(FlipRecAssist(current, temp));
}

sll_node_t *SLLFlipRec(sll_node_t *root)
{
	assert (NULL != root);

	root = (FlipRecAssist(NULL, root));

	return root;
}




sll_node_t *SLLFindIntersection(const sll_node_t *root1,
												 const sll_node_t *root2)
{
	sll_node_t *long_root = NULL;
	sll_node_t *short_root = NULL;

	size_t long_len = 0;
	size_t short_len = 0;
	size_t temp = 0;
	size_t difference = 0;
	size_t i = 0;

	assert(NULL != root1);
	assert(NULL != root2);

	long_len = SLLCount(root1);
	short_len = SLLCount(root2);

	long_root = (sll_node_t *)root1;
	short_root = (sll_node_t *)root2;

	/*check which sll is longer, and switch pointers and lengths if needed*/
	if (long_len < short_len)
	{
		short_root = (sll_node_t *)root1;
		long_root = (sll_node_t *)root2;

		temp = long_len;
		long_len = short_len;
		short_len = temp;
	}

	difference = long_len - short_len;

	for (i = 0; i < difference; ++i) /* make the lengths equal */
	{
		long_root = long_root->next;
	}

	while((long_root->next) != (short_root->next)) /*search the intersection*/
	{
		long_root = long_root->next;
		short_root = short_root->next;
	}

	return(long_root->next);
}

int SLLHasLoop(const sll_node_t *root)
{
	sll_node_t *root_skips_twice = NULL;
	int has_loop = 0;

	sll_node_t *temp = NULL;

	assert(NULL != root);

	temp = (sll_node_t *)root;

	root_skips_twice = (sll_node_t *)(temp->next);

	while (
			(root_skips_twice != temp) &&
			(NULL != (root_skips_twice))&&
			(NULL != (root_skips_twice->next))
		  )
	{
		temp = temp->next;
		root_skips_twice = root_skips_twice->next->next;
	}

	if (temp == root_skips_twice)
	{
		has_loop = 1;
	}

	return (has_loop);
}
