/*
Developer: Ezra Gordon
Reviewer: Yossi
Status: S
*/

#include <stdio.h>

size_t strlength(const char *s);

int main ()
{
	char *str = "Hello World";
	char *str2 = " ";
	char *str3 = "";
	char *str4 = "Ezra Gordon";
	char *str5 = NULL;

	printf("Length of %s is: %zu characters\n", str, strlength(str));
	printf("Length of %s is: %zu characters\n", str2, strlength(str2));
	printf("Length of %s is: %zu characters\n", str3, strlength(str3));
	printf("Length of %s is: %zu characters\n", str4, strlength(str4));
	printf("Length of %s is: %zu characters\n", str5, strlength(str5));

	printf("Result: %d\n", strcompare(str, str2));
	return 0;
}

size_t strlength(const char *s)
{
	if (NULL == s)
	{
		printf("Error: Invalid memory address");
		return 0;
	}
	
	size_t len = 0;
	
	while ('\0' != *s) 											/* Haven't reached terminating value */
	{
		++len;
		++s;
	}
	return len;
}
