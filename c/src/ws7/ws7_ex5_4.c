#include <assert.h>
#include <string.h> /* strlen */
#include <ctype.h> /* tolower */
#include <stdlib.h> /* malloc */
#include "ws7_ex5_1.h"

char *StrDup(const char *s)
{
	char *dest = NULL;

	assert(NULL != s);

	dest = (char*) malloc(StrLen(s) * sizeof(char));

	if (NULL == dest) /* If not enough memory is available */
	{
		return (NULL);
	}

	return (StrCpy(dest, s));
}

char *StrCat(char *dest, const char *src)
{
	char *cat_pos = NULL;

	assert(NULL != dest);
	assert(NULL != src);

	cat_pos = dest + StrLen(dest);

	while ('\0' != *src)
	{
		*cat_pos = *src;
		++src;
		++cat_pos;
	}

	*cat_pos = '\0'; /* add terminator */

	return (dest);
}

char *StrNCat(char *dest, const char *src, size_t n)
{
	char *cat_pos = NULL;

	assert(NULL != dest);
	assert(NULL != src);

	cat_pos = dest + StrLen(dest);

	while ('\0' != *src && n > 0)
	{
		*cat_pos = *src;
		++cat_pos;
		++src;
		--n;
	}

	*cat_pos = '\0';

	return (dest);

}

char *StrStr(const char *haystack, const char *needle)
{
	const char* start_needle = NULL;
	const char* orig_needle = NULL;

	assert(NULL != haystack);
	assert(NULL != needle);

	start_needle = haystack;
	orig_needle = needle;

	while ('\0' != *needle && '\0' != *haystack) /* Neither string has ended */
	{
		if (*needle == *haystack) /* characters match */
		{
			++needle;
			++haystack;
		}
		else
		{
			needle = orig_needle;	  /* Go back to first character of needle */
			++start_needle;			  /* New possible match will start where
									   					       haystack ended */
			haystack = start_needle;
		}
	}

	if ('\0' == *needle)
	{
		return ((char *)start_needle);
	}

	return (NULL);
}

size_t StrSpn(const char *str1, const char *str2)
{
	const char *str1_start = str1;
	const char *str2_start = str2;
	size_t matching_chars = 0;
	size_t current_matching = 0;

	/* check if pointer exists */
	assert(NULL != str1);
	assert(NULL != str2);

	while ('\0' != *str2 && '\0' != *str1)/* While both strings haven't ended */
	{
		if (*str1 == *str2) /* characters match */
		{
			++current_matching;
			++str1;
			++str2;
		}
		else
		{
			current_matching = 0; /* zero current matching characters */
			str1 = str1_start;
			++str2_start; /* start from next str2 character */
			str2 = str2_start;
		}

		if (matching_chars < current_matching)
		{
			matching_chars = current_matching;
		}
	}

	return (matching_chars);
}
