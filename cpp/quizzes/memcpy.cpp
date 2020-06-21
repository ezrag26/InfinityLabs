#include <iostream>
#include <cstddef>

char *memcpy(char *dest, char *src, size_t n)
{
    char *dest_ptr = dest;
    char *src_ptr = src;

    for (int i = 0; i < n; ++i, ++dest_ptr, ++src_ptr)
    {
        *dest_ptr = *src_ptr;
    }

    return dest;
}

int main()
{
    int a = 7;
    int *ptr = &a;
    
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;


    *(char *)&ptr = 1;
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;
}

// I would have expected it to print ptr's address and the value 1
// GDB showed ptr = some address and *ptr = garbage value
// cout printed ptr = some address and *ptr = garbage value
