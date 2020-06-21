#include <stdio.h> /* printf */

#include "ws2_ex.h"
int HasDigit(int tmp_from, int digit);
int main()
{

	const char *strings[] = {"Test", "t", "racecar", "/racecar/", "?/ ?", "",
					   "12321"}; 							/* IsPalindrome */
	/*const char *expected_results[] = {"tseT", "t", "racecar", "racecar/", "? /?",
									"", "12321"};*/			/* IsPalindrome */
	int strings_size = sizeof(strings)/sizeof(char *);		/* IsPalindrome */
	int i = 0; 												/* IsPalindrome */
	int from = 1;											/* SevenBoom 	*/
	int to = 150;											/* SevenBoom 	*/
	int *ptr1 = &from;										/* SwapPtrs 	*/
	int *ptr2 = &to;										/* SwapPtrs 	*/
	int **pptr1 = &ptr1;									/* SwapPtrs 	*/
	int **pptr2 = &ptr2;									/* SwapPtrs 	*/
	const char *int_string[] = {"999999999", "999999999", "111111111","012345678", 
							 "876543210", "34567", "2345678"}; 	 /* AddStrs */
	char result_string[100] = "";

/*************************** IsPalindrome Tests *******************************/
	printf("IsPalindrome:\n");
	for (i = 0; i < strings_size; ++i)
	{
		if (!IsPalindrome(strings[i]))
		{
			printf("\'%s\' is not a palindrome\n", strings[i]);
		}
		else
		{
			printf("\'%s\' is a palindrome\n", strings[i]);
		}
	}


/********************************* SevenBoom **********************************/
	printf("\nSevenBoom:\n");
	SevenBoom(from, to);

/********************************** SwapPtrs **********************************/
	printf("\nSwapPtrs:\n");
	printf("Before:\nPtr1 Address: %p\nPtr2 Address: %p\n", (void *)*pptr1, (void *)*pptr2);
	SwapPtrs(pptr1, pptr2);
	printf("After:\nPtr1 Address: %p\nPtr2 Address: %p\n", (void *)*pptr1, (void *)*pptr2);

/********************************** AddStrs ***********************************/

	printf("\nAddStrs:\n");
	printf("%s + %s = %s\n", int_string[0], int_string[1], AddStrs(int_string[0], int_string[1], result_string));
	printf("%s + %s = %s\n", int_string[1], int_string[2], AddStrs(int_string[1], int_string[2], result_string));
	printf("%s + %s = %s\n", int_string[3], int_string[4], AddStrs(int_string[3], int_string[4], result_string));
	printf("%s + %s = %s\n", int_string[5], int_string[6], AddStrs(int_string[5], int_string[6], result_string));
	printf("%s + %s = %s\n", int_string[2], int_string[5], AddStrs(int_string[2], int_string[5], result_string));

	return (0);
}
