#include <stdio.h>
#include <string.h>
#include <assert.h>

int IsRotation(const char *s1, const char *s2);

int main()
{
	const char *string1[] = {"", "12345", "12345", "54321", "12345", "12123"};
	const char *string2[] = {"", "12345", "34512", "32154", "123",   "12312"};
	int expected[] = 		{1,  1, 	  1,       1, 	    0,       1      };
	size_t i = 0;
	
	for (i = 0; i < sizeof(string1)/sizeof(*string1); ++i)
	{
		if (expected[i] != IsRotation(string1[i], string2[i]))
		{
			printf("IsRotation Failed at %lu\n", i);
			printf("Expected: %d\nReturned: %d\n\n", expected[i], IsRotation(string1[i], string2[i]));
		}
	}
	return 0;
}

int IsRotation(const char *s1, const char *s2)
{
	const char *s2_start = s2;
	size_t s1_len = 0;
	size_t s2_len = 0;
	size_t is_same_count = 0;
	
	assert(NULL != s1);
	assert(NULL != s2);
	
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	
	if (s1_len != s2_len)
	{
		return 0;
	}
	
	while (*s1 != *s2 && '\0' != *s2)
	{
		++s2;
	}
	
	while (*s1 == *s2 && '\0' != *s1)
	{
		++s1;
		++s2;
		++is_same_count;
		
		if ('\0' == *s2)
		{
			s2 = s2_start;
		}
	}
	
	if (is_same_count == s1_len)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
