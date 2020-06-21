#include <stdlib.h>/*system*/
#include <stdio.h> /*printf*/
#define ESC 27

/*function prints A or T if it was recieved from stdin */
/*The function will run until "ESC" will be pressed*/
int main ()
{
	char c = '\0';
	
	system("stty -icanon -echo"); /*stop terminal buffering*/

	
	while (ESC != c) /*while ESC wasn't pressed*/
	{
		c = getchar(); /*stdin*/
				
		switch (c)
		{
			case 'A':
				printf("%c is pressed\n", c);
				break;
			case 'T':
				printf("%c is pressed\n", c);
				break;
		}
	}
system("stty icanon echo"); /*resume terminal buffering*/

return 0;
}

