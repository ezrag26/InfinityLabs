#include <iostream>
int countSetBits(int num);
void countSetBitsArr(int *arr, size_t length);

int main()
{
    int arr[] = {1, 2, 4, 8, 16, 32, 64, 128};
    int arr2[] = {3, 5, 9, 17, 33, 65, 129};
    int arr3[] = {1 - 0, 2 - 1, 4 - 1, 8 - 1, 16 - 1, 32 - 1, 64 - 1, 128 - 1};

    countSetBitsArr(arr, sizeof(arr)/sizeof(arr[0]));
    countSetBitsArr(arr2, sizeof(arr2)/sizeof(arr2[0]));
    countSetBitsArr(arr3, sizeof(arr3)/sizeof(arr3[0]));
}

void countSetBitsArr(int* arr, size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        std::cout << countSetBits(arr[i]) << std::endl;
    }
}

int countSetBits(int num)
{
    int const BITS = 32;
    int totalSetBits = 0;
    int shift = 0;

    for (int i = 0; i < BITS; ++i, ++shift)
    {
        if (((num >> shift) & 1) != 0)
        {
            ++totalSetBits;
        }
    }

    return totalSetBits;
}
