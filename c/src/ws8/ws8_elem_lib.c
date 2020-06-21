#include <stdlib.h> /* malloc 		  */
#include <string.h> /* strcpy, strcat */
#include <stdio.h> 	/* printf 		  */
#include <assert.h> /* assert		  */

#include "ws8_elem.h"

#define SPACE_FOR_NULL (1)

static return_val_t PrintString(element_t *p);

static return_val_t PrintInt(element_t *p);

static return_val_t PrintFloat(element_t *p);

static return_val_t AddToString(int num, element_t *p);

static return_val_t AddToInt(int num, element_t *p);

static return_val_t AddToFloat(int num, element_t *p);

static return_val_t Free(element_t *p);

static return_val_t DoNothing();

/* Function to initialize the elements of the array and give each member its 
proper functions that will be performed on the values */
return_val_t InitElem(void *elem, element_types_t type, element_t *p)
{

	assert(NULL != elem);
	assert(NULL != p);

	switch (type)
	{
		case STRING:
			/* Allocate room for the string */
			p->p_elem = (char *)malloc(sizeof(char) * strlen(elem)
													 + SPACE_FOR_NULL);
			
			if (NULL == p->p_elem)					 /* Malloc didn't succeed */
			{
				return (ALLOCATION_ERROR);
			}
			
			strcpy(p->p_elem, elem);				 /* copy string to struct */
			
			p->elem_funcs_t.print = PrintString;
			p->elem_funcs_t.add = AddToString;
			p->elem_funcs_t.free = Free;
			
			break;
		case INT:
			p->p_elem = (void *) *(long *)elem;
			p->elem_funcs_t.print = PrintInt;
			p->elem_funcs_t.add = AddToInt;
			p->elem_funcs_t.free = DoNothing;
			
			break;
		case FLOAT:
			p->p_elem = (void *) *(long *)elem;
			p->elem_funcs_t.print = PrintFloat;
			p->elem_funcs_t.add = AddToFloat;
			p->elem_funcs_t.free = DoNothing; 	 /* Nothing needs to be freed */
			
			break;
		default:
			break;
	}
	
	return (SUCCESS);
}

/* Prints the value of an element of type char * */
static return_val_t PrintString(element_t *p)
{
	assert(NULL != p);
	
	printf("%s\n", (char *)p->p_elem);

	return (SUCCESS);
}

/* Prints the value of an element of type int */
static return_val_t PrintInt(element_t *p)
{
	assert(NULL != p);

	printf("%d\n", *(int *)&p->p_elem);
	
	return (SUCCESS);
}

/* Prints the value of an element of type float */
static return_val_t PrintFloat(element_t *p)
{
	assert(NULL != p);

	printf("%f\n", *(float *)&p->p_elem);
	
	return (SUCCESS);
}

/* Add an int to an element of type char * */
static return_val_t AddToString(int num, element_t *p)
{
	size_t count = 0;
	int num_digits = num;
	void *ptr_for_realloc = NULL;
	while (num_digits > 0)
	{
		num_digits /= 10;
		++count;
	}

	assert(NULL != p);
	
	ptr_for_realloc = realloc(p->p_elem, strlen(p->p_elem) + SPACE_FOR_NULL
													 + count);
	
	if (NULL == ptr_for_realloc)
	{
		return (ALLOCATION_ERROR);
	}

	/* to print an integer like a string */
	sprintf((char *) p->p_elem, "%s%d", (char *) p->p_elem, num);
	
	return (SUCCESS);
}

/* Add an int to an element of type int */
static return_val_t AddToInt(int num, element_t *p)
{
	int tmp = 0;
	assert(NULL != p);
	
	tmp = *(int *)&p->p_elem + num;
	
	p->p_elem = (void *) *(long *)&tmp;
	
	return (SUCCESS);
}

/* Add an int to an element of type float */
static return_val_t AddToFloat(int num, element_t *p)
{
	float tmp = 0;
	assert(NULL != p);	
	
	tmp = *(float *)&p->p_elem + num;
	
	p->p_elem = (void *) *(long *)&tmp;
	
	return (SUCCESS);
}

/* Free allocated memory */
static return_val_t Free(element_t *p)
{
	assert(NULL != p);

	free(p);
	
	return (SUCCESS);
}

/* If there is no need for free to happen, do nothing */
static return_val_t DoNothing()
{
	return (SUCCESS);
}

