/*
*Developer: Ezra Gordon
*Reviewer: Liron Tzemach
*Status: A
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* system */

#define ESC 27

int Lut();
void Press(char ch);
void Nothing(char ch);

int main()
{

	Lut();

	return (0);
}

int Lut()
{
	int i = 0;
	void (*total_chars[256])(char); 			  /* create array of pointers */
	char ch = '\0';

	/* stop terminal buffering, and stop echoing keyboard */
	int system_ret = system("stty -icanon -echo");

	/* assign each element the pointer to its function */
	for (i = 0; i < 256; ++i)
	{
		if (i != 'A' && i != 'T')
		{
			total_chars[i] = Nothing;
		}
		else
		{
			total_chars[i] = Press;
		}
	}

	/* if system failed, let user know */
	if (system_ret == -1)
	{
		printf("System failed");
	}

	/* as long as ESC hasn't been pressed, perform the function at the arrays
																		index */
	while (ESC != ch)
	{
		ch = getchar();
		total_chars[(int)ch](ch);
	}

	/* return terminal to default state */
	system_ret = system("stty icanon echo");

	/* if system failed, let user know */
	if (system_ret == -1)
	{
		printf("System failed");
	}

	return (0);
}

/* Prints which key was pressed */
void Press(char ch)
{

	if ('A' == ch || 'T' == ch)
	{
		printf("%c pressed\n", ch);
	}

}

/* A function that does nothing */
void Nothing(char ch)
{
	(void)(ch);
}
