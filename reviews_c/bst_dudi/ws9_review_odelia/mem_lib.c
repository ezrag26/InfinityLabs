#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


#include "mem_lib.h"

/* set n times the char represented by an integer to ptr location */
void *Memset(void *ptr, int a, size_t n)
{
	size_t first_bytes =(SIZE_OF_WORD - ((size_t)ptr % SIZE_OF_WORD)) % SIZE_OF_WORD;
	size_t i = 0;
	unsigned char word[SIZE_OF_WORD] ={0};
	void *start_p = ptr;
	unsigned char ch = (unsigned char )a;
	
	assert(NULL != ptr);

	for (i = 0; i < SIZE_OF_WORD; ++i)/* creating a word chunk */
	{
		word[i] = ch;
	}

	/* if the address isn't alligned - set chars till the alligned address */
	while (SIZE_OF_WORD > (first_bytes--))
	{
		*((char *)ptr) = ch;
		ptr = ((char *)ptr ) + 1;
		--n;
	}

	/* set word chunks */
	while (SIZE_OF_WORD <= n)
	{
		*((size_t *)ptr) = *(size_t *)word;
		ptr = ((size_t *)ptr) + 1;
		n -= SIZE_OF_WORD;
	}

	/* if there are still chars to add - set them at the end */
	while (n--)
	{
		*((char *)ptr) = ch;
		ptr = ((char *)ptr ) + 1;
	}

	return start_p;
}




/* copy n bytes from src (str2) to dest(str1) (dont treat overlap) */
void *Memcpy(void *str1, const void *str2, size_t n)
{
	size_t first_bytes = (SIZE_OF_WORD - ((size_t)str1 % SIZE_OF_WORD)) % SIZE_OF_WORD;

	void *start_p = str1;

	assert(NULL != str1);
	assert(NULL != str1);

	/* if the address isn't alligned - set chars till the alligned address */
	while (SIZE_OF_WORD > (first_bytes--))
	{
		*((char *)str1) = *((char *)str2);
		str1 = ((char *)str1) + 1;
		str2 = ((char *)str2) + 1;
		--n;
	}

	/* set word chunks */
	while (SIZE_OF_WORD <= n)
	{
		*((size_t *)str1) = *((size_t *)str2);
		str1 = ((size_t *)str1) + 1;
		str2 = ((size_t *)str2) + 1;
		n -= SIZE_OF_WORD;
	}

	/* if there are still chars to add - set them at the end */
	while (n--)
	{
		*((char *)str1) = *((char *)str2);
		str1 = ((char *)str1) + 1;
		str2 = ((char *)str2) + 1;
	}

	return start_p;
}

/* move n bytes from src to dest - treat overlap */
void *Memmove(void *dest, const void *src, size_t n)
{
	size_t diff = (char *)dest - (char *)src;
	/*size_t overlap = n - diff;*/
	size_t left_overs = n % diff;

	if (dest > src )
	{
		/* move the last bytes */
		Memcpy((char *)dest + n -left_overs,
							(char *)dest + n - diff - left_overs, left_overs);
		n -= left_overs;

		while (n > diff)
		{
			/* move by diff chuncks */
			Memcpy((char *)dest + n - diff,(char *)dest + n - (2 * diff), diff);
			n -= diff;
		}

		Memcpy((char *)dest,(char *)src, diff);
	}
	else
	{
		return Memcpy(dest, src, n);
	}

	return dest;
}
