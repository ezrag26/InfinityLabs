#include <stdio.h> /* printf */

#include "binary_search_tree.h"

#include "utils.h"
#include "tests.h"

#define COUNT (10)

typedef struct bst_node_s bst_node_t;

struct bst_node_s
{
    void *data;
    bst_node_t *children[2];
    bst_node_t *parent;
};

struct binary_search_tree_s
{
    bst_node_t sentinel;
    bst_cmp_t bst_cmp;
    void *param;
};

void print2DUtil(bst_node_t *root, int space)
{
    int i = 0;
    if (root == NULL)
        return;

    space += COUNT;

    print2DUtil(root->children[1], space);

    printf("\n");
    for (i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", *(int *)(root->data));

    print2DUtil(root->children[0], space);
}

int TestBSTCreate();
int TestBSTGetData();
int TestBSTRemove();
int TestBSTBegin();
int TestBSTFindIs();
int TestBSTFindIsNot();
int TestBSTForEachSuccess();
int TestBSTForEachFail();
int TestBSTNext();
int TestBSTPrev();
int TestBSTIsSameIteratorIs();

int main()
{
    size_t failures = 0;

    puts("Testing Binary Search Tree...");

    TEST(TestBSTCreate(), "BSTCreate");
    TEST(TestBSTGetData(), "BSTGetData");
    TEST(TestBSTRemove(), "BSTRemove");
    TEST(TestBSTBegin(), "BSTBegin");
    TEST(TestBSTFindIs(), "BSTFindIs");
    TEST(TestBSTFindIsNot(), "BSTFindIsNot");
    TEST(TestBSTForEachSuccess(), "BSTForEachSuccess");
    TEST(TestBSTForEachFail(), "BSTForEachFail");
    TEST(TestBSTNext(), "BSTNext");
    TEST(TestBSTPrev(), "BSTPrev");
    TEST(TestBSTIsSameIteratorIs(), "BSTIsSameIteratorIs");

    PRNT_STATUS(failures);

    return (failures);
}

static int compare(const void *data1, const void *data2, void *param)
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

static int act(void *data, void *param)
{
    int result = *(int *)data + *(int *)param;

    if (10000 > result)
    {
        return (0);
    }

    return (1);
}

int TestBSTCreate()
{
    size_t failures = 0;
    size_t i = 0;
    size_t j = 0;
    int parami[] = {5, 0, -1, 7, 20, 33, -5, -2, 16, 17, 30, 40};
    int paramj[] = {1, 19, 3, 21, -18, 14, 26, 91, 100, 54, 93, 25};
    bst_iter_t insert_ptrsi[12] = {NULL};
    bst_iter_t insert_ptrsj[12] = {NULL};
    void *data_ptr = NULL;

    bst_t *bst = BSTCreate(compare, &parami[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0, j = 0; i < ARR_SIZE(parami); ++i, ++j)
    {
        insert_ptrsi[i] = BSTInsert(bst, &parami[i]);
        insert_ptrsj[j] = BSTInsert(bst, &paramj[j]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + j + 2), %lu, %lu);
    }

    for (i = 0, j = 0; i < ARR_SIZE(insert_ptrsi); ++i, ++j)
    {
        REQUIRE(*(int *)BSTGetData(insert_ptrsi[i]), !=, parami[i], %d, %d);
        REQUIRE(*(int *)BSTGetData(insert_ptrsj[j]), !=, paramj[j], %d, %d);
    }

    /*print2DUtil(insert_ptrsi[0], 0);*/

    REQUIRE(*(int *)BSTGetData(BSTBegin(bst)), !=, -18, %d, %d);

    for (i = 0, j = (ARR_SIZE(insert_ptrsj) - 1); i < ARR_SIZE(insert_ptrsi); ++i, --j)
    {
        data_ptr = BSTRemove(insert_ptrsi[i]);
        REQUIRE(*(int *)data_ptr, !=, parami[i], %d, %d);
        data_ptr = BSTRemove(insert_ptrsj[j]);
        REQUIRE(*(int *)data_ptr, !=, paramj[j], %d, %d);

    }

    BSTDestroy(bst);

    return (failures);

}

int TestBSTGetData()
{
    size_t failures = 0;
    size_t i = 0;
    size_t j = 0;
    int parami[] = {5, 0, -1, 7};
    int paramj[] = {1, 19, 3, 21};
    bst_iter_t insert_ptrsi[4] = {NULL};
    bst_iter_t insert_ptrsj[4] = {NULL};

    bst_t *bst = BSTCreate(compare, &parami[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0, j = 0; i < ARR_SIZE(parami); ++i, ++j)
    {
        insert_ptrsi[i] = BSTInsert(bst, &parami[i]);
        insert_ptrsj[j] = BSTInsert(bst, &paramj[j]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + j + 2), %lu, %lu);
    }

    for (i = 0, j = 0; i < ARR_SIZE(insert_ptrsi); ++i, ++j)
    {
        REQUIRE(*(int *)BSTGetData(insert_ptrsi[i]), !=, parami[i], %d, %d);
        REQUIRE(*(int *)BSTGetData(insert_ptrsj[j]), !=, paramj[j], %d, %d);
    }

    BSTDestroy(bst);

    return (failures);
}

int TestBSTRemove()
{
    size_t failures = 0;
    size_t i = 0;
    size_t j = 0;
    int parami[] = {5, 0, -1, 7};
    int paramj[] = {1, 19, 3, 21};
    bst_iter_t insert_ptrsi[4] = {NULL};
    bst_iter_t insert_ptrsj[4] = {NULL};

    bst_t *bst = BSTCreate(compare, &parami[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0, j = 0; i < ARR_SIZE(parami); ++i, ++j)
    {
        insert_ptrsi[i] = BSTInsert(bst, &parami[i]);
        insert_ptrsj[j] = BSTInsert(bst, &paramj[j]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + j + 2), %lu, %lu);
    }

    for (i = 0, j = 0; i < ARR_SIZE(parami); ++i, ++j)
    {
        REQUIRE(*(int *)BSTRemove(insert_ptrsi[i]), !=, parami[i], %d, %d);
        REQUIRE(*(int *)BSTRemove(insert_ptrsj[j]), !=, paramj[j], %d, %d);
        REQUIRE(BSTSize(bst), !=, (ARR_SIZE(parami) + ARR_SIZE(paramj) - i - j - 2), %lu, %lu);
    }

    BSTDestroy(bst);

    return (failures);
}

int TestBSTBegin()
{
    size_t failures = 0;
    size_t i = 0;
    size_t j = 0;
    int parami[] = {5, 0, -1, 7};
    int paramj[] = {1, 19, 3, 21};
    bst_iter_t insert_ptrsi[4] = {NULL};
    bst_iter_t insert_ptrsj[4] = {NULL};

    bst_t *bst = BSTCreate(compare, &parami[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0, j = 0; i < ARR_SIZE(parami); ++i, ++j)
    {
        insert_ptrsi[i] = BSTInsert(bst, &parami[i]);
        insert_ptrsj[j] = BSTInsert(bst, &paramj[j]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + j + 2), %lu, %lu);
    }

    REQUIRE(*(int *)BSTGetData(BSTBegin(bst)), !=, -1, %d, %d);
    BSTRemove(insert_ptrsi[2]);
    REQUIRE(*(int *)BSTGetData(BSTBegin(bst)), !=, 0, %d, %d);
    BSTRemove(insert_ptrsi[1]);
    REQUIRE(*(int *)BSTGetData(BSTBegin(bst)), !=, 1, %d, %d);
    BSTRemove(insert_ptrsj[0]);
    REQUIRE(*(int *)BSTGetData(BSTBegin(bst)), !=, 3, %d, %d);
    BSTRemove(insert_ptrsj[2]);
    REQUIRE(*(int *)BSTGetData(BSTBegin(bst)), !=, 5, %d, %d);

    BSTDestroy(bst);

    return (failures);
}

int TestBSTFindIs()
{
    size_t failures = 0;
    size_t i = 0;
    int param[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int check[] = {21, 1, 0, -1, 5, 3, 7, 19};
    int ptr_indexes[] = {7, 4, 1, 2, 0, 6, 3, 5};
    bst_iter_t insert_ptrs[8] = {NULL};

    bst_t *bst = BSTCreate(compare, &param[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0; i < ARR_SIZE(param); ++i)
    {
        insert_ptrs[i] = BSTInsert(bst, &param[i]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + 1), %lu, %lu);
    }

    for (i = 0; i < ARR_SIZE(insert_ptrs); ++i)
    {
        REQUIRE((void *)BSTFind(bst, &check[i]), !=, (void *)insert_ptrs[ptr_indexes[i]], %p, %p);
    }

    BSTDestroy(bst);

    return (failures);
}

int TestBSTFindIsNot()
{
    size_t failures = 0;
    size_t i = 0;
    int param[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int check[] = {10, 6, 8, -2, 100, 35, 18, 11};
    bst_iter_t insert_ptrs[8] = {NULL};

    bst_t *bst = BSTCreate(compare, &param[i]);
    bst_iter_t end = BSTEnd(bst);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0; i < ARR_SIZE(param); ++i)
    {
        insert_ptrs[i] = BSTInsert(bst, &param[i]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + 1), %lu, %lu);
    }

    for (i = 0; i < ARR_SIZE(insert_ptrs); ++i)
    {
        REQUIRE((void *)BSTFind(bst, &check[i]), !=, (void *)end, %p, %p);
    }

    BSTDestroy(bst);

    return (failures);
}

int TestBSTForEachSuccess()
{
    size_t failures = 0;
    size_t i = 0;
    int param[] = {5, 0, -1, 7, 1, 19, 3, 21};

    bst_t *bst = BSTCreate(compare, &param[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0; i < ARR_SIZE(param); ++i)
    {
        BSTInsert(bst, &param[i]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + 1), %lu, %lu);
    }

    REQUIRE(BSTForEach(BSTBegin(bst), BSTEnd(bst), act, &param[1]), !=, 0, %d, %d);

    BSTDestroy(bst);

    return (failures);
}

int TestBSTForEachFail()
{
    size_t failures = 0;
    size_t i = 0;
    int param[] = {5, 0, -1, 7, 1, 19000, 3, 21};

    bst_t *bst = BSTCreate(compare, &param[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0; i < ARR_SIZE(param); ++i)
    {
        BSTInsert(bst, &param[i]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + 1), %lu, %lu);
    }

    REQUIRE(BSTForEach(BSTBegin(bst), BSTEnd(bst), act, &param[1]), !=, 1, %d, %d);

    BSTDestroy(bst);

    return (failures);
}

int TestBSTNext()
{
    size_t failures = 0;
    size_t i = 0;
    int param[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int check_index[] = {2, 1, 4, 6, 0, 3, 5, 7};
    bst_iter_t insert_ptrs[8] = {NULL};
    bst_iter_t current = NULL;

    bst_t *bst = BSTCreate(compare, &param[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0; i < ARR_SIZE(param); ++i)
    {
        insert_ptrs[i] = BSTInsert(bst, &param[i]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + 1), %lu, %lu);
    }

    /*print2DUtil(insert_ptrs[0], 0);*/

    current = BSTBegin(bst);
    REQUIRE(*(int *)BSTGetData(current), !=, *(int *)BSTGetData(insert_ptrs[check_index[0]]), %d, %d);

    for (i = 1; i < ARR_SIZE(insert_ptrs); ++i)
    {
        current = BSTNext(current);
        REQUIRE(*(int *)BSTGetData(current), !=, *(int *)BSTGetData(insert_ptrs[check_index[i]]), %d, %d);

    }

    BSTDestroy(bst);

    return (failures);
}

int TestBSTPrev()
{
    size_t failures = 0;
    size_t i = 0;
    int param[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int check_index[] = {2, 1, 4, 6, 0, 3, 5, 7};
    bst_iter_t insert_ptrs[8] = {NULL};
    bst_iter_t current = NULL;

    bst_t *bst = BSTCreate(compare, &param[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0; i < ARR_SIZE(param); ++i)
    {
        insert_ptrs[i] = BSTInsert(bst, &param[i]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + 1), %lu, %lu);
    }

    /*print2DUtil(insert_ptrs[0], 0);*/

    current = BSTPrev(BSTEnd(bst));
    REQUIRE(*(int *)BSTGetData(current), !=, *(int *)BSTGetData(insert_ptrs[check_index[7]]), %d, %d);

    for (i = ARR_SIZE(insert_ptrs) - 2; i < ARR_SIZE(insert_ptrs); --i)
    {
        current = BSTPrev(current);
        REQUIRE(*(int *)BSTGetData(current), !=, *(int *)BSTGetData(insert_ptrs[check_index[i]]), %d, %d);

    }

    BSTDestroy(bst);

    return (failures);
}

int TestBSTIsSameIteratorIs()
{
    size_t failures = 0;
    size_t i = 0;
    int param[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int check_index[] = {2, 1, 4, 6, 0, 3, 5, 7};
    bst_iter_t insert_ptrs[8] = {NULL};
    bst_iter_t current = NULL;

    bst_t *bst = BSTCreate(compare, &param[i]);

    REQUIRE(BSTIsEmpty(bst), !=, 1, %d, %d);
    REQUIRE(BSTSize(bst), !=, 0UL, %lu, %lu);

    for (i = 0; i < ARR_SIZE(param); ++i)
    {
        insert_ptrs[i] = BSTInsert(bst, &param[i]);
        REQUIRE(BSTIsEmpty(bst), !=, 0, %d, %d);
        REQUIRE(BSTSize(bst), !=, (i + 1), %lu, %lu);
    }

    /*print2DUtil(insert_ptrs[0], 0);*/

    current = BSTBegin(bst);

    for (i = 0; i < ARR_SIZE(insert_ptrs); ++i)
    {
        REQUIRE(BSTIsSameIterator(current, insert_ptrs[check_index[i]]), !=, 1, %d, %d);
        current = BSTNext(current);
    }

    BSTDestroy(bst);

    return (failures);
}
