#include <stdio.h>
#include <stddef.h>

#define MAX2(a, b) (a > b ? a : b)

#define MAX3(a, b, c) (MAX2(MAX2(a, b), c))

#define SIZEOF_VAR(var) ((char *)(&var + 1) - (char *)&var)

#define SIZEOF_TYPE(type) ((size_t)((type *)0 + 1))

int main ()
{
	int i = 0;
	int j = 0;
	int k = 0;
	int num = 4;
	char ch = 'a';
	float f = 3.54;
	
	for (i = -1; i < 2; ++i)
	{
		for (j = -1; j < 2; ++j)
		{
			printf("Max of %d and %d: %d\n", i, j, MAX2(i, j));
		}
	}

	for (i = -1; i < 2; ++i)
	{
		for (j = -1; j < 2; ++j)
		{
			for (k = -1; k < 2; ++k)
			{	
				printf("Max of %d and %d and %d: %d\n", i, j, k, MAX3(i, j,\
						 k));
			}
		}
	}

	
	printf("Size of var num of type int: %lu\n", SIZEOF_VAR(num));
	printf("Size of var ch of type char: %lu\n", SIZEOF_VAR(ch));
	printf("Size of var f of type float: %lu\n", SIZEOF_VAR(f));
	
	printf("Size of int: %lu\n", SIZEOF_TYPE(int));
	printf("Size of char: %lu\n", SIZEOF_TYPE(double));
	printf("Size of float: %lu\n", SIZEOF_TYPE(float));
	
	
	return (0);
}

