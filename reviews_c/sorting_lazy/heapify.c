/*******************************************************************************
*																			   *
*	DataStructures - Heapify - Source code									   *
*	Developer: Lazy Frid						  							   *
*	Reviewer: Dan															   *
*	Status: S 00.11.2019													   *
*	Date: 06.11.2019														   *
*																			   *
*******************************************************************************/
#include <assert.h>						/* assert			 */
#include <stdlib.h>						/* malloc, free		 */
#include <string.h>						/* memcpy			 */

#include "heapify.h"


void HeapSiftUp(void *arr, size_t elem_size, size_t index, heapify_cmp_t cmp, void *param)
{
	char *byte_array = arr;
	size_t current_i = index;
	void *parent_data = NULL;
	void *climbing_data = NULL;

	assert(arr);

	/* save our sifting node data aside */
	climbing_data = malloc(elem_size);
	if (NULL == climbing_data) return;
	memcpy(climbing_data, byte_array + (index * elem_size), elem_size);
	
	while (current_i > 0)	/* climb no more than array begin */
	{
		parent_data = byte_array + ((current_i - 1) / 2) * elem_size;

		/* if our node is of higher priority - push parent down */
		if (0 < cmp(climbing_data, parent_data, param))
		{
			memcpy(byte_array + (current_i * elem_size), parent_data, elem_size);
			current_i = (current_i - 1) / 2;
		}
		else
		{
			break;
		}
	}
	/* after all lower priority parents pushed down - put our node on top */
	memcpy(byte_array + (current_i * elem_size), climbing_data, elem_size);

	free(climbing_data);

	return;
}


void HeapSiftDown(void *arr, size_t elem_size, size_t arr_size, size_t index, heapify_cmp_t cmp, void *param)
{
	char *byte_array = arr;
	size_t current_i = index, left_i = 0, right_i = 0;
	void *sliding_data = NULL;
	int is_right = 0;

	assert(arr);

	/* save our sifting node aside */
	sliding_data = malloc(elem_size);
	if (NULL == sliding_data) return;
	memcpy(sliding_data, byte_array + (index * elem_size), elem_size);

	while ((left_i = (current_i * 2) + 1) < arr_size)	/* at least one kid */
	{
		if ((right_i = (current_i * 2) + 2) < arr_size)	/* has two kids */
		{	
			/* check if right kid is higher priority */
			is_right = (0 < cmp(byte_array + (right_i * elem_size), byte_array + (left_i * elem_size), param));
		}
		else
		{
			is_right = 0;
		}
		
		/* if higher priority kid is also higher from parent */
		if (0 < cmp(byte_array + (left_i + is_right) * elem_size, sliding_data, param))
		{
			/* the kid climb up to parent place */
			memcpy(byte_array + current_i * elem_size, byte_array + (left_i + is_right) * elem_size, elem_size);
			current_i = left_i + is_right;
		}
		else
		{
			break;
		}
	}
	memcpy(byte_array + current_i * elem_size, sliding_data, elem_size);
	
	free(sliding_data);
	return;
}
