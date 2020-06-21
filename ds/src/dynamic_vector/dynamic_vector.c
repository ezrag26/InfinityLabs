/*
* Date: 1/9/2019
* Developer: Ezra
* Reviewer: Dudi
* Status: S
*/

#include <stdio.h>  /* fprintf 				 */
#include <stdlib.h> /* malloc, realloc, free */
#include <stddef.h> /* size_t				 */
#include <assert.h> /* assert				 */
#include <string.h> /* memcpy				 */

#include "dynamic_vector.h"

#define INCREASE_REALLOC (1.5)
#define REDUCE_REALLOC (0.75)

struct dynamic_vector
{
	char *p_dv;
	size_t element_size;
	size_t capacity;
	size_t count;
};

/********************************* DVCreate ***********************************/

dv_t *DVCreate(size_t max_size, size_t element_size)
{
	/* Create struct for dynamic vector */
	dv_t *d_vector = (dv_t *)malloc(sizeof(dv_t));

	if (NULL == d_vector)
	{
		PRNT_ERR("Memory Allocation Error");
		return (NULL);
	}

	/* create space for each element in dynamic vector based on users request */
	d_vector->p_dv = (char *)malloc(max_size * element_size);

	if (NULL == d_vector->p_dv)
	{
		PRNT_ERR("Memory Allocation Error");

		free(d_vector); d_vector = NULL;
		return (NULL);
	}

	d_vector->element_size = element_size;
	d_vector->capacity = max_size;
	d_vector->count = max_size;

	return (d_vector);
}

/********************************* DVDestroy **********************************/

void DVDestroy(dv_t *d_vector)
{
	if (NULL != d_vector)
	{
		free(d_vector->p_dv); d_vector->p_dv = NULL;
		free(d_vector); d_vector = NULL;
	}
}

/******************************* DVGetElemAddress *****************************/

void *DVGetElemAddress(const dv_t *d_vector, size_t index)
{
	assert(NULL != d_vector);

	return (d_vector->p_dv + (index * d_vector->element_size));
}

/********************************** DVReserve *********************************/

int DVReserve(dv_t *d_vector, size_t add_size)
{
	char *d_vector_temp = NULL;

	assert(NULL != d_vector);

	/* realloc add_size spaces in addition to capacity for possible future use*/
	d_vector_temp = realloc(d_vector->p_dv, (d_vector->capacity + add_size)
					* d_vector->element_size);

	if (NULL == d_vector_temp)
	{
		PRNT_ERR("Memory Allocation Error");
		return (1);
	}

	d_vector->p_dv = d_vector_temp;

	d_vector->capacity += add_size;					  /* update capacity size */

	return (0);
}

/********************************** DVCapacity ********************************/

size_t DVCapacity(const dv_t *d_vector)
{
	assert(NULL != d_vector);

	return (d_vector->capacity);
}

/************************************ DVSize **********************************/

size_t DVSize(const dv_t *d_vector)
{
	assert(NULL != d_vector);

	return (d_vector->count);
}

/************************************ DVPush **********************************/

int DVPush(dv_t *d_vector, const void *element)
{
	char *d_vector_temp = NULL;

	assert(NULL != d_vector);

	if (d_vector->count == d_vector->capacity)
	{
		if (2 > d_vector->capacity)
		{
			d_vector->capacity = 2;
		}
		/* realloc capacity * 1.5 */
		d_vector_temp = realloc(d_vector->p_dv, d_vector->capacity
						* INCREASE_REALLOC * d_vector->element_size);

		if (NULL == d_vector_temp) 							/* realloc failed */
		{
			PRNT_ERR("Memory Allocation Error");
			return (1);
		}

		d_vector->p_dv = d_vector_temp;

		d_vector->capacity *= INCREASE_REALLOC; 			 /* update capacity count */
	}

	/* copy element to pointer + number of elements in vector */
	memcpy(d_vector->p_dv + d_vector->count * d_vector->element_size,
											   element, d_vector->element_size);

	++d_vector->count;								/* update element counter */

	return (0);
}

/************************************* DVPop **********************************/

void DVPop(dv_t *d_vector)
{
	char *d_vector_temp = NULL;

	assert(NULL != d_vector);

	--d_vector->count;

	/* count is <= to 50% of capacity */
	if (d_vector->count	<= d_vector->capacity / 2)
	{
		/* decrease capacity by 25% */
		d_vector_temp = realloc(d_vector->p_dv,
				  d_vector->capacity * REDUCE_REALLOC * d_vector->element_size);

		if (NULL == d_vector_temp)
		{
			PRNT_ERR("Memory Allocation Error");
			return;
		}

		d_vector->p_dv = d_vector_temp;

		d_vector->capacity *= REDUCE_REALLOC;
	}

}
