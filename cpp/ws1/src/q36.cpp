#include <iostream>

using namespace std;

class X
{
public:
    X() { cout << "X" << this << " : " << &m_a << endl; }
    virtual ~X() { cout << "X dtor: " << this << endl; }
private:
    double m_a;
};

class Y : public X
{
public:
    Y() { cout << "Y" << this <<  " : " << &m_b << endl; }
     ~Y() { cout << "Y dtor: " << this << endl; }
private:
    int m_b;
};

void Foo(X x) {}

int main()
{
    X *xp = new Y[5];

    delete[] xp;

    // Y y1;
    // Foo(y1);

    return 0;
}
