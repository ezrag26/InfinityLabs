#include <iostream>

#include "before_you_start.hpp"

using namespace std;

extern "C" void Foo() {
    std::cout << "In function Foo\n";
    std::cout << "A change in the function Foo\n";
};

extern "C" void Bla() {
    std::cout << "In function Bla\n";
    std::cout << "A change in the function Bla\n";
}