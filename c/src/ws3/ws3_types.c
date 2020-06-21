/*
*Developer: Ezra Gordon
*Reviewer: Tom Goldberg
*Status: A
*/

#include <stdio.h> /* printf */

/* Program that prints to stdout the sizes of the data_types */

int main ()
{
    char *types[] = {"int", "unsigned int", "short int", "unsigned short int",
                          "long int", "unsigned long int",
                          "float", "double", "long double", "char",
                          "unsigned char"};

    /*int size = sizeof(types)/sizeof(char *);
    int i = 0;

   	for (i = 0; i < size ; ++i)
    {
        printf("%s: %lu (bytes)\n", types[i], sizeof(types[i]));
    }*/

    printf("%s: %lu (bytes)\n", types[0], sizeof(int));
    printf("%s: %lu (bytes)\n", types[1], sizeof(unsigned long));
    printf("%s: %lu (bytes)\n", types[2], sizeof(short int));
    printf("%s: %lu (bytes)\n", types[3], sizeof(unsigned short int));
    printf("%s: %lu (bytes)\n", types[4], sizeof(long int));
    printf("%s: %lu (bytes)\n", types[5], sizeof(unsigned long int));
    printf("%s: %lu (bytes)\n", types[6], sizeof(float));
    printf("%s: %lu (bytes)\n", types[7], sizeof(double));
    printf("%s: %lu (bytes)\n", types[8], sizeof(long double));
    printf("%s: %lu (bytes)\n", types[9], sizeof(char));
    printf("%s: %lu (bytes)\n", types[10], sizeof(unsigned char));

    return (0);
}
