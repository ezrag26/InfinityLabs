/*******************************************************************************
 * Date: 		22/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Shir
 * Satus: 		S
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert 		*/
#include <unistd.h> /* sleep		*/
#include <time.h>   /* time_t 		*/

#include "scheduler.h"
#include "tasker.h"
#include "priority_queue.h"
#include "utils.h"

struct scheduler
{
	pq_t *pq;
	int stop;
};

static unsigned int CompareTime(const void *data1, const void *data2, void *param)
{
	(void)(param);

	return (TaskerDiffTime((task_t *)data1, (task_t *)data2));
}

static int UIDIsMatch(const void *data1, const void *data2, void *param)
{
	(void)(data2);

	return (TaskerUIDIsMatch((task_t *)data1, *(u_id_t *)param));
}

scheduler_t *SchedulerCreate()
{

	scheduler_t *sched = (scheduler_t *)malloc(sizeof(scheduler_t));

	if (NULL == sched)
	{
		PRNT_ERR("Malloc allocation failed");
		return (NULL);
	}

	sched->pq = PQCreate((pq_cmp_t)CompareTime, NULL);

	if (NULL == sched->pq)
	{
		PRNT_ERR("Malloc allocation failed");
		free(sched); sched = NULL;
		return (NULL);
	}

	sched->stop = 0;

	return (sched);
}

void SchedulerDestroy(scheduler_t *sched)
{
	if (NULL != sched)
	{
		SchedulerClear(sched);
		PQDestroy(sched->pq);
		free(sched); sched = NULL;
	}
}

u_id_t SchedulerAdd(scheduler_t *sched, func_t func, void *param, size_t interval)
{
	task_t *task = NULL;
	u_id_t uid = UIDCreate();

	assert(NULL != sched);

	if (UIDIsBad(uid))
	{
		PRNT_ERR("Bad UID");
		return (BAD_UID);
	}

	task = TaskerCreateTask(uid, (task_func_t)func, param, interval);

	if (NULL == task)
	{
		PRNT_ERR("Error creating task");
		return (BAD_UID);
	}

	if (1 == PQPush(sched->pq, task))
	{
		PRNT_ERR("Error adding task");
		TaskerDestroy(task);
		return (BAD_UID);
	}

	return (uid);
}

int SchedulerRemove(scheduler_t *sched, u_id_t uid)
{
	task_t *task_to_remove = NULL;

	assert(NULL != sched);

	/* remove task if the uid requested to remove is found */
	task_to_remove = (task_t *)PQErase(sched->pq,
									  (pq_is_match_t)UIDIsMatch,
									  &uid);

	/* didn't find the task with requeted uid */
	if (NULL == task_to_remove)
	{
		return (1);
	}

	TaskerDestroy(task_to_remove);

	return (0);
}

static int InitScheduler(scheduler_t *sched)
{
	pq_t* new_pq = PQCreate((pq_cmp_t)CompareTime, NULL);
	task_t *popped_task = NULL;

	assert(NULL != sched);

	/**
	 * make new list with updated times in case user didn't run scheduler
	 * immediately after adding the tasks
	 */
	while (!SchedulerIsEmpty(sched))
	{
		popped_task = PQPop(sched->pq);
		if (-1 == TaskerResetNextCall(popped_task) ||
			1 == PQPush(new_pq, popped_task))
		{
			PRNT_ERR("Error initializing program");
			TaskerDestroy(popped_task);
			SchedulerClear(sched);
			PQDestroy(sched->pq);
			sched->pq = new_pq;
			SchedulerClear(sched);
			return (1);
		}
	}

	/* destroy old pq */
	SchedulerClear(sched);
	PQDestroy(sched->pq);

	/* sched points to new pq */
	sched->pq = new_pq;

	return (0);
}

static int Sleep(task_t *task)
{
	double sleep_time = 0;
	time_t current_time = time(NULL);

	if (-1 == current_time)
	{
		PRNT_ERR("Time Error");
		return (-1);
	}

	assert(NULL != task);

	/* check if task's next call has already passed */
	sleep_time = difftime(TaskerGetNextCall(task), current_time);

	/* next_call has passed, should run immediately */
	if (0 > sleep_time)
	{
		sleep_time = 0;
	}

	while (sleep_time != 0)
	{
		sleep_time = sleep((unsigned int)sleep_time);
	}

	return (0);
}

int SchedulerRun(scheduler_t *sched)
{
	task_t *current_task = NULL;
	int exe_return = 0;
	u_id_t uid = {0};

	assert(NULL != sched);

	if (1 == InitScheduler(sched))
	{
		PRNT_ERR("Error initializing program");
		return (1);
	}

	sched->stop = 0;

	while (sched->stop == 0 && !SchedulerIsEmpty(sched))
	{
		/* get current task and its uid */
		current_task = PQPeek(sched->pq);
		uid = TaskerGetTaskUID(current_task);

		/* error is sleeping */
		if (-1 == Sleep(current_task))
		{
			SchedulerClear(sched);
			PRNT_ERR("Time Error");
			return (1);
		}

		exe_return = TaskerExecute(current_task);

		/* find task with its uid and erase */
		current_task = PQErase(sched->pq, (pq_is_match_t)UIDIsMatch, &uid);

		/* check whether function should be put back into list or not */
		if (NULL != current_task) 			     /* task is still in the list */
		{
			switch (exe_return)
			{
				/* task should continue to run */
				case 0:

					/* error updating next call */
					if (-1 == TaskerUpdateNextCall(current_task))
					{
						SchedulerClear(sched);
						PRNT_ERR("Time Error");
						return (1);
					}

					if (1 == PQPush(sched->pq, current_task))
					{
						SchedulerClear(sched);
						TaskerDestroy(current_task);
						PRNT_ERR("Error adding task");
						return (1);
					}

					break;
				default:
					TaskerDestroy(current_task);
					break;
			}
		}
	}

	return (!sched->stop);
}

void SchedulerStop(scheduler_t *sched)
{
	assert(NULL != sched);

	sched->stop = 1;
}

size_t SchedulerSize(const scheduler_t *sched)
{
	assert(NULL != sched);

	return (PQSize(sched->pq));
}

int SchedulerIsEmpty(const scheduler_t *sched)
{
	assert(NULL != sched);

	return (PQIsEmpty(sched->pq));
}

void SchedulerClear(scheduler_t *sched)
{
	task_t *task_to_free = NULL;

	assert(NULL != sched);

	while (!SchedulerIsEmpty(sched))
	{
		task_to_free = PQPop(sched->pq);

		TaskerDestroy(task_to_free);
	}
}
