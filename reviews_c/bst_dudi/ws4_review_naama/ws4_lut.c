#include <stdio.h> /*printf*/
#include <stdlib.h>/*system*/
#define ESC 27

int EmptyFunc (char c)
{
	return (c);
}

int PrintT(char c)
{
	printf("%c is pressed\n", c);	
	return (c);
}

int PrintA(char c)
{
	printf("%c is pressed\n", c);
	return (c);	
}

int PressESC(char c)
{
	return (c);
}

int main ()
{
	int c = '\0';
	int x = 0;
	int i = 0;
	int (*ptr[256]) (char);

	for (;i < 256; ++i)
	{
		ptr[i] = EmptyFunc;
	}
	
	ptr['A'] = PrintA;
	ptr['T'] = PrintT;
	ptr[ESC] = PressESC;
	
	
	system("stty -icanon -echo"); /*stop terminal buffering*/
	
	while (ESC != x)
	{
		c = getchar();
		x = (*ptr[c])((char)c); 
	}
	
	system("stty icanon echo"); /*resume terminal buffering*/
	
	return 0;
}
