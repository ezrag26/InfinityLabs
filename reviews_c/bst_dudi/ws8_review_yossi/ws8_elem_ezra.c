#include <stdio.h>

#include "ws8_elem.h"
#include "utils.h"

int main()
{
	float f[] = {3.5334, 9.834, 0.042};
	int num[] = {20, 15, 100};
	int i = 0;
	char *string[] = {"Hi", "Hello", "Test"};
	element_t arr[10] = {0};

	InitElement(STR_ELEM, string[0], &arr[0]);
	InitElement(INT_ELEM, &num[0], &arr[1]);
	InitElement(FLOAT_ELEM, &f[0], &arr[2]);
	InitElement(STR_ELEM, string[1], &arr[3]);
	InitElement(INT_ELEM, &num[1], &arr[4]);
	InitElement(FLOAT_ELEM, &f[1], &arr[5]);
	InitElement(STR_ELEM, string[2], &arr[6]);
	InitElement(INT_ELEM, &num[2], &arr[7]);
	InitElement(FLOAT_ELEM, &f[2], &arr[8]);
	InitElement(STR_ELEM, string[1], &arr[9]);

	for (i = 0; i < 10; ++i)
	{
		printf("Elem %d: ", i);
		PrintElem(&arr[i]);
	}

	for (i = 0; i < 10; ++i)
	{
		AddToElem(&arr[i], num[0]);
	}
	printf("\n");
	for (i = 0; i < 10; ++i)
	{
		printf("Elem %d: ", i);
		PrintElem(&arr[i]);
	}

	for (i = 0; i < 10; ++i)
	{
		CleanElem(&arr[i]);
	}

	return 0;
}
