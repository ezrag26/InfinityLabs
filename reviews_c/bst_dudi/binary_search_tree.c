
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "binary_search_tree.h"
#include "utils.h"

typedef struct bst_node_s bst_node_t;
typedef  enum which_child{LEFT, RIGHT}which_child_t;

struct bst_node_s
{
    void *data;
    bst_node_t *children[2];
    bst_node_t *parent;
} ;

struct binary_search_tree_s
{
    bst_node_t sentinel;
    bst_cmp_t bst_cmp;
    void *param;
} ;

bst_t *BSTCreate(bst_cmp_t bst_cmp, void *param)
{
	bst_t * bst = (bst_t *)malloc(sizeof(bst_t));
	if (NULL == bst)
	{
		PRINT_ERR("Memory allocate failed");
		return (NULL);
	}

	/* initialize fields of main struct: */
 	bst->bst_cmp = bst_cmp;
	bst->param = param;

	/* initialize fields of sentinel:  */
	(bst->sentinel).data = NULL;
	(bst->sentinel).parent = NULL;
	(bst->sentinel).children[0] = NULL;
	(bst->sentinel).children[1] = NULL;

	return (bst);
}

/* check the smallest node of a given root:  */
static bst_iter_t BSTMostLeft(const bst_iter_t base)
{
	bst_iter_t current = NULL;

	assert(NULL != base);
	current = base;

	while(NULL != (current->children)[0])
	{
		current = (bst_iter_t)((current->children)[0]);
	}

	return(current);
}

/* check the biggest node of a given root:  */
static bst_iter_t BSTMostRight(const bst_iter_t base)
{
	bst_iter_t current = NULL;

	assert(NULL != base);
	current = base;

	while(NULL != (current->children)[1])
	{
		current = (bst_iter_t)((current->children)[1]);
	}

	return(current);
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_iter_t current = NULL;

	assert(NULL != bst);
	/* initialize current to sentinel: */
	current = (bst_iter_t)(&(((bst_t *)bst)->sentinel));

	/* return the smallest node or sentinel if empty: */ 
	return(BSTMostLeft(current));
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	assert(NULL != bst);

	return ((bst_iter_t)&(((bst_t *)bst)->sentinel));
}

bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_iter_t find_next = iter;

	assert(NULL != iter);

	/* check if there is a bigger node underneath iter: */
	if(NULL != iter->children[1])
	{
		find_next = BSTMostLeft(iter->children[1]);
	}
	/* if there isnt, check who is the bigger above: */
	else
	{
		while(find_next->parent->children[0] != find_next)
		{
			find_next = find_next->parent;
		}
		find_next = find_next->parent;
	}
	
	return (find_next);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_iter_t find_prev = iter;

	assert(NULL != iter);

    /* check if there is a smaller node underneath iter: */
	if(NULL != iter->children[0])
	{
		find_prev =  BSTMostRight(iter->children[0]);
	}
	/* if there isnt, check who is the smaller above: */
	else
	{
		while(find_prev->parent->children[1] != find_prev)
		{
			find_prev = find_prev->parent;
		}
		find_prev = find_prev->parent;
	}
	
	return (find_prev);
}

/* creating a new node: */
static bst_node_t *BSTCreateNewNode()
{
	bst_node_t *new_node = (bst_node_t *)malloc(sizeof(bst_node_t));

	return (new_node);
}

/* insert a new node to the binary tree: */
static bst_iter_t BSTInsertLeafAfter(bst_t *bst, bst_iter_t parent,
									 bst_iter_t data, which_child_t which_child)
{
	bst_node_t *new_node = BSTCreateNewNode();
	if(NULL == new_node)
	{
		PRINT_ERR("allocate failed")
		return (BSTEnd(bst));
	}

	/* initialize the fields of the new node, and its parent: */
	parent->children[which_child] = new_node;
	new_node->data = data;
	new_node->children[0] = NULL;
	new_node->children[1] = NULL;
    new_node->parent = parent;

	return ((bst_iter_t)new_node);
}

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
	bst_iter_t parent = NULL;
	bst_iter_t current = NULL;
	which_child_t which_child = LEFT;

	assert(NULL != bst);

	/* start at root: */
	parent = &(bst->sentinel);
	current = (bst->sentinel).children[0];

	/* finding the right location of the new node: */
	while(NULL != current)
	{
		parent = current;

		/* if new data is bigger than the current node: */
		if(bst->bst_cmp(data, current->data, bst->param) > 0)
		{
			which_child = RIGHT;
		}

		/* if new data is smaller than the current node: */
		else if(bst->bst_cmp(data, current->data, bst->param) < 0)
		{		
			which_child = LEFT;
		}

		/* if the new data is already exist: */
		else 
		{
			return(BSTEnd(bst));
		}

		current =  current->children[which_child];
	}

	return(BSTInsertLeafAfter(bst,parent, data, which_child));
}

int BSTIsEmpty(const bst_t *bst)
{
	int is_empty = 0;

	if (NULL == (bst->sentinel).children[0])
	{
		is_empty = 1;
	}

	return(is_empty);
}

int BSTIsSameIterator(bst_iter_t iter1, bst_iter_t iter2)
{
	return(iter1 == iter2);
}

void *BSTGetData(bst_iter_t iter)
{
	assert(NULL != iter);

	return(iter->data);
}

size_t BSTSize(const bst_t *bst)
{
	bst_iter_t current = NULL;
	size_t size = 0;

	assert(NULL != bst);

	current = BSTBegin(bst);

	while(!BSTIsSameIterator(current, BSTEnd(bst)))
	{
		current = BSTNext(current);	
		++size;
	}

	return(size);
}

/* finding in what parent branch iter exist: */
static which_child_t BSTWhatBranch(bst_iter_t iter)
{
	bst_iter_t parent = NULL;
	which_child_t which_child= 0;

	assert(NULL != iter);
	
	parent = iter->parent;

	if(BSTIsSameIterator(parent->children[LEFT], iter))
	{
		which_child = LEFT;
	}	
	else
	{
		which_child = RIGHT;
	}

	return (which_child);
}

static void BSTRemoveNoChildCase(bst_iter_t iter)
{
	bst_iter_t parent = NULL;
	which_child_t which_child= 0;

	assert(NULL != iter);
	parent = iter->parent;

	/* disconnecting iter from the tree */
	which_child = BSTWhatBranch(iter);
	parent->children[which_child] = NULL;
	
	free(iter); iter = NULL;
}

void BSTRemoveTwoChildCase(bst_iter_t to_be_removed)
{
	bst_iter_t to_be_connected = BSTMostRight(to_be_removed->children[0]);
	bst_iter_t to_be_connected_parent = to_be_connected->parent;
	which_child_t which_branch_discon = BSTWhatBranch(to_be_removed);
	
	/* set parent to_be_removed parent: */
	(to_be_removed->parent)->children[which_branch_discon] = to_be_connected;
	(to_be_connected->parent) = (to_be_removed->parent);

	/* set right child:: */
	(to_be_connected)->children[RIGHT] = to_be_removed->children[RIGHT];
	to_be_removed->children[RIGHT]->parent = to_be_connected;

	/* if to be removed iter is not the parent of most right: */
	if(!BSTIsSameIterator(to_be_connected_parent, to_be_removed))
	{
		to_be_connected_parent->children[1] = to_be_connected->children[0];

		/*if to_be_connected has a child: */
		if(NULL != to_be_connected->children[0])
		{
			to_be_connected->children[0]->parent = to_be_connected->parent;
		}
		/* set left child:: */
		(to_be_connected->children)[LEFT] = to_be_removed->children[LEFT];
		(to_be_removed)->children[LEFT]->parent = to_be_connected;
	}
	
	free(to_be_removed); to_be_removed = NULL;
}

void BSTRemoveOneChildCase(bst_iter_t iter)
{
	bst_iter_t child = NULL;
	which_child_t which_branch = 0;

	assert(NULL != iter);

	/* connecting child to parent */
	child = ((iter->children[0] != NULL) ? iter->children[0] :
								           iter->children[1]);  
	child->parent = iter->parent;

	/* connecting parent to child */
	which_branch = BSTWhatBranch(iter);
	iter->parent->children[which_branch] = child;

	free(iter); iter = NULL;
}

void *BSTRemove(bst_iter_t iter)
{
	void *data = NULL;
	int children_num = 0;

	assert(NULL != iter);
	
	data = iter->data;
	children_num = (NULL != iter->children[LEFT]) +
				   (NULL != iter->children[RIGHT]);

 	switch (children_num)
	 {
	 case 0:
		BSTRemoveNoChildCase(iter);
		break;

	 case 1:
		BSTRemoveOneChildCase(iter);	
		break;
	 
	 case 2:
		BSTRemoveTwoChildCase(iter);
		break;
	 } 

	return(data);
}

void BSTDestroy(bst_t *bst)
{
	bst_iter_t  next = NULL;
	bst_iter_t  runner = NULL;
	bst_iter_t  end = NULL;

	assert(NULL != bst);

	end = BSTEnd(bst);
	runner = BSTBegin(bst);
	next = runner;

	while(!BSTIsSameIterator(runner, end))
	{
		next = BSTNext(runner);
		BSTRemove(runner);
		runner = next;
	}

	free(bst); bst = NULL;
}

int BSTForEach(bst_iter_t begin, bst_iter_t end, act_t act, void *param)
{
	bst_iter_t  runner = NULL;
	int result = 0;

	assert(NULL != begin);
	assert(NULL != end);

	for(runner = begin; !BSTIsSameIterator(runner, end) && result == 0;
													 runner = BSTNext(runner))
	{
		result = act(BSTGetData(runner), param);	
	}

	return result;
}

bst_iter_t BSTFind(bst_t *bst, const void *data_to_find)
{
	bst_iter_t current = NULL;
	which_child_t which_child = 0;

	assert(NULL != bst);

	/* start at root: */
	current = (bst->sentinel).children[0];

	/* finding the data: */
	while(NULL != current)
	{
		/* if new data is bigger than the current node: */
		if(bst->bst_cmp(data_to_find, current->data, bst->param) > 0)
		{
			which_child = RIGHT;
		}

		/* if new data is smaller than the current node: */
		else if(bst->bst_cmp(data_to_find, current->data, bst->param) < 0)
		{		
			which_child = LEFT;
		}

		/* if the data fount: */
		else 
		{
			return (current);	
		}

		current =  current->children[which_child];
	}

	return(BSTEnd(bst));
}
