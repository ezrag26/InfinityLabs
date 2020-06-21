/********************/
/* Date: 28/08/2019 */
/* Developer: Ezra  */
/* Reviewer: Tom    */
/* Status: A  		*/
/********************/

#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "bit_array.h"

#if ((4 == SIZE_OF_LONG) && (8 == SIZE_OF_LONG))
#error This library only works on 32- or 64-bit systems
#endif

#define CHAR_BIT (8)
#define BITS_IN_BIT_ARRAY (sizeof(size_t) * CHAR_BIT)
#define SIZE_OF_LONG (__SIZEOF_LONG__)
#define TWO_POWER_EIGHT (256)

#if SIZE_OF_LONG == 4
#define ALL_BITS ((bit_arr_t)0xFFFFFFFF)
#define NO_BITS ((bit_arr_t)0x00000000)
#define RIGHT_BIT ((bit_arr_t)0x00000001)
#define LEFT_BIT ((bit_arr_t)0x80000000)
#endif


#if SIZE_OF_LONG == 8
#define ALL_BITS ((bit_arr_t)0xFFFFFFFFFFFFFFFF)
#define NO_BITS ((bit_arr_t)0x0000000000000000)
#define RIGHT_BIT ((bit_arr_t)0x0000000000000001)
#define LEFT_BIT ((bit_arr_t)0x8000000000000000)
#endif

bit_arr_t BitArrSetAllOn(bit_arr_t b)
{
	(void)b;
	return (ALL_BITS);
}

bit_arr_t BitArrSetAllOff(bit_arr_t b)
{
	(void)b;
	return (NO_BITS);
}

bit_arr_t BitArrSetOn(bit_arr_t b, size_t index)
{
	return (b | (RIGHT_BIT << index));
}

bit_arr_t BitArrSetOff(bit_arr_t b, size_t index)
{
	return (b & ~(RIGHT_BIT << index));
}

bit_arr_t BitArrSetBit(bit_arr_t b, size_t index, int value)
{
	if (1 == value)
	{
		return (b | (RIGHT_BIT << index));
	}
	else
	{
		return (b & ~(RIGHT_BIT << index));
	}
}

bit_arr_t BitArrFlipBit(bit_arr_t b, size_t index)
{
	return (b ^ (RIGHT_BIT << index));
}

bit_arr_t BitArrMirror(bit_arr_t b)
{

#if	SIZE_OF_LONG == 4
	/* swap every 2 adjacent bits */
	b = (((b & 0xAAAAAAAA) >> 1) | ((b & 0x55555555) << 1));

	/* swap every adjacent half nibbles */
	b = (((b & 0xCCCCCCCC) >> 2) | ((b & 0x33333333) << 2));

	/* swap every adjacent nibbles */
	b = (((b & 0xF0F0F0F0) >> 4) | ((b & 0x0F0F0F0F) << 4));

	/* swap every adjacent bytes */
	b = (((b & 0xFF00FF00) >> 8) | ((b & 0x00FF00FF) << 8));

	/* swap every adjacent 2 bytes */
	b = (((b & 0xFFFF0000) >> 16) | ((b & 0x0000FFFF) << 16));

#endif
#if	SIZE_OF_LONG == 8
	/* swap every 2 adjacent bits */
	b = (((b & 0xAAAAAAAAAAAAAAAA) >> 1) | ((b & 0x5555555555555555) << 1));

	/* swap every adjacent half nibbles */
	b = (((b & 0xCCCCCCCCCCCCCCCC) >> 2) | ((b & 0x3333333333333333) << 2));

	/* swap every adjacent nibbles */
	b = (((b & 0xF0F0F0F0F0F0F0F0) >> 4) | ((b & 0x0F0F0F0F0F0F0F0F) << 4));

	/* swap every adjacent bytes */
	b = (((b & 0xFF00FF00FF00FF00) >> 8) | ((b & 0x00FF00FF00FF00FF) << 8));

	/* swap every adjacent 2 bytes */
	b = (((b & 0xFFFF0000FFFF0000) >> 16) | ((b & 0x0000FFFF0000FFFF) << 16));

	/* swap every adjacent 4 bytes */
	b = (((b & 0xFFFFFFFF00000000) >> 32) | ((b & 0x00000000FFFFFFFF) << 32));
#endif
	return (b);
}

bit_arr_t BitArrMirrorLUT(bit_arr_t b)
{
	size_t i = 0;
	unsigned char *p_b = (unsigned char *)&b;
	bit_arr_t b_temp = 0;
	unsigned char *p_b_temp = (unsigned char *)&b_temp;
	bit_arr_t temp = 0;
	static unsigned char COUNT_LUT[256] = {0};
	static int LUT_initialized = 0;


	if (0 == LUT_initialized)
	{
		for (i = 0; i < TWO_POWER_EIGHT; ++i)
		{
			/* swap every 2 adjacent bits */
			temp =	(((i & 0xAA) >> 1) | ((i & 0x55) << 1));

			/* swap every adjacent half nibbles */
			temp =	(((temp & 0xCC) >> 2) | ((temp & 0x33) << 2));

			/* swap every adjacent nibbles */
			temp =	(((temp & 0xF0) >> 4) | ((temp & 0x0F) << 4));

			COUNT_LUT[i] = (unsigned char)temp;
		}
	}

	LUT_initialized = 1;

	for (i = SIZE_OF_LONG; i > 0; --i)
	{
		/* Put first byte in last position, next byte in next position, etc.. */
		*(p_b_temp + i - 1) = COUNT_LUT[(int)*p_b];
		++p_b;
	}
	return (b_temp);
}

int BitArrIsOn(bit_arr_t b, size_t index)
{
	return (b & (RIGHT_BIT << index) ? 1 : 0);
}

int BitArrIsOff(bit_arr_t b, size_t index)
{
	return ((((RIGHT_BIT << index) & (b | ~(RIGHT_BIT << index))) == 0) ? 1 : 0);
}

size_t BitArrCountOn(bit_arr_t b)
{

#if	SIZE_OF_LONG == 4
	/* add every 2 adjacent bits */
	b = (((b & 0xAAAAAAAA) >> 1) + ((b & 0x55555555)));

	/* add every adjacent half nibble */
	b = (((b & 0xCCCCCCCC) >> 2) + ((b & 0x33333333)));

	/* add every adjacent nibble */
	b = (((b & 0xF0F0F0F0) >> 4) + ((b & 0x0F0F0F0F)));

	/* add every adjacent byte */
	b = (((b & 0xFF00FF00) >> 8) + ((b & 0x00FF00FF)));

	/* add every adjacent 2 bytes */
	b = (((b & 0xFFFF0000) >> 16) + ((b & 0x0000FFFF)));
#endif

#if	SIZE_OF_LONG == 8
	/* add every 2 adjacent bits */
	b = (((b & 0xAAAAAAAAAAAAAAAA) >> 1) + ((b & 0x5555555555555555)));

	/* add every adjacent half nibble */
	b = (((b & 0xCCCCCCCCCCCCCCCC) >> 2) + ((b & 0x3333333333333333)));

	/* add every adjacent nibble */
	b = (((b & 0xF0F0F0F0F0F0F0F0) >> 4) + ((b & 0x0F0F0F0F0F0F0F0F)));

	/* add every adjacent byte */
	b = (((b & 0xFF00FF00FF00FF00) >> 8) + ((b & 0x00FF00FF00FF00FF)));

	/* add every adjacent 2 bytes */
	b = (((b & 0xFFFF0000FFFF0000) >> 16) + ((b & 0x0000FFFF0000FFFF)));

	/* add every adjacent 4 bytes */
	b = (((b & 0xFFFFFFFF00000000) >> 32) + ((b & 0x00000000FFFFFFFF)));
#endif

	return ((size_t)b);
}

size_t BitArrCountOnLUT(bit_arr_t b)
{
	size_t i = 0;
	unsigned char *p_b = (unsigned char *)&b;
	size_t result = 0;
	static unsigned char COUNT_LUT[256] = {0};
	static int LUT_initialized = 0;

	if (0 == LUT_initialized)
	{
		for (i = 0; i < TWO_POWER_EIGHT; ++i)
		{
			COUNT_LUT[i] = BitArrCountOn(i);
		}
	}

	LUT_initialized = 1;

	for (i = 0; i < SIZE_OF_LONG; ++i)
	{
		result += COUNT_LUT[(int)*(p_b + i)];
	}

	return (result);
}

size_t BitArrCountOff(bit_arr_t b)
{
	/* subtract all the set bits from the toal bits */

	return ((size_t)(BITS_IN_BIT_ARRAY - BitArrCountOn(b)));
}

bit_arr_t BitArrRotateRight(bit_arr_t b, size_t n)
{
	n %= BITS_IN_BIT_ARRAY;

	/* Shift the bit array right the requested amount and shift the bit array */
	/* left the total amount of bits minus the requested amount of rotations */
	return ((b >> n) | (b << (BITS_IN_BIT_ARRAY - n)));
}

bit_arr_t BitArrRotateLeft(bit_arr_t b, size_t n)
{
	n %= BITS_IN_BIT_ARRAY;

	/* Shift the bit array left the requested amount and shift the bit array */
	/* right the total amount of bits minus the requested amount of rotations */
	return ((b << n) | (b >> (BITS_IN_BIT_ARRAY - n)));
}

char *BitArrToString(bit_arr_t b, char *dest)
{
	size_t i = 0;

	/* i is less than total bytes */
	for (i = 0; i < (sizeof(size_t) * CHAR_BIT); ++i)
	{
		/* if the left bit of b equals 0x8000000000000000 */
		dest[i] = (char)((LEFT_BIT == (b & LEFT_BIT)) + '0');
		b <<= 1;									  /* shift for next check */
	}
	dest[i] = '\0';									   /* add null terminator */

	return (dest);
}
