#include <stdio.h>

#include "ws8_elem.h"

int main()
{
	float f[] = {3.5334, 9.834, 0.042};
	int num[] = {20, 15, 100};
	int i = 0;
	char *string[] = {"Hi", "Hello", "Test"};
	element_t arr[10] = {0};

	InitElem(string[0], STRING, &arr[0]);
	InitElem(&num[0], INT, &arr[1]);
	InitElem(&f[0], FLOAT, &arr[2]);
	InitElem(string[1], STRING, &arr[3]);
	InitElem(&num[1], INT, &arr[4]);
	InitElem(&f[1], FLOAT, &arr[5]);
	InitElem(string[2], STRING, &arr[6]);
	InitElem(&num[2], INT, &arr[7]);
	InitElem(&f[2], FLOAT, &arr[8]);
	InitElem(string[1], STRING, &arr[9]);

	for (i = 0; i < 10; ++i)
	{
		printf("Elem %d: ", i);
		arr[i].elem_funcs_t.print(&arr[i]);
	}

	for (i = 0; i < 10; ++i)
	{
		arr[i].elem_funcs_t.add(num[0], &arr[i]);
	}
	printf("\n");
	for (i = 0; i < 10; ++i)
	{
		printf("Elem %d: ", i);
		arr[i].elem_funcs_t.print(&arr[i]);
	}
		
	for (i = 0; i < 10; ++i)
	{
		arr[i].elem_funcs_t.free(arr[i].p_elem);
	}
	
	return (0);
}
