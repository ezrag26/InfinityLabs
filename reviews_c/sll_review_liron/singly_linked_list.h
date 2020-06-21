#ifndef __OL73_LINKED_LIST_H__
#define __OL73_LINKED_LIST_H__

typedef struct sll_node sll_node_t;

struct sll_node
{
	void *data;
	sll_node_t *next;
};


/* allocation and create new node,
 * size of alloation is size of type sll_node_t. 
 * possible next node if wanted
 * return value: pointer to new node with the data
 * Time compexity: O(1) */
sll_node_t *SLLCreateNode(void *data, sll_node_t *next);

/* destroy all nodes! 
 * start from root and destroy all next nodes in his list 
 * Time compexity: O(n) */
void SLLFreeAll(sll_node_t* root);


/* put node after the adrress of where,
 * return value: adrress of node.
 * Time compexity: O(1) */
sll_node_t *SLLInsertAfter(sll_node_t* where, sll_node_t *node);


/* put new node before the node in addrres where.
 ** worning:the address of pointers that you keep in your program my change. 
 * return value: return the address of node after the adding to the list 
 * Time compexity: O(1) */
sll_node_t * SLLInsert(sll_node_t* where, sll_node_t* node);


/* remove following node,
 * return value: returns removed node,the next pointer in the remove 
 * node is NULL.
 * Time compexity: O(1) */
sll_node_t *SLLRemoveAfter(sll_node_t* node);

/* remove send node,
 ** worning: is undefined behavior is you try to remove the last node in the. 
 * return value: returns removed node,the next pointer in the remove 
 * node is NULL.
 * Time compexity: O(1) */
sll_node_t *SLLRemove(sll_node_t* node);


/* find node with same data, cmp must return success return(0 to cmp).
 * return value: returns the pointer with the compared data.
 * Time compexity: O(n) */
sll_node_t *SLLFind(const sll_node_t *root,
                const void *data_to_find,
 int (*cmp)(const void *current_data, const void *data_to_find));
typedef int (*cmp_t)(const void *current_data, const void *data_to_find);


/* act on each node, act must be a function that returns seccess return 
 * Time compexity: O(n) */
int SLLForEach(sll_node_t *root, int (*act)(void *data, void *param), void *param);
typedef int (*act_t)(void *data, void *param);

/* return number of connected nodes 
 * Time compexity: O(n) */
size_t SLLCount(const sll_node_t *root);

/* flip all the nodes
 * return value: return the new root to the flip list.
 * Time compexity: O(n) */
sll_node_t *SLLFlip(sll_node_t *root);

/* return node that is an intersection between roots or NULL.
 * Time compexity: O(n) */
sll_node_t *SLLFindIntersection(const sll_node_t *root1, 
                           const sll_node_t *root2);

/* returns 1 if has loop 
 * Time compexity: O(n) */
int SLLHasLoop(const sll_node_t *root);

#endif /* __OL73_LINKED_LIST_H__ */
