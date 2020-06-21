#include <iostream>
#include <exception>

using namespace std;

void Foo()
{
    throw runtime_error("In Foo()");
}

void TerminateHandler()
{
    cout << "In TerminateHandler()" << endl;
    // abort();
}

int main()
{
    set_terminate(TerminateHandler);
    // terminate();
    // set_unexpected(TerminateHandler);
    // unexpected();
    // try
    // {
        // Foo();
        throw 0;
    // }
    // catch(const exception& e)
    // {
    //     cerr << e.what() << endl;
    //     // terminate();
    // }
    
}
