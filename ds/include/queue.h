#ifndef __OL73_QUEUE_H__
#define __OL73_QUEUE_H__

#include <stddef.h>	/* size_t */

#include "utils.h"

typedef struct queue queue_t;

/*
 * Create new queue
 * Returns pointer to the new queue
 * Time Complexity O(n)
 */
queue_t *QueueCreate();

/*
 * Remove the queue
 * Returns nothing
 * Time Complexity O(n)
 */
void QueueDestroy(queue_t *queue_p);

/*
 * Remove the current first in
 * Returns nothing
 * Time Complexity O(1)
 */
void QueueDequeue(queue_t *queue_p);

/*
 * Add to the queue
 * Returns nothing
 * Time Complexity O(n)
 */
void QueueEnqueue(queue_t *queue_p, void *data);

/*
 * Counts size of the queue
 * Returns length of queue
 * Time Complexity O(n)
 */
size_t QueueSize(const queue_t *queue_p);

/*
 * Checks if queue is empty
 * Returns 1 if queue is empty, 0 otherwise
 * Time Complexity O(1)
 */
int QueueIsEmpty(const queue_t *queue_p);

/*
 * Appends queue queue_p1 to queue queue_p2
 * Returns pointer to queue_p1
 * Time Complexity O(1)
 * Note: queue_p2 will become empty
 */
queue_t *QueueAppend(queue_t *queue_p1, queue_t *queue_2);

/*
 * Looks at the data of the first in
 * Returns pointer to data of the first in
 * Time Complexity O(1)
 */
void *QueuePeek(const queue_t *queue_p);

#endif	/* __OL73_QUEUE_H__ */
