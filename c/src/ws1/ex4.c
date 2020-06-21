#include <stdio.h> /* printf */

double TenToPower(int exp);

int main (void)
{
    int exp1 = 3, exp2 = 0, exp3 = -2;
    
    printf("10^%d = %f\n", exp1, TenToPower(exp1));
    printf("10^%d = %f\n", exp2, TenToPower(exp2));
    printf("10^%d = %f\n", exp3, TenToPower(exp3));
    
	return 0;
}

/* Calculate 10^exp */
/* exp can range from -6 to 22 */
double TenToPower(int exp)
{
	double base = 10;
    double result = 1;
	int i = 0;

    if (exp < 0)
    {
        base = 1/base;
        exp = -exp;
    }

    for (i = 0; i < exp; i++)
    {
        result = result * base;
    }

    return result;
}
