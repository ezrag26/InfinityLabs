#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "rec_string.h" /* definitions */

size_t RecStrLen(const char *s)
{
    assert(NULL != s);

    return (('\0' == *s) ? 0 : (1 + RecStrLen(s + 1)));
}

int RecStrCmp(const char *s1, const char *s2)
{
    assert(NULL != s1);
    assert(NULL != s2);

    if (*s1 != *s2 || '\0' == *s1)
    {
        return (*s1 - *s2);
    }

    return (RecStrCmp((s1 + 1), (s2 + 1)));
}

char *RecStrCpy(char *dest, const char *src)
{
    char ch = '\0';

    assert(NULL != dest);
    assert(NULL != src);

    ch = *src;
    *dest = ch;

    if ('\0' == ch)
    {
        return (dest);
    }

    return (RecStrCpy((dest + 1), (src + 1)) - 1);
}

char *RecStrCat(char *dest, const char *src)
{
    size_t dest_length = 0;

    assert(NULL != dest);
    assert(NULL != src);

    dest_length = RecStrLen(dest);

    return (RecStrCpy((dest + dest_length), src) - dest_length);
}

static int RecStrNCmp(const char *s1, const char *s2, size_t n)
{
    assert(NULL != s1);
    assert(NULL != s2);

    if (0 == n || *s1 != *s2 || '\0' == *s1)
    {
        return (*s1 - *s2);
    }

    return (RecStrNCmp((s1 + 1), (s2 + 1), (n - 1)));
}
/*
static char *RecStrChr(const char *s, int c)
{
    assert (NULL != s);

    if ('\0' == *s)
    {
        return (NULL);
    }

    if (c == *s)
    {
        return ((char *)s);
    }

    return (RecStrChr((s + 1), c));
}
*/
static char *FindStartOfString(const char *haystack, const char *needle, size_t needle_length)
{
    /* reached end */
    if ('\0' == *haystack)
    {
        return (NULL);
    }

    /* needle wasn't found in haystack */
    if ((0 == RecStrNCmp(haystack, needle, needle_length - 1)))
    {
        return ((char *)haystack);
    }

    return (RecStrStr(haystack + 1, needle));
}

char *RecStrStr(const char *haystack, const char *needle)
{
    size_t needle_length = 0;

    assert(NULL != haystack);
    assert(NULL != needle);

    needle_length = RecStrLen(needle);

    /* if needle is empty, return beginning of haystack */
    if (0 == needle_length)
    {
        return ((char *)haystack);
    }

    return (FindStartOfString(haystack, needle, needle_length));
}
