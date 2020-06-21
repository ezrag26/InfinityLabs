#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h> /* fprintf */

#ifndef NDEBUG
#define PRNT_ERR(x) (fprintf(stderr, x"\n"))
#else
#define PRNT_ERR(x)
#endif /* NDEBUG */

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

#define FLIP_SIGN(x) (-x)
#define ABS(x) (x < 0 ? FLIP_SIGN(x) : x)

#endif /* __UTILS_H__ */
