#include <stdio.h>
#include <stddef.h>

#include "utils.h"

void MaxAfterZero(unsigned char ch);

int main()
{
	unsigned char ch[] = {1, 2, 3, 1, 5, 2, 6, 3, 7, 8, 27, 3, 0, 1, 35 ,3, 3, 5, 3, 6 ,7, 3, 7, 3, 2, 7, 0, 1, 1, 1, 1, 3, 5, 2, 6, 3, 2, 6, 7, 0, 1, 5, 0};
	size_t i = 0;
	
	for (i = 0; i < ARR_SIZE(ch); ++i)
	{
		MaxAfterZero(ch[i]);
	}
	
	return (0);
}

void MaxAfterZero(unsigned char ch)
{
	static unsigned int buffer[256] = {0};
	static size_t max = 0;
	size_t i = 0;
	
	if (0 < ch)
	{
		buffer[ch] += 1;
		
		if (buffer[ch] > max)
		{
			max = buffer[ch];
		}
	}
	else
	{
		printf("%lu\n", max);
		
		max = 0;
		
		for (i = 0; i < 256; ++i)
		{
			buffer[i] = 0;
		}
	}
}
