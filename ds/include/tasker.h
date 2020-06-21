#ifndef __OL73_TASKER_H__
#define __OL73_TASKER_H__

#include <stddef.h> /* size_t */

#include "uid.h"

typedef struct task task_t;

/**
 * Should return 0 if it should stay in the list, or anything else if it should
 *      be removed
 */
typedef int (*task_func_t)(void *param);

/**
 * Creates a task
 * @param uid the uid of the task
 * @param func the function to be added, with return value as stated above
 * @param param anything the user would like
 * @param interval the total seconds until the function should be called again
 * returns pointer to the task, or NULL upon failure
 */
task_t *TaskerCreateTask(u_id_t uid, task_func_t func, void *param, size_t interval);

/**
 * Removes and frees memory of @param task
 * returns nothing
 */
void TaskerDestroy(task_t *task);

/**
 * Gets @param task's next call
 * Returns @param's next call
 */
time_t TaskerGetNextCall(task_t *task);

/**
 * Executes @param task
 * returns return value of the task's function. Any value returned not in
 *		accordance to the requirements as stated above may result in undefined
 *	    behavior
 */
int TaskerExecute(task_t *task);

/**
 * Gets @param task's UID
 * returns the task's UID
 */
u_id_t TaskerGetTaskUID(task_t *task);

/**
 * Calculates the difference in time between @param task2's next call and
 *      @param task1's next call
 * returns the difference in seconds
 */
unsigned int TaskerDiffTime(task_t *task1, task_t *task2);

/**
 * Updates @param task's next call based off its interval and the current time
 * returns 0 upon success, or -1 upon failure
 * interval cannot be larger than the max value of int
 */
int TaskerResetNextCall(task_t *task);

/**
 * Updates the @param task's next call based off its interval and its next call
 * returns 0 upon success, or -1 upon failure
 * interval cannot be larger than the max value of int
 */
int TaskerUpdateNextCall(task_t *task);

/**
 * Checks if @param task's UID is the same as a given @param uid
 * returns 1 if they are the same, 0 otherwise
 */
int TaskerUIDIsMatch(task_t *task, u_id_t uid);

#endif /* __OL73_TASKER_H__ */
