#include <iostream>
using namespace std;
class X
{
public:
    X(){ cout << "X Ctor" << endl; }
    ~X(){ cout << "X Dtor" << endl; }
private:
    int x;
};

class Y
{
public:
    Y(){ cout << "Y Ctor" << endl; }
    virtual ~Y(){ cout << "Y Dtor" << endl; }
    virtual void Foo(){}
    void Bar()const;
private:
    X m_x;
    int m_a;
};

class Der: public Y
{
public:
    Der() { cout << "Der Ctor" << endl; }
    ~Der() { cout << "Der Dtor" << endl; }
    virtual void Dodo(){}

private:
    X m_x2;
};

int main() {

    Y y1;
    Der d1;
}
