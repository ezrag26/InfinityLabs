#ifndef __OL73_LINKED_LIST_H__
#define __OL73_LINKED_LIST_H__

#include <stddef.h> /* size_t */
#include "utils.h"

typedef struct sll_node sll_node_t;
typedef int (*compare_t)(const void *current_data, const void *data_to_find);
typedef int (*action_t)(void *data, void *param);

struct sll_node
{
	void *data;
	sll_node_t *next;
};
/*
*	Creates node based on data and next node
*	Returns address of new node
*	Complexity: O(n)
*/
sll_node_t *SLLCreateNode(void *data, sll_node_t *next);

/*
*	Free all nodes of root
*	Returns nothing
*	Complexity: O(n)
*/
void SLLFreeAll(sll_node_t *root);

/*
*	Insert node after where's location
*	Returns address where node was inserted
*	Complexity: O(1)
*/
sll_node_t *SLLInsertAfter(sll_node_t *where, sll_node_t *node);

/*
*	Inster node at where's location
*	Returns address where node was inserted
*	where pointer becomes invalid
*	Complexity: O(1)
*/
sll_node_t *SLLInsert(sll_node_t *where, sll_node_t *node);

/*
*	Remove node after node's location
*	Returns address where node was inserted
*	Complexity: O(1)
*/
sll_node_t *SLLRemoveAfter(sll_node_t *node);

/*
*	Remove node
*	Returns address where node was inserted
*	where pointer becomes invalid
*	Complexity: O(1)
*/
sll_node_t *SLLRemove(sll_node_t *node);

/*
*	Finds a node based on a given data_to_find using a given compare function
		between each node's data and the data_to_find. Runs on each node if no
		match was found
*	Returns address of first instance where node's data and data_to_find are
		equal, or NULL if not found
*	Complexity: O(n)
*/
sll_node_t *SLLFind(sll_node_t *root, void *data_to_find,
			   int (*compare)(const void *current_data, const void *data_to_find));

/*
*	Performs an action on each node based on a given function on the data and
		param
*	Returns 0 if the action was successfully performed on each node, 1 on
		failure
*	Complexity: O(n)
*/
int SLLForEach(sll_node_t *root, int (*act)(void *data, void *param), void *param);

/*
*	Count number of nodes in a list
*	Returns number of nodes in the list. A list with a loop will result in a
		segmentation fault
*	Complexity: O(n)
*/
size_t SLLCount(const sll_node_t *root);

/*
*	Flips the list direction
*	Returns address of new root in the list
*	Complexity: O(n)
*/
sll_node_t *SLLFlip(sll_node_t *root);
sll_node_t *SLLRecFlip(sll_node_t *root);

/*
*	Finds the intersection of two lists
*	Returns address of the intersecting node
*	Complexity: O(n)
*/
sll_node_t *SLLFindIntersection(const sll_node_t *root1, const sll_node_t *root2);

/*
*	Checks if the list has a loop
*	Returns 1 if list has a loop, 0 if it does not
*	Complexity: O(n)
*/
int SLLHasLoop(const sll_node_t *root);

#endif /* __OL73_LINKED_LIST_H__ */
