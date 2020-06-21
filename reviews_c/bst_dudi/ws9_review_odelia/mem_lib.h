#ifndef __MEM_LIB_H__
#define __MEM_LIB_H__

#define BITS_IN_BYTE 8
#define SIZE_OF_WORD 8

/* set n times the char represented by an integer to ptr location */
void *Memset(void *str, int c, size_t n);

/* copy n bytes from src (str2) to dest(str1) (dont treat overlap) */
void *Memcpy(void *str1, const void *str2,size_t n);

/* move n bytes from src to dest - treat overlap */
void *Memmove(void *str1, const void *str2,size_t n);

#endif /* __MEM_LIB_H__ */
