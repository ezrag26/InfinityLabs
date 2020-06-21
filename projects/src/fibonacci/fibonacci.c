/*******************************************************************************
 * Date: 		22/10/2019
 * Developer:	Ezra Gordon
 * Reviewer:
 * Satus: 		S
 ******************************************************************************/

#include <stddef.h> /* size_t */

#include "fibonacci.h"

#include "utils.h"

/*unsigned int FibonacciInterval(unsigned int num)
{
    size_t i = 0;
    unsigned int current = 0;
    unsigned int prev = 1;
    unsigned int result = 0;

    for (i = 0; i < num; ++i)
    {
        current = prev;
        prev = result;
        result = prev + current;
    }

    return (result);
}*/

unsigned int FibonacciInterval(unsigned int num)
{
    size_t i = 0;
    unsigned int num2 = 0;
    unsigned int num1 = 1;

    for (i = 0; i < num; ++i)
    {
        num2 = num1 + num2;
        num1 = num2 - num1;
    }

    return (num2);
}

unsigned int FibonacciRecursive(unsigned int num)
{
    return ((num < 2) ? num : FibonacciRecursive(num - 2) + FibonacciRecursive(num - 1));
}
