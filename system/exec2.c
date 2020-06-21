#include <stdio.h>
#include <unistd.h>

int main()
{
    extern int shared;
    printf("exec2: %d\n", shared);

    sleep(30);

    printf("exec2: %d\n", shared);

    return (0);
}
