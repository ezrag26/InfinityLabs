#include <iostream>
#include <exception>
#include <cstdlib>

using namespace std;

class X
{
public:
    X();
    ~X();
private:
    int m_a;
};

int Foo(int) throw(bad_alloc) { throw bad_alloc(); }

void Bar() throw(bad_cast) {}

X::X() { cout << "Ctor()" << endl; }

X::~X()
{
    cout << "Dtor()" << endl;
    cerr << Foo(m_a) << endl;
    cout << "Dtor() after Foo()" << endl;
}

void Fishi()
{
    X x1;

    Bar();
}

int main()
{
    Fishi();
}
