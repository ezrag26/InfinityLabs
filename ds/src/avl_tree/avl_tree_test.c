#include <stdio.h> /* printf */

#include "avl_tree.h"

#include "utils.h"
#include "tests.h"

#define COUNT (10)

typedef struct avl_node_s avl_node_t;

struct avl_node_s
{
	void *data;
	avl_node_t *children[2];
	size_t height;
} ;

struct avl_tree_s
{
	avl_node_t *root;
	avl_cmp_t avl_cmp;
} ;

void print2DUtil(avl_node_t *root, int space)
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

int TestAVLCreate();
int TestAVLRemove();
int TestAVLFindIs();
int TestAVLFindIsNot();
int TestAVLForEachSuccess();
int TestAVLForEachFail();
int TestAVLHeightIncrease();
int TestAVLHeightDecrease();
int TestAVLBalanceSorted();
int TestAVLBalanceUnsorted();

int main()
{
    size_t failures = 0;

    puts("Testing AVL Tree...");

    TEST(TestAVLCreate(), "AVLCreate");
    TEST(TestAVLRemove(), "AVLRemove");
    TEST(TestAVLFindIs(), "AVLFindIs");
    TEST(TestAVLFindIsNot(), "AVLFindIsNot");
    TEST(TestAVLForEachSuccess(), "AVLForEachSuccess");
    TEST(TestAVLForEachFail(), "AVLForEachFail");
    TEST(TestAVLHeightIncrease(), "AVLHeightIncrease");
    TEST(TestAVLHeightDecrease(), "AVLHeightDecrease");
    TEST(TestAVLBalanceSorted(), "AVLBalanceSorted");
    TEST(TestAVLBalanceUnsorted(), "AVLBalanceUnsorted");

    PRNT_STATUS(failures);

    return (failures);
}

static int compare(const void *data1, const void *data2)
{
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

int TestAVLCreate()
{
    size_t failures = 0;
    size_t i = 0;
    size_t j = 0;
    int datai[] = {5, 0, -1, 7, 20, 33, -5, -2, 16, 17, 30, 40};
    int dataj[] = {1, 19, 3, 21, -18, 14, 26, 91, 100, 54, 93, 25};
    int insert_reti[12] = {0};
    int insert_retj[12] = {0};
    void *data_ptr = NULL;

    avl_t *avl = AVLCreate(compare);

    REQUIRE(AVLIsEmpty(avl), !=, 1, %d, %d);
    REQUIRE(AVLSize(avl), !=, 0UL, %lu, %lu);

    for (i = 0, j = 0; i < ARR_SIZE(datai); ++i, ++j)
    {
        insert_reti[i] = AVLInsert(avl, &datai[i]);
        insert_retj[j] = AVLInsert(avl, &dataj[j]);
        REQUIRE(AVLIsEmpty(avl), !=, 0, %d, %d);
        REQUIRE(AVLSize(avl), !=, (i + j + 2), %lu, %lu);
    }

    /*print2DUtil(avl->root, 0);*/

    for (i = 0, j = (ARR_SIZE(insert_retj) - 1); i < ARR_SIZE(insert_reti); ++i, --j)
    {
        data_ptr = AVLFind(avl, &datai[i]);
        REQUIRE(*(int *)data_ptr, !=, datai[i], %d, %d);
        data_ptr = AVLFind(avl, &dataj[j]);
        REQUIRE(*(int *)data_ptr, !=, dataj[j], %d, %d);
    }

    AVLDestroy(avl);

    return (failures);
}

int TestAVLRemove()
{
    size_t failures = 0;
    size_t i = 0;
    size_t j = 0;
    int datai[] = {5, 0, -1, 7};
    int to_remove[] = {5, 3, 19, 1, 21, -1, 7, 0};
    int dataj[] = {1, 19, 3, 21};
    /*size_t exp_height[] = {2, 2, 2, 1, 1, 1, 0, 0};*/

    avl_t *avl = AVLCreate(compare);

    REQUIRE(AVLIsEmpty(avl), !=, 1, %d, %d);
    REQUIRE(AVLSize(avl), !=, 0UL, %lu, %lu);

    for (i = 0, j = 0; i < ARR_SIZE(datai); ++i, ++j)
    {
        AVLInsert(avl, &datai[i]);
        AVLInsert(avl, &dataj[j]);
        REQUIRE(AVLIsEmpty(avl), !=, 0, %d, %d);
        REQUIRE(AVLSize(avl), !=, (i + j + 2), %lu, %lu);
    }

    /*print2DUtil(avl->root, 0);*/

    for (i = 0; i < ARR_SIZE(to_remove); ++i)
    {
        AVLRemove(avl, &to_remove[i]);
        REQUIRE(AVLSize(avl), !=, (ARR_SIZE(to_remove) - i - 1), %lu, %lu);
        /*REQUIRE(AVLHeight(avl), !=, exp_height[i], %lu, %lu);*/
    }

    AVLDestroy(avl);

    return (failures);
}

int TestAVLFindIs()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int check[] = {21, 1, 0, -1, 5, 3, 7, 19};
    int ptr_indexes[] = {7, 4, 1, 2, 0, 6, 3, 5};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(check); ++i)
    {
        REQUIRE(AVLFind(avl, &check[i]), ==, NULL, %p, %p);
    }

    for (i = 0; i < ARR_SIZE(check); ++i)
    {
        REQUIRE(*(int *)AVLFind(avl, &check[i]), !=, data[ptr_indexes[i]], %d, %d);
    }

    AVLDestroy(avl);

    return (failures);
}

int TestAVLFindIsNot()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int check[] = {10, 6, 8, -2, 100, 35, 18, 11};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(check); ++i)
    {
        REQUIRE(AVLFind(avl, &check[i]), !=, NULL, %p, %p);
    }

    AVLDestroy(avl);

    return (failures);
}

int TestAVLForEachSuccess()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {5, 0, -1, 7, 1, 19, 3, 21};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
    }

    REQUIRE(AVLForEach(avl, act, &data[1]), !=, 0, %d, %d);

    AVLDestroy(avl);

    return (failures);
}

int TestAVLForEachFail()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {5, 0, -1, 7, 1, 19000, 3, 21};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
    }

    REQUIRE(AVLForEach(avl, act, &data[1]), !=, 1, %d, %d);

    AVLDestroy(avl);

    return (failures);
}

int TestAVLHeightIncrease()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {5, 0, -1, 7, 1, 19, 3, 21};
    size_t exp_height[] = {0, 1, 1, 2, 2, 2, 3, 3};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
        REQUIRE(AVLHeight(avl), !=, exp_height[i], %lu, %lu);
    }

    /*print2DUtil(avl->root, 0);*/

    AVLDestroy(avl);

    return (failures);
}

int TestAVLHeightDecrease()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {5, 0, -1, 7, 1, 19, 3, 21};
    int remove[] = {7, 1, 19, 5, 21, 3, 0, -1};
    size_t exp_height[] = {3, 2, 2, 2, 1, 1, 0};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
    }

    for (i = 0; i < ARR_SIZE(exp_height); ++i)
    {
        AVLRemove(avl, &remove[i]);
        REQUIRE(AVLHeight(avl), !=, exp_height[i], %lu, %lu);
    }

    /*print2DUtil(avl->root, 0);*/

    AVLDestroy(avl);

    return (failures);
}

int TestAVLBalanceSorted()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    size_t exp_height[] = {0, 1, 1, 2, 2, 2, 2, 3, 3};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
        REQUIRE(AVLHeight(avl), !=, exp_height[i], %lu, %lu);
    }

    /*print2DUtil(avl->root, 0);*/

    AVLDestroy(avl);

    return (failures);
}

int TestAVLBalanceUnsorted()
{
    size_t failures = 0;
    size_t i = 0;
    int data[] = {5, 2, 8, 10, 9, 3, 19, 20, 15};
    size_t exp_height[] = {0, 1, 1, 2, 2, 2, 3, 3, 3};

    avl_t *avl = AVLCreate(compare);

    for (i = 0; i < ARR_SIZE(data); ++i)
    {
        AVLInsert(avl, &data[i]);
        REQUIRE(AVLHeight(avl), !=, exp_height[i], %lu, %lu);
    }

    /*print2DUtil(avl->root, 0);*/

    AVLDestroy(avl);

    return (failures);
}
