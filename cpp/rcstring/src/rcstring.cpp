#include <iostream>
#include <cstring>
#include "rcstring.hpp"

namespace ilrd {

RCString::Resource *RCString::ResourceInit(const char *str_) throw(std::bad_alloc)
{
    size_t len = strlen(str_) + EOL_CHAR;
    Resource *ptr = (Resource *)operator new(offsetof(Resource, m_string) + len);
        
    ptr->m_counter = 1;
    memcpy(ptr->m_string, str_, len);
    
    return ptr;
}

bool RCString::IsLastResource(RCString::Resource* resource)
{
#ifndef NDEBUG
    PrintCounter(resource); 
#endif /* NDEBUG */
    return --resource->m_counter == 0;
}

void RCString::DeleteResource(RCString::Resource* resource)
{
#ifndef NDEBUG
    PrintCounter(resource);
#endif /* NDEBUG */
    delete resource;
    resource = NULL;
}

// default constructor
RCString::RCString(const char *string_) : m_resource(ResourceInit(string_))
{
#ifndef NDEBUG
    PrintCounter(m_resource);
#endif /* NDEBUG */
}
    
// copy constructor
RCString::RCString(const RCString& other_)
    : m_resource(other_.m_resource)
{ 
    ++m_resource->m_counter;
#ifndef NDEBUG
    PrintCounter(m_resource);
#endif /* NDEBUG */
}

RCString& RCString::operator=(const RCString& other_) // assignment operator
{
    /* in case this is not a self assignment, might need to delete later */
    Resource *tmp = m_resource;

    /* change resource */
    m_resource = other_.m_resource;
    ++m_resource->m_counter;
#ifndef NDEBUG
    PrintCounter(m_resource);
#endif /* NDEBUG */

    /* nothing else is using this resource */
    if (IsLastResource(tmp)) DeleteResource(tmp);
    
    return *this;
}

// destructor
RCString::~RCString() { if (IsLastResource(m_resource)) DeleteResource(m_resource); }

size_t RCString::Length() const { return strlen(RCStr()); }

const char *RCString::RCStr() const { return m_resource->m_string; }

char& RCString::operator[](size_t pos)
{
    assert(pos < Length());
    
    /* in case this is the last RCString that holds this resource, might need to delete later */
    Resource *tmp = m_resource;
    
    m_resource = ResourceInit(RCStr());
#ifndef NDEBUG
    PrintCounter(m_resource);
#endif /* NDEBUG */
    
    /* string might be changed, don't want it to change for all RCStrings with this string */
    if (IsLastResource(tmp)) { DeleteResource(tmp); }

    return m_resource->m_string[pos];
}

char RCString::operator[](size_t pos) const
{
    assert(pos < Length());
    
    return RCStr()[pos];
}

bool operator==(const RCString& string, const RCString& other_)
{
    return strcmp(string.RCStr(), other_.RCStr()) == 0;
}

bool operator<(const RCString& string, const RCString& other_)
{
    return strcmp(string.RCStr(), other_.RCStr()) < 0;
}

bool operator>(const RCString& string, const RCString& other_)
{
    return strcmp(string.RCStr(), other_.RCStr()) > 0;
}

std::ostream& operator<<(std::ostream& os_, const RCString& str_)
{
    os_ << str_.RCStr();

    return os_;
}

std::istream& operator>>(std::istream& is_, RCString& str_) //TODO:
{
    std::string input;
    
    std::getline(is_, input);           // get until new line
    
    str_ = input.c_str();               // assign string to variable

    return is_;
}

} // ilrd
