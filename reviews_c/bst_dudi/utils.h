#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>


#define PRINT_ERR(x) fprintf(stderr,"%s || line %d\n",x,__LINE__);
#ifndef NDBUG
#define PRINT_DBUG fprintf(stderr, "error in alocating memory for main struct");
#else 
#define PRINT_DBUG
#endif

#define CHECK(x) if (x){ return 1;}

#define ERROR_IF_NOT_EQUAL(x, y, s) \
if (x != y)\
{\
	PRINT_ERR(s);\
	return 1;\
}\

#define MAX2(a,b) (a > b ? a : b)
#define MAX3(a,b,c) (c > MAX2(a,b) ? c : MAX2(a,b))
#define UNUSED(x) ((void	)(x))
#endif	/*	__UTILS_H__ */

