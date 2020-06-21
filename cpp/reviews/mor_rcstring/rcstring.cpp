#include <cstddef>      // size_t
#include <iostream>     // I/O operators
#include "rcstring.hpp" 
#include "utils.hpp"

#define INPUT_SIZE 30

namespace ilrd
{

RCString::RCString(const char *str_) : m_resource(RCResourceInit(str_)){}

/*
    TODO: I don't think the copy ctor should change the resource...
    While this accomplishes what you need when declaring a new variable, the copy ctor is also called when sending to a function and when returning it from a function
    This ends up creating a new resource when that isn't what you want
*/
RCString::RCString(const RCString& other_) : m_resource(ChangeResource(NULL, other_.m_resource)){}

RCString& RCString::operator=(const RCString& other_)
{
    m_resource = ChangeResource(m_resource, other_.m_resource);
    return (*this);
}

RCString::~RCString()
{
    /*
        TODO: sometimes you use this->m_resource or this->MethodName(), and sometimes you just do m_resource or MethodName().
        Either way is fine, but you should choose one and be consistent.
    */
    if (--(this->m_resource->counter) == 0)
    {
        delete (this->m_resource);
    }
}

size_t RCString::Length() const
{
    return (strlen(this->RCStr()));
}

const char *RCString::RCStr() const
{
    return (m_resource->string); 
}

/*
    TODO: I think you should use ChangeResource() here. Think about what happens if there are a few RCStrings
    that use this resource. You will return a reference to a position in the array that can be changed,
    and if the user changes the content for one of the RCStrings, it will change it for all of them...
*/ 
char& RCString::operator[](size_t pos)
{
    ASSERT(pos <= Length()); /* TODO: I think this needs to be <, not <= */
    char *ch = m_resource->string + pos;
    return (*ch);
}

char RCString::operator[](size_t pos)const
{
    ASSERT(pos <= Length());
    return (this->RCStr()[pos]);
}

bool operator==(const RCString& string_, const RCString& other_)
{
    return ((strcmp(string_.RCStr(), other_.RCStr())) == 0);
}

bool operator<(const RCString& string_, const RCString& other_)
{
    return ((strcmp(string_.RCStr(), other_.RCStr())) < 0);
}

bool operator>(const RCString& string_, const RCString& other_)
{
    return ((strcmp(string_.RCStr(), other_.RCStr())) > 0);
}

std::ostream& operator<<(std::ostream& os_, const RCString& str_)
{
    return (os_ << str_.RCStr());
}

std::istream& operator>>(std::istream& is_, RCString& str_)
{
    /*
        TODO: Just something to think about - this obviously limits what can be entered as input to INPUT_SIZE.
        There is a way to receive all the input without limiting the size, though it may not be the most efficient.
    */
    char stringInput[INPUT_SIZE];

    is_ >> stringInput;

    str_ = stringInput;
    // Copy assignment operator is used.

    return (is_);
}

#ifndef NDEBUG
    size_t RCString::RCCounter() const
    {
        return (this->m_resource->counter);
    }
#endif

}

