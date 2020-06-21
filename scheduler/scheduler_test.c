#include <stdio.h>

#include "utils.h"
#include "tests.h"
#include "scheduler.h"

int TestSchedulerCreate();
int TestSchedulerSize();
int TestSchedulerRemove();
int TestSchedulerRun();
int TestSchedulerRunRemove();
int TestSchedulerRunAdd();
int TestSchedulerIsEmpty();
int TestSchedulerClear();

size_t failures = 0;
static scheduler_t *sched_param = NULL;

int main()
{
    puts("Testing Scheduler...");
    TEST(TestSchedulerCreate(), "TestSchedulerCreate");
    TEST(TestSchedulerSize(), "TestSchedulerSize");
    TEST(TestSchedulerRemove(), "TestSchedulerRemove");
    TEST(TestSchedulerRun(), "TestSchedulerRun");
    TEST(TestSchedulerRunRemove(), "TestSchedulerRunRemove");
    TEST(TestSchedulerRunAdd(), "TestSchedulerRunAdd");
	TEST(TestSchedulerIsEmpty(), "TestSchedulerIsEmpty");
	TEST(TestSchedulerClear(), "TestSchedulerClear");

    PRNT_STATUS(failures);

    return (failures);
}

int function(void *param)
{
    printf("%d\n", *(int *)param);

    return (0);
}

int function_stop(void *param)
{
    SchedulerStop((scheduler_t *)param);

    return (0);
}

int function_remove(void *param)
{
    SchedulerRemove(sched_param, *(u_id_t *)param);

    return (0);
}

int function_add(void *param)
{
	SchedulerAdd(sched_param, function, param, 1);

	return (0);
}

int TestSchedulerCreate()
{
    scheduler_t *sched = SchedulerCreate();

    SchedulerDestroy(sched);

    return (failures);
}

int TestSchedulerSize()
{
    size_t i = 0;
    int param[] = {0, 4, -1, 4};
    size_t interval[] = {1, 3, 2, 6};

    scheduler_t *sched = SchedulerCreate();

    for (i = 0; i < ARR_SIZE(interval); ++i)
    {
        SchedulerAdd(sched, function, &param[i], interval[i]);
        if (SchedulerSize(sched) != i + 1)
        {
            printf("\tFAILED at index %lu\n", i);
            printf("\t\tExpected %lu\n", i + 1);
            printf("\t\tReturned %lu\n", SchedulerSize(sched));
        }
    }

    SchedulerDestroy(sched);

    return (failures);
}

int TestSchedulerRemove()
{
    size_t i = 0;
    int param[] = {0, 4, -1, 4};
    size_t interval[] = {1, 3, 2, 6};
    u_id_t uids[4] = {{0}};

    scheduler_t *sched = SchedulerCreate();

    for (i = 0; i < ARR_SIZE(interval); ++i)
    {
        uids[i] = SchedulerAdd(sched, function, &param[i], interval[i]);
        if (SchedulerSize(sched) != i + 1)
        {
            printf("\tFAILED at index %lu\n", i);
            printf("\t\tExpected %lu\n", i + 1);
            printf("\t\tReturned %lu\n", SchedulerSize(sched));
        }
    }

    SchedulerRemove(sched, uids[2]);

    if (SchedulerSize(sched) != ARR_SIZE(interval) - 1)
    {
        printf("\tFAILED\n");
        printf("\t\tExpected %lu\n", ARR_SIZE(interval) - 1);
        printf("\t\tReturned %lu\n", SchedulerSize(sched));
    }

    SchedulerDestroy(sched);

    return (failures);
}

int TestSchedulerRun()
{
    size_t i = 0;
    int param[] = {1, 2, 3, 4};
    size_t interval[] = {1, 1, 5, 7};

    scheduler_t *sched = SchedulerCreate();

    for (i = 0; i < ARR_SIZE(interval) - 1; ++i)
    {
        SchedulerAdd(sched, function, &param[i], interval[i]);
        if (SchedulerSize(sched) != i + 1)
        {
            printf("\tFAILED at index %lu\n", i);
            printf("\t\tExpected %lu\n", i + 1);
            printf("\t\tReturned %lu\n", SchedulerSize(sched));
        }
    }

    SchedulerAdd(sched, function_stop, sched, interval[i]);

    SchedulerRun(sched);

    SchedulerDestroy(sched);

    return (failures);
}

int TestSchedulerRunRemove()
{
    int param[] = {6, 7, 8, 9,};
    size_t interval[] = {6, 3, 4, 7};
	u_id_t uids[4] = {{0}};

    scheduler_t *sched = SchedulerCreate();
    sched_param = sched;

	uids[0] = SchedulerAdd(sched, function, &param[0], interval[0]);

	uids[1] = SchedulerAdd(sched, function, &param[1], interval[1]);

    uids[2] = SchedulerAdd(sched, function_remove, &uids[1], interval[2]);

    uids[3] = SchedulerAdd(sched, function_stop, sched_param, interval[3]);

    SchedulerRun(sched);

    SchedulerDestroy(sched);

    return (failures);
}

int TestSchedulerRunAdd()
{
    int param[] = {6, 7, 8, 9, 10};
    size_t interval[] = {6, 3, 4, 7};
	u_id_t uids[4] = {{0}};

    scheduler_t *sched = SchedulerCreate();
    sched_param = sched;

	uids[0] = SchedulerAdd(sched, function, &param[0], interval[0]);

	uids[1] = SchedulerAdd(sched, function, &param[1], interval[1]);

    uids[2] = SchedulerAdd(sched, function_add, &param[4], interval[2]);

    uids[3] = SchedulerAdd(sched, function_stop, sched_param, interval[3]);

    SchedulerRun(sched);

    SchedulerDestroy(sched);

    return (failures);
}

int TestSchedulerIsEmpty()
{
    size_t i = 0;
    int param[] = {0, 4, -1, 4};
    size_t interval[] = {1, 3, 2, 6};
    int exp_is_empty[] = {0, 0, 0, 0};

    scheduler_t *sched = SchedulerCreate();

	if (SchedulerIsEmpty(sched) != 1)
    {
        printf("\tFAILED on line %d\n", __LINE__);
        printf("\t\tExpected %d\n", 1);
        printf("\t\tReturned %d\n", SchedulerIsEmpty(sched));
    }

    for (i = 0; i < ARR_SIZE(interval); ++i)
    {
        SchedulerAdd(sched, function, &param[i], interval[i]);
        if (SchedulerIsEmpty(sched) != exp_is_empty[i])
        {
            printf("\tFAILED at index %lu\n", i);
            printf("\t\tExpected %d\n", exp_is_empty[i]);
            printf("\t\tReturned %d\n", SchedulerIsEmpty(sched));
        }
    }

    SchedulerDestroy(sched);

    return (failures);
}

int TestSchedulerClear()
{
    size_t i = 0;
    int param[] = {0};
    size_t interval[] = {1};

    scheduler_t *sched = SchedulerCreate();

	if (SchedulerIsEmpty(sched) != 1)
    {
        printf("\tFAILED on line %d\n", __LINE__);
        printf("\t\tExpected %d\n", 1);
        printf("\t\tReturned %d\n", SchedulerIsEmpty(sched));
    }

    SchedulerAdd(sched, function, &param[i], interval[i]);

    if (SchedulerIsEmpty(sched) != 0)
    {
        printf("\tFAILED on line %d\n", __LINE__);
        printf("\t\tExpected %d\n", 0);
        printf("\t\tReturned %d\n", SchedulerIsEmpty(sched));
    }

	SchedulerClear(sched);

    if (SchedulerIsEmpty(sched) != 1)
    {
        printf("\tFAILED on line %d\n", __LINE__);
        printf("\t\tExpected %d\n", 1);
        printf("\t\tReturned %d\n", SchedulerIsEmpty(sched));
    }

    SchedulerDestroy(sched);

    return (failures);
}
