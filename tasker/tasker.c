/*******************************************************************************
 * Date: 		22/9/2019
 * Developer:	Ezra Gordon
 * Reviewer:	Shir
 * Satus: 		S
 ******************************************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert 		*/
#include <time.h>   /* time_t 		*/

#include "tasker.h"
#include "utils.h"

struct task
{
	u_id_t uid;
	task_func_t func;
	void *param;
	size_t interval;
	time_t next_call;
};

task_t *TaskerCreateTask(u_id_t uid, task_func_t func, void *param, size_t interval)
{
	task_t *task = (task_t *)malloc(sizeof(task_t));

	assert(NULL != func);

	if (NULL == task)
	{
		PRNT_ERR("Malloc allocation failed");
		return (NULL);
	}

	task->uid = uid;
	task->func = func;
	task->param = param;
	task->interval = interval;

	/* error in rerieving current time */
	if (-1 == TaskerResetNextCall(task))
	{
		PRNT_ERR("Time Error");
		TaskerDestroy(task);
		return (NULL);
	}

	return (task);
}

void TaskerDestroy(task_t *task)
{
	if (NULL != task)
	{
		free(task); task = NULL;
	}
}

time_t TaskerGetNextCall(task_t *task)
{
	assert(NULL != task);

	return (task->next_call);
}

int TaskerExecute(task_t *task)
{
	assert(NULL != task);

	return (task->func(task->param));
}

u_id_t TaskerGetTaskUID(task_t *task)
{
	assert(NULL != task);

	return (task->uid);
}

static time_t CalculateNextCall(time_t time, size_t interval)
{
	struct tm *tmp = NULL;

	/* to perform arithmetic operations on time_t variables */
	tmp = localtime(&time);

	if (NULL == tmp)
	{
		PRNT_ERR("Time Error");
		return (-1);
	}

	/* add the interval to current number of seconds since Epoch */
	tmp->tm_sec += (int)(interval);

	return (mktime(tmp));
}

int TaskerResetNextCall(task_t *task)
{
	assert(NULL != task);

	task->next_call = CalculateNextCall(time(NULL), task->interval);

	if (-1 == task->next_call)
	{
		PRNT_ERR("Time Error");
		return (-1);
	}

	return (0);
}

int TaskerUpdateNextCall(task_t *task)
{
	assert(NULL != task);

	task->next_call = CalculateNextCall(task->next_call, task->interval);

	if (-1 == task->next_call)
	{
		PRNT_ERR("Time Error");
		return (-1);
	}

	return (0);
}

unsigned int TaskerDiffTime(task_t *task1, task_t *task2)
{
	return ((unsigned int)difftime(task2->next_call, task1->next_call));
}

int TaskerUIDIsMatch(task_t *task, u_id_t uid)
{
	return (UIDIsSame(task->uid, uid));
}
