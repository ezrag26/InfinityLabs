#include <iostream>

#include "composite2.hpp"

using namespace std;
using namespace ilrd;


int main()
{
    Leaf l1("l1");
    Leaf l2("l2");
    Composite c1("c1");
    Composite c2("c2");

    c1.AddComponent(&l1);
    c1.AddComponent(&l2);

    c2.AddComponent(&c1);
    
    cout << "TOTAL c1 Components: " << c1.Count() << endl;
    cout << "TOTAL c2 Components: " << c2.Count() << endl;

    l1.PrintName();
    l2.PrintName();
    c1.PrintName();
    c2.PrintName();
    
}
