#include <iostream>
using namespace std;

class Base
{
public:
    virtual void foo()
    {
        cout << "Base::Foo()" << endl;
    }
};

class Derived : public Base
{
public:
    void foo(int i)
    {
        cout << "Derived::Foo()" << endl;
    }
};

int main()
{
    Derived d;
    d.foo();
}
