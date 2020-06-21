#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "calculator.h"
#include "utils.h"
#include "tests.h"

int TestCalculator();

int main()
{
    size_t failures = 0;

    puts("Testing Calculator...");
    TEST(TestCalculator(), "TestCalculator");

    PRNT_STATUS(failures);

    return (failures);
}

int TestCalculator()
{
    size_t failures = 0;
    size_t i = 0;
    double result = 0;
    status_t status = SUCCESS;

    char *str[] = {
                               "7+8",
                               "8+8*3+-2^5",
                               "8+8*3+-2^",
                               "2/0",
                               "8++8*((3-2)*5)",
                               "3-2)*5",
                               "(3-2)*5+ 5*(4+4+4"
                  };

    double exp_result[] = {
                               15,
                               0,
                               0,
                               0,
                               48,
                               0,
                               0
                          };

    status_t exp_status[] = {
                               SUCCESS,
                               SUCCESS,
                               SYNTAX_ERROR,
                               MATH_ERROR,
                               SUCCESS,
                               SYNTAX_ERROR,
                               SYNTAX_ERROR
                            };


    for (i = 0; i < ARR_SIZE(str); ++i)
    {
        status = Calculate(str[i], &result);
        REQUIRE(result, !=, exp_result[i], %f, %f);
        REQUIRE(status, !=, exp_status[i], %d, %d);

    }

    return (failures);
}
