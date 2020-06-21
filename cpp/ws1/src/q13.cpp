#include <iostream>

using namespace std;

    const int i = 3;
int main()
{
    int *ip = (int *)&i;
    *ip = 5;
    //int arr[i];

    cout << i << *ip << endl;
    return 0;
}
