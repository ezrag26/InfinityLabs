#include <stdio.h> /* fprintf */

#ifndef NDEBUG
#define PRNT_ERR(x) (fprintf(stderr, x"\n"))
#else
#define PRNT_ERR(x)
#endif /* NDEBUG */

#define ARR_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)

#define TEST(x, message) (x == 0 ? 0 : fprintf(stderr, "%s\n", message))

#define REQUIRE(ret, operator, exp, format1, format2) {\
		if (ret operator exp)\
		{\
			printf("\tFailed | %s | Line %d\n", __FILE__, __LINE__);\
			printf("\t\tExpected: " #format1 "\n", exp);\
			printf("\t\tReturned: " #format2 "\n", ret);\
			failures += (size_t)FAILURE;\
		}\
													  }

#define PRNT_STATUS(failures) (0 == failures ? \
				 puts("All tests passed.") : \
				 printf("%lu failure/s occurred\n", failures))

typedef enum {SUCCESS, FAILURE} ret_status_t;
