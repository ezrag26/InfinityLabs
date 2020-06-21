#include <iostream>
using namespace std;

int main()
{
    bool b1 = true;
    cout << "sizeof(b1): " << sizeof(b1) << endl;
    cout << "b1: " << b1 << endl;
    bool b2;
    cout << "sizeof(b2): " << sizeof(b2) << endl;
    cout << "b2: " << b2 << endl;
    int i = b1;
    cout << "sizeof(i): " << sizeof(i) << endl;
    cout << "i: " << i << endl;
    i = 7;
    cout << "sizeof(i): " << sizeof(i) << endl;
    cout << "i: " << i << endl;
    b2 = i;
    cout << "b2: " << b2 << endl;


    int n = 100;
    cout << "n: " << n << endl;
    char c = n;
    cout << "c: " << c << endl;

    return 0;
}