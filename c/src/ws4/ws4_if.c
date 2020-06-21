/*
*Developer: Ezra Gordon
*Reviewer: Liron Tzemach
*Status: A
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* getchar() */

void If();

int main()
{
	If();
	return (0);
}

void If()
{
	char ch = '\0';

	/* stop terminal buffering, and stop echoing keyboard */
	int system_ret = system("stty -icanon -echo");

	/* if system failed, let user know */
	if (system_ret == -1)
	{
		printf("System failed");
	}

	/* as long as ESC hasn't been pressed, if the target letters have been
	pressed, type which one was pressed */
	while (27 != ch) /* exit */
	{
		ch = getchar();
		if('A' == ch || 'T' == ch)
		{
			printf("%c pressed\n", ch);
		}
	}

	/* return terminal to default state */
	system_ret = system("stty icanon echo");

	/* if system failed, let user know */
	if (system_ret == -1)
	{
		printf("System failed");
	}
}
