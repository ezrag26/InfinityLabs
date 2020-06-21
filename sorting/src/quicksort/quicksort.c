#include <stdlib.h> /* alloc family */
#include <assert.h> /* assert 		*/
#include <string.h> /* memcpy		*/

#include "quicksort.h"
#include "utils.h"

static size_t Partition(void *base, size_t elems, size_t size, int (*cmp)(const void *, const void *));

void QuickSort(void *base, size_t elems, size_t size, int (*cmp)(const void *, const void *))
{
    size_t partition = 0;

	assert(NULL != base);

    if (1 >= elems)
    {
        return;
    }

    partition = Partition(base, elems, size, cmp);

    QuickSort(base, partition, size, cmp);
    QuickSort((char *)base + ((partition + 1) * size), elems - (partition + 1), size, cmp);
}

static void Swap(void *data1, void *data2, size_t element_size)
{
	size_t size = element_size;
	size_t tmp = 0;
    size_t *data1_ptr = (size_t *)data1;
    size_t *data2_ptr = (size_t *)data2;

	/* copy sizeof(size_t) bytes until less than sizeof(size_t) bytes to copy */
	while (sizeof(size_t) <= size)
	{
		tmp = *data1_ptr;
		*data1_ptr = *data2_ptr;
		*data2_ptr = tmp;
		++data1_ptr;
        ++data2_ptr;
		size -= sizeof(size_t);
	}

	/* copy rest of bytes */
    if (size > 0)
    {
		memcpy(&tmp, data1_ptr, size);
		memcpy(data1_ptr, data2_ptr, size);
		memcpy(data2_ptr, &tmp, size);
    }
}

static void *GetPivot(void *base, size_t elems, size_t size, int (*cmp)(const void *, const void *))
{
	size_t lo = 0;
	size_t hi = (elems - 1) * size;
	size_t mid = ((lo + hi) / 2);
	char *array = (char *)base;

	assert(NULL != base);

	if (cmp((array + mid), (array + lo)) < 0)
	{
		Swap((array + mid), (array + lo), size);
	}
	if (cmp((array + hi), (array + lo)) < 0)
	{
		Swap((array + hi), (array + lo), size);
	}
	if (cmp((array + mid), (array + hi)) < 0)
	{
		Swap((array + mid), (array + hi), size);
	}
	return (array + hi);
}

static size_t Partition(void *base, size_t elems, size_t size, int (*cmp)(const void *, const void *))
{
    size_t left = 0;
    size_t end = elems - 1;
    size_t right = end - 1;
    char *start = (char *)base;
    char *pivot = NULL;

	assert(NULL != base);

	pivot = (char *)GetPivot(base, elems, size, cmp);

    while (1)
    {
		/* find first number larger than pivot starting from the left */
        while (left < end && (0 >= cmp((start + (left * size)), pivot)))
        {
            ++left;
        }

		/* find first number smaller than pivot starting from the right */
        while (right > left && (0 <= cmp((start + (right * size)), pivot)))
        {
            --right;
        }

		/* paths cross */
        if (left >= right)
        {
			/* swap pivot with the larger number */
            Swap(start + (left * size), pivot, size);
            return (left);
        }

		/* swap larger number with smaller number */
        Swap(start + (left * size), start + (right * size), size);
    }
}
