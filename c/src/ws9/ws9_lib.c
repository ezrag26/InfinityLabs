/******************
* Developer: Ezra *
* Reviewer: Shir  *
* Status: S		  *
* Date: 26/8/19	  *
*******************/


#include <stdio.h>  /* printf, sprintf */
#include <assert.h>	/* assert		   */
#include <string.h> /* strlen		   */

#include "ws9_lib.h"

#define LETTERS_IN_ALPHABET (26)
#define IS_LITTLE_ENDIAN (*(short *)&"\x11\xFF" == (short)0xFF11)

int main()
{

	int val[] = {-128, 10, 0};
	char buffer[100];
	const char *string[] = {"-12345", "12345", "0"};
	size_t i = 0;
	int base = 16;
	char arr1[] = {'a', 'b', 'c', 'd', 'r', '\0'};
	char arr2[] = {'a', 's', 'c', 'z', 'r', '\0'};
	char arr3[] = {'d', 's', 'c', 'z', 't', '\0'};
	
/**************************** ItoaBase10 Tests *******************************/	
	
	printf("Testing ItoaBase10...\n");
	for (i = 0; i < sizeof(val)/sizeof(val[0]); ++i)
	{
		printf("%s\n", ItoaBase10(val[i], buffer, 10));
	}
	
/******************************* Itoa Tests **********************************/	
	
	printf("Testing Itoa...\n");
	for (i = 0; i < sizeof(val)/sizeof(val[0]); ++i)
	{
		printf("%s\n", Itoa(val[i], buffer, base));
	}
	
/***************************** AtoiBase10 Tests ******************************/	
	
	printf("Testing AtoiBase10...\n");
	for (i = 0; i < sizeof(string)/sizeof(*string); ++i)
	{
		printf("%d\n", AtoiBase10(string[i]));
	}

/******************************* Atoi Tests **********************************/	
	
	printf("Testing Atoi...\n");
	for (i = 0; i < sizeof(string)/sizeof(*string); ++i)
	{
		printf("%d\n", Atoi(string[i], base));
	}
	
	
/**************************** CharInFirst2 Tests *****************************/	
	
	printf("Testing CharInFirst2...\n");
	CharInFirst2(arr1, arr2, arr3);
	
/***************************** Little/Big Endian *****************************/
	
	if (IsLittleEndian() == 1)
	{	
		printf("Little Endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}
	
	if (IS_LITTLE_ENDIAN == 1)
	{	
		printf("Little Endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}
	
	return (0);
}

static char *ReverseString(char *string, size_t length)
{
	char *right = string + length - 1;
	char *left = string;
	char tmp = '\0';

	assert(NULL != string);
	
	/* while all digits haven't swapped, swap the end digits */
	while (left < right)
	{
		tmp = *left;
		*left = *right;
		*right = tmp;
		++left;
		--right;
	}
	
	return (string);
}

char *ItoaBase10(int value, char *str, int base)
{
	int temp_value = value;
	size_t i = 0;
	int current_digit = 0;
	
	assert(NULL != str);
	
	if (0 == value)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	
	 /* if value is a negative number, change it to pos for the time being */
	if (value < 0)
	{
		temp_value = -value;
	}	
	
	while (temp_value > 0)
	{
		current_digit = temp_value % base; 			/* find last digit of str */
		str[i] = (char)current_digit + '0';
		temp_value /= base; 			 /* divide by base to find next digit */
		++i;
	}
	
	if (value < 0) 				  /* if value is negative, add the minus sign */
	{
		str[i] = '-';
		++i;
	}
	
	str[i] = '\0';								/* add null terminator to end */
	
	str = ReverseString(str, i); 						/* reverse the string */
	
	return (str);
}

int AtoiBase10(const char *str)
{
	int value = 0;
	size_t str_len = 0;
	size_t i = 0;
	int is_neg = 0;
	
	assert(NULL != str);
	
	if ('-' == str[0]) 						  		  /* skip over minus sign */
	{
		++str;
		is_neg = 1;
	}
	
	str_len = strlen(str);
	
	for (i = 0; i < str_len; ++i)
	{
		value *= 10; 							  /* Add place for next digit */
		value += ((int)str[i] - '0');						 /* Add int value */
	}
	
	if (is_neg)
	{
		value *= -1;						   /* change back to negative num */
	}
	
	return (value);
}

char *Itoa(int value, char *str, int base)
{
	int temp_value = value;
	size_t i = 0;
	int current_digit = 0;
	
	assert(NULL != str);
	
	if (0 == value) /* value is 0, just need to return 0 with null terminator */
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	
	 /* if value is a negative number, change it to pos for the time being */
	if (value < 0)
	{
		temp_value = -value;
	}	
	
	while (temp_value > 0)
	{
		current_digit = temp_value % base; 			/* find last digit of str */
		if(current_digit <= 9)
		{
			/* add it to the array as a char */
			str[i] = (char)current_digit + '0';
		}
		else
		{
			str[i] = (char)current_digit + '0' + 7; 	 /* for base above 10 */
		}
		temp_value /= base; 			 /* divide by base to find next digit */
		++i;
	}
	
	if (value < 0) 				  /* if value is negative, add the minus sign */
	{
		str[i] = '-';
		++i;
	}
	
	str[i] = '\0';								/* add null terminator to end */
	
	str = ReverseString(str, i); 						/* reverse the string */
	
	return (str);
	
}

int Atoi(const char *str, int base)
{

	int value = 0;
	size_t i = 0;
	int sign = 1;
	
	if ('-' == *(str + i)) /* if number is negative, start from next position */
	{
		++i;
		sign = -1;
	}
	
	while (
		   (*(str + i) >= '0' && *(str + i) <= '9') ||
		   (*(str + i) >= 'A' && *(str + i) <= 'Z') ||
		   (*(str + i) >= 'a' && *(str + i) <= 'z')
		  )
	{
		value *= base;
		
		if (*(str + i) <= '9')
		{
			value += *(str + i) - '0';
		}
		else if (*(str + i) <= 'Z')
		{
			value += *(str + i) - 'A' + 10;
		}
		else if (*(str + i) <= 'z')
		{
			value += *(str + i) - 'a' + 10;
		}
		
		++i;
	}
	
	return (value * sign);
}

void CharInFirst2(char *arr1, char *arr2, char *arr3)
{
	/* buffer with enough room for ASCII Characters */
	char buffer1[127] = {0};

	int num_of_letter = 0;
	int i = 0;
	
	while ('\0' != *arr1)
	{
		num_of_letter = (int)arr1[i];
		buffer1[num_of_letter] += 1;   /* array index of the int value is set */
		++arr1;
	}
	
	while ('\0' != *arr2)
	{
		num_of_letter = (int)arr2[i];
		buffer1[num_of_letter] += 1;   /* array index of the int value is set */
		++arr2;
	}
	
	while ('\0' != *arr3)
	{
		num_of_letter = (int)arr3[i];
		buffer1[num_of_letter] += 3;   /* array index of the int value is set */
		++arr3;
	}
	
	for (i = 0; i < 123 - 1; ++i)
	{
		/* character was found in both the first arrays but not the third */
		if (buffer1[i] == 2)
		{
			printf("%c\n", (char)i);
		}
	}
}

int IsLittleEndian()
{
	int n = 0x0001;
	char *check = (char *)&n;
	return (*check ? 1 : 0);
}
