#include <iostream>
#include "q15.hpp"
using namespace std;

// template <typename T>
// T Max(T t1, T t2)
// {
//     return t1 > t2 ? t1 : t2;
// }

int main()
{
    int arr[12];

    cout << Max<int>(3, 5) << endl;
    // cout << Max<int *>(3, 5) << endl; // error: no matching function for call to 'Max'
    cout << Max<double>(12.9, 3.7) << endl;
    cout << Max<int *>(arr, arr + 8) << endl;
    cout << Max('a', 'b') << endl;

    foo();

    return 0;
}
