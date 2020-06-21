#include <iostream>

class X
{
public:
    explicit X(int a_);
    void Foo();

// private:
    int m_a;
};

X::X(int a_): m_a(a_)
{

}

void X::Foo()
{
    std::cout << m_a << std::endl;
}

void Foo(const X& x_)
{
    std::cout << x_.m_a << std::endl;
}

int main()
{
    X x1;

    x1.Foo();
    std::cout << x1.m_a;
    Foo(x1);

    return 0;
}
