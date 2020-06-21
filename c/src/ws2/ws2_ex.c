/*
*Developer: Ezra Gordon
*Reviewer: Erez
*/

#include <string.h> /* strlen */
#include <assert.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "ws2_ex.h"

int HasDigit(int tmp_from, int digit);

/********************************* IsPalindrome *******************************/
/* Checks if a string is the same if written in reverse                       */
/*Status: A                  								                  */
/******************************************************************************/
int IsPalindrome(const char *str)
{
	const char *end = NULL;

	assert(NULL != str);

	end = str + strlen(str) - 1;

	while ((str < end) && (*str == *end)) /* while the left check hasn't passed
									the mid-point and the values are the same */
	{
		++str;
		--end;
	}

	if (*str != *end)
	{
		return (0);
	}
	return (1);
}

/************************************ SevenBoom *******************************/
/* Prints "Boom!" if a number contains a 7 or divides evenly by 7             */
/*Status: A                  								                  */
/******************************************************************************/
void SevenBoom(int from, int to)
{
	int is_boom = 0;
	int digit = 7;

	while (from <= to)
	{
		if (0 == (from % digit)) 		 /* If the number divides evenly by 7 */
		{
			printf("BOOM! ");
			is_boom = 1;
		}
		else
		{
			is_boom = HasDigit(from, digit);
		}

		if (!is_boom) 								/* If no boom has occured */
		{
			printf("%d ", from);
		}

		++from;
		is_boom = 0;
	}
	printf("\n");
}

int HasDigit(int from, int digit)
{
	while (from > 0)
	{
		if (digit == (from % 10))	/* if remainder is 7, the number contains
																		a 7 */
		{
			printf("BOOM! ");
			return (1);
		}
		else
		{
			from /= 10; 			/* last digit will be removed in implict
															   	   conversion */
		}
	}
	return (0);
}

/********************************** PointerSwap *******************************/
/*Swaps the address the pointer to pointer points to                          */
/*Status: A                   								                  */
/******************************************************************************/

void SwapPtrs(int **pptr1, int **pptr2)
{
	int *ptr_tmp = NULL;

	assert(NULL != pptr1);
	assert(NULL != pptr2);

	ptr_tmp = *pptr1;
	*pptr1 = *pptr2;
	*pptr2 = ptr_tmp;
}

/********************************** AddStrs ***********************************/
/*Adds to numbers represented as strings and returns the calculated total     */
/*Status: A                   								                  */
/******************************************************************************/

char *AddStrs(const char *str1, const char *str2, char *result)
{
	int length1 = 0;
	int length2 = 0;
	int max_length = 0;
	int min_length = 0;
	const char *max_str = NULL;
	const char *min_str = NULL;
	int digit_of_string1 = 0;
	int digit_of_string2 = 0;
	int digit_for_final_string = 0;
	int carry_over = 0;
	char *result_start = NULL;

	/* Check if pointers exist */
	assert(NULL != str1);
	assert(NULL != str2);
	assert(NULL != result);

	length1 = strlen(str1);
	length2 = strlen(str2);

	/* Find max/min strings and lengths */
	if (length1 > length2)
	{
		max_length = length1;
		max_str = str1;
		min_length = length2;
		min_str = str2;
	}
	else
	{
		max_length = length2;
		max_str = str2;
		min_length = length1;
		min_str = str1;
	}

	result_start = result;
	result = result + max_length + 1;


	*result = '\0'; 								/* Add null terminator */
	--result;

	while (min_length) /* As long as min_length is greater than 0 */
	{
		/* convert charaters to int */
		digit_of_string1 = (int)(*(min_str + min_length - 1) - '0');
		digit_of_string2 = (int)(*(max_str + max_length - 1) - '0');
		digit_for_final_string = carry_over + digit_of_string1
								 + digit_of_string2; /* add digits together */

		/* take carry-over value to next digit */
		carry_over = digit_for_final_string / 10;

		/* keep the remainder as the current digit */
		digit_for_final_string = digit_for_final_string % 10;

		/* convert back to character */
		*result = (char)digit_for_final_string + '0';

		--result;
		--max_length;
		--min_length;
	}

	do
	{
		if (max_length > 0)
		{
			/* convert charater to int */
			digit_for_final_string = (int)(*(max_str + max_length - 1) - '0');
		}
		else
		{
			/* if both strings were the same size */
			digit_for_final_string = 0;
		}

		digit_for_final_string += carry_over; /* add carry-over */

			/* convert back to character */
		digit_for_final_string = digit_for_final_string + '0';

		*result = (char)digit_for_final_string; /* Add number to string */
		carry_over = 0;
		--result;
		--max_length;
	}
	while (max_length >= 0);

	return (result_start);
}
