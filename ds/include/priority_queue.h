/*******************************************************************************
 * Date: 		15/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Erez
 * Satus: 		S
 ******************************************************************************/

#ifndef __OL73_PRIORITY_QUEUE_H__
#define __OL73_PRIORITY_QUEUE_H__

#include <stddef.h> /* size_t */

/*
 * @param pq is a pointer to the priorirty queue
 */

typedef struct p_queue pq_t;

/*
 * Compare function for the priorirty queue's order
 * With a given param, it should return a negative number if data1 has less
 * 		priority over data2 with a given given param, 0 if they they are the
 * 		same, and a positive number if data1 has more priority over data2
 */
typedef int (*pq_cmp_t)(const void *data1, const void *data2, void *param);

/*
 * Checks if data satisifes a condition with a given param
 * Should return 1 upon a successful match, 0 upon a failure
 */
typedef int (*pq_is_match_t)(const void *data, void *param);

/*
 * Creates priority queue with a given compare function and param
 * @param compare see typedef pq_cmp_t
 * @param param the param used in the compare function
 * Returns: pointer to priority queue, or NULL if failed
 * Time Complexity: O(1) amortized
 */
pq_t *PQCreate(pq_cmp_t compare, void *param);

/*
 * Destroys priority queue pq and frees memory
 * Returns: nothing
 * Time Complexity: O(n)
 */
void PQDestroy(pq_t *pq);

/*
 * Adds element to priority queue pq with given data
 * @param data A pointer to the data to be inserted
 * Returns: 0 upon success, 1 upon failure
 * Time Complexity: O(n)
 */
int PQPush(pq_t *pq, void *data);

/*
 * Removes first element in priority queue pq
 * Returns: pointer to the pop'd element's data
 * Using PQPush on an empty list will result in undefined behavior
 * Time Complexity: O(1)
 */
void *PQPop(pq_t *pq);

/*
 * Finds data of the first element in priority queue pq
 * Returns: pointer to the first element's data
 * Using PQPeek on an empty list will result in undefined behavior
 * Time Complexity: O(1)
 */
void *PQPeek(const pq_t *pq);

/*
 * Finds current size of priority queue pq
 * Returns: size of pq
 * Time Complexity: O(n)
 */
size_t PQSize(const pq_t *pq);

/*
 * Checks if priority queue pq is empty
 * Returns: 1 if pq is empty, 0 otherwise
 * Time Complexity: O(1)
 */
int PQIsEmpty(const pq_t *pq);

/*
 * Removes all elements stored within priority queue pq and frees the allocated
 * 		memory
 * All data within the queue will be lost
 * Returns: nothing
 * Time Complexity: O(n)
 */
void PQClear(pq_t *pq);

/*
 * Erases the first element in priority queue pq that satisfies a given
 *		is_match function
 * @param is_match see typedef pq_is_match_t
 * @param param The param used in is_match
 * Returns: pointer to data of element erased
 * Time Complexity: O(n)
 */
void *PQErase(pq_t *pq, pq_is_match_t is_match, void *param);

#endif /* __OL73_PRIORITY_QUEUE_H__ */
