#include <iostream>
#include "q11.hpp"

using namespace std;

void Foo()
{
    cout << "Foo()" << endl;
}

void Foo(int i)
{
    cout << "Foo(int i)" << endl;
}

void Foo(char c)
{
    cout << "Foo(char c)" << endl;
}


// #include <stdio.h>
// #include "q11.h"

// void Foo()
// {
//     printf("Foo()\n");
// }

// void Foo(int i)
// {
//     printf("Foo(int i)\n");
// }

// void Foo(char c)
// {
//     printf("Foo(char c)\n");
// }
