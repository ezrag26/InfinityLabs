#ifndef _FS_734_STRING_HPP_
#define _FS_734_STRING_HPP_

#include <cstddef> // size_t

namespace ilrd
{

class String
{
public:
    String(const char *string_ = ""); // purposely NOT explicit, want to support implicit conversions
    ~String();
    String(const String& other_);
    String& operator=(const String& other_);
    size_t Length() const;
    const char *CStr() const;

private:
    char *m_cstr;
};

} // ilrd

#endif // _FS734_STRING_HPP_
