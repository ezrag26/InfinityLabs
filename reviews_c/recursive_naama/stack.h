#ifndef __OL73_DS_STACK_H__
#define __OL73_DS_STACK_H__

#include <stddef.h> /* size_t */

#include "utils.h"

typedef struct stack mystack_t;

/* returns 1 if data1 is before data2, otherwise 0 */
typedef int (*is_before_t)(const void *data1, const void *data2, void *param);

/*
*  Initialize a new stack.
*  Return value is pointer to created stack or NULL if failed
*/
mystack_t *StackCreate(size_t capacity, size_t element_size);

/*
*  Remove a stack from memory.
*  Does not return anything.
*  Destroying a stack that doesn't exist will return unexpected results.
*/
void StackDestroy(mystack_t *stack);

/*
*  Remove the last element from the stack.
*  Does not return anything.
*  A pop with nothing in the stack with return in unexpected results.
*/
void StackPop(mystack_t *stack);

/*
*  Add a new element to the stack.
*  Does not return anything.
*  A push with a full stack will return unexpected results.
*/
void StackPush(mystack_t *stack, const void *element_p);

/*
*  Look at last value in the stack.
*  Returns pointer to element.
*/
void *StackPeek(const mystack_t *stack);

/*
*  Find the max size of the stack.
*  Returns the max size of the stack.
*  A stack was pushed or popped too many times will return unexpected results.
*/
size_t StackSize(const mystack_t *stack);

/*
*  Current number of elements in the stack.
*  Returns current number.
*  A stack was pushed or popped too many times will return unexpected results.
*/
size_t StackCount(const mystack_t *stack);

/*
*  Checks if the stack is empty.
*  Returns 1 if the stack is empty, 0 if not empty.
*  A stack popped too many times will return 0 upon check.
*/
int StackIsEmpty(const mystack_t *stack);

void SortStack(mystack_t *stack, is_before_t is_before, void *param);

#endif /* __OL73_DS_STACK_H__ */
