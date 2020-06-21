#include <time.h>

#define TEST(x, func_name) {printf("Testing %s...\n", func_name);\
						 	x == 0 ? 0 : fprintf(stderr, "Error in %s\n", func_name);\
						   }

#define REQUIRE(ret, operator, exp, format1, format2) {\
		if (ret operator exp)\
		{\
			printf("\tFailed | %s | Line %d\n", __FILE__, __LINE__);\
			printf("\t\tExpected: " #format1 "\n", exp);\
			printf("\t\tReturned: " #format2 "\n", ret);\
			failures += 1;\
		}\
													  }

#define PRNT_STATUS(failures) (0 == failures ? \
				 puts("\tAll tests passed.") : \
				 printf("%lu failure/s occurred\n", failures))
/*
#define CLOCK_VARS {clock_t begin = 0;\
					clock_t end = 0;\
					double time_spent = 0;\
                   }

#define BEGIN_CLOCK(begin) {begin = clock();\
                           }

#define STOP_CLOCK(begin, end, time_spent) {end = clock();\
					time_spent = (double)(end - begin) / CLOCKS_PER_SEC;\
					printf("%lf\n", time_spent);\
                                           }
*/
/* typedef enum {SUCCESS, FAILURE} ret_status_t; */
