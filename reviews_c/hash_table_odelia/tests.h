#ifndef __TESTS_H__
#define __TESTS_H__
#include <time.h>

#define RED		31
#define GREEN	32
#define	WHITE	37

/* Pradeep Padala */
void textcolor(int attr, int fg, int bg)
{
	char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg, bg);
	printf("%s", command);
}

/*
#define TEST(x, func_name) {\
							char *status = "passed.";\
							printf("\tTesting %s... ", func_name);\
							textcolor(1, GREEN, 3);\
							if(0 != x) {\
							status = "failed. Error in "#func_name;\
							textcolor(1, RED, 3); }\
							fprintf(stderr, "%s\n", status);\
							textcolor(0, WHITE, 0); \
						   }
*/

#define TEST(x, func_name) {printf("\tTesting %s... ", func_name);\
						 	if (x == 0) { puts("passed."); }\
							else { fprintf(stderr, "Error in %s\n", func_name); }\
						   }

#define REQUIRE(ret, operator, exp, format1, format2) {\
		if (ret operator exp)\
		{\
			printf("failed.\n\t\t%s line %d\n", __FILE__, __LINE__);\
			printf("\t\tExpected: " #format1 "\n", exp);\
			printf("\t\tReturned: " #format2 "\n", ret);\
			failures += 1;\
		}\
													  }

#define PRNT_STATUS(failures) (0 == failures ? \
				 puts("All tests passed.") : \
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

#endif /* __TESTS_H__ */
