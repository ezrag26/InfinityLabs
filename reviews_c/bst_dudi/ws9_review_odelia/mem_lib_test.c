#include <stdio.h>

#include "mem_lib.h"


int main()
{
	int i = 0;
	size_t j = 0;
	char str[50] = "123456789012345678901234567890";
	char str1[50] = "123456789012345678901234567890";
	
	
	printf("%s\n", str);
	printf("%s\n", str1);
	
	/*Memcpy(str, &str[2], 11);*/
	
	/*Memset(str, 'b', 8);*/
	memmove(&(str1[7]),str1,12);
	Memmove(&(str[7]),str, 12);
	
	if(0 == strcmp(str,str1))
	{
		printf("ok\n");
	}
	/*Memmove(&(str[8]), str, 12);*/
	
	printf("%s\n", str);
	printf("%s\n", str1);
	
	
	
	return 0;
}
