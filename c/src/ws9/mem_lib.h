#ifndef __MEM_LIB_H__
#define __MEM_LIB_H__

#include <limits.h>

#define BYTES_IN_WORD ((__WORDSIZE ) / (__CHAR_BIT__))

typedef struct
{
	char word[BYTES_IN_WORD];
} word_size_t;

void *Memset(void *s, int c, size_t n);

void *Memcpy(void *dest, const void *src, size_t n);

void *Memcpy2(void *dest, const void *src, size_t n);

void *Memmove(void *dest, const void *src, size_t n);

void *Memcpy3(void *dest, const void *src, size_t n);

#endif /* __MEM_LIB_H__ */
