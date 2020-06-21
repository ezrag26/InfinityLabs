/*
 * Developer: Ezra Gordon
 * Reviewer: Liron
 * Status: S
 * Date: 29/8/2019
 */

#include <stdio.h>  /* fprintf		*/
#include <stddef.h> /* size_t       */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memmove      */
#include <assert.h> /* assert		*/

#include "stack.h"

struct stack
{
	char *stack_p;       /* capacity * element_size		  */
	size_t size;         /* max size of stack             */
	size_t element_size; /* size of each element in stack */
	size_t num_elems;    /* current number of elements    */
};

/* create the stack and return it as a pointer */
mystack_t *StackCreate(size_t capacity, size_t element_size)
{
	/* Allocate memory for stack struct */
	mystack_t *the_stack = (mystack_t *)malloc(sizeof(mystack_t));

	if (NULL == the_stack)
	{
#ifndef NDEBUG
		fprintf(stderr, "Memory Allocation Error\n");
#endif
		return (NULL);
	}

	/* Allocate memory for stack elements*/
	the_stack->stack_p = (char *)malloc(capacity * element_size);

	if (NULL == the_stack->stack_p)
	{
		free(the_stack); the_stack = NULL;
#ifndef NDEBUG
		fprintf(stderr, "Memory Allocation Error\n");
#endif
		return (NULL);
	}

	/* Initialize elements according to users requests and 0 for num of elems */
	the_stack->size = capacity;
	the_stack->element_size = element_size;
	the_stack->num_elems = 0;

	return (the_stack);
}

/* destroy the stack */
void StackDestroy(mystack_t *stack)
{
	if(NULL != stack)
	{
		/* point to first beginning of stack elements */
		stack->stack_p -= stack->num_elems * stack->element_size;

		/* free stack elements and stack */
		free(stack->stack_p); stack->stack_p = NULL;
		free(stack); stack = NULL;
	}
}

/* remove the last element in the stack */
void StackPop(mystack_t *stack)
{
	assert(NULL != stack);

	/* Point to last element */
	stack->stack_p -= stack->element_size;
	--stack->num_elems;
}

/* add an element to the stack */
void StackPush(mystack_t *stack, const void *element_p)
{
	assert(NULL != stack);
	assert(NULL != element_p);

	/* cpy element to stack */
	memcpy(stack->stack_p, element_p, stack->element_size);

	/* point to next address */
	stack->stack_p += stack->element_size;

	++stack->num_elems;
}

/* Return the last element in the stack */
void *StackPeek(const mystack_t *stack)
{
	assert(NULL != stack);

	/* return element at previous address */
	return ((void *)(stack->stack_p - stack->element_size));
}

/* Returns the max size of the stack */
size_t StackSize(const mystack_t *stack)
{
	assert(NULL != stack);

	return (stack->size);
}

/* counts the number of elements in the stack */
size_t StackCount(const mystack_t *stack)
{
	assert(NULL != stack);

	return (stack->num_elems);
}

/* Returns 1 if the stack is empty, 0 if the stack is not empty */
int StackIsEmpty(const mystack_t *stack)
{
	assert(NULL != stack);

	return (0 == stack->num_elems);
}

static void InsertStack(mystack_t *stack, is_before_t is_before, void *param, const int *data)
{
	const int data2 = *(int *)StackPeek(stack);

	if (StackIsEmpty(stack) || !is_before(data, &data2, param))
	{
		StackPush(stack, data);
	}
	else
	{
		StackPop(stack);
		InsertStack(stack, is_before, param, data);
		StackPush(stack, &data2);
		return;
	}
}

void SortStack(mystack_t *stack, is_before_t is_before, void *param)
{
	const int *data = NULL;

	assert(NULL != stack);

	if (StackIsEmpty(stack))
	{
		return;
	}

	data = (int *)StackPeek(stack);
	StackPop(stack);
	SortStack(stack, is_before, param);
	InsertStack(stack, is_before, param, data);

	return;
}
