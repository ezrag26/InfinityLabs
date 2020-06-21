/*
 * Developer: Yossi
 * Reviewer: Ezra
 * Status: A
 */

#ifndef __OL73_WS8_ELEM_H__
#define __OL73_WS8_ELEM_H__


/******************************************
 * New element types should be added here *
 ******************************************/
typedef enum
{
	INT_ELEM,
	FLOAT_ELEM,
	STR_ELEM
} elem_types_t;


/*****************************************************
 * New element operation status should be added here *
 *****************************************************/
typedef enum
{
	TYPE_ERROR = -3,
	MEM_ERROR = -2,
	FAILED = -1,
	SUCCESS = 0,
	SUCCESS_INIT = 1,
	SUCCESS_PRT = 2,
	SUCCESS_ADD = 3,
	SUCCESS_CLN = 4
} elem_status_t;


/********************************************
 * New element members should be added here *
 ********************************************/
typedef struct
{
	void *val_ptr;
	struct
	{
		elem_status_t (*print)();
		elem_status_t (*add)();
		elem_status_t (*clean)();
	} elem_funcs;
} element_t;

/*****************************
 * Element functions library *
 *****************************/
elem_status_t InitElement(elem_types_t type, const void *value, element_t *dest);
elem_status_t PrintElem(element_t *dest);
elem_status_t AddToElem(element_t *dest, int add);
elem_status_t CleanElem(element_t *dest);

#endif	/*	__OL73_WS8_ELEM_H__ */
