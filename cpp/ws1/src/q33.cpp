#include <iostream>
// #include <exception>

void Bar(int *) {}
void Fishi() {}
void Fifi(int *) {}
void Dodo() {}


int main()
{
    // 1 way
    try {
        int *ip = new int;
        Bar(ip);
        Fishi();
        Fifi(ip);
        Dodo();
        delete ip;
    }
    catch (const std::bad_alloc& ignored) {} 

    // Another way
    int *ip = new (std::nothrow) int;
    if (ip)
    {
        Bar(ip);
        Fishi();
        Fifi(ip);
        Dodo();
        delete ip;
    }
}
