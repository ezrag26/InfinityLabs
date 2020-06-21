/*
 * Developer: Yossi
 * Reviewer: Ezra
 * Status: A
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ws8_elem.h"
#include "utils.h"

#define MAX_INT_DIGITS 20


static elem_status_t InitElemInt(const void *value, element_t *dest);
static elem_status_t InitElemFloat(const void *value, element_t *dest);
static elem_status_t InitElemStr(const void *value, element_t *dest);
static elem_status_t PrintInt(element_t *dest);
static elem_status_t PrintFloat(element_t *dest);
static elem_status_t PrintStr(element_t *dest);
static elem_status_t AddToStr(element_t *dest, int add);
static elem_status_t AddToFloat(element_t *dest, int add);
static elem_status_t AddToInt(element_t *dest, int add);
static elem_status_t CleanStr(element_t *dest);
static elem_status_t CleanFloat(element_t *dest);
static elem_status_t CleanInt(element_t *dest);

/**********************************
 * LUT for element initialization *
 * (array of pointers to funcs)   *
 **********************************/
static elem_status_t (*init_lut[])(const void *value, element_t *dest) =
{
	InitElemInt,
	InitElemFloat,
	InitElemStr
};

/******************************************
 * Initialization functions for element_t *
 ******************************************/
elem_status_t InitElement(elem_types_t type, const void *value, element_t *dest)
{
	elem_status_t status = 0;
	assert(NULL != value);
	assert(NULL != dest);

	/* This function initialize element_t instances.
	 * New types should be added to enum elem_type_t in "ws8_elem.h" before
	 * added to this function (as well as to other function in this file */
	status = init_lut[type]((const void *)value, dest);

	return (status);
}


static elem_status_t InitElemInt(const void *value, element_t *dest)
{
	/* Bits of the 8 bytes starting at the int address are assigned to val_ptr */
	dest->val_ptr = (void *)(*(long *)value);

	dest->elem_funcs.print = PrintInt;
	dest->elem_funcs.add = AddToInt;
	dest->elem_funcs.clean = CleanInt;

	return (SUCCESS_INIT);
}

static elem_status_t InitElemFloat(const void *value, element_t *dest)
{
	/* Bits of the 8 bytes starting at the float address are assigned to val_ptr */
	dest->val_ptr = (void *)(*((long *)(value)));

	dest->elem_funcs.print = PrintFloat;
	dest->elem_funcs.add = AddToFloat;
	dest->elem_funcs.clean = CleanFloat;

	return (SUCCESS_INIT);
}

static elem_status_t InitElemStr(const void *value, element_t *dest)
{
	dest->val_ptr = malloc(strlen(value) + sizeof(*(char *)value));
	if (NULL == dest->val_ptr) return (MEM_ERROR);

	/* Copy input into allocated memory, pointed by the val_ptr */
	strcpy(dest->val_ptr, value);

	dest->elem_funcs.print = PrintStr;
	dest->elem_funcs.add = AddToStr;
	dest->elem_funcs.clean = CleanStr;

	return (SUCCESS_INIT);
}


/*********************************
 * Print functions for element_t *
 *********************************/

elem_status_t PrintElem(element_t *dest)
{
	assert(NULL != dest);
	return (dest->elem_funcs.print(dest));
}


static elem_status_t PrintInt(element_t *dest)
{
	/* Access the value stored in val_ptr via an int pointer */
	printf("%d\n", *(int *)&dest->val_ptr);

	return (SUCCESS_PRT);
}

static elem_status_t PrintFloat(element_t *dest)
{
	/* Access the value stored in val_ptr via a float pointer */
	printf("%f\n", *(float *)&dest->val_ptr);

	return (SUCCESS_PRT);
}

static elem_status_t PrintStr(element_t *dest)
{
	printf("%s\n", (char *)dest->val_ptr);

	return (SUCCESS_PRT);
}


/*******************************
 * Add functions for element_t *
 *******************************/
elem_status_t AddToElem(element_t *dest, int add)
{
	assert(NULL != dest);
	return (dest->elem_funcs.add(dest, add));
}


static elem_status_t AddToInt(element_t *dest, int add)
{
	/* Access the value stored in val_ptr via int pointer, then add
	 * the "add" int to that value, and store it back into val_ptr */
	dest->val_ptr = (void *)((long)dest->val_ptr + (long)add);

	return (SUCCESS_ADD);
}

static elem_status_t AddToFloat(element_t *dest, int add)
{
	/* Access the value stored in val_ptr via float pointer, then
	 * add the "add" int to that value, and store it in a float var */
	float f_val = *((float *)&dest->val_ptr) + (float)add;
	/* Store the bits of the float back into val_ptr */
	dest->val_ptr = (void *)(*((long *)(&f_val)));

	return (SUCCESS_ADD);
}

static elem_status_t AddToStr(element_t *dest, int add)
{
	char buffer[MAX_INT_DIGITS] = "";
	/* Convert "add" to str and store it in buffer */
	sprintf(buffer, "%d", add);

	dest->val_ptr = realloc(
		dest->val_ptr, strlen((char *)dest->val_ptr) + strlen(buffer) + 1);

	/* add the buffered str to the str pointed by val_ptr */
	strcat((char *)dest->val_ptr, buffer);

	return (SUCCESS_ADD);
}


/**************************************************************
 * Clean element_t. Always call Clean before exiting program. *
 **************************************************************/
elem_status_t CleanElem(element_t *dest)
{
	assert(NULL != dest);
	return (dest->elem_funcs.clean(dest));
}


static elem_status_t CleanInt(element_t *dest)
{
	dest->val_ptr = NULL;

	return (SUCCESS_CLN);
}

static elem_status_t CleanFloat(element_t *dest)
{
	dest->val_ptr = NULL;

	return (SUCCESS_CLN);
}

static elem_status_t CleanStr(element_t *dest)
{
	/* Clear str before freeing pointer */
	memset((char *)dest->val_ptr, '\0', strlen((char *)dest->val_ptr));
	free(dest->val_ptr);

	dest->val_ptr = NULL;

	return (SUCCESS_CLN);
}
