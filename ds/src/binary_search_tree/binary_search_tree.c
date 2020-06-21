/*******************************************************************************
 * Date: 		15/10/2019
 * Developer:	Ezra Gordon
 * Reviewer:    Dan
 * Satus: 		S
 ******************************************************************************/

#include <stdlib.h> /* alloc family, free */
#include <assert.h> /* assert             */

#include "binary_search_tree.h"

#include "utils.h"

#define DEADBEEF ((void *)0xDEADBEEF)

typedef enum {LEFT, RIGHT} child_side_t;

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

/*############################# Helper Functions ##############################*/

static bst_node_t *InitializeNode(bst_node_t *node,
                                  bst_node_t *parent,
                                  void *data)
{
    assert(NULL != node);

    node->data = data;
    node->children[LEFT] = NULL;
    node->children[RIGHT] = NULL;
    node->parent = parent;

    return (node);
}

static bst_iter_t NodeToIter(bst_node_t *node)
{
    return ((bst_iter_t)node);
}

static bst_node_t *IterToNode(bst_iter_t iter)
{
    return ((bst_node_t *)iter);
}

static bst_node_t *FindEdgeChild(bst_node_t *node, child_side_t ORIGINATING_SIDE)
{
    while (NULL != node->children[ORIGINATING_SIDE])
    {
        node = node->children[ORIGINATING_SIDE];
    }

    return (node);
}

static void BSTRearrangeNodes(bst_node_t *cur_node,
                              bst_node_t *new_parent,
                              bst_node_t *new_parent_child,
                              bst_node_t *cur_node_child,
                              child_side_t ORIGINATING_SIDE)
{
    if (NULL == new_parent_child)
    {
        new_parent->children[ORIGINATING_SIDE] = cur_node_child;
        cur_node_child->parent = new_parent;
    }
    else if (NULL == cur_node_child)
    {
        new_parent->children[ORIGINATING_SIDE] = new_parent_child;
        new_parent_child->parent = new_parent;
    }
    else
    {
        cur_node = new_parent_child;

        /* while there's a child on the original side side, go to that child */
        cur_node = FindEdgeChild(cur_node, ORIGINATING_SIDE);

        new_parent->children[ORIGINATING_SIDE] = new_parent_child;
        new_parent_child->parent = new_parent;

        cur_node->children[ORIGINATING_SIDE] = cur_node_child;
        cur_node_child->parent = cur_node;
    }
}

static void BSTRemoveDanglingPointers(bst_node_t *to_remove)
{
    to_remove->parent = NULL;
    to_remove->children[RIGHT] = NULL;
    to_remove->children[LEFT] = NULL;
    to_remove->data = NULL;
}

static bst_node_t *FindEnd(bst_node_t *cur_node, child_side_t DIRECTION)
{
    child_side_t OPP_DIRECTION = -(DIRECTION - 1);

    /* go to the direction side's child */
    cur_node = cur_node->children[DIRECTION];

    /* while there is a child on the opp direction side, go to that child */
    cur_node = FindEdgeChild(cur_node, OPP_DIRECTION);

    return (NodeToIter(cur_node));
}

/*############################## User Functions ##############################*/

/********************************* BSTCreate **********************************/

bst_t *BSTCreate(bst_cmp_t bst_cmp, void *param)
{
    bst_t *bst = (bst_t *)malloc(sizeof(bst_t));

    if (NULL == bst)
    {
        PRNT_ERR("Memory allocation error");
        return (NULL);
    }

    /* sentinel initialization */
    bst->sentinel.data = DEADBEEF;
    bst->sentinel.children[LEFT] = NULL;
    bst->sentinel.children[RIGHT] = &(bst->sentinel);
    bst->sentinel.parent = DEADBEEF;

    bst->bst_cmp = bst_cmp;
    bst->param = param;

    return (bst);
}

/********************************* BSTDestroy *********************************/

void BSTDestroy(bst_t *bst)
{
    bst_iter_t cur_node = NULL;
    bst_iter_t next_node = NULL;
    bst_iter_t sentinel = NULL;

    assert (NULL != bst);

    cur_node = BSTBegin(bst);
    sentinel = BSTEnd(bst);

    /* while haven't reached sentinel, destroy the node */
    while (!BSTIsSameIterator(cur_node, sentinel))
    {
        next_node = BSTNext(cur_node);

        BSTRemove(cur_node);

        cur_node = next_node;
    }

    free(bst); bst = NULL;
}

/********************************* BSTInsert **********************************/

bst_iter_t BSTInsert(bst_t *bst, void *data)
{
    bst_node_t *node = NULL;
    bst_node_t *cur_node = NULL;
    bst_iter_t end = NULL;
    child_side_t child_side = 0;

    assert(NULL != bst);

    end = BSTEnd(bst);

    cur_node = IterToNode(end);

    /* while not inserted */
    while (NULL != cur_node->children[child_side])
    {
        int cmp_return = bst->bst_cmp(cur_node->children[child_side]->data,
                                      data,
                                      bst->param);
        cur_node = cur_node->children[child_side];

        /* RIGHT if greater than, LEFT is less than */
        child_side = (0 > cmp_return);

        if (0 == cmp_return)
        {
            free(node); node = NULL;
            return (end);
        }
    }

    node = (bst_node_t *)malloc(sizeof(bst_node_t));

    if (NULL == node)
    {
        PRNT_ERR("Memory allocation error");
        return (end);
    }

    cur_node->children[child_side] = InitializeNode(node, cur_node, data);

    return (NodeToIter(cur_node->children[child_side]));
}

/********************************* BSTRemove **********************************/

void *BSTRemove(bst_iter_t iter)
{
    bst_node_t *cur_node = NULL;
    bst_node_t *parent = NULL;
    bst_node_t *to_remove = NULL;
    bst_node_t *right_child = NULL;
    bst_node_t *left_child = NULL;
    void *data = NULL;

    assert(NULL != IterToNode(iter));

    data = BSTGetData(iter);
    to_remove = IterToNode(iter);
    cur_node = to_remove;
    right_child = cur_node->children[RIGHT];
    left_child = cur_node->children[LEFT];
    parent = cur_node->parent;

    /* has no children */
    if (NULL == left_child && NULL == right_child)
    {
        /* originated from left side */
        if (cur_node == parent->children[LEFT])
        {
            parent->children[LEFT] = NULL;
        } /* originated from right side */
        else
        {
            parent->children[RIGHT] = NULL;
        }
    } /* originated from left side */
    else if (cur_node == parent->children[LEFT])
    {
        BSTRearrangeNodes(cur_node, parent, right_child, left_child, LEFT);
    } /* originated from right side */
    else
    {
        BSTRearrangeNodes(cur_node, parent, left_child, right_child, RIGHT);
    }

    BSTRemoveDanglingPointers(to_remove);

    free(to_remove); to_remove = NULL;

    return (data);
}

/********************************** BSTSize ***********************************/

size_t BSTSize(const bst_t *bst)
{
    size_t count = 0;
    bst_iter_t cur_iter = NULL;

    assert(NULL != bst);

    cur_iter = BSTBegin(bst);

    /* while haven't reached sentinel, go to next iter and increment count */
    while (!BSTIsSameIterator(cur_iter, BSTEnd(bst)))
    {
        cur_iter = BSTNext(cur_iter);
        ++count;
    }

    return (count);
}

/********************************* BSTIsEmpty *********************************/

int BSTIsEmpty(const bst_t *bst)
{
    /* sentinel does not have left child */
    return (NULL == IterToNode(BSTEnd(bst))->children[LEFT]);
}

/********************************** BSTBegin **********************************/

bst_iter_t BSTBegin(const bst_t *bst)
{
    bst_node_t *cur_node = NULL;

    assert(NULL != bst);

    cur_node = IterToNode(BSTEnd(bst));

    /* while the left child is not NULL, go to left child */
    cur_node = FindEdgeChild(cur_node, LEFT);

    return (NodeToIter(cur_node));
}

/*********************************** BSTEnd ***********************************/

bst_iter_t BSTEnd(const bst_t *bst)
{
    assert(NULL != bst);

    return ((bst_iter_t)&(bst->sentinel));
}

/********************************** BSTNext ***********************************/

bst_iter_t BSTNext(bst_iter_t iter)
{
    bst_node_t *cur_node = IterToNode(iter);

    assert(NULL != cur_node);

    /* if there is a right child, find next greatest node */
    if (NULL != cur_node->children[RIGHT])
    {
        cur_node = FindEnd(cur_node, RIGHT);

        return (NodeToIter(cur_node));
    }

    /* while the parent's left child isn't itself, go to parent */
    while (cur_node->parent->children[LEFT] != cur_node)
    {
        cur_node = cur_node->parent;
    }

    /* go to parent */
    cur_node = cur_node->parent;

    return (NodeToIter(cur_node));
}

/********************************** BSTPrev ***********************************/

bst_iter_t BSTPrev(bst_iter_t iter)
{
    bst_node_t *cur_node = IterToNode(iter);

    assert(NULL != IterToNode(iter));

    /* if there is a left child, find next smallest node */
    if (NULL != cur_node->children[LEFT])
    {
        cur_node = FindEnd(cur_node, LEFT);

        return (NodeToIter(cur_node));
    }

    /* while the parent's right child isn't itself, go to parent */
    while (cur_node->parent->children[RIGHT] != cur_node)
    {
        cur_node = cur_node->parent;
    }

    /* go to parent */
    cur_node = cur_node->parent;

    return (NodeToIter(cur_node));
}

/********************************* BSTGetData *********************************/

void *BSTGetData(bst_iter_t iter)
{
    assert(NULL != iter);

    return (IterToNode(iter)->data);
}

/***************************** BSTIsSameIterator ******************************/

int BSTIsSameIterator(bst_iter_t iter1, bst_iter_t iter2)
{
    assert(NULL != IterToNode(iter1));
    assert(NULL != IterToNode(iter2));

    return (iter1 == iter2);
}

/********************************** BSTFind ***********************************/

bst_iter_t BSTFind(bst_t *bst, const void *data_to_find)
{
    /*bst_iter_t cur_iter = NULL;*/
    bst_iter_t end = NULL;
    bst_node_t *cur_node = NULL;
    int cmp = 0;
    child_side_t child_side = LEFT;

    assert(NULL != bst);

    end = BSTEnd(bst);
    /*cur_iter = BSTBegin(bst);*/
    cur_node = (bst_node_t *)end->children[LEFT];

    while (cur_node != NULL)
    {
        cmp = bst->bst_cmp(BSTGetData(cur_node), data_to_find, bst->param);

        if (0 < cmp)
        {
            child_side = LEFT;
        }
        else if (0 > cmp)
        {
            child_side = RIGHT;
        }
        else
        {
            return (NodeToIter(cur_node));
        }

        cur_node = cur_node->children[child_side];
    }

    if (NULL == cur_node)
    {
        return (end);
    }

    return (NodeToIter(cur_node));

    /* while haven't reached end or a match, compare data with next iter */
/*    for (cur_iter = BSTBegin(bst);
         !BSTIsSameIterator(cur_iter, end);
         cur_iter = BSTNext(cur_iter))
    {
        if(0 == bst->bst_cmp(BSTGetData(cur_iter), data_to_find, bst->param))
        {
            break;
        }
    }
    return (cur_iter);
    */
}

/********************************* BSTForEach *********************************/

int BSTForEach(bst_iter_t begin, bst_iter_t end, act_t act, void *param)
{
    bst_iter_t cur_iter = NULL;
    int act_return = 0;

    assert(NULL != begin);
    assert(NULL != end);

    cur_iter = begin;

    /*
     * while haven't reached end and act function returns successful,
     * go to next iter
     */
    while (!BSTIsSameIterator(cur_iter, end) &&
           0 == (act_return = act(BSTGetData(cur_iter), param)))
    {
        cur_iter = BSTNext(cur_iter);
    }

    return (act_return);
}
