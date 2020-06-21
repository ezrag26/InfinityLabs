/* developr: David Ezra
   reviewer: Ezra Gordon
   status: f
*/

#include <stdio.h>
#include <assert.h>               /* for assertion of input	*/
#include <string.h>
#include <stdlib.h>               /* for malloc	*/
#include "ws2_ex.h"



/*****************************   Is polindrome   *****************************/
/*       A function that checks if a string is a palindrome  */

int IsPalindrome(const char *str)
{
	int ispal = 1;                    /*return-value of the function*/
	size_t size = strlen(str);
	char *end = (char*)str + (size -1);

	while (str < end)           /*  as long as the function doesnt get */
	{                           /*  to the center of the string        */
		if (*str != *end)
		{
			ispal = 0;			/*   if the is a different value between */
			break;			    /*   the two directions return 0  	  */
		}
		++ str;
		--end;
	}
							/* convention to put () around return statement */
	return ispal;			    /* if the string is a palindrome return 1 */
}


/*********************************   Boom    ********************************/
/*   A function that recieves a range, and prints all numbers in the range,
	 except for the numbers that contain the digit 7 are divisble by 7 with
	 no reminder.instead of those numbers the function prints BO         */

int SevenBoom (int bgn, int end)
{
	int digit = 7;
/* Make sure to have spaces between operators and operands to incrase readabiity */
	for (bgn = bgn; bgn <=end; ++bgn) /*  proceed along range  */
	{
		if (bgn%7 == 0)                /* if the number is divisable by 7*/
		{
			printf(" BOOM ");
			continue;
		}
					/* remove space between end braces '}' from if/else blocks with the coninuing if/else blocks */
		else if (HasTheDigit(bgn, digit)) /* if the number cointains */
		{                                 /* the digit 7             */
			printf(" BOOM ");
			continue;
		}
					/* remove space between end braces '}' from if/else blocks with the coninuing if/else blocks */
		else
		{
			printf(" %d ", bgn);
		}

	}

	printf("\n");
	return 0; /* convention to put () around return statement */
}

/*    A function that checks if a number contain specific digit   */

int HasTheDigit (int num, int digit)
{
	int answer = 0;

	while(num != 0)
	{
		if (num%10 == digit || num%10 == -digit) /* Separate operator from operands */
		{
			answer = 1;
			break;
		}

		num /= 10;
	}

	return answer; /* convention to put () around return statement */
}

/***********************    SwapPointers   *********************************/
/*       A function that recieves two pointers and switch them   */

void SwapPtrs (int **ppi1, int **ppi2)
{
	int *pi_temp = NULL;	/*   temp pointer for switching   */

	assert(NULL != ppi1);
	assert(NULL != ppi2);

	pi_temp = *ppi1;

	*ppi1 = *ppi2;
	*ppi2 = pi_temp;
}


/*****************************    AddingCalc    ******************************/
/*     A fumction that add 2 numbers represented by strings */

char *AddStrs(const char *num1, const char *num2, char *result)
{

	char *longer = NULL;
	char *shorter = NULL;
	size_t shorter_len = 0;
	size_t longer_len = 0;

	int cary = 0;
	int i = 0;

	assert(NULL != num1);
	assert(NULL != num2);
	assert(NULL != result);

/*  definng who is longer  */
	if (strlen(num1) >= strlen(num2))
	{
		longer = (char*)num1; /* casting convention (char *)num1 */
		shorter = (char*)num2;
	}

	else
	{
		longer =  (char*)num2;
		shorter = (char*)num1;
	}

/*  moving all strings to the right most size  */
    shorter_len = strlen(shorter); /* You've already essentially done this measurement above with longer and shorter.. Try combining them to remove un-needed variables */
	longer_len = strlen(longer);
	shorter = shorter + shorter_len -1; /* add some comments explaning the reasoning behind -1, or +2, etc. */
	longer = longer + longer_len -1;
	result = result + longer_len +2;

	*result = '\0';
	--result;

/*  first step - claculate until the end of shoter  */
	for(i = 0; i < (int)shorter_len; ++i)
	{
 	*result = Reminder((*longer + *shorter), cary);
	cary = Cary(*longer + *shorter, cary);
	--longer;
	--shorter;
	--result;
	}
/*  second step - claculate until the end of longer  */
	for(i = i; i < (int)longer_len; ++i)
	{
 		*result = Reminder(*longer, cary);
		cary = Cary(*longer, cary);
		--result;
		--longer;
	}

/*  if there is carry left  */
	if (cary == 1)
	{
		*result = '1';
	}
	else
	{
		++result;
	}

	return result; /* convention to put () around return statement */
}


/*  A function that recieves two numbers represented by chars
	and returns the reminder */
char Reminder(char num, int cary) /* These two parts (Cary and Reminder) seem way too long to me. Think about how you can receive a remainder and the carry number by using the modular '%' operator and divider '/' */
{
	char result;

	if (num >= ('0' + '0')) /* if num present two numbers */
	{
		result = num + cary - '0';
	}
	else
	{
		result = num + cary;
	}

	if (result>'9')        /* if num is bigger than 10, return the reminder*/
	{
		result -= 10;
	}

	return result; /* convention to put () around return statement */
}

/*  A function that recieves two numbers represented by chars
	and returns the cary */
char Cary(char num, int cary) /* These two parts (Cary and Reminder) seem way too long to me. Think about how you can receive a remainder and the carry number by using the modular '%' operator and divider '/' in way less code */
{
	char result;

	if (num >= ('0' + '0'))
	{
		result = num + cary - '0';
	}
	else
	{
		result = num + cary;
	}

	if (result>'9')
	{
		cary = 1; /* if num is bigger than 10, cary is 1  */
	}

	else
	{
		cary = 0; /* if num is smaller than 10, cary is 0  */
	}

	return cary; /* convention to put () around return statement */
}
