#ifndef __OL73_AVL_TREE_H__
#define __OL73_AVL_TREE_H__

#include <stddef.h> /*size_t */

/* this is the typedef for the avl tree. This will be used as a
 pointer to the avl */
typedef struct avl_tree_s avl_t;

/* typedef for the compare function of the avl tree. Compare must
 return value less than/ equal to/ greater than 0 when data1 is less than
 equal to/ greater than data2 respectivly*/
typedef int (*avl_cmp_t)(const void *data1, const void *data2);

/* this typedef is for the act_t function for ForEach, act function must return
 0 for success and anything else for failure*/
typedef int (*act_t)(void *data, void* param);


/**
 * Create new avl tree
 * @param avl_cmp compare function of the AVL
 * @param param ptr to compare function parameters
 * @return ptr to AVL, returns NULL on error
 * @complexity
 */
avl_t *AVLCreate(avl_cmp_t avl_cmp);

/**
 * Destroy and free avl tree
 * @param avl ptr to avl tree
 * @complexity O(n)
 */
void AVLDestroy(avl_t *avl);

/**
 * Insert new data to AVL.
 * @param avl ptr to AVL
 * @param data ptr to data
 * @return 0 if insert succeed, and non zero otherwise.
 * @complexity O(log(n))
 */
int AVLInsert(avl_t *avl, void *data);

/**
 * Remove data from AVL.
 * @param ptr to data in the avl tree.
 * @complexity O(log(n))
 */
void AVLRemove(avl_t *avl, void *data);

/**
* Calculates the Height of an avl tree.
* @param avl ptr to avl tree.
* @return the height of tree, return value of empty avl is undefined.
* @complexity O(1)
*/
size_t AVLHeight(const avl_t *avl);

/**
 * Count number of data nodes.
 * @param avl ptr to avl.
 * @return number of data nodes.
 * @complexity O(n)
 */
size_t AVLSize(const avl_t *avl);

/**
 * Check if avl tree is empty.
 * @param avl ptr to AVL
 * @return 1 if empty, 0 otherwise
 * @complexity O(1)
 */
int AVLIsEmpty(const avl_t *avl);

/**
 * Find data in AVL according to the compare function.
 * @param avl ptr to avl tree.
 * @param data_to_find ptr to data to find
 * @return ptr to data in avl, returns NULL if did not find.
 * @complexity O(log(n))
 */
void *AVLFind(avl_t *avl, const void *data_to_find);

/**
 * Act on each data in the AVL in given range.
 * @param act ptr to action function
 * @param param ptr to parameters to action function
 * @return 0 if succesfull. If a call to act failed returns immediately  the
 *  act return value.
 * @complexity O(n)
 */
int AVLForEach(avl_t *avl, act_t act, void *param);

#endif /* __OL73_AVL_TREE_H__ */
