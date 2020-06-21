#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h> /*size_t */


typedef struct hash_table hash_t;

typedef size_t (*hash_func_t)(const void *key);

/* typedef for the is match function of the hash table. is match
   returns 1 indicating a match and 0 otherwise */
typedef int (*hash_is_match_t)(const void *data, const void *data_to_find);

/* typedef for the hash_act_t function for ForEach, act function must return
    0 for success and anything else for failure*/
typedef int (*hash_act_t)(void *data, void* param);

/**
 * Creates new hash table
 * @param hash_func
 * @param is_match func for find and remove
 * @param num_of_buckets
 * @return ptr to new hash table, returns NULL on error
 * @complexity O(k) when k is number of buckets
 */
hash_t *HTCreate(hash_func_t hash_func, hash_is_match_t is_match, size_t num_of_buckets);

/**
 * Destroys hash table
 * @param hash ptr to hash table
 * @complexity O(n)
 */
void HTDestroy(hash_t *hash);

/**
 * Inserts new data to hash table.
 * @param hash ptr to hash table.
 * @param data ptr to data.
 * @return 0 if insert succeed, and non zero otherwise.
 * @complexity O(1)
 */
int HTInsert(hash_t *hash, void *data);

/**
 * Removes data from hash table.
 * @param hash ptr to hash table.
 * @param ptr to data in hash table.
 * @complexity O(1)
 */
void HTRemove(hash_t *hash, const void *data);

/**
 * Counts how many entries are in the hash table.
 * @param hash ptr to hash table.
 * @return size of hash table.
 * @complexity O(n)
 */
size_t HTSize(const hash_t *hash);

/**
 * Checks if the hash table is empty.
 * @param hash ptr to hash table.
 * @return 1 if empty, 0 otherwise.
 * @complexity O(k) when k is number of buckets
 */
int HTIsEmpty(const hash_t *hash);

/**
 * Finds data in the hash table according to the is match function.
 * @param hash ptr to hash table.
 * @param data_to_find ptr to data
 * @return ptr to data in the hash table, returns NULL if did not find.
 * @complexity O(1)
 */
void *HTFind(const hash_t *hash, const void *data_to_find);

/**
 * Act on each data in the hash table.
 * @param hash ptr to hash table.
 * @param act ptr to action function
 * @param param ptr to parameters to action function
 * @return 0 if succesfull. If a call to act failed returns immediately  the
 *  act return value.
 * @complexity O(n)
 */
int HTForEach(hash_t *hash, hash_act_t act, void *param);



#endif /* __HASH_TABLE_H__*/
