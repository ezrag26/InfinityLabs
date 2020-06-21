#include <stdlib.h> /* alloc family */
#include <assert.h> /* assert */

#include "hash_table.h"
#include "doubly_linked_list.h" /* DLLPopFront, DLLPopBack, DLLInsert, etc. */

#include "utils.h"

struct hash_table
{
	hash_func_t hash_func;
	hash_is_match_t is_match;
	size_t num_of_buckets;
	dll_t *buckets[1];
};

/********************************** HTCreate **********************************/

hash_t *HTCreate(hash_func_t hash_func,
                 hash_is_match_t is_match,
                 size_t num_of_buckets)
{
    hash_t *hash = (hash_t *)malloc(sizeof(hash_t)
                    + (sizeof(dll_t *) * (num_of_buckets - 1)));
    size_t i = 0;

    if (NULL == hash)
    {
        PRNT_ERR("Memory allocation failed");
        return (NULL);
    }

    hash->hash_func = hash_func;
    hash->is_match = is_match;
    hash->num_of_buckets = num_of_buckets;

    for (i = 0; i < num_of_buckets; ++i)
    {
        *(hash->buckets + i) = DLLCreate();

        if (NULL == *(hash->buckets + i))
        {
            HTDestroy(hash); hash = NULL;
            return (NULL);
        }
    }

    return (hash);
}

/********************************** HTDestroy *********************************/

void HTDestroy(hash_t *hash)
{
    size_t i = 0;

    assert(NULL != hash);

    for (i = 0; i < hash->num_of_buckets; ++i)
    {
        DLLDestroy(*(hash->buckets + i));
    }

    free(hash); hash = NULL;
}

static dll_t *GetDLL(const hash_t *hash, const void *data)
{
    size_t hash_return = 0;
    size_t index = 0;

    hash_return = hash->hash_func(data);
    index = hash_return % hash->num_of_buckets;

    return (*(hash->buckets + index));
}

/********************************** HTInsert **********************************/

int HTInsert(hash_t *hash, void *data)
{
    dll_t *dll = NULL;
    dll_iter_t insert_ret = NULL;
    dll_iter_t end = NULL;

    assert(NULL != hash);

    dll = GetDLL(hash, data);
    end = DLLEnd(dll);

    insert_ret = DLLPushFront(dll, data);

    return (DLLIsSameIter(end, insert_ret));
}

/********************************** FindIter **********************************/

static dll_iter_t FindIter(const hash_t *hash, const void *data)
{
    dll_t *dll = NULL;
    dll_iter_t begin = NULL;
    dll_iter_t end = NULL;

    dll = GetDLL(hash, data);
    begin = DLLBegin(dll);
    end = DLLEnd(dll);

    return (DLLFind(begin, end, data, hash->is_match));
}

void HTRemove(hash_t *hash, const void *data)
{
    assert(NULL != hash);

    DLLRemove(FindIter(hash, data));
}

/*********************************** HTSize ***********************************/
size_t HTSize(const hash_t *hash)
{
    size_t i = 0;
    size_t count = 0;

    assert(NULL != hash);

    for (i = 0; i < hash->num_of_buckets; ++i)
    {
        count += DLLSize(*(hash->buckets + i));
    }

    return (count);
}

/********************************** HTIsEmpty *********************************/

int HTIsEmpty(const hash_t *hash)
{
    size_t i = 0;

    assert(NULL != hash);

    for (i = 0; i < hash->num_of_buckets; ++i)
    {
        if (!DLLIsEmpty(*(hash->buckets + i)))
        {
            return (0);
        }
    }

    return (1);
}

/*********************************** HTFind ***********************************/

void *HTFind(const hash_t *hash, const void *data_to_find)
{
    dll_t *dll = NULL;
    dll_iter_t end = NULL;
    dll_iter_t found_iter = NULL;
    void *ret_data = NULL;

    assert(NULL != hash);

    dll = GetDLL(hash, data_to_find);
    end = DLLEnd(dll);

    found_iter = FindIter(hash, data_to_find);

    /* did not find iter */
    if (DLLIsSameIter(end, found_iter))
    {
        return (NULL);
    }

    ret_data = DLLGetData(found_iter);

    /* found_iter, and successfully pushed */
    if (!DLLIsSameIter(end, DLLPushFront(dll, (void *)ret_data)))
    {
        /* remove the original iter from the list */
        DLLRemove(found_iter);
    }

    return (ret_data);
}

/********************************** HTForEach *********************************/

int HTForEach(hash_t *hash, hash_act_t act, void *param)
{
    dll_t *dll = NULL;
    int act_return = 0;
    size_t i = 0;

    assert(NULL != hash);

    for (i = 0; i < hash->num_of_buckets; ++i)
    {
        dll = *(hash->buckets + i);
        if ((act_return = DLLForEach(DLLBegin(dll), DLLEnd(dll), act, param)))
        {
            break;
        }
    }

    return (act_return);
}
