#include <stdio.h>  /* printf */
#include <string.h> /* strcmp */

#include "hash_table.h"

#include "utils.h"
#include "tests.h"

#define BUCKETS (10000)

int TestHTCreateDestroy();
int TestHTInsert();
int TestHTRemove();
int TestHTSize();
int TestHTIsEmpty();
int TestHTFind();
int TestHTForEach();

int main()
{
    size_t failures = 0;

    puts("Testing Hash Table...");
    TEST(TestHTCreateDestroy(), "TestHTCreateDestroy");
    TEST(TestHTInsert(), "TestHTInsert");
    TEST(TestHTRemove(), "TestHTRemove");
    TEST(TestHTSize(), "TestHTSize");
    TEST(TestHTIsEmpty(), "TestHTIsEmpty");
    TEST(TestHTFind(), "TestHTFind");
    TEST(TestHTForEach(), "TestHTForEach");


    PRNT_STATUS(failures);
    return(failures);
}

size_t HashFunc(const void *key)
{
    size_t result = 0;
    size_t i = 0;
    size_t letters_to_count = 3;

    for (i = 0; i < letters_to_count && *((char *)key + i) != '\0'; ++i)
    {
        result += ((int)*(char *)key + i);
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

int TestHTCreateDestroy()
{
    size_t failures = 0;
    size_t num_of_buckets = BUCKETS;

    hash_t *hash = HTCreate(HashFunc, IsMatch, num_of_buckets);

    HTDestroy(hash);

    return (failures);
}

int TestHTInsert()
{
    size_t failures = 0;
    size_t i = 0;
    size_t num_of_buckets = BUCKETS;
    char *string[] = {"abc", "a", "abba", "z", "az", "za"};
    int insert_ret = 0;

    hash_t *hash = HTCreate(HashFunc, IsMatch, num_of_buckets);

    for (i = 0; i < ARR_SIZE(string); ++i)
    {
        insert_ret = HTInsert(hash, string[i]);
        REQUIRE(insert_ret, !=, 0, %d, %d);
    }


    HTDestroy(hash);

    return (failures);
}

int TestHTRemove()
{
    size_t failures = 0;
    size_t i = 0;
    size_t num_of_buckets = BUCKETS;
    char *string[] = {"a", "aba", "abba", "zaz", "zzz",
                      "abza", "test", "hello", "world", "123"};
    size_t exp_size[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    hash_t *hash = HTCreate(HashFunc, IsMatch, num_of_buckets);

    for (i = 0; i < ARR_SIZE(string); ++i)
    {
        HTInsert(hash, string[i]);
    }

    REQUIRE(HTSize(hash), !=, exp_size[0], %lu, %lu);

    for (i = 0; i < ARR_SIZE(string); ++i)
    {
        HTRemove(hash, string[i]);
        REQUIRE(HTSize(hash), !=, exp_size[i + 1], %lu, %lu);
    }

    HTDestroy(hash);

    return (failures);
}

int TestHTSize()
{
    size_t failures = 0;
    size_t i = 0;
    size_t num_of_buckets = BUCKETS;
    char *string[] = {"a", "aba", "abba", "zaz", "zzz",
                      "abza", "test", "hello", "world", "123"};
    size_t exp_size[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    hash_t *hash = HTCreate(HashFunc, IsMatch, num_of_buckets);

    REQUIRE(HTSize(hash), !=, exp_size[i], %lu, %lu);

    for (i = 0; i < ARR_SIZE(string); ++i)
    {
        HTInsert(hash, string[i]);
        REQUIRE(HTSize(hash), !=, exp_size[i + 1], %lu, %lu);
    }

    HTDestroy(hash);

    return (failures);
}

int TestHTIsEmpty()
{
    size_t failures = 0;
    size_t i = 0;
    size_t num_of_buckets = BUCKETS;
    char *string[] = {"a", "aba", "abba", "zaz", "zzz",
                      "abza", "test", "hello", "world", "123"};
    int exp_ret[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    hash_t *hash = HTCreate(HashFunc, IsMatch, num_of_buckets);

    REQUIRE(HTIsEmpty(hash), !=, exp_ret[i], %d, %d);

    for (i = 0; i < ARR_SIZE(string); ++i)
    {
        HTInsert(hash, string[i]);
        REQUIRE(HTIsEmpty(hash), !=, exp_ret[i + 1], %d, %d);
    }

    HTDestroy(hash);

    return (failures);
}

int TestHTFind()
{
    size_t failures = 0;
    size_t i = 0;
    size_t num_of_buckets = BUCKETS;
    char *string[] = {"a", "aba", "abba", "zaz", "zzz",
                      "abza", "test", "hello", "world", "123"};
    char *not_found[] = {"54", "fqf", "fheiuwq", "fnao"};
/*    int data[] = {-1, 50, 0, 99999, 10000};
    int not_found_nums[] = {4, 15677, 213542, 74, 2352, 754};
    int param = 2;
*/
    hash_t *hash = HTCreate(HashFunc, IsMatch, num_of_buckets);
/*    hash_t *hash2 = HTCreate(HashFuncInt, IsMatchInt, num_of_buckets);
*/
    for (i = 0; i < ARR_SIZE(string); ++i)
    {
        HTInsert(hash, string[i]);
    }

    for (i = 0; i < ARR_SIZE(string); ++i)
    {
        REQUIRE((char *)HTFind(hash, string[i]), !=, string[i], %s, %s);
    }

    for (i = 0; i < ARR_SIZE(not_found); ++i)
    {
        REQUIRE(HTFind(hash, not_found[i]), !=, NULL, %p, %p);
    }
/*
    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HTInsert(hash2, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        REQUIRE(HTFind(hash2, &data[i]), ==, NULL, %p, %p);
    }

    HTForEach(hash2, Act, &param);

    for (i = 0; i < ARR_SIZE(not_found_nums); ++i)
    {
        REQUIRE(HTFind(hash2, &data[i]), !=, NULL, %p, %p);
    }
*/

    HTDestroy(hash);
    /*HTDestroy(hash2);*/

    return (failures);
}

int TestHTForEach()
{
    size_t failures = 0;
    size_t i = 0;
    size_t num_of_buckets = BUCKETS;
    int data[] = {-1, 50, 0, 99999, 10000};
    int data2[] = {-1, 50, 0, 99999, 10000};
    int param = 2;
    int exp_find[] = {-2, 100, 0, 199998, 20000};

    hash_t *hash = HTCreate(HashFuncInt, IsMatchInt, num_of_buckets);


    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HTInsert(hash, &data[i]);
    }

    HTForEach(hash, Act, &param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        if (2 == i)
        {
            REQUIRE(HTFind(hash, &data2[i]), ==, NULL, %p, %p);
            continue;
        }
        REQUIRE(HTFind(hash, &data2[i]), !=, NULL, %p, %p);
    }

    for (i = 0; i < ARR_SIZE(exp_find); ++i)
    {
        REQUIRE(HTFind(hash, &exp_find[i]), ==, NULL, %p, %p);
    }


    HTDestroy(hash);

    return (failures);
}
