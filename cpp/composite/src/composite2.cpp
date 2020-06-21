#include <iostream>

#include "composite2.hpp"

using namespace std;

namespace ilrd
{
    
    Leaf::Leaf(char *name_) : m_name(name_)
    {

    }

    int Leaf::Count()
    {
        return 1;
    }
    
    void Leaf::AddComponent(ComponentInterface* comp)
    {

    }

    void Leaf::PrintName()
    {
        cout << m_name << endl;
    }

    Composite::Composite(char *name_) : m_name(name_)
    {

    }

    int Composite::Count()
    {
        int count = 0;
        for (vector<ComponentInterface *>::iterator it = list.begin(); it != list.end(); ++it)
        {
            count += (*it)->Count();
        }

        return count + 1;
    }

    void Composite::AddComponent(ComponentInterface* comp)
    {
        list.push_back(comp);
    }

    void Composite::PrintName()
    {
        cout << m_name << endl;
        for (vector<ComponentInterface *>::iterator it = list.begin(); it != list.end(); ++it)
        {
            (*it)->PrintName();
        }
    }

} // ilrd
