#include <stdlib.h>

int main()
{
    int *ptr = (int *)malloc(1000 * sizeof(int));
    delete ptr;

    int *ptr2 = new int[1000];
    free(ptr2);
}
