#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include <stddef.h> /* size_t */

typedef struct dll_node *sol_iter_t;
typedef struct sorted_list sol_t;

typedef int (*is_before_t)(const void *data1,const void *data2, void *param);
/* function returns 1 if found, 0 otherwise */ 
typedef int (*is_findif_t)(void *data, void *param);
typedef int (*sol_act_t)(void *list_data, void *param);

/**
* The sorted linked list program implements an application that
* do manipulations on sorted linked list according to the user demand.
*
* @author  Tom GOldberg
* @version 1.0
* @since   12-09-2019
*/

/****************************************************************************
*description: The function create new sorted linked list.
*input: pointer to function is_before and paramater for the function
*output: the function return pointer to the new sorted list
*complexity:0(1) 															*/
sol_t *SortedListCreate(is_before_t is_before, void *param);

/****************************************************************************
*description: The function destroy/free the allocated memory.
*input: The function get ptr to the list.
*output: 
*complexity:0(1) 															*/
void SortedListDestroy(sol_t *list);

/****************************************************************************
*description: The function insert new node to the sorted list at his sortted
* place.
*input: The function get ptr to the list and ptr to the data of the new node.
*output: iterator to the new node or ptr to the end if fail (malloc failed)
*complexity:0(1) 															*/
sol_iter_t SortedListInsert(sol_t *list, void *data);

/****************************************************************************
*description: The function remove a node at relevant place
*input: iterator to the relevat node.
*output: iterator to the new node or ptr to the end if fail (malloc failed)
*complexity:0(1) 															*/
sol_iter_t SortedListRemove(sol_iter_t iter);

/****************************************************************************
*description: The function pop the first node.
*input: ptr to the list
*output: ptr to the data poped
*complexity:0(1) 															*/
void *SortedListPopFront(sol_t *list);

/****************************************************************************
*description: The function pop the last node.
*input: ptr to the list
*output: ptr to the data poped
*complexity:0(1) 															*/
void *SortedListPopBack(sol_t *list);

/****************************************************************************
*description: The function return the size of the sorted list
*input: ptr to the list
*output: the size of the list
*complexity:0(n) 															*/
size_t SortedListSize(const sol_t *list);

/****************************************************************************
*description: The function tell the user if the list is empty of nodes.
*input: ptr to the list
*output: 1 if empty, else 0
*complexity:0(1) 															*/
int SortedListIsEmpty(const sol_t *list);

/****************************************************************************
*description: The function point to first node of the list.
*input: ptr to the list
*output: ptr to the first node
*complexity:0(1) 															*/
sol_iter_t SortedListBegin(const sol_t *list);

/****************************************************************************
*description: The function point to end node of the list.
*input: ptr to the list
*output: ptr to the end node
*complexity:0(1) 															*/	
sol_iter_t SortedListEnd(const sol_t *list);

/****************************************************************************
*description: The function point to next node.
*input: iterator to a specific node
*output: ptr to the node next to the one got from the user
*complexity:0(1) 															*/
sol_iter_t SortedListNext(sol_iter_t iter);

/****************************************************************************
*description: The function point to prev node.
*input: iterator to a specific node
*output: ptr to the node prev to the one got from the user
*complexity:0(1) 															*/

sol_iter_t SortedListPrev(sol_iter_t iter);

/****************************************************************************
*description: The function tells us if to iterators points to the same node
*input:2 iterators
*output: 1 for same iterator, else 0;
*complexity:0(1) 															*/

int SortedListIsSameIterator(sol_iter_t iter1, sol_iter_t iter2);

/****************************************************************************
*description: The function point to the data within a specific nide.
*input: iterator to the list.
*output: pointer to the data at that specific node.
*complexity:0(1) 															*/
void *SortedListGetData(sol_iter_t iter);

/****************************************************************************
*description: The function check if a specific data is whithin a specific
* range in the list.
*input:ptr to the list, ptr to the start of th elist, ptr to the end of the 
*list, the specific data.
*output: if found ptr to the node with the data, else ptr to the end node
*complexity:0(n) 															*/
sol_iter_t SortedListFind(sol_t *list, sol_iter_t start, sol_iter_t end, 
const void *data_to_find);

/****************************************************************************
*description: The function check if function if_findif is valid in a specific 
*node within a specific range.
*input:ptr to the function, ptr to a param, ptr for the start of the list, 
*ptr for the end of the list
*output: 1 if found ptr to the node with the data, else ptr to the end node
*complexity:0(n) 															*/

sol_iter_t SortedListFindIf(is_findif_t is_findif, void *param, sol_iter_t start, sol_iter_t end);
/****************************************************************************
*description: The function run a specific function (act) on the nodes
* between a specific range.
*input:ptr to the function, ptr to a param, ptr for the start of the list, 
*ptr for the end of the list
*output:  0 if the function run on all the noeds. else 1, 					
*complexity:0(n) 															*/
int SortedListForEach(sol_iter_t start, sol_iter_t end, sol_act_t act, void *param);

/****************************************************************************
*description: The function merge two lists into one list , leave list 2 empty, 
*and return list1
*input:2 ptrs for 2 lists.
*output:  ptr to the merged list. 											
*complexity:0(n) 															*/
sol_t *SortedListMerge(sol_t *list1, sol_t *list2);

#endif /*__SORTED_LIST_H__*/

