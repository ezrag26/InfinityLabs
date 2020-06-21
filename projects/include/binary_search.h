#ifndef __OL73_BINARY_SEARCH_H__
#define __OL73_BINARY_SEARCH_H__

#include <stddef.h> /* size_t */

void *BinarySearch(const void *key, const void *base,
                     size_t nmemb, size_t size,
                     int (*cmp)(const void *, const void *));

void *RecBinarySearch(const void *key, const void *base,
                     size_t elems, size_t size,
                     int (*cmp)(const void *, const void *));

#endif /* __OL73_BINARY_SEARCH_H__ */
