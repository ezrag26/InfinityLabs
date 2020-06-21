#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <stddef.h> /* size_t */

/* this is the typedef for the binary search tree. This will be used as a
 pointer to the BST */
typedef struct binary_search_tree_s bst_t;

/* typedef for the compare function of the binary search tree. Compare must
 return value less than/ equal to/ greater than 0 when data1 is less than
 equal to/ greater than data2 respectivly*/
typedef int (*bst_cmp_t)(const void *data1, const void *data2, void *param);

/* this typedef is for the act_t function for ForEach, act function must return
 0 for success and anything else for failure*/
typedef int (*act_t)(void *data, void *param);

/* this is the typedef for the iterator of the binary search tree. DO NOT TRY
 TO USE THE BST_NODE_T AS ITS IMPLEMENTATION CAN CHANGE WITHOUT WARNING */
typedef struct bst_node_s *bst_iter_t;


/**
 * Create new binary search tree
 * @param bst_cmp compare function of the BST
 * @param param ptr to compare function parameters
 * @return ptr to BST, returns NULL on error
 * @complexity O(1) or malloc
 */
bst_t *BSTCreate(bst_cmp_t bst_cmp, void *param);

/**
 * Destroy and free binary search tree
 * @param bst ptr to binary search tree
 * @complexity O(n) or free
 */
void BSTDestroy(bst_t *bst);

/**
 * Insert new data to BST.
 * @param bst ptr to BST
 * @param data ptr to data
 * @return iterator to new data, returns END iterator on error or if compare
 * key already exists.
 * @complexity O(n)
 */
bst_iter_t BSTInsert(bst_t *bst, void *data);

/**
 * Remove data from BST.
 * @param iter iterator to data in BST
 * @return ptr to data
 * @complexity O(n)
 */
void *BSTRemove(bst_iter_t iter);

/**
 * Count number of data nodes.
 * @param bst ptr to BST
 * @return number of data nodes.
 * @complexity O(n)
 */
size_t BSTSize(const bst_t *bst);

/**
 * Check if binary search tree is empty.
 * @param bst ptr to BST
 * @return 1 if empty, 0 otherwise
 * @complexity O(1)
 */
int BSTIsEmpty(const bst_t *bst);

/**
 * Get the iterator for the smallest data according to compare function.
 * @param bst ptr to BST
 * @return iterator to smallest data, or END for empty BST.
 * @complexity O(n)
 */
bst_iter_t BSTBegin(const bst_t *bst);

/**
 * Get the END iterator.
 * @param bst ptr to BST
 * @return iterator to END.
 * @complexity O(1)
 */
bst_iter_t BSTEnd(const bst_t *bst);

/**
 * Get the next iterator according to compare function.
 * @param iter iterator to data in BST
 * @return iterator to the next data
 * next of the END iterator will have undefined behavior.
 * @complexity O(n)
 */
bst_iter_t BSTNext(bst_iter_t iter);

/**
 * Get the previous iterator according to compare function.
 * @param iter iterator to data in BST
 * @return iterator to previous data
 * previous of the smallest data will have undefined behavior
 * @complexity O(n)
 */
bst_iter_t BSTPrev(bst_iter_t iter);

/**
 * Get the data stored at iter in BST.
 * @param iter iterator to data in BST
 * @return ptr to data
 * getting data of END iterator will result in undefined behavior.
 * @complexity O(1)
 */
void *BSTGetData(bst_iter_t iter);

/**
 * Check if iter1 and iter2 are the same iterator.
 * @param iter1 iterator to BST
 * @param iter2 iterator to BST
 * @return 1 if iterators are the same, 0 otherwise.
 * @complexity O(1)
 */
int BSTIsSameIterator(bst_iter_t iter1, bst_iter_t iter2);

/**
 * Find data in BST according to the compare function.
 * @param bst ptr to binary search tree.
 * @param data_to_find ptr to data to find
 * @return iterator to data in BST, returns END if did not find.
 * @complexity O(n)
 */
bst_iter_t BSTFind(bst_t *bst, const void *data_to_find);

/**
 * Act on each data in the BST in given range.
 * @param begin iterator to beginning of range
 * @param end iterator at the end of range (not included in search)
 * @param act ptr to action function
 * @param param ptr to parameters to action function
 * @return 0 if succesfull. If a call to act failed returns immediately  the
 *  act return value.
 * @complexity O(n)
 */
int BSTForEach(bst_iter_t begin, bst_iter_t end, act_t act, void *param);

#endif /* __BINARY_SEARCH_TREE_H__ */
