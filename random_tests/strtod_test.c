#include <stdio.h>  /* printf */
#include <stdlib.h> /* strtod */

int main()
{
    const char *expression1 = ".123$456#789";
    const char **ptr1 = &expression1;
    const char *expression2 = "++123$456#789";
    const char **ptr2 = &expression2;
    const char *expression3 = "0!123$456#789";
    const char **ptr3 = &expression3;
    double x =  0;

    printf("Stats w/ num not 0:\n\tExpression: %s\n", expression1);
    x = strtod(expression1, (char **)ptr1);
    printf("\tReturned: %lf\n", x);
    printf("\tPoints to: %s\n", *ptr1);

    printf("\n");

    printf("Starts w/ non-num:\n\tExpression: %s\n", expression2);
    x = strtod(expression2, (char **)ptr2);
    printf("\tReturned: %lf\n", x);
    printf("\tPoints to: %s\n", *ptr2);

    printf("\n");

    printf("Start w/ 0:\n\tExpression: %s\n", expression3);
    x = strtod(expression3, (char **)ptr3);
    printf("\tReturned: %lf\n", x);
    printf("\tPoints to: %s\n", *ptr3);

    return (0);
}
