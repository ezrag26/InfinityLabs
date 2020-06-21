#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "fibonacci.h"

#include "utils.h"
#include "tests.h"

int TestFibonacciInterval();
int TestFibonacciRecursive();

int main()
{
    size_t failures = 0;

    puts("Testing Fibonacci...");
    TEST(TestFibonacciInterval(), "TestFibonacciInterval");
    TEST(TestFibonacciRecursive(), "TestFibonacciRecursive");

    PRNT_STATUS(failures);
    return (failures);
}

int TestFibonacciInterval()
{
    size_t i = 0;
    size_t failures = 0;
    unsigned int exp_result[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144,
                                 233, 377, 610, 987, 1597, 2584, 4181, 6765,
                                 10946, 17711, 28657, 46368, 75025, 121393,
                                 196418, 317811};
    unsigned int returned = 0;

    for (i = 0; i < ARR_SIZE(exp_result); ++i)
    {
        returned = IterFibonacci(i);
        REQUIRE(returned, !=, exp_result[i], %d, %d);
    }

    return failures;
}

int TestFibonacciRecursive()
{
    size_t i = 0;
    size_t failures = 0;
    unsigned int exp_result[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144,
                                 233, 377, 610, 987, 1597, 2584, 4181, 6765,
                                 10946, 17711, 28657, 46368, 75025, 121393,
                                 196418, 317811};
    unsigned int returned = 0;

    for (i = 0; i < ARR_SIZE(exp_result); ++i)
    {
        returned = RecFibonacci(i);
        REQUIRE(returned, !=, exp_result[i], %d, %d);
    }

    return failures;
}
