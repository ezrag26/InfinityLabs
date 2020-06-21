#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "hash_table.h"
#include "doubly_linked_list.h"



struct hash_table
{
	hash_func_t hash_func;
	hash_is_match_t is_match;
	size_t num_of_buckets;
	dll_t *buckets[1];
};


/********************************* Create *************************************/

static int CreateTable(hash_t *table)
{
    size_t i = 0;

    for (i = 0; i < table->num_of_buckets; ++i)
    {
        table->buckets[i] = DLLCreate();
        if (NULL == table->buckets[i])
        {
            for (; i > 0; --i)
            {
                DLLDestroy(table->buckets[i - 1]);
                free(table->buckets); *(table->buckets) = NULL;
            }

            return 1;
        }
    }

    return 0;
}

hash_t *HTCreate(hash_func_t hash_func, hash_is_match_t is_match, size_t num_of_buckets)
{
    int status = 0;
    hash_t *hash_table = (hash_t *)malloc(sizeof(hash_t) + 
                                    (sizeof(dll_t *) * (num_of_buckets - 1)));
    if (NULL == hash_table)
    {
        return NULL;
    }
    
    hash_table->num_of_buckets = num_of_buckets;

    status = CreateTable(hash_table);

    if (1 == status)
    {   
        free(hash_table); hash_table = NULL;

        return NULL;
    }
    
    hash_table->is_match = is_match;
    hash_table->hash_func = hash_func;

    return hash_table;
}

/********************************* Destroy ************************************/

static void DestroyTable(hash_t *hash_table)
{    
    size_t i = 0;

    for (i = 0; i < hash_table->num_of_buckets; ++i)
    {
        DLLDestroy(hash_table->buckets[i]);
    }

    hash_table->buckets[0] = NULL;
}

void HTDestroy(hash_t *hash_table)
{
    assert(NULL != hash_table);

    DestroyTable(hash_table);
    free(hash_table); hash_table = NULL;
}

/********************************* Remove *************************************/

void HTRemove(hash_t *hash_table, const void *data_to_remove)
{
    size_t index = 0;
    dll_iter_t begin = NULL;
    dll_iter_t end = NULL;
    dll_iter_t to_remove = NULL;

    assert(NULL != hash_table);

    index = hash_table->hash_func(data_to_remove);
    begin = DLLBegin(hash_table->buckets[index]);
    end = DLLEnd(hash_table->buckets[index]);
    
    to_remove = DLLFind(begin, end, data_to_remove, 
                                            hash_table->is_match);
    DLLRemove(to_remove);
}

/********************************* Insert *************************************/

int HTInsert(hash_t *hash_table, void *data)
{
    size_t index = 0;
    dll_iter_t end = NULL;
    dll_iter_t inserted = NULL;

    assert(NULL != hash_table);

    index = hash_table->hash_func(data);
    end = DLLEnd(hash_table->buckets[index]);
    inserted = DLLPushFront(hash_table->buckets[index], data);
    if (DLLIsSameIter(inserted, end))
    {
        return 1;
    }

    return 0;
}

/********************************* Size ***************************************/

size_t HTSize(const hash_t *hash_table)
{
    size_t size = 0;
    size_t i = 0;
    
    assert(NULL != hash_table);

    for (i = 0; i < hash_table->num_of_buckets; ++i)
    {
        size += DLLSize(hash_table->buckets[i]);
    }
    
    return size;
}

/********************************* Is Empty ***********************************/

int HTIsEmpty(const hash_t *hash_table)
{
    size_t i = 0;
    int is_empty = 1;

    assert(NULL != hash_table);

    for (i = 0; (i < hash_table->num_of_buckets) && is_empty ; i++)
    {
        is_empty = DLLIsEmpty(hash_table->buckets[i]);
    }
    
    return is_empty;
}

/********************************* Find ***************************************/

void *HTFind(const hash_t *hash_table, const void *data_to_find)
{
    size_t index = 0;
    dll_iter_t begin = NULL;
    dll_iter_t end = NULL;
    dll_iter_t wanted_data = NULL;
    
    index = hash_table->hash_func(data_to_find);
    begin = DLLBegin(hash_table->buckets[index]);
    end = DLLEnd(hash_table->buckets[index]);
    
    wanted_data = DLLFind(begin, end, data_to_find, hash_table->is_match);
    if (DLLIsSameIter(wanted_data, end))
    {
        return NULL;
    }

    return DLLGetData(wanted_data);
}

void *HTAdvancedFind(const hash_t *hash_table, const void *data_to_find)
{
    size_t index = 0;
    dll_iter_t begin = NULL;
    dll_iter_t end = NULL;
    dll_iter_t wanted_iter = NULL;
    void *data = NULL;

    index = hash_table->hash_func(data_to_find);
    begin = DLLBegin(hash_table->buckets[index]);
    end = DLLEnd(hash_table->buckets[index]);
    
    wanted_iter = DLLFind(begin, end, data_to_find, hash_table->is_match);
    if (DLLIsSameIter(wanted_iter, end))
    {
        return NULL;
    }
    
    data = DLLGetData(wanted_iter);

    DLLRemove(wanted_iter);
    DLLPushFront(hash_table->buckets[index], data);

    return data;
}

/********************************* For Each ***********************************/

int HTForEach(hash_t *hash_table, act_t act, void *param)
{
    int status = 0;
    size_t i = 0;

    assert(NULL != hash_table);

    for (i = 0; (i < hash_table->num_of_buckets) && status; i++)
    {
        status = DLLForEach(DLLBegin(hash_table->buckets[i]), 
                            DLLEnd(hash_table->buckets[i]), act, param);   
    }
    
    return status;
}
