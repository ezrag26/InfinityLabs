#include <cstring> // length, strcpy

#include "string.hpp"

using namespace ilrd;

String::String(const char *string_) : m_cstr(new char[strlen(string_) + 1]) // implementation of ctor
{
    memcpy(m_cstr, string_, strlen(string_));
}

String::~String() // implementation of dtor
{
    delete[] m_cstr;
}

String::String(const String& other_): m_cstr(new char[other_.Length() + 1]) // implementation of cctor
{
    memcpy(m_cstr, other_.m_cstr, other_.Length());
}

String& String::operator=(const String& other_) // implementation of assignment operator
{
    char *tmp = strdup(other_.m_cstr);
    
    delete[] m_cstr;

    m_cstr = strdup(tmp);
    
    delete[] tmp; tmp = NULL;
    
    return *this;
}

size_t String::Length() const
{
    return strlen(m_cstr);
}

const char *String::CStr() const // getter
{
    return m_cstr;
}
