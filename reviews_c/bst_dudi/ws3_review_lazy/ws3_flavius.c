/*
*Developer: Lazy Frid
*Reviewer: Ezra Gordon
*Status: F
*/

#include <stdio.h>						/* for printf */
#include <stdlib.h>						/* for malloc */

int Flavius(int n, int start)
{
	/* A few comments explaining what's going on would be helpful to the next
	reader - remember, I know what the code is supposed to do, but someone else
	probably doesn't. */
	int i = 0;
	int *arr = malloc(sizeof(int) * n);

	for (i = 0; i < n; ++i)
	{
		*(arr + i) = (i + 1) % n;
	}

	i = start - 1;

	while (i != *(arr + i))
	{
		printf("#%d was killed.\n", *(arr + i) + 1);
		*(arr + i) = *(arr + *(arr + i));
		i = *(arr + i);
	}
	printf("#%d is last one alive!\n", i + 1);

	free(arr);

	return (i + 1);
}

int main()
{
	printf("Flavius(5,3) >\n");
	Flavius(5,3);

	printf("\nFlavius(5,3) >\n"); /* Not critical, but you probably meant to
									print (14, 6) */
	Flavius(14,6);

	return 0;
}
