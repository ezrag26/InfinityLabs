#ifndef __OL73_SCHEDULER_H__
#define __OL73_SCHEDULER_H__

#include <stddef.h> /* size_t */

#include "uid.h"

/******************************************************************************/

typedef struct scheduler scheduler_t;

/****************************** User Functions ********************************/

/**
 * Must return 0 if it should stay in the task list, or anything else if it
 *      should be removed
 */
typedef int (*func_t)(void *param);

/******************************************************************************/

/**
 * Creates a scheduler
 * Returns a pointer to the scheduler, or NULL upon failure
 * Time Complexity: O(1) amortized
 */
scheduler_t *SchedulerCreate();

/**
 * Destorys and frees memory of @param sched
 * Returns nothing
 * Time Complexity: O(n)
 */
void SchedulerDestroy(scheduler_t *sched);

/**
 * Adds a task to @param sched
 * @param func user function with return value as stated above
 * @param param additional input
 * @param interval number of total seconds until the function should be called
 * 		again number (0, max value of unsigned int]
 * Returns the task's uid, or BAD_UID upon failure
 * Time Complexity: O(n)
 */
u_id_t SchedulerAdd(scheduler_t *sched, func_t func, void *param, size_t interval);

/**
 * Removes and frees memory of a task with @param uid in @param sched
 * Returns 0 if the task was found and removed, 1 if it wasn't in the scheduler
 * Time Complexity: O(n)
 */
int SchedulerRemove(scheduler_t *sched, u_id_t uid);

/*
 * Runs @param sched based on added tasks
 * A full cycle of running is assumed to take place within 1 second. There may
 *      be a delay if too many tasks are running, or if a task takes a long time
 *		to run. Any task not run on time will run immediatey when its turn comes
 * Returns 0 on success, 1 on failure. Upon any failure, the scheduler is
 * 		cleared and can be refilled at user's wish, or destroyed when finished
 * Time Complexity: O(inifnity)
 */
int SchedulerRun(scheduler_t *sched);

/*
 * Stops @param sched from running
 * Returns nothing
 * Time Complexity: O(1)
 */
void SchedulerStop(scheduler_t *sched);

/*
 * Checks the number of tasks in @param sched
 * Returns number of tasks in sched
 * Time Complexity: O(n)
 */
size_t SchedulerSize(const scheduler_t *sched);

/*
 * Checks if @param sched is empty
 * Returns 1 if it is empty, 0 otherwise
 * Time Complexity: O(1)
 */
int SchedulerIsEmpty(const scheduler_t *sched);

/*
 * Removes and frees all tasks within @param sched
 * scheduler is can be refilled at user's wish, or destroyed when finished
 * Returns nothing
 * Time Complexity: O(n)
 */
void SchedulerClear(scheduler_t *sched);

#endif /* __OL73_SCHEDULER_H__ */
