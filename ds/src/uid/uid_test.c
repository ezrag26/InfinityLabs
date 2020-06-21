#include <stdio.h>  /* printf */
#include <stddef.h> /* size_t */

#include "uid.h"
#include "utils.h"
#include "tests.h"

int TestUIDCreate();
int TestUIDIsSame();
int TestUIDIsBadValid();
int TestUIDIsBadInvalid();

size_t failures = 0;

int main()
{
    puts("Testing UID...");
    TEST(TestUIDCreate(), "UIDCreate");
    TEST(TestUIDIsSame(), "UIDIsSame");
    TEST(TestUIDIsBadValid(), "UIDIsBadValid");
    TEST(TestUIDIsBadInvalid(), "UIDIsBadInvalid");

    PRNT_STATUS(failures);

    return (failures);
}

int TestUIDCreate()
{
    size_t i = 0;
    u_id_t uid_nums[5] = {{0}};


    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
        uid_nums[i] = UIDCreate();
    }


    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
        if (uid_nums[i].num != (i + 1))
        {
            printf("\tFAILED\n");
            printf("\t\tExpected: %lu\n", (i + 1));
            printf("\t\tReturned: %lu\n", uid_nums[i].num);
            ++failures;
        }
        /*
        printf("Num: %lu\n", uid_nums[i].num);
        printf("Time: %lu\n", uid_nums[i].timestamp);
        printf("PID: %d\n", uid_nums[i].pid);
		*/
    }

    return (failures);
}

int TestUIDIsSame()
{
    size_t i = 0;
    u_id_t uid_nums[5] = {{0}};


    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
        uid_nums[i] = UIDCreate();
    }


    for (i = 1; i < ARR_SIZE(uid_nums); ++i)
    {
        if (UIDIsSame(uid_nums[i - 1], uid_nums[i]) != 0)
        {
            printf("\tFAILED\n");
            printf("\t\tExpected: %d\n", 0);
            printf("\t\tReturned: %d\n", UIDIsSame(uid_nums[i - 1], uid_nums[i]));
            ++failures;
        }

        if (UIDIsSame(uid_nums[i - 1], uid_nums[i - 1]) != 1)
        {
            printf("\tFAILED\n");
            printf("\t\tExpected: %d\n", 1);
            printf("\t\tReturned: %d\n", UIDIsSame(uid_nums[i - 1], uid_nums[i - 1]));
            ++failures;
        }
    }

    return (failures);
}

int TestUIDIsBadValid()
{
    size_t i = 0;
    u_id_t uid_nums[5] = {{0}};


    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
        uid_nums[i] = UIDCreate();
    }


    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
        if (UIDIsBad(uid_nums[i]) != 1 && uid_nums[i].timestamp == -1)
        {
            printf("\tFAILED\n");
            printf("\t\tExpected: %d\n", 0);
            printf("\t\tReturned: %d\n", UIDIsSame(uid_nums[i - 1], uid_nums[i]));
            ++failures;
        }

        if (UIDIsBad(uid_nums[i]) == 1 && uid_nums[i].timestamp != -1)
        {
            printf("\tFAILED\n");
            printf("\t\tExpected: %d\n", 0);
            printf("\t\tReturned: %d\n", UIDIsSame(uid_nums[i - 1], uid_nums[i]));
            ++failures;
        }
    }

    return (failures);
}

int TestUIDIsBadInvalid()
{
    size_t i = 0;
    u_id_t uid_nums[5] = {{0}};


    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
        uid_nums[i] = UIDCreate();
    }

    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
    	uid_nums[i].num = 0;
        uid_nums[i].timestamp = -1;
        uid_nums[i].pid = 0;
    }


    for (i = 0; i < ARR_SIZE(uid_nums); ++i)
    {
        if (UIDIsBad(uid_nums[i]) != 1)
        {
            printf("\tFAILED\n");
            printf("\t\tExpected: %d\n", 1);
            printf("\t\tReturned: %d\n", UIDIsBad(uid_nums[i]));
            ++failures;
        }
    }

    return (failures);
}
