/*******************************************************************************
*																			   *
*	RecString																   *
*	Developer: Naama Amir												   	   *
*	Reviwer: 																   *
*																			   *
*******************************************************************************/

#include <stddef.h> 		/*		size_t	 */
#include <assert.h> 		/*		assert	 */

size_t RecStrLen(const char *str)
{	
	assert(str);

	if ('\0' == *str)
	{
		return 0;
	}
	
	++str;
	
	return (1 + RecStrLen(str));
}

int RecStrCmp (const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);
	
	if ((*str1 != *str2) || ('\0' == *str2))
	{
		return (*str1 - *str2);
	}
	
	++str1; ++str2;
	
	return (RecStrCmp(str1, str2));
}

char *RecStrCpy(char *str_dest, const char *str_src)
{
	assert(str_dest);
	assert(str_src);

	*str_dest = *str_src;
	
	if ('\0' == *str_src)
	{
		return str_dest;
	}

	return (RecStrCpy(str_dest + 1, str_src + 1) - 1);
}

char *RecStrCat(char *str_dest, const char *str_src)
{
	assert(str_dest);
	assert(str_src);

	RecStrCpy(str_dest + RecStrLen(str_dest), str_src);

	return(str_dest);
}

static int RecStrNCmp(const char *str1, const char *str2, size_t n)
{
	assert(str1);
	assert(str2);
	
	if ((*str1 != *str2) || ('\0' == *str2) || (1 == n))
	{
		return (*str1 - *str2);
	}
	
	++str1; ++str2;
	
	return (RecStrNCmp(str1, str2, n - 1));
}

static char *RecStrChr(const char *str1, int c)
{
	assert(str1);
	
	if (*str1 == c)
	{
		return ((char *)str1);
	}
	if ('\0' == *str1)
	{
		return NULL;
	}

	return (RecStrChr(str1 + 1, c));
}

static char *RecStrStrResult(const char *haystack, const char *needle, size_t size)
{
	assert(haystack);
	assert(needle);

	if (NULL == RecStrChr(haystack, *needle))
	{
		return NULL;
	}

	if (0 == RecStrNCmp(haystack, needle, size))
	{
		return (char *)haystack;
	}

	return(RecStrStrResult(haystack + 1, needle, size));
}

char *RecStrStr(const char *haystack, const char *needle)
{
	size_t size = 0;
	
	assert(haystack);
	assert(needle);

	size =  RecStrLen(needle);

	if (0 == size)
	{
		return ((char *)haystack);
	}

	return (RecStrStrResult(haystack, needle, size));

	
}


