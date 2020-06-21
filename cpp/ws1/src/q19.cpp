#include <iostream>

struct X
{
    explicit X(); // No arg (default) ctor
    explicit X(int a_, int b_ = 8); // arg ctor
    ~X(); // dtor
    X(const X& other_); // copy ctor (cctor)
    X& operator=(const X& other_); // assignment operator

    int m_a;
    const int m_b;
};

struct Y
{
    X m_x;
    int m_i;
};

X::X(): m_a(3), m_b(4)
{
    // m_a = 3;
    // m_b = 4; // error because m_b is declared as const
    std::cout << "this: " << this << 
                " X default ctor. m_a: " << m_a << " || " <<
                "m_b: " << m_b << std::endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_)
{
    std::cout << "this: " << this <<
                " X int ctor. m_a: " << m_a << " || " <<
                "m_b: " << m_b << std::endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b)
{
    std::cout << "this: " << this <<
                " X int cctor. m_a: " << m_a << " || " <<
                "m_b: " << m_b << std::endl;
}

X& X::operator=(const X& other_)
{
    m_a = other_.m_a;
    // m_b = other_.m_b; // error because m_b is declared as const
    std::cout << "this: " << this << " || " <<
                "X assignment operator: m_a: " << m_a <<
                " || does not change m_b: " << m_b << std::endl;

    return *this;
}

X::~X()
{
    std::cout << "this: " << this <<
                " X dtor. m_a: " << m_a << " || " <<
                "m_b: " << m_b << std::endl;
}

int main()
{
    X x1;
    X x2(7);
    X *px = new X(x2);
    X x3(9, 10);
    X x4(x1);

    x1 = x3;

    delete px; px = 0;

    return 0;
}
