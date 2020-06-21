#include <iostream>
using namespace std;

class FixedStack
{
public:
    FixedStack()
    {
        top = -1;
    }

    void Push(int d) throw (out_of_range)
    {
        if (top >= CAPACITY - 1) throw out_of_range("Stack is full");

        stack[++top] = d;
    }

    int Pop() throw (out_of_range)
    {
        if (-1 == top) throw out_of_range("Stack is empty");

        // return stack[--top]; original return statement: this would never return the last item added
        return stack[top--];
    }

private:
    static const int CAPACITY = 100;
    int stack[CAPACITY];
    int top;
};
// represents a fixed sized stack

int main()
{
    FixedStack fs;
    
    for (int i = 0; i < 100; ++i)
    {
        fs.Push(i);
    }

    try
    {
        fs.Push(100);
    }
    catch(const out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    for (int i = 0; i < 100; ++i)
    {
        cout << fs.Pop() << endl;
    }

    try
    {
        fs.Pop();
    }
    catch(const out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
