#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#define ARRAY_ELEMS (256)

void InFirst2(char arr1[], size_t len1, char arr2[], size_t len2, char arr3[], size_t len3)
{
	size_t i = 0;
	int buffer[ARRAY_ELEMS] = {0};
	int index = 0;

	assert(arr1);
	assert(arr2);
	assert(arr3);
	
	for (i = 0; i < len1; ++i)
	{
		index = arr1[i];
		buffer[index] = 1;
	}

	for (i = 0; i < len2; ++i)
	{
		index = arr2[i];
		if(buffer[index] == 1)
		{
			buffer[index] = 2;
		}
	}
	
	for (i = 0; i < len3; ++i)
	{
		index = arr3[i];
		buffer[index] = 3;
	}
	
	for (i = 0; i < ARRAY_ELEMS; ++i)
	{
		if (buffer[i] == 2)
		{
			printf("%c\n", (char)i);
		}
	}
	
}

int main()
{

	char arr1[] = {'a', 'c', 'e', 'f'};
	char arr2[] = {'a', 'c', 'e', 'e'};
	char arr3[] = {'a', 'b', 'r', 'f'};
	size_t lengths = 4;
	
	InFirst2(arr1, lengths, arr2, lengths, arr3, lengths);
	
	return (0);
}
