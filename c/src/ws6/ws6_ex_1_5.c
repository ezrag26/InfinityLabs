#include <stdio.h> /* printf */

#include "ws6_ex.h"

/* returns x * (2^y) */
long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);
}

/******************************************************************************/

/* checks if a number is a power of 2 using a loop */
int IsPow2Loop(unsigned int n)
{
	int count = 0;
	/* if counter is 2 (or more) it is not a pow of 2 */
	while (n > 0 && count < 2)
	{
		if (n & 1)
		{
			++count; 				 /* if bit is set, add one to the counter */
		}
		n >>= 1;
	}

	if (1 == count)												/* power of 2 */
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/******************************************************************************/

/* checks if a number is a power of 2 without a loop */
int IsPow2(unsigned int n)
{
	/* number isn't 0 and the (number - 1) has completely set bits */
	if ((n > 0) && (n & (n - 1)) == 0)
	{
		return (1);
	}
	
	return (0);
}

/******************************************************************************/

/* Adds 1 to an unsigned integer without using arithmetic operators */
unsigned int AddOne(unsigned int n)
{
	unsigned int current_check = 1; 		 /* start check at number 00...01 */
	
	while (current_check > 0)
	{
		if (current_check == (n & current_check)) 	 /* if current bit is a 1 */
		{
			n = ~n; 					   /* flip bits to make current bit 0 */
			n |= current_check;			/* All bits will stay the same except
											   the current one which is now 1 */
			n = ~n;					 /* Flip bits again to make current bit 0 */
			current_check <<= 1;						/* shift 1 left to check
																	 next bit */
		}
		else if (0 == (n & current_check))			 /* if current bit is a 0 */
		{
			n |= current_check;						/* Make the current bit 1 */
			break;											/* end the checks */
		}
	}

	return (n);
}

/******************************************************************************/

/* prints "true" if the number has exactly 3 bits set */
void Print3One(unsigned int arr[], int length)
{
	int count = 0;
	int i = 0;
	unsigned int current_check = 1;
	
	for (i = 0; i < length; ++i)
	{
		current_check = 1;
		count = 0;
		/* number hasn't been fully checked and there aren't more than 3 set 			   bits */
		while (0 < current_check && 4 > count)
		{
			if (arr[i] & current_check)				  	/* current bit is set */
			{
				++count;
			}
			current_check <<= 1;				   /* shift to check next bit */
		}

		if (3 == count)
		{
			arr[i] = 1;
		}
		else
		{
			arr[i] = 0;
		}
	}
}

/******************************************************************************/

/* uses loop to mirror the byte's bits */
unsigned char ByteMirrorLoop(unsigned char n)
{
	unsigned char right_check = 0x01;
	unsigned char new_n = 0x00;
	size_t char_size = sizeof(n);
	size_t i = 0;
	
	while(i < char_size)
	{
		if (right_check == (n & right_check)) 					/* bit is set */
		{
			new_n <<= 1;						 /* add new space for the bit */
			new_n ^= right_check;				 /* set the bit */
		}
		else
		{
			new_n <<= 1;				   /* add a new space and leave unset */
		}
		
		n >>= 1;							   /* shift number for next check */
		++i;
	}
	return new_n;
}

/******************************************************************************/

/* mirrors the byte's bits without a loop */
unsigned char ByteMirror(unsigned char n)
{
	/* Switch the bits of each half nibble */
	n = (((n & 0xAA) >> 1) | ((n & 0x55)) << 1);
	/* switch the bits for the nibble on each side*/
	n = (((n & 0xCC) >> 2) | ((n & 0x33)) << 2);
	/* switch the nibbles of the byte */
	n = (((n & 0xF0) >> 4) | ((n & 0x0F)) << 4);
	
	return (n);
}

