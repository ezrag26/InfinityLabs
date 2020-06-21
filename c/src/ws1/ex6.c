#include <stdio.h> /* printf */

int swap(int *num1, int *num2);

int main()
{
	int num1 = 3;
    int num2 = 8;

    printf("First:\nnum1 = %d\nnum2 = %d\n", num1, num2);

    swap(&num1, &num2);

    printf("Now:\nnum1 = %d\nnum2 = %d\n", num1, num2);
    
	return 0;
}

/* Swaps the numbers of two variables */
int swap(int *num1, int *num2)
{
    int tmp = *num1; /* Store first number in tmp so that it can overwritten" */
    *num1 = *num2;
    *num2 = tmp;

    return 0;
}
