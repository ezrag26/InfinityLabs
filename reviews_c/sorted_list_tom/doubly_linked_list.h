#ifndef __OL73_DOUBLY_LINKED_LIST_H__
#define __OL73_DOUBLY_LINKED_LIST_H__

#include <stddef.h> /* size_t */

/* 
 * Checks for a match between the current iterator data and a given data_to_find
 * Should return 0 upon success, and any other number upon failure
 */
typedef int (*is_match_t)(const void *current_data, const void *data_to_find);

/* 
 * Performs something to each iterator with a given data param
 * Should return 0 upon success, and 1 upon failure
 */
typedef int (*act_t)(void *data, void *param);

/* 
 * Type of the  Doubly Linked List dll
 */
typedef struct dll dll_t;

/*
 * Type of the iterator
 */
typedef void *dll_iter_t;

/*******************************************************************************
 * Creates DLL
 * Returns pointer to DLL upon success, or NULL if failed
 * Time Complexity: O(n)
 */
dll_t *DLLCreate();

/*******************************************************************************
 * Removes DLL dll
 * Returns nothing
 * Time Complexity: O(n)
 */
void DLLDestroy(dll_t *dll);

/*******************************************************************************
 * Inserts item with given data at given iterator's position
 * Returns iterator upon success, or one after the end if failed
 * Time Complexity: O(n)
 */
dll_iter_t DLLInsert(dll_t *dll, dll_iter_t iter, void *data);

/*******************************************************************************
 * Removes item at given iterator's position
 * Returns nothing
 * If DLL is empty, remove will result in undefined behavior
 * Time Complexity: O(1)
 */
void DLLRemove(dll_iter_t iter);

/*******************************************************************************
 * Finds item witin position begin until end (not including) with data_to_find
 * Returns iterator to item if found, or iterator to one after end if not found
 * Time Complexity: O(n)
 */
dll_iter_t DLLFind(dll_iter_t begin, dll_iter_t end,
					const void *data_to_find,
					is_match_t is_match);

/*******************************************************************************
 * Performs function Act on all items in list from item at start until finish 
 *		(not including).
 * Returns 0 on success, 1 on failure
 * Time Complexity: O(n)
 */
int DLLForEach(dll_iter_t start, dll_iter_t finish,
			   act_t Act, void *param);

/*******************************************************************************
 * Finds number of items in list dll
 * Returns number of items in list dll
 * Time Complexity: O(n)
 */
size_t DLLSize(dll_t *dll);

/*******************************************************************************
 * Check if list dll is empty
 * Returns 1 if list dll is emtpy, 0 otherwise
 * Time Complexity: O(1)
 */
int DLLIsEmpty(dll_t *dll);

/*******************************************************************************
 * Inserts item with given data to the front of list dll
 * Returns iterator to item upon succes, or iterator to one after the end if 
 *		failed
 * Time Complexity: O(n)
 */
dll_iter_t DLLPushFront(dll_t *dll, void *data);

/*******************************************************************************
 * Removes item at the front of list dll
 * Returns poiner to item's data
 * If linked list is empty, pop will result in undefined behavior
 * Time Complexity: O(1)
 */
void *DLLPopFront(dll_t *dll);

/*******************************************************************************
 * Inserts item with given data to the end of list dll
 * Returns iterator to item upon succes, or iterator to one after the end if 
 *		failed
 * Time Complexity: O(n)
 */
dll_iter_t DLLPushBack(dll_t *dll, void *data);

/*******************************************************************************
 * Removes item at the end of list dll
 * Returns poiner to item's data
 * If linked list is empty, pop will result in undefined behavior
 * Time Complexity: O(1)
 */
void *DLLPopBack(dll_t *dll);

/*******************************************************************************
 * Gets iterator to next item in list dll
 * Returns iterator to next item in list dll
 * Time Complexity: O(1)
 */
dll_iter_t DLLNext(dll_iter_t iter);

/*******************************************************************************
 * Gets iterator to previous item in list dll
 * Returns iterator to previous item in list dll
 * Time Complexity: O(1)
 */
dll_iter_t DLLPrev(dll_iter_t iter);

/*******************************************************************************
 * Gets data of iterator in list dll
 * Returns pointer to data
 * Time Complexity: O(1)
 */
void *DLLGetData(dll_iter_t iter);

/*******************************************************************************
 * Gets iterator at front of list dll
 * Returns iterator to item
 * Time Complexity: O(1)
 */
dll_iter_t DLLBegin(const dll_t *dll);

/*******************************************************************************
 * Gets iterator at one past the end item in list dll
 * Returns iterator to one past the end item in list dll
 * Time Complexity: O(1)
 */
dll_iter_t DLLEnd(const dll_t *dll);

/*******************************************************************************
 * Checks if two iterators are the same
 * Returns 1 if the two iterators are the same, 0 otherwise
 * Time Complexity: O(1)
 */
int DLLIsSameIter(dll_iter_t i, dll_iter_t j);

/*******************************************************************************
 * Moves all items from iterator src_first (including) until src_last (not 
 *		including) to the iterator dest (before). The items not moved from src 
 *		are rejoined together
 * Returns nothing
 * if src_first and src_last are not from the same list, it will result in
 *		undefined behavior
 * Time Complexity: O(1)
 */
void DLLSplice(dll_iter_t dest, dll_iter_t src_first, dll_iter_t src_last);

#endif /*__OL73_DOUBLY_LINKED_LIST_H__*/
