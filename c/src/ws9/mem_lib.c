/******************
* Developer: Ezra *
* Reviewer: Shir  *
* Status: S		  *
* Date: 26/8/19	  *
*******************/

#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "mem_lib.h"

#define EXTRA_DIGIT (1)

int main ()
{
	char string[] = "this is a sentence to see if memset will work";
	char string1[] = "this is a sentence to see if memset will work";
	int set_nums[] = {1, 2, 3, 4, 5, 6, 7};
	int set_nums1[] = {1, 2, 3, 4, 5, 6, 7};
	
	char str_src[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_src1[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_src3[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_src4[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_src5[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_src6[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_src7[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_src8[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str_dest[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest1[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest3[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest4[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest5[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest6[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest7[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest8[] = "abcdefghijklmnopqrstuvwxyz";
/*	
	int cpy_nums[] = {1, 2, 3, 4, 5, 6, 7};
	int cpy_nums2[] = {3, 4, 1, 6, 2, 7, 8};
	int cpy_nums1[] = {1, 2, 3, 4, 5, 6, 7};
	int cpy_nums3[] = {3, 4, 1, 6, 2, 7, 8};
*/
	char str_dest_move[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest_move1[] = "abcdefghijklmnopqrstuvwxyz";
	int move_nums1[] = {1, 2, 3, 4, 5, 6, 7};
	int move_nums2[] = {1, 2, 3, 4, 5, 6, 7};
						 /*"abcdefabcdefgnopqrstuvwxyz"*/

/****************************** MemSet **************************************/
	printf("MemSet Test...\n");
	printf("%s\n", (char *)Memset(string, '$', 16));
	printf("%s\n", (char *)memset(string1, '$', 16));
	
	printf("%d\n", *(int *)Memset(set_nums, 'c', 3));
	printf("%d\n", *(int *)memset(set_nums1, 'c', 3));
	printf("\n");
	
/****************************** MemCpy **************************************/
	printf("MemCpy Test 1...");
/*	if (0 != strcmp(Memcpy(str_dest + 2, str_src + 4, 18), memcpy(str_dest1 + 2, str_src1 + 4, 18)))
	{
		printf("Failed\n");
	}
*/	printf("\n%s\n", (char *)Memcpy(str_dest + 2, str_src + 4, 18));
	printf("%s\n\n", (char *)memcpy(str_dest1 + 2, str_src1 + 4, 18));
	
	printf("MemCpy Test 2...");
/*	if (0 != strcmp(Memcpy(str_dest3 + 2, str_src3 + 4, 22), memcpy(str_dest4 + 2, str_src4 + 4, 22)))
	{
		printf("Failed\n");
	}
*/	printf("\n%s\n", (char *)Memcpy(str_dest3 + 2, str_src3 + 4, 22));
	printf("%s\n\n", (char *)memcpy(str_dest4 + 2, str_src4 + 4, 22));
	
	printf("MemCpy Test 3...");
/*	if (0 != strcmp(Memcpy(str_dest5 + 4, str_src5 + 2, 18), memcpy(str_dest6 + 4, str_src6 + 2, 18)))
	{
		printf("Failed\n");
	}
*/	printf("\n%s\n", (char *)Memcpy(str_dest5 + 4, str_src5 + 2, 18));
	printf("%s\n\n", (char *)memcpy(str_dest6 + 4, str_src6 + 2, 18));
	/* 34567890ABCDEFGHIJwxyz*/
	printf("MemCpy Test 4...");
/*	if(0 != strcmp(Memcpy(str_dest7 + 4, str_src7 + 2, 22), memcpy(str_dest8 + 4, str_src8 + 2, 22)))
	{
		printf("Failed\n");
	}
*/	printf("\n%s\n", (char *)Memcpy(str_dest7 + 4, str_src7 + 2, 22));
	printf("%s\n\n", (char *)memcpy(str_dest8 + 4, str_src8 + 2, 22));
/*
	printf("%d\n", *(int *)Memcpy(cpy_nums, cpy_nums2, 3));
	printf("%d\n", *(int *)memcpy(cpy_nums1, cpy_nums3, 3));
*/
	printf("\n");
	
/****************************** MemMove *************************************/
	printf("MemMove Test...\n");
	printf("%s\n", (char *)Memmove(str_dest_move + 6, str_dest_move, 7));
	printf("%s\n", (char *)memmove(str_dest_move1 + 6, str_dest_move1, 7));
	
	printf("%d\n", *(int *)Memmove(move_nums1, move_nums1, 3));
	printf("%d\n", *(int *)memmove(move_nums2, move_nums2, 3));
	
	printf("\n");
	
	return 0;
}

void *Memset(void *s, int c, size_t n)
{
	char *p_s = s;
	size_t offset = 0;
	size_t i = 0;
	word_size_t word = {0};
	/* for creating 8 bytes of the character */
	char *p_word = (char *)&word;
	unsigned char ch = (unsigned char)c;
	
	assert(NULL != s);
	
	/* Number of bytes in word minus the bytes from start of string */
	offset = (BYTES_IN_WORD - ((size_t)p_s % BYTES_IN_WORD)) % BYTES_IN_WORD;
	
	/* while not at the end of the offset, write byte by byte */
	for (i = 0; i < offset && 0 < n ; ++i)
	{
		*(p_s + i) = ch;
		--n;
	}
	
	/* create the full word */
	for (i = 0; i < BYTES_IN_WORD; ++i)
	{
		*p_word = ch;								   /* assign current byte */
		++p_word;									     /* next byte of word */
	}
	
	/* while there is enough room to write the full word */
	while (n >= BYTES_IN_WORD)
	{
		*(word_size_t *)p_s = word;
		n -= BYTES_IN_WORD;
		p_s += BYTES_IN_WORD;
	}
	
	/* if there is less than a word to be written, write until the end of n */
	for (i = 0; i < n; ++i)
	{
		*(p_s + i) = ch;
	}

	return (s);
}

void *Memcpy(void *dest, const void *src, size_t n)
{
	word_size_t write;
	word_size_t read;
	char *p_write = (char *)&write;
	char *p_read = (char *)&read;
	char *ptr_dest = dest;
	const char *ptr_src = src;
	size_t dest_offset = 0;
	size_t src_offset = 0;
	size_t i = 0;
	size_t j = 0;
	
	assert(NULL != dest);
	assert(NULL != src);	

	/* Number of bytes in word minus the bytes from start of string */
	dest_offset = (BYTES_IN_WORD - ((size_t)dest % BYTES_IN_WORD)) %
																  BYTES_IN_WORD;

	/* while not at the end of the dest_offset, write byte by byte */
	for (i = 0; i < dest_offset && 0 < n; ++i, --n)
	{
		*ptr_dest = *ptr_src;
		++ptr_dest;
		++ptr_src;
	}

	/* while not at the end of the src_offset, write byte by byte */
	src_offset = (BYTES_IN_WORD - ((size_t)ptr_src % BYTES_IN_WORD)) %
																  BYTES_IN_WORD;
	
	for (i = 0; i < src_offset; ++i)
	{
		*p_write = *ptr_src;
		++ptr_src;
		++p_write;
	}
	
	while (n >= BYTES_IN_WORD)
	{
		
		/* create full word to copy to write */
		read = *(word_size_t *)ptr_src;
		ptr_src += BYTES_IN_WORD;

		/* copy from read until write is full */
		for (j = 0; i < BYTES_IN_WORD; ++i, ++j)
		{
			*p_write = *p_read;
			++p_write;
			++p_read;
		}
		
		/* return p_write back to write */
		p_write = (char *)&write;
	
		/* copy write to dest */
		*(word_size_t *)ptr_dest = write;
		n -= BYTES_IN_WORD;
		ptr_dest += BYTES_IN_WORD;

		/* copy the rest of read to write */
		for (i = 0; j < BYTES_IN_WORD; ++i, ++j)
		{
			*p_write = *p_read;
			++p_write;
			++p_read;
		}
		p_read = (char *)&read;
	}
	
	
	if (i < BYTES_IN_WORD)
	{
		read = *(word_size_t *)ptr_src;
		ptr_src += BYTES_IN_WORD;
		
		while (i < BYTES_IN_WORD)
		{
			*p_write = *p_read;
			++p_write;
			++p_read;
			++i;
		}
	}
	
	p_read = (char *)&read;
	p_write = (char *)&write;
	
	/* if there is less than a word to be written, write until the end of n */
	for (i = 0; i < n; ++i)
	{
		*ptr_dest = *p_write;
		++ptr_dest;
		++p_write;
	}


	return (dest);
}

void *Memmove(void *dest, const void *src, size_t n)
{

	char *ptr_dest = (char *)dest;
	char *ptr_src = (char *)src;
	
	assert(NULL != dest);
	assert(NULL != src);

	/* if the to-be-copied area overlaps with the dest */
	if ((ptr_src + n) > ptr_dest)
	{
		if (ptr_src > ptr_dest)
		{
			Memcpy(ptr_dest, ptr_src, n);
		}
		
		else 				/* while they overlap */
		{
			/* copy last digit to be copied to the last position of dest */
			*(ptr_dest + n - EXTRA_DIGIT) = *(ptr_src + n - EXTRA_DIGIT); 
			--n;
		}
	}
	else
	{
		Memcpy(ptr_dest, ptr_src, n);
	}
	
	if (n > 0)
	{
		Memcpy(ptr_dest, ptr_src, n);
	}
	
	return (dest);
}
