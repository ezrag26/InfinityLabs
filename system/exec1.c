#include <stdio.h>
#include <unistd.h>

int main()
{
    extern int shared;
    shared = 6;
    printf("exec1: %d\n", shared);

    sleep(20);

    shared = 10;

    printf("exec1: %d\n", shared);

    return (0);

}
