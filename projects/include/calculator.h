#ifndef __OL73_CALCULATOR_H__
#define __OL73_CALCULATOR_H__

typedef enum {SUCCESS, MATH_ERROR, SYNTAX_ERROR, ALLOC_ERROR} status_t;

/**
 * @brief Function calculates the result of an expression in a string.
 * The correct syntax must follow most usual math syntax. Also the calculator
 *  will not accept the following:
 *  - opening parantheses '(' after a number (it will NOT be considered
 *      multiplication). For example 5(2+4) will not be accepted.
 *  - more than 2 simple operators (+, -) or 2 and more complex operators (*, /)
 *      in a row. For example 3+++3 or 3**7 will not be accepted.
 * - a closing parantheses ')' immediately after an opening parantheses '('.
 *      For example () will not be accepted.
 * @param expression ptr to expression.
 * @param result double ptr to the result of the equation.
 * @return status_t return value according to the above status_t enum.
 */
status_t Calculate(const char *expression, double *result);

#endif /* __OL73_CALCULATOR_H__ */
