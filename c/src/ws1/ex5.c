#include <stdio.h> /* printf */

int flips(int num);

int main (void)
{
    int num = -1460, num2 = 1460, num3 = 12345, num4 = 0123;
    
	printf("%d\n", flips(num));
    printf("%d\n", flips(num2));
    printf("%d\n", flips(num3));
    printf("%d\n", flips(num4));
    
	return 0;
}

int flips(int num)
{
	int result = 0;
    int is_pos = 1;

    if (num < 0)
    {
        is_pos = -1;
    	num = -num;
    }

    while (num > 0)
    {
    	result *= 10;           /* Move decimal right place to right */
    	result += num % 10;     /* Add remainder from 10 / num */
    	num /= 10;              /* Remove last digit from num */
    }

  	return is_pos * result;   /* Place correct sign based on original input */
}
