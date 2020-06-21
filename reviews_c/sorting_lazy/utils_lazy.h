#ifndef __UTILS_H__
#define __UTILS_H__

#include "stdio.h"

#define MAX2(a, b)		((a > b) ? a : b)
#define MAX3(a, b, c)	(MAX2(MAX2(a, b), c))
#define MIN2(a, b)		((a < b) ? a : b)
#define MIN3(a, b, c)	(MIN2(MIN2(a, b), c))

#define UNUSED(x)		(void)(x)

#define ARRSIZE(x)		(sizeof(x)/sizeof(*x))

#ifndef NDEBUG
#define DBG_PRT(x)		(fputs(x"\n", stderr))

#else
#define DBG_PRT(x) 

#endif


#endif						/* __UTILS_H__ */
