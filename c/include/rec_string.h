#ifndef __OL73_rec_string_h__
#define __OL73_rec_string_h__

#include <stddef.h>  /* for size_t definition */

/* strings must end with a termination null byte. (undefined behavior if not) */
/**
 * @brief calculate the length of a string
 *
 * @param s ptr to the string
 * @return size_t the number of characters in the string
 * @time_complexity O(n)
 * @space_complexity O(n)
 */
size_t RecStrLen(const char *s);

/**
 * @brief compare two strings

 * @param s1 first string for comparison
 * @param s2 second string for comparison
 * @return int less than, equal to, or greater than zero if  s1  is  found,
       respectively, to be less than, to match, or be greater than s2
 * @time_complexity O(n), n is shorter of s1/s2
 * @space_complexity O(n), n is shorter of s1/s2
 */
int RecStrCmp(const char *s1, const char *s2);

/**
 * @brief copy a string
 * The function copies from src until and including the null character and into
 *  dest starting at the first character.
 * @param dest ptr to a destination string that must be big enough to contain
 *  src, or else undefined behavior will occur.
 * @param src ptr to a source string to copy from.
 * @return char* ptr to the beginning of the changed dest.
 * @time_complexity O(n)
 * @space_complexity O(n)
 */
char *RecStrCpy(char *dest, const char *src);

/**
 * @brief concatenate two strings.
 * The function copies all characters from src including the null
 *  character, into the end of dest (replacing its null character).
 * @param dest ptr to string that is large enough to hold both its own length
 *  and src.
 * @param src ptr to a source string to concatenate from.
 * @return char* ptr to the beginning of dest.
 * @time_complexity O(n+m)
 * @space_complexity O(n) n is longer of dest/src
 */
char *RecStrCat(char *dest, const char *src);

/**
 * @brief locate a substring
 * Function finds the first appearance of needle string haystack string.
 * @param haystack ptr to a string to search in
 * @param needle ptr to sub-string to search for
 * @return char* ptr to the first char of the first appearance of
 *  needle in haystack, or NULL if no such appearance was found.
 * @time_complexity O(n*m)
 * @space_complexity O(n+m)
 */
char *RecStrStr(const char *haystack, const char *needle);


#endif /* __OL73_rec_string_h__ */
