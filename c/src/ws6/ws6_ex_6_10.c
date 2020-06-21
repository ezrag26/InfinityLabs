#include <stddef.h> /* sizeof */
#include <assert.h> /* assert */

#include "ws6_ex.h"

/* checks if the 2nd and 6th bits are both set */
unsigned int Bits2And6(unsigned char ch)
{
	return (0x22 == (0x22 & ch)); 			 /* 2nd and 6th bits are both set */
}

/******************************************************************************/

/* checks if at least one bit is set in the 2nd and 6th bits */
unsigned int Bits2Or6(unsigned char ch)
{
	return (0 != (0x22 & ch));						   /* at least one is set */
}

/******************************************************************************/

/* swaps the 3rd and 5th bits of a char */
unsigned char SwapBits(unsigned char ch)
{
	/* check if the 3rd/5th bit is set or unset, and move it to the position it 	   needs to be swapped to */
	unsigned char tmp = (((ch & 0x04) << 2)) | (((ch & 0x10) >> 2));
	
	/* if the 3rd/5th bit was set, unset the bit */
	ch &= 0xEB; 										   /* 0xEB = 11101011 */
	
	/* set the bit if it needs to be set */
	return tmp |= ch;
}

/******************************************************************************/

/* returns the closest (smaller) number that divides evenly by 16 */
unsigned int DividedBy16(unsigned int n)
{
	/* if any bits are set below 2^4 (16), it is not divisible by 16, so take 
	the next closest (smaller) number */
	return (n & 0xFFFFFFF0);
}

/******************************************************************************/

/* swaps the values of two variables */
int Swap2Vars(unsigned int *n1, unsigned int *n2)
{

	assert(NULL != n1);
	assert(NULL != n2);

	*n1 = (*n1 ^ *n2);
	*n2 = (*n1 ^ *n2);					/* XOR of XOR equals the first number */
	*n1 = (*n1 ^ *n2);			/* XOR of XOR of XOR equals the second number */
}

/******************************************************************************/

/* counts the amount of bits that are set in a number with a loop */
int CountSetBitsLoop(int n)
{
	int count = 0;
	
	while (n > 0) 						/* haven't finished checking the bits */
	{
		if (1 == (n & 1)) 										/* bit is set */
		{
			++count;
		}
		
		n >>= 1;
	}
	
	return (count);
}

/******************************************************************************/

/* counts the amount of bits that are set in a number without a loop */
int CountSetBits(int n)
{
	/* Add the left bits with the right bits of each half nibble */
	n = ((n & 0xAAAAAAAA) >> 1) + ((n & 0x55555555));
	/* Add the left bits with the right bits of each nibble */
	n = ((n & 0xCCCCCCCC) >> 2) + ((n & 0x33333333));
	/* Add the left bits with the right bits of each double nibble */
	n = ((n & 0xF0F0F0F0) >> 4) + ((n & 0x0F0F0F0F));
	/* Add the left bits with the right bits of each quadruple nibble */
	n = ((n & 0xFF00FF00) >> 8) + ((n & 0x00FF00FF));
	/* Add the left bits with the right bits of the whole number */
	n = ((n & 0xFFFF0000) >> 16) + ((n & 0x0000FFFF));

	return (n);
}
