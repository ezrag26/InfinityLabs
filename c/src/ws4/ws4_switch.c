/*
*Developer: Ezra Gordon
*Reviewer: Liron Tzemach
*Status: A
*/

#include <stdio.h> /* printf */
#include <stdlib.h> /* getchar() */

int Switch();

int main()
{

	Switch();
	return (0);
}

int Switch()
{
	char ch = '\0';

	/* stop terminal buffering, and stop echoing keyboard */
	int system_ret = system("stty -icanon -echo");

	/* if system failed, let user know */
	if (-1 == system_ret)
	{
		printf("System failed");
	}

	/* as long as ESC hasn't been pressed, if the target letters have been
	pressed, type which one was pressed */
	while (27 != ch)
	{
		ch = getchar();
		switch (ch)
		{
			case 'A':
				printf("A pressed\n");
				break;
			case 'T':
				printf("T pressed\n");
				break;
		}
	}

	/* return terminal to default state */
	system_ret = system("stty icanon echo");

	/* if system failed, let user know */
	if (-1 == system_ret)
	{
		printf("System failed");
	}

	return (0);
}
