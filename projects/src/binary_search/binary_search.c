#include "binary_search.h"

void *BinarySearch(const void *key, const void *base,
                     size_t elems, size_t size,
                     int (*cmp)(const void *, const void *))
{
	size_t left = 0;
	size_t right = elems;
	size_t mid = (left + right) / 2;
	char *arr = (char *)base;

	while (mid != left)
	{
		switch (cmp((arr + (mid * size)), key))
		{
			case 1:
				right = mid;
				break;
			case -1:
				left = mid;
				break;
			default:
				return (arr + (mid * size));
				break;
		}
		mid = (left + right) / 2;
	}

	if (0 == cmp((arr + (left * size)), key))
	{
		return (arr + (left * size));
	}
	else
	{
		return (NULL);
	}
}

void *RecBinarySearch(const void *key, const void *base,
                     size_t elems, size_t size,
                     int (*cmp)(const void *, const void *))
{
	size_t left = 0;
	size_t right = elems;
	size_t mid = (left + right) / 2;
	char *arr = (char *)base;

	if (mid == left)
	{
		if (0 == cmp((arr + (left * size)), key))
		{
			return (arr + (left * size));
		}
		else
		{
			return (NULL);
		}
	}

	switch (cmp((arr + (mid * size)), key))
	{
		case 1:
			return RecBinarySearch(key, arr, elems - mid, size, cmp);
		case -1:
			return RecBinarySearch(key, arr + (mid * size), elems - mid, size, cmp);
		default:
			return (arr + (mid * size));
	}
}
