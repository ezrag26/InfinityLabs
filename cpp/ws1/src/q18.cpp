#include <iostream>

void Foo(const double& d)
{
    std::cout << d << std::endl;
    std::cout << &d << std::endl;
    // d = 1;
}

void Bar(double& d)
{
    std::cout << d << std::endl;
}

int main()
{
    int i = 30;
    int& ir = i;

    // std::cout << i << std::endl;
    // std::cout << &i << std::endl;
    // std::cout << ir << std::endl;
    // std::cout << &ir << std::endl;

    Foo(i);
    // Bar(i);

    // std::cout << &i << std::endl;
    
    Bar(reinterpret_cast<double>(i));
}
