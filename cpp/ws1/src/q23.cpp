#include <iostream>

struct X
{
    X(int a_, int b_);

    void Inc();
    void Dec();

    int m_a;
    int m_b;
};

X::X(int a_, int b_): m_a(a_), m_b(b_)
{}

void X::Inc()
{
    std::cout << "this: " << this << std::endl;
    ++m_a;
    ++m_b;
}

void X::Dec()
{
    std::cout << "this: " << this << std::endl;
    --m_a;
    --m_b;
}

void Inc() {}

int main()
{
    X x1(7, -55);
    X x2(x1);

    std::cout << "x1: " << &x1 << std::endl;
    std::cout << "x2: " << &x2 << std::endl;

    Inc();

    std::cout << "x1 before x1.Inc():" << std::endl;
    std::cout << "x1.m_a: " << x1.m_a << std::endl;
    std::cout << "x1.m_b: " << x1.m_b << std::endl;

    x1.Inc();

    std::cout << "x1 after x1.Inc():" << std::endl;
    std::cout << "x1.m_a: " << x1.m_a << std::endl;
    std::cout << "x1.m_b: " << x1.m_b << std::endl;

    x1.Inc();

    std::cout << "x1 after x1.Inc():" << std::endl;
    std::cout << "x1.m_a: " << x1.m_a << std::endl;
    std::cout << "x1.m_b: " << x1.m_b << std::endl;

    std::cout << "x2 before x2.Dec():" << std::endl;
    std::cout << "x2.m_a: " << x2.m_a << std::endl;
    std::cout << "x2.m_b: " << x2.m_b << std::endl;
    
    x2.Dec();

    std::cout << "x2 after x2.Dec():" << std::endl;
    std::cout << "x2.m_a: " << x2.m_a << std::endl;
    std::cout << "x2.m_b: " << x2.m_b << std::endl;

    return 0;
}
