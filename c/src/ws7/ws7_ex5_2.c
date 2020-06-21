#include <assert.h>
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */
#include <stdlib.h> /* malloc */
#include "ws7_ex5_1.h"


char *StrNCpy(char *dest, const char *src, size_t n)
{
	char *start = dest;
	int counter = (int)n;

	assert(NULL != dest);
	assert(NULL != src);

	/* Start copying */
	/* Counter hasn't ended and not at end of string */
	while (counter > 0 && ('\0' != *src))
	{
		*dest = *src;
		++src;
		++dest;
		--counter;
	}

	/* If string has ended but counter hasn't, add terminating null */
	while (0 < counter)
	{
		*dest = '\0';
		++dest;
		--counter;
	}

	return (start);
}

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
