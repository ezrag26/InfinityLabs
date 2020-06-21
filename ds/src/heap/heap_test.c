#include <stdio.h> /* printf */

#include "heap.h"

#include "utils.h"
#include "tests.h"

int TestHeapCreateDestroy();
int TestHeapPush();
int TestHeapPushMany();
int TestHeapIsEmpty();
int TestHeapIsNotEmpty();
int TestHeapSizeEmpty();
int TestHeapSizeNotEmpty();
int TestHeapPeekSorted();
int TestHeapPeekUnSorted();
int TestHeapPopSorted();
int TestHeapPopUnSorted();
int TestHeapRemoveSorted();
int TestHeapRemoveUnSorted();

int main()
{
    size_t failures = 0;

    puts("Testing Heap...");
    TEST(TestHeapCreateDestroy(), "TestHeapCreateDestroy");
    TEST(TestHeapPush(), "TestHeapPush");
    TEST(TestHeapPushMany(), "TestHeapPushMany");
    TEST(TestHeapIsEmpty(), "TestHeapIsEmpty");
    TEST(TestHeapIsNotEmpty(), "TestHeapIsNotEmpty");
    TEST(TestHeapSizeEmpty(), "TestHeapSizeEmpty");
    TEST(TestHeapSizeNotEmpty(), "TestHeapSizeNotEmpty");
    TEST(TestHeapPeekSorted(), "TestHeapPeekSorted");
    TEST(TestHeapPeekUnSorted(), "TestHeapPeekUnSorted");
    TEST(TestHeapPopSorted(), "TestHeapPopSorted");
    TEST(TestHeapPopUnSorted(), "TestHeapPopUnSorted");
    TEST(TestHeapRemoveSorted(), "TestHeapRemoveSorted");
    TEST(TestHeapRemoveUnSorted(), "TestHeapRemoveUnSorted");

    PRNT_STATUS(failures);
    return (failures);
}

int HeapCmp(const void *data1, const void *data2, void *param)
{
    (void)param;

    if (*(int *)data1 < *(int *)data2)
    {
        return (-1);
    }
    else if (*(int *)data1 > *(int *)data2)
    {
        return (1);
    }
    else
    {
        return (0);
    }
}

int HeapIsMatch(const void *data, void *param)
{
    return (*(int *)data == *(int *)param);
}

int TestHeapCreateDestroy()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    heap_t *heap = NULL;

    for (i = 0; i < 5; ++i)
    {
        heap = HeapCreate(HeapCmp, param);
        HeapDestroy(heap);
    }

    return (failures);
}

int TestHeapPush()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {1};
    int push_return = 0;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        push_return = HeapPush(heap, &data[i]);
        REQUIRE(push_return, !=, 0, %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapPushMany()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {1, 2, 3, 4};
    int push_return = 0;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        push_return = HeapPush(heap, &data[i]);
        REQUIRE(push_return, !=, 0, %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapIsEmpty()
{
    size_t failures = 0;
    int *param = NULL;
    heap_t *heap = HeapCreate(HeapCmp, param);

    REQUIRE(HeapIsEmpty(heap), !=, 1, %d, %d);

    HeapDestroy(heap);
    return (failures);
}

int TestHeapIsNotEmpty()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {1, 2, 3, 4};
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
        REQUIRE(HeapIsEmpty(heap), !=, 0, %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapSizeEmpty()
{
    size_t failures = 0;
    int *param = NULL;
    heap_t *heap = HeapCreate(HeapCmp, param);

    REQUIRE(HeapSize(heap), !=, 0lu, %lu, %lu);

    HeapDestroy(heap);
    return (failures);
}

int TestHeapSizeNotEmpty()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {1, 2, 3, 4};
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
        REQUIRE(HeapSize(heap), !=, i + 1, %lu, %lu);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapPeekSorted()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {1, 2, 3, 4};
    int exp_peek[] = {1, 2, 3, 4};
    int *peek = NULL;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
        peek = HeapPeek(heap);
        REQUIRE(*(int *)peek, !=, exp_peek[i], %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapPeekUnSorted()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {4, 2, 6, 3};
    int exp_peek[] = {4, 4, 6, 6};
    int *peek = NULL;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
        peek = HeapPeek(heap);
        REQUIRE(*(int *)peek, !=, exp_peek[i], %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapPopSorted()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {1, 2, 3, 4};
    int exp_pop[] = {4, 3, 2, 1};
    int exp_peek[] = {4, 3, 2, 1};
    int pop = 0;
    int peek = 0;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        peek = *(int *)HeapPeek(heap);
        pop = *(int *)HeapPop(heap);
        REQUIRE(peek, !=, exp_peek[i], %d, %d);
        REQUIRE(pop, !=, exp_pop[i], %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapPopUnSorted()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {4, 2, 6, 3};
    int exp_pop[] = {6, 4, 3, 2};
    int exp_peek[] = {6, 4, 3, 2};
    int pop = 0;
    int peek = 0;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        peek = *(int *)HeapPeek(heap);
        pop = *(int *)HeapPop(heap);
        REQUIRE(peek, !=, exp_peek[i], %d, %d);
        REQUIRE(pop, !=, exp_pop[i], %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapRemoveSorted()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {-2, -1, 0, 1, 2, 3, 4, 5, 6};
    int to_remove[] = {6, -2, 3, 5, 0, 4, 2, -1, 1};
    int exp_peek[] = {6, 5, 5, 5, 4, 4, 2, 1, 1};
    int exp_remove[] = {6, -2, 3, 5, 0, 4, 2, -1, 1};
    int *peek = 0;
    int *remove = 0;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        peek = HeapPeek(heap);
        remove = HeapRemove(heap, HeapIsMatch, to_remove + i);
        REQUIRE(*(int *)peek, !=, exp_peek[i], %d, %d);
        REQUIRE(*(int *)remove, !=, exp_remove[i], %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}

int TestHeapRemoveUnSorted()
{
    size_t failures = 0;
    size_t i = 0;
    int *param = NULL;
    int data[] = {15, 3, 19, 30, 24, 0, -1, 20, 33, 18, 12, 26};
    int to_remove[] = {19, 33, 18, 15, 0, 30, 12, 26, -1, 24, 3, 20};
    int exp_peek[] = {33, 33, 30, 30, 30, 30, 26, 26, 24, 24, 20, 20};
    int exp_remove[] = {19, 33, 18, 15, 0, 30, 12, 26, -1, 24, 3, 20};
    int *peek = NULL;
    int *remove = NULL;
    heap_t *heap = HeapCreate(HeapCmp, param);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        HeapPush(heap, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        peek = HeapPeek(heap);
        remove = HeapRemove(heap, HeapIsMatch, to_remove + i);
        REQUIRE(*(int *)peek, !=, exp_peek[i], %d, %d);
        REQUIRE(*(int *)remove, !=, exp_remove[i], %d, %d);
    }

    HeapDestroy(heap);
    return (failures);
}
