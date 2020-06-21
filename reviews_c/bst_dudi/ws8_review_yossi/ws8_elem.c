/*
 * Developer: Yossi
 * Reviewer: Ezra
 * Status: A
 */

#include <stdlib.h>

#include "ws8_elem.h"
#include "utils.h"


/* Example main func for the program.
 * Available operations are declared in the ws8_elem.h file.
 * User should use CleanElem() before exiting the program. */
int main()
{
	size_t elem = 0;

	int i = 1024;
	float f = 3.141593;
	char *str = "Hello World";

	element_t arr[3] = {0};
	InitElement(INT_ELEM, &i, &arr[0]);
	InitElement(FLOAT_ELEM, &f, &arr[1]);
	InitElement(STR_ELEM, str, &arr[2]);

	for (elem = 0; ARR_SIZE(arr) > elem; ++elem)
	{
		/* Macro for function calls defined in ws8_elem.h */
		PrintElem(&arr[elem]);
		AddToElem(&arr[elem], 18);
		PrintElem(&arr[elem]);
		CleanElem(&arr[elem]);
	}

	return (0);
}
