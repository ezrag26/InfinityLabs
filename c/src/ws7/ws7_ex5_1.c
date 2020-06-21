#include <assert.h>
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */
#include <stdlib.h> /* malloc */
#include "ws7_ex5_1.h"

size_t StrLen(const char *s)
{
	const char *base = s;

	assert(NULL != s);				/* Check for invalid memory address"   */

	/* Calculate string length */
	while ('\0' != *s) 				/* Haven't reached terminating value   */
	{
		++s;
	}
	return (s - base);
}

int StrCmp (const char *s1, const char *s2)
{
	assert(NULL != s1);				/* Check for invalid memory address" */
	assert(NULL != s2);				/* Check for invalid memory address" */

	/* Still the same and haven't reach string's end */
	while ((*s1 == *s2) && '\0' != *s1)
	{
		++s1;
		++s2;
	}

	return (*s1 - *s2);
}

char *StrCpy(char *dest, const char *src)
{
	char *start = dest;

	assert(NULL != dest);
	assert(NULL != src);

	while ('\0' != *src) 			/* Not at end of string */
	{
		*dest = *src;
		++src;
		++dest;
	}

	*dest = '\0'; 					/* add terminating null */

	return (start);
}
