#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc, calloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include <stdio.h>  /*fprintf*/

#include "stack.h"  /*assert*/
struct stack
{
	char *stack_p;       /* [malloc size * element_size] */
	size_t size;         /* max size of stack, max num of elemnts  =capacity */
	size_t element_size;
	size_t top;          /* current number of elements   */
} ;



mystack_t *StackCreate(size_t capacity,  size_t element_size)
{
	mystack_t *stack = malloc(sizeof(mystack_t));


	/* allocate memory for stack stucture*/
	if (NULL == stack)
	{
		#ifndef NDBUG
		fprintf(stderr, "Error allocating memory to new stack.");
		#endif
		return(stack);
	}

	/* allocate memory for stack itself, in order to store elements */
	stack->stack_p = calloc(element_size, capacity);

	if (NULL == stack->stack_p)
	{
		free(stack); stack = NULL;
		return(stack);
	}

	stack->size =  capacity;
	stack->element_size = element_size;
	stack->top = 0;

	return(stack);
}


void StackDestroy(mystack_t *stack)
{
	if (NULL != stack)
	{
		free(stack->stack_p); stack->stack_p = NULL;
		free(stack); stack = NULL;
	}
}


void StackPop(mystack_t *stack)
{
	assert(NULL != stack);

	--(stack->top);
}


void StackPush(mystack_t *stack, const void *element_p)
{
	assert(NULL != stack);
	assert(NULL != element_p);
	/* copy element receieved in arguments into stack */
	memcpy((stack->stack_p + (stack->top * stack->element_size))
			,element_p, stack->element_size);
	++(stack->top);
}


void *StackPeek(const mystack_t *stack)
{
	assert(NULL != stack);

	return (stack->stack_p + ((stack->top -1) * stack->element_size));
}


size_t StackSize(const mystack_t *stack)
{
	assert(NULL != stack);
	return (stack->size);
}


size_t StackCount(const mystack_t *stack)
{
	assert(NULL != stack);

	return (stack->top);
}


int StackIsEmpty(const mystack_t *stack)
{
	assert(NULL != stack);

	return (!(0 < (stack->top)));
}

void InsertSort(mystack_t *stack, is_before_t IsBefore, void *param, int *data)
{
	int temp = 0;

	if((StackIsEmpty(stack)) || (!IsBefore(data, StackPeek(stack), param)))
	{
		StackPush(stack, data);
	}
	else
	{
		temp = *(int *)StackPeek(stack);
		StackPop(stack);
		InsertSort(stack, IsBefore, param, data);
		StackPush(stack, &temp);
	}
}

 void SortStack(mystack_t *stack, is_before_t IsBefore, void *param)
 {
	int *data = NULL;

	assert(NULL != stack);
	if (StackIsEmpty(stack))
	{
		return;
	}
	data = (int *)StackPeek(stack);
	StackPop(stack);
	SortStack(stack, IsBefore, param);
	InsertSort(stack, IsBefore, param, data);
 }
