/*
* Date: 1/9/2019
* Developer: Ezra
* Reviewer: Dudi
* Status: S
*/

#ifndef __OL73_DYNAMIC_VECTOR_H__
#define __OL73_DYNAMIC_VECTOR_H__

#include <stddef.h> /* size_t */

#include "utils.h"

typedef struct dynamic_vector dv_t;

/*
* Create the dynamic vector equal to the capacity * element_size
* A capacity and/or element_size of 0 results in undefined behavior
* Return pointer to the dynamic vector or NULL if failed
* Complexity: O(1) or malloc's complexity
*/
dv_t *DVCreate(size_t capacity, size_t element_size);

/*
* Remove the dynamic vector
* Does not return anything
* Complexity: O(1)
*/
void DVDestroy(dv_t *d_vector);

/*
* Get address of an element at index index
* Returns a void pointer to the element
* Undefined behavior with index above vector size
* Complexity: O(1)
*/
void *DVGetElemAddress(const dv_t *d_vector, size_t index);

/*
* Reserves add_size number of additional spaces in the dynamic vector
* Returns 0 if reserve was successful, 1 if it failed. If DVReserve() was
*	successful, the pointer to vector may have changed and therefore is suggested to
*	call DVGetElemAddress() to receive the location of the first address of
*	vector
* Complexity: realloc's complexity
*/
int DVReserve(dv_t *d_vector, size_t add_capacity);

/*
* Total max size of the dynamic vector
* Returns the max size
* Complexity: O(1)
*/
size_t DVCapacity(const dv_t *d_vector);

/*
* Total current number of elements
* Returns current number of elements
* Complexity: O(1)
*/
size_t DVSize(const dv_t *d_vector);

/*
* Adds element to the end of the dynamic vector
* Extend by 1.5 times the current capacity if there is no more room to push
* Returns 0 upon success, 1 if memory allocation failed. If DVPush() was
*	successful pointer to vector may have changed and therefore is suggested to
*	call DVGetElemAddress() to receive the location of the first address of
*	vector
* Push with 0 elements in vector results in undefined behavior
* Complexity: Amortized O(1)
*/
int DVPush(dv_t *d_vector, const void *element);

/*
* Removes last element from the dynamic vector
* Does not return anything.  If DVPop() was successful, pointer to vector may
*	have changed and therefore is suggested to call DVGetElemAddress() to
*	receive the location of the first address of vector
* If size becomes 50% or less of capacity, resize capacity to 0.75%
* Pop when size is <= 0 will have undefined behavior
* Complexity: Amortized O(1)
*/
void DVPop(dv_t *d_vector);

#endif /* __OL73_DYNAMIC_VECTOR_H__ */
