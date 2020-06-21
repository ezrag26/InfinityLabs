#include <stdio.h>
#include "g.h"

int Foo();
int main()
{
	printf("%d\n", g_s);
	Foo();
	printf("%d\n", g_s);
	
	return 0;
}
