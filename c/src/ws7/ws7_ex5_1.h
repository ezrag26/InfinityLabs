#ifndef __OL73_WS2_STRING_H__
#define __OL73_WS2_STRING_H__

#include <stddef.h> /* size_t */

size_t StrLen(const char *s);
int StrCmp (const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrNCpy(char *dest, const char *src, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *s, int c);
char *StrDup(const char *s);
char *StrCat(char *dest, const char *src);
char *StrNCat(char *dest, const char *src, size_t n);
char *StrStr(const char *haystack, const char *needle);
size_t StrSpn(const char *str1, const char *str2);

#endif /* __OL73_WS2_STRING_H__ */
