#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

class X
{
public:
    X() { cout << "Ctor" << endl; }
    ~X() { cout << "Dtor" << endl;}
};

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog\n"): runtime_error(s_) {}
};

void Fifi()
{
    throw BadDog("bad pup\n");
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    X x1;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main()
{
    try
    {
        Bar();
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exciting."; exit(2);
    }
    catch(BadDog& b)
    {
        cerr << "BadDog exception: " << b.what(); exit(3);
    }
    catch(exception& r)
    {
        cerr << "unknown excpetion: " << r.what();
        exit(4);
    }
    
    return 0;
}
