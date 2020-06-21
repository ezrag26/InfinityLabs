#include <assert.h>
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */
#include <stdlib.h> /* malloc */
#include "ws7_ex5_1.h"


int StrCaseCmp(const char *s1, const char *s2)
{
	assert(NULL != s1);
	assert(NULL != s2);

	/* Compare until end of string by lowercase value */
	while ((tolower(*s1) == tolower(*s2)) && '\0' != *s1)
	{
		++s1;
		++s2;
	}

	return (tolower(*s1) - tolower(*s2));
}

char *StrChr(const char *s, int c)
{
	char character = (char)c;

	assert(NULL != s);

	while (*s != character && '\0' != *s)
	{
		++s;
	}

	if (*s == character)
	{
		return ((char*)s);
	}
	else
	{
		return (NULL);
	}
}

