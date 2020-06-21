#ifndef FS_734_RCSTRING_HPP
#define FS_734_RCSTRING_HPP

#include <cstddef> //size_t
#include <iosfwd> //i/ostream

namespace ilrd
{

class RCString
{
public:
	RCString(const char *str_ = ""); // implicit convertion
	RCString(const RCString& other_); // cCtor
	RCString& operator=(const RCString& other_); // assignment operator
	~RCString(); // dtor
	size_t Length() const;
	const char *RCStr() const; // getter
	
	char& operator[](size_t pos); //returns modifiable reference
	char operator[](size_t pos) const;
private:
	struct Resource
	{
		size_t m_counter;
		char m_string[1]; //flexible array
	};
	Resource *m_resource;
	static const size_t CHAR_SIZE = sizeof(char);

	static Resource *ResourceInit(const char *str_) throw(std::bad_alloc);
	static const size_t EOL_CHAR = CHAR_SIZE;
	bool IsLastResource(RCString::Resource* resource);
	void DeleteResource(RCString::Resource* resource);

	#ifndef NDEBUG
	static void PrintCounter(const Resource *const resource)
	{
		std::cout << resource << " : " << resource->m_counter << std::endl;
	}
	#endif /* NDEBUG */
};

	bool operator==(const RCString& string, const RCString& other_); //supports implicit conversion
	bool operator<(const RCString& string, const RCString& other_);
    bool operator>(const RCString& string, const RCString& other_);
	std::ostream& operator<<(std::ostream& os_, const RCString& str_);
	std::istream& operator>>(std::istream& is_, RCString& str_);
} // namespace ilrd


#endif // FS_734_RCSTRING_HPP
