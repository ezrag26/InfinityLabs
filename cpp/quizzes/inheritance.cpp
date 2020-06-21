#include <iostream>

using namespace std;

struct Base
{
    Base() { cout << "Base ctor" << endl; }
    ~Base() { cout << "Base dtor" << endl; }
    Base(const Base&) { cout << "Base cctor" << endl; }
    virtual void operator=(const Base& b) { cout << "Base =" << endl; }
    virtual void print() { cout << "Base print" << endl; }
};

struct Derived : public Base
{
    Derived() { cout << "Derived ctor" << endl; }
    ~Derived() { cout << "Derived dtor" << endl; }
    Derived(const Derived&) { cout << "Derived cctor" << endl; }
    virtual void operator=(const Derived& b) { cout << "Derived =" << endl; }
    virtual void print() { cout << "Derived print" << endl; }
};

void Print(Base p)
{
    p.print();
}

int main()
{
    Base b;
    Base *bp = new Derived();

    Print(b);
    Print(*bp);
    bp->print();

    delete bp;
    return 0;
}
