#include <stdio.h>  /* printf */
#include <assert.h> /* assert */

#include "ws6_ex.h"

/* prints the bit formation of a float number */
void PrintFloatBits(float f)
{
	unsigned int check = 0x80000000;						   /* 1000...0000 */
	int *ptr = (int *)&f;				/* explicit casting to work with bits */
	
	while (check > 0)					/* haven't finished checking the bits */
	{
		if(check == (check & *ptr)) 						/* bit is set */
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	
		check >>= 1;
	}
	
	printf("\n");
}
