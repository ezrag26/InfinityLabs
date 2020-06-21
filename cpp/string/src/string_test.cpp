#include <iostream>

#include "string.hpp"

int main()
{
    using namespace ilrd;

    String s1("hello");
    std::cout << s1.CStr() << std::endl;
    std::cout << s1.Length() << std::endl;

    String s2(s1);
    std::cout << s2.CStr() << std::endl;

    String s3;
    std::cout << s3.CStr() << std::endl;
    
    s3 = s2;

    std::cout << s3.CStr() << std::endl;

    s2 = "a new string";

    std::cout << s2.CStr() << std::endl;
    std::cout << s2.Length() << std::endl;

    std::cout << s1.CStr() << std::endl;
    std::cout << s3.CStr() << std::endl;
}
