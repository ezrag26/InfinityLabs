/*
 * Date: 4.9.19
 * Developer: Naama
 * Reviewer: Yossi
 * Status: S
 */

#ifndef __OL73_LINKED_LIST_H__
#define __OL73_LINKED_LIST_H__

typedef struct sll_node sll_node_t;

struct sll_node
{
	void *data;
	sll_node_t *next;
};

typedef int (*cmp_t)(const void *current_data, const void *data_to_find);
typedef int (*act_t)(void *data, void *param);
#include <stddef.h> /*size_t*/


/*
 * recieves a void pointer to data and address of the next node of type
 * sll_node_t create new node, possible next node if wanted. if not wanted -
 * next node is null.
 * return value: address of the new created node, of type sll_node_t.
 * complexity: O(1)
 */
sll_node_t *SLLCreateNode(void *data, sll_node_t *next);

/*
 * recieves the pointer to the root of list of type sll_node_t
 * free all the nodes until encounter the last one, that points to NULL.
 * return value: no return value.
 * complexity: O(n)
 */
void SLLFreeAll(sll_node_t* root);


/* recieves an sll_node_t pointer the node we want to insert (node), and an
 * sll_node_t pointer to the address of node that suppose to point at him
 * (where).
 * return value: an sll_node_t pointer to the new node.
 * complexity: O(1)
 */
sll_node_t *SLLInsertAfter(sll_node_t* where, sll_node_t *node);



/* recieves an sll_node_t pointer the node we want to insert (node), and an
 * sll_node_t pointer to the address of node we want to point with the new node.
 * The pointer to the old node becomes invalid.
 * return value: an sll_node_t pointer to the new node.
 * complexity: O(1)
 */
sll_node_t * SLLInsert(sll_node_t* where, sll_node_t* node);



/* recieves an sll_node_t pointer the node and remove following node
 * return value: an sll_node_t pointer to the new node.
 * complexity: O(1)
 */
sll_node_t *SLLRemoveAfter(sll_node_t* node);




/* recieves an sll_node_t pointer the node and remove the node
 * return value: an sll_node_t pointer to the removed node. The pointer to the
 * old node becomes invalid.
 * return value:
 * WARNING: won't remove the last node.
 * complexity: O(1)
 */
sll_node_t *SLLRemove(sll_node_t* node);



/*
 * recieves a const sll_node_t pointer the root, const void pointer to data to
 * find and a pointer to a function. (loops through the whole list).
 * the function recieves the const void pointer to current data in the node and
 * const void pointer to the data to find and compare their value.
 * return value in the function required to be  0 for a match between the data
 * and 1 if it didn't match.
 * return value: an sll_node_t pointer to the node with the requested data.
 * complexity: O(n)
 */
sll_node_t *SLLFind(const sll_node_t *root, const void *data_to_find,
 																cmp_t func_cmp);



/*
 * recieves a sll_node_t pointer the root, a pointer to a function act and
 * a parameter needed for the act function (optional), of type void pointer.
 * the function recieves the const void pointer to current data in the node and
 * void pointer to the data to the paramater, and performs an act on every node
 * in the list.
 * return value of the function act is 0 for success and 1 for failure.
 * return value: 0 for success and 1 for failure of type int
 * complexity: O(n)
 */
int SLLForEach(sll_node_t *root, act_t func_act, void *param);

/*
 * recieves a const sll_node_t pointer the root and checks how many nodes are
 * connected. (loops through the whole list).
 * return value: size_t number of connected nodes.
 * complexity: O(n)
 */
size_t SLLCount(const sll_node_t *root);

/*
 * recieves a const sll_node_t pointer the root and flips the direction of the
 * list (points backwars). (function loops through the whole list).
 * return value: sll_node_t pointer the root.
 * complexity: O(n)
 */
sll_node_t *SLLFlip(sll_node_t *root);

/*
 * recieves two const sll_node_t pointer for 2 different roots. given there is
 * an intersection between the roots, function checks and returns the
 * intersection node. function go over the whole list.
 * return value: sll_node_t pointer to the intersection between roots.
 * complexity: O(n)
 */
sll_node_t *SLLFindIntersection(const sll_node_t *root1,
                           const sll_node_t *root2);

/* recieves a const sll_node_t pointer the root and checks if there is a loop in
 * the sll. if there is a loop, function loops through the whole list.
 * returns int - 1 if it contains a loop and 0 if not.
 * complexity: O(n)
 */
int SLLHasLoop(const sll_node_t *root);

/*
 * recieves a const sll_node_t pointer the root and flips the direction of the
 * list (points backwars). (function loops through the whole list, recursively).
 * return value: sll_node_t pointer the root.
 * complexity: O(n)
 */
sll_node_t *SLLFlipRec(sll_node_t *root);

#endif /* __OL73_LINKED_LIST_H__ */
