#include <iostream>

using namespace std;

class X
{
public:
    X( double d_) : m_a(d_) { }
    virtual ~X() { /*cout << this << endl;*/ }
private:
    double m_a;
};

class Y : public X
{
public:
    Y(double d_, int i_): X(d_), m_b(i_) {}
private:
    int m_b;
};

int main()
{
    Y y1(0.0, 0), y2(14.2, 5);
    Y y3(0.0, 0), y4(14.2, 5);

    X &x1 = y1;
    X &x2 = y2;

    x1 = x2;
    y3 = y4;

    return 0;
}
