#include <iostream>

using namespace std;

namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo() 
    {
        cout << "useless::Foo()" << endl;
    }

    namespace wasteoftyme
    {
        void Foo() 
        {
            cout << "useless::wasteoftyme::Foo()" << endl;
        }
    } // namespace wasteoftyme
} // namespace useless

namespace stupid
{
    void Foo() 
    {
        cout << "stupid::Foo()" << endl;
    }
    void Bar() 
    {
        cout << "stupid::Bar()" << endl;
    }
    void DoNothing(unsigned int i) 
    {
        cout << "stupid::DoNothing(unsigned int): i = " << i <<endl;
    }
} // namespace stupid

namespace useless
{
    void DoNothing(int i) 
    {
        cout << "useless::DoNothing(int): i = " << i << endl;
    }
} // namespace useless

using namespace useless;

void DoStuff()
{
    cout << "DoStuff()" << endl;
    stupid::Bar();
    Foo();
    using stupid::Foo;
    Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() 
{
    cout << "Foo()" << endl;
}

using namespace stupid;

namespace comeone = useless::wasteoftyme;

void DoMoreStuff()
{
    cout << "DoMoreStuff()" << endl;
    comeone::Foo();
    ::Foo();
    Bar();
    DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
    void DoUselessStuff()
    {
        cout << "useless::DoUselessStuff()" << endl;
        DoNothing(g_wasteful[3] + 1);
    }
} //namespace useless

int main()
{
    useless::Foo();
    useless::wasteoftyme::Foo();
    stupid::Foo();
    stupid::Bar();
    stupid::DoNothing(-1);
    stupid::DoNothing(1);
    useless::DoNothing(-1);
    useless::DoNothing(1);
    DoStuff();
    ::Foo();
    DoMoreStuff();
    useless::DoUselessStuff();
}
