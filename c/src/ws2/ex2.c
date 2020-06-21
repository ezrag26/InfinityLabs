/*
Developer: Ezra Gordon
Reviewer: Yossi
Status: S
*/

#include <stdio.h>

int StrCmp (const char *s1, const char *s2);

int main ()
{
	char *str = "Hello World";
	char *str2 = " ";
	char *str3 = "";
	char *str4 = "Ezra Gordon";
	char *str5 = NULL;
	char *str6 = "Hello World";

	printf("Result: %d\n", StrCmp(str, str6));
	printf("Result: %d\n", StrCmp(str2, str));
	printf("Result: %d\n", StrCmp(str3, str5));
	printf("Result: %d\n", StrCmp(str4, str6));
	printf("Result: %d\n", StrCmp(str5, str2));

	return 0;
}


int StrCmp (const char *s1, const char *s2)
{
	if (NULL == s1 || NULL == s2)
	{
		printf("Error: Invalid memory address");
		return 0;
	}

	int result = 0;

	while (0 == result)
	{
			if (*s1 != *s2)
			{
				return *s1 - *s2;
			}
			
			++s1;
			++s2;

			if ('\0' == *s1 && '\0' == *s2){return result;} 	/* Reached end of both strings and therefore match*/
	}
}
