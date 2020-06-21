#include <stdio.h>
#include <string.h>

#include "mem_lib.h"

int main ()
{
	char string[] = "this is a sentence to see if memset will work";
	char string1[] = "this is a sentence to see if memset will work";
	int set_nums[] = {1, 2, 3, 4, 5, 6, 7};
	int set_nums1[] = {1, 2, 3, 4, 5, 6, 7};

	char str_src[] = "123456789012345678901234567890";
	char str_src1[] = "123456789012345678901234567890";
	int cpy_nums[] = {1, 2, 3, 4, 5, 6, 7};
	int cpy_nums2[] = {3, 4, 1, 6, 2, 7, 8};
	char str_dest[] = "abcdefghijklmnopqrstuvwxyz";
	char str_dest1[] = "abcdefghijklmnopqrstuvwxyz";
	int cpy_nums1[] = {1, 2, 3, 4, 5, 6, 7};
	int cpy_nums3[] = {3, 4, 1, 6, 2, 7, 8};

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
	printf("MemCpy Test...\n");
	printf("%s\n", (char *)Memcpy(str_dest, str_src, 18));
	printf("%s\n", (char *)memcpy(str_dest1, str_src1, 18));

	printf("%d\n", *(int *)Memcpy(cpy_nums, cpy_nums2, 3));
	printf("%d\n", *(int *)memcpy(cpy_nums1, cpy_nums3, 3));

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
