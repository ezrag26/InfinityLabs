#include <iostream>

#include "complex.hpp"

void Print(const ilrd::Complex& c)
{
    std::cout << c << std::endl;
}

void Print(bool boolean)
{
    const char *answer = boolean ? "true" : "false";
    std::cout << answer << std::endl;
}

void Print(const char *string)
{
    std::cout << string << std::endl;
}

#include <ctime>
void Benchmark()
{
    ilrd::Complex c(1, 1);

    time_t start = time(NULL);
    for (int i = 0; i < 100000; ++i)
    {
        c = c + c;
    }
    time_t end = time(NULL);
    
    std::cout << difftime(end, start) << std::endl;
}

int main()
{
    const double epsilon = 0.0000001f;

    ilrd::Complex c1;
    ilrd::Complex c2(c1);
    ilrd::Complex c3(5, -1);
    ilrd::Complex c4 = c3;
    ilrd::Complex c5(-2, 3);

    const size_t len = 5;
    
    ilrd::Complex cs[len] = {c1, c2, c3, c4, c5};

    Print("The Objects");
    double reals[len] = {0, 0, 5, 5, -2};
    double imags[len] = {0, 0, -1, -1, 3};

    for (size_t i = 0; i < sizeof(reals)/sizeof(reals[0]); ++i)
    {
        // assert(fabs(cs[i].GetReal() - reals[i] < epsilon));
        // assert(fabs(cs[i].GetImaginary() - imags[i] < epsilon));
    }

    // Print(c1);
    // Print(c2);
    // Print(c3);
    // Print(c4);

    Print("Addition");
    Print(c1 + c2); // 0 + 0i
    Print(c2 + c3); // 5 - 1i
    Print(c3 + c4); // 10 - 2i
    Print(c5 *= c3);// -7 + 17i
    Print(c5);      // -7 + 17i
    std::cout << &c5 << std::endl;
    c5 = c5 * c5;   // -240 + -238i
    std::cout << &c5 << std::endl;
    Print(c5);      // -240 + -238i

    Print("== false");
    Print(c1 == c3);
    Print(c1 == c4);
    Print(c2 == c3);
    Print(c2 == c4);

    Print("== true");
    Print(c1 == c1);
    Print(c2 == c2);
    Print(c3 == c3);
    Print(c4 == c4);
    Print(c1 == c2);
    Print(c3 == c4);

    Print("Subtraction");
    Print(c1 - c2); // 0 + 0i
    Print(c2 - c3); // -5 + 1i
    Print(c3 - c4); // 0 + 0i

    Print("Multiplication");
    Print(c1 * c2);
    Print(c1 * c3);
    Print(c1 * c4);

    Print(c2 * c3);
    Print(c2 * c4);

    Print(c3 * c4); // 24 - 10i

    // ilrd::Complex c6;
    // std::cin >> c6;
    // Print(c6);

    Benchmark();

    return 0;
}
