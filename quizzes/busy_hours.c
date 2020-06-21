#include <stdio.h> /* printf */

#include "utils.h"
#include "tests.h"

#define DAY_HOURS (24)

int BusyHours(int *arrival, int *exit, size_t size);
int TestBusyHours();
int TestBusyHoursEmpty();

int main()
{
    size_t failures = 0;

    puts("Testing Busy Hours...");
    TEST(TestBusyHours(), "TestBusyHours");
    /*TEST(TestBusyHoursEmpty(), "TestBusyHoursEmpty");*/

    PRNT_STATUS(failures);
    return (failures);
}

int BusyHours(int *arrival, int *exit, size_t size)
{
    size_t buffer[DAY_HOURS] = {0};
    size_t max = 0;
    int result = 0;
    size_t i = 0;
    size_t j = 0;

    for (i = 0; i < size; ++i)
    {
        for (j = arrival[i]; j < (size_t)exit[i]; ++j)
        {
            buffer[j] += 1;
        }
    }

    for (i = 0; i < DAY_HOURS; ++i)
    {
        if (buffer[i] > max)
        {
            max = buffer[i];
        }
    }

    for (i = 0; i < DAY_HOURS; ++i)
    {
        if (buffer[i] == max)
        {
            result |= (1 << i);
        }
    }

    return (result);
}

int TestBusyHours()
{
    size_t failures = 0;
    int arrivals[] = {1, 2, 9, 5, 5};
    int exits[] =    {5, 4, 12, 9, 12};
    int exp_result = 4076;
    size_t size = ARR_SIZE(arrivals);

    int returned = BusyHours(arrivals, exits, size);

    REQUIRE(returned, !=, exp_result, %d, %d);
    return (failures);
}

int TestBusyHoursEmpty()
{
    size_t failures = 0;
    int arrivals[] = {0};
    int exits[] =    {0};
    int exp_result = 0;
    size_t size = ARR_SIZE(arrivals);

    int returned = BusyHours(arrivals, exits, size);

    REQUIRE(returned, !=, exp_result, %d, %d);
    return (failures);
}
