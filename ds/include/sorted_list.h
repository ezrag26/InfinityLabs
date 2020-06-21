#ifndef __OL73_SORTED_LIST_H__
#define __OL73_SORTED_LIST_H__

#include <stddef.h> /* size_t  */

/******************************************************************************/
/* Type for the iterator sol_iter_t */
typedef struct dll_node * sol_iter_t;

/* Type for the list */
typedef struct sorted_list sol_t;

/* Function returns 1 if data1 is before data2, 0 otherwise */
typedef int (*is_before_t)(const void *data1, const void *data2, void *param);

/* Function returns 1 if found, 0 otherwise */
typedef int (*is_findif_t)(void *data, void *param);

/* Function returns 0 if action was successful, otherwise anything else */
typedef int (*sol_act_t)(void *current_data, void *param);

/******************************************************************************/

/*******************************************************************************
 * Creates sorted list with a given sort function and param
 * Returns a poiner to the sorted list or NULL if failed
 * Time Complexity: O(n)
 */
sol_t *SortedListCreate(is_before_t is_before, void *param);

/*******************************************************************************
 * Destroys sorted list sl and frees memory
 * Returns nothing
 * Time Complexity: O(n)
 */
void SortedListDestroy(sol_t *sl);

/*******************************************************************************
 * Inserts given data to list sl according to the IsBefore function and param
 *		in SortedListCreate()
 * Returns iterator to where data was inserted upon succeess, or one after the
 *		item upon failure
 * Time Complexity: O(n)
 */
sol_iter_t SortedListInsert(sol_t *sl, void *data);

/*******************************************************************************
 * Removes given iter and frees memory
 * Returns next iterator
 * If list is empty, or if called on one before the first list item, remove 
 *		will result in undefined behavior
 * Time Complexity: O(1)
 */
sol_iter_t SortedListRemove(sol_iter_t iter);

/*******************************************************************************
 * Removes first item in list sl
 * Returns pointer to item's data
 * Time Complexity: O(1)
 */
void *SortedListPopFront(sol_t *sl);

/*******************************************************************************
 * Removes last item in list sl
 * Returns pointer to item's data
 * Time Complexity: O(1)
 */
void *SortedListPopBack(sol_t *sl);

/*******************************************************************************
 * Finds number of items in list sl
 * Returns number of items in list sl
 * Time Complexity: O(n)
 */
size_t SortedListSize(const sol_t *sl);

/*******************************************************************************
 * Checks if list sl is empty
 * Returns 1 if list sl is empty, 0 otherwise
 * Time Complexity: O(1)
 */
int SortedListIsEmpty(const sol_t *sl);

/*******************************************************************************
 * Finds the first item in list sl
 * Returns itertor to first item, or iterator to one past the list if list is
 * 		empty
 * Time Complexity: O(1)
 */
sol_iter_t SortedListBegin(const sol_t *sl);

/*******************************************************************************
 * Finds the iterator one past the list sl
 * Returns itertor to the iterator one past the list sl
 * Time Complexity: O(1)
 */
sol_iter_t SortedListEnd(const sol_t *sl);

/*******************************************************************************
 * Finds the next iterator of iter in the list
 * Returns the next iterator of iter in the list
 * Using SortedListNext() on an iterator of one after the list will resul in 
 *		undefined behavior
 * Time Complexity: O(1)
 */
sol_iter_t SortedListNext(sol_iter_t iter);

/*******************************************************************************
 * Finds the previous iterator of iter in the list
 * Returns the previous iterator of iter in the list
 * Using SortedListPrev on an iterator of one before the list will result in 
 *		undefined behavior
 * Time Complexity: O(1)
 */
sol_iter_t SortedListPrev(sol_iter_t iter);

/*******************************************************************************
 * Checks if two iterators, i and j, are the same
 * Returns 1 if the two iterators are the same, 0 otherwise
 * Time Complexity: O(1)
 */
int SortedListIsSameIterator(sol_iter_t i, sol_iter_t j);

/*******************************************************************************
 * Gets the data of the iterator iter
 * Returns a pointer to the data
 * Time Complexity: O(1)
 */
void *SortedListGetData(sol_iter_t iter);

/*******************************************************************************
 * Finds the iterator within the range of iterators start (including) and finish
 *		 (excluding) in list sl with the same data of a given data_to_find
 * Returns the iterator if the same data is found, or finish if not found
 * Time Complexity: O(n)
 */
sol_iter_t SortedListFind(sol_t *sl, \
						 sol_iter_t start, \
						 sol_iter_t finish, \
						 const void *data_to_find);

/*******************************************************************************
 * Finds the iterator within the range of iterators start (including) and finish
 *		(excluding) in list sl that satisfy the IsFindIf function and a given
 *		param
 * Returns the iterator if the function was satisfied, or finish if not found
 * Time Complexity: O(n)
 */
sol_iter_t SortedListFindIf(is_findif_t is_findif, \
						   void *param, \
						   sol_iter_t start, \
						   sol_iter_t finish);

/*******************************************************************************
 * Performs Action on each iterator within the range of iterators start (including) and finish (excluding) in list sl that satisfy the IsFindIf function and a given param
 * Returns the Action failure result if failed on one of the iterators, or 0 if
 *		Action was successfully peformed on each iterator
 * Time Complexity: O(n)
 */
int SortedListForEach(sol_iter_t start, \
					  sol_iter_t finish, \
					  sol_act_t act, \
					  void *param);

/* merge both lists into list 1, leave list 2 empty, return list1
 * ????Takes the IsBefore function of the sl1??????
 */
 /*******************************************************************************
 * Merges two lists, sl1 and sl2, with the same sort method
 * Returns the merged list sl1
 * List sl2 will become an empty list
 * If sl1 and sl2 are not of the same sort method, undefined behavior will occur
 * Time Complexity: O(n)
 */
sol_t *SortedListMerge(sol_t *sl1, sol_t *sl2);

#endif /* __OL73_SORTED_LIST_H__ */
