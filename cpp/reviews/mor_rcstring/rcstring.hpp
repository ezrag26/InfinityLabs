#ifndef ILRD_8384_RCSTRING_HPP
#define ILRD_8384_RCSTRING_HPP

#include <cstddef>  //size_t
#include <iostream> //ostream
#include <string.h>     // strlen, memcpy

namespace ilrd
{
class RCString
{
public:
	RCString(const char *str_ = ""); //implicit convertion
	RCString(const RCString& other_); //cCtor
	RCString& operator=(const RCString& other_);
	~RCString();
	size_t Length() const;
	const char *RCStr() const;
	
	char& operator[](size_t pos); //returns modifiable reference
	char operator[](size_t pos)const;

#ifndef NDEBUG
    size_t RCCounter() const;
#endif

private:
	struct Resource
	{
		size_t counter;
		char string[1]; //flexible array
	};
	Resource *m_resource;

	static const size_t CHAR_SIZE = sizeof(char);
	static const size_t EOL_CHAR = CHAR_SIZE;
	
    static RCString::Resource *RCResourceInit(const char *str_)
    {
        size_t stringLen = strlen(str_);
        RCString::Resource *resource = static_cast<RCString::Resource *>(operator new(
                                                                    offsetof(Resource, string) +
                                                                    sizeof(char) * stringLen + /* TODO: you have a static const variable for CHAR_SIZE */
                                                                    EOL_CHAR));
        memcpy(resource->string, str_, stringLen + EOL_CHAR);
        resource->counter = 1;
        return (resource);
    }

    static RCString::Resource *ChangeResource(Resource *curr_, Resource *other_)
    {
        if (curr_ != other_ && curr_ != NULL)
            // curr_ != other_ - In case it assigns itself. 
        {
            if (--(curr_->counter) == 0)
            {
                delete (curr_);
            }
        }
        other_->counter += 1;
        return (other_);
    }

};

	bool operator==(const RCString& string_, const RCString& other_);
    //supports implicit conversion

	bool operator<(const RCString& string_, const RCString& other_);
    bool operator>(const RCString& string_, const RCString& other_);
	std::ostream& operator<<(std::ostream& os_, const RCString& str_);
    std::istream& operator>>(std::istream& is_, RCString& str_);
} // namespace ilrd


#endif // ILRD_8384_RCSTRING_HPP
