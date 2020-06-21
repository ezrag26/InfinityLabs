/*
 * Developer: Yossi
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <limits.h>
#include <stdio.h>

/*
 *Errors and tests
 */
#ifndef NDEBUG
#define DEBUG_PRINT_ERROR(err) fprintf(stderr, err);
#else
#define DEBUG_PRINT_ERROR(err) ()
#endif

#define TEST(test, error) {\
	if(0 != test()) {\
	--errors; \
	fputs(error, stderr); }\
}
/* End of errors and tests */

#define UNUSED(x) (void)(x)

#define ARR_SIZE(arr) ( sizeof(arr) / sizeof(arr[0]) )

#define MIN2(a, b) ( ((a) < (b)) ? (a) : (b) )
#define MAX2(a, b) ( ((a) > (b)) ? (a) : (b) )
#define MIN3(a, b, c) ( MIN2(MIN2(a, b), c) )
#define MAX3(a, b, c) ( MAX2(MAX2(a, b), c) )
/*
#define CHAR_IN_WORD ( ( __WORDSIZE ) / ( CHAR_BIT ) )
typedef union
{
	char arr[CHAR_IN_WORD];
} word_t;
*/

#endif	/*	__UTILS_H__ */
