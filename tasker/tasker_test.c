#include <stdio.h>

#include "utils.h"
#include "tests.h"
#include "tasker.h"

int TestTaskerCreate();
int TestTaskerDiffTime();
int TestTaskerUIDIsMatch();
int TestTaskerExecute();

size_t failures = 0;

int main()
{
	puts("Testing Tasker...");
	TEST(TestTaskerCreate(), "TestTaskerCreate");
	TEST(TestTaskerDiffTime(), "TestTaskerDiffTime");
	TEST(TestTaskerUIDIsMatch(), "TestTaskerUIDIsMatch");
	TEST(TestTaskerExecute(), "TestTaskerExecute");

	PRNT_STATUS(failures);

	return 0;
}

int func2(void *param)
{
	printf("Task: %d\n", *(int *)param);

	return (0);
}

int func(void *param)
{
	u_id_t uid = UIDCreate();
	size_t interval = 5;
	int num = 30;
	task_t *task = NULL;

	if (UIDIsBad(uid))
	{
		return (1);
	}

	task = TaskerCreateTask(uid, func2, &num, interval);

	num += *(int *)param;

	TaskerExecute(task);

	TaskerDestroy(task);

	return (0);
}

int TestTaskerCreate()
{
	u_id_t uid = UIDCreate();
	int param = 1;
	size_t interval = 5;

	task_t *task = NULL;

	if (UIDIsBad(uid))
	{
		return (1);
	}

	task = TaskerCreateTask(uid, func2, &param, interval);

	if (UIDIsSame(TaskerGetTaskUID(task), uid) != 1)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", 1);
		printf("\t\tReturned: %d\n", UIDIsSame(TaskerGetTaskUID(task), uid));
		++failures;
	}

	TaskerDestroy(task);

	return (failures);
}

int TestTaskerDiffTime()
{
	u_id_t uid1 = UIDCreate();
	u_id_t uid2 = UIDCreate();
	int param = 1;
	size_t interval[] = {1, 3, 5};

	task_t *task1 = NULL;
	task_t *task2 = NULL;

	if (UIDIsBad(uid1))
	{
		return (1);
	}

	if (UIDIsBad(uid2))
	{
		return (1);
	}

	task1 = TaskerCreateTask(uid1, func2, &param, interval[0]);
	task2 = TaskerCreateTask(uid2, func2, &param, interval[1]);

	if (TaskerDiffTime(task1, task1) != interval[0] - interval[0])
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %lu\n", interval[0] - interval[0]);
		printf("\t\tReturned: %d\n", TaskerDiffTime(task1, task1));
		++failures;
	}

	TaskerDestroy(task1);
	TaskerDestroy(task2);

	return (failures);
}

int TestTaskerUIDIsMatch()
{
	u_id_t uid1 = UIDCreate();
	u_id_t uid2 = UIDCreate();
	int param = 1;
	size_t interval[] = {3, 1, 5};

	task_t *task1 = NULL;
	task_t *task2 = NULL;

	if (UIDIsBad(uid1))
	{
		return (1);
	}

	if (UIDIsBad(uid2))
	{
		return (1);
	}

	task1 = TaskerCreateTask(uid1, func2, &param, interval[0]);
	task2 = TaskerCreateTask(uid2, func2, &param, interval[1]);

	if (TaskerUIDIsMatch(task1, uid2) != 0)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", 0);
		printf("\t\tReturned: %d\n", TaskerUIDIsMatch(task1, uid2));
		++failures;
	}

	if (TaskerUIDIsMatch(task1, uid1) != 1)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", 1);
		printf("\t\tReturned: %d\n", TaskerUIDIsMatch(task1, uid1));
		++failures;
	}

	if (TaskerUIDIsMatch(task2, uid2) != 1)
	{
		printf("\tFAILED on line %d\n", __LINE__);
		printf("\t\tExpected: %d\n", 1);
		printf("\t\tReturned: %d\n", TaskerUIDIsMatch(task2, uid2));
		++failures;
	}

	TaskerDestroy(task1);
	TaskerDestroy(task2);

	return (failures);
}

int TestTaskerExecute()
{
	u_id_t uid1 = UIDCreate();
	u_id_t uid2 = UIDCreate();
	int param[] = {5, 8};
	size_t interval[] = {3, 1, 5};

	task_t *task1 = NULL;
	task_t *task2 = NULL;

	if (UIDIsBad(uid1))
	{
		return (1);
	}

	if (UIDIsBad(uid2))
	{
		return (1);
	}

	task1 = TaskerCreateTask(uid1, func, &param[0], interval[0]);
	task2 = TaskerCreateTask(uid2, func, &param[1], interval[1]);

	TaskerExecute(task1);

	TaskerDestroy(task1);
	TaskerDestroy(task2);

	return (failures);
}
