#include <stdio.h>  /* printf         */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* alloc family   */

#include "hash_table.h"

#include "utils.h"
#include "tests.h"

#define BUCKETS (25000)

int TestWordSearch();

int main(int args, char **argv)
{
    size_t failures = 0;
    TestWordSearch(args, argv);

    return(failures);
}

size_t HashFunc(const void *key)
{
    size_t result = 0;
    size_t i = 0;
    size_t letters_to_count = 3;
    int mult_arr[] = {1, 10, 100};

    for (i = 0; i < letters_to_count && *((char *)key + i) != '\0'; ++i)
    {
        result += ((int)*(char *)key + i) * mult_arr[i];
    }

    return (result);
}

size_t HashFuncInt(const void *key)
{
    size_t result = 0;
    size_t i = 0;
    size_t num_to_count = 1;
    int data = *(int *)key;

    if (data < 0)
    {
        data = FLIP_SIGN(data);
    }

    for (i = 0; i < num_to_count && 0 < data; ++i)
    {
        result += (data % 10);
        data /= 10;
    }

    return (result);
}

int IsMatch(const void *data, const void *data_to_find)
{
    return (!strcmp((const char *)data, (const char *)data_to_find));
}

int IsMatchInt(const void *data, const void *data_to_find)
{
    return (*(int *)data == *(int *)data_to_find);
}

int Act(void *data, void* param)
{
    *(int *)data *= *(int *)param;

    return (0);
}

static int FreeMalloc(void *data, void* param)
{
    UNUSED(param);
    free(data); data = NULL;

    return (0);
}

int TestWordSearch(int args, char **argv)
{
    size_t failures = 0;
    size_t num_of_buckets = BUCKETS;
    int insert_ret = 0;
    char *string = NULL;
    FILE *file = fopen("/usr/share/dict/words", "r");
    hash_t *hash = HTCreate(HashFunc, IsMatch, num_of_buckets);
    void *find_return = NULL;
    int i = 0;

    if (NULL == file)
    {
        printf("Error opening file\n");
        return (1);
    }

    while (NULL != (fgets(string = (char *)malloc(50), 50, file)))
    {
        string[strlen(string) - 1] = '\0';
        insert_ret = HTInsert(hash, string);
        REQUIRE(insert_ret, !=, 0, %d, %d);
    }
    fclose(file);
    free(string);

    for (i = 1; i < args; ++i)
    {
        if ((find_return = HTFind(hash, argv[i])))
        {
            printf("\n\"%s\" is in the dictionary\n", (char *)(argv[i]));
        }
        else
        {
            printf("\n\"%s\" is not in the dictionary\n", (char *)(argv[i]));
        }

    }

    HTForEach(hash, FreeMalloc, NULL);

    HTDestroy(hash);

    return (failures);
}
