#include <iostream>
using namespace std;

int sum(int x = 0, int y = 0)
{
    return x + y;
}

int main()
{
    cout << "function sum(): " << sum() << endl;
    cout << "function sum(int 5): " << sum(5) << endl;
    cout << "function sum(int 5, int 3): " << sum(5, 3) << endl;
}
