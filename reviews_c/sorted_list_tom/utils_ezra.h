#include <stdio.h> /* fprintf */

#ifndef NDEBUG
#define PRNT_ERR(x) (fprintf(stderr, x"\n"))
#else
#define PRNT_ERR(x)
#endif /* NDEBUG */

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

#define TEST(x) (failures = x)

#define PRNT_STATUS(failures) (0 == failures ? \
							   puts("All tests passed.") : \
							   printf("%lu failures occurred\n", failures))
