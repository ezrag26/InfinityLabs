#include <unistd.h> /* ssize_t      */
#include <stdlib.h> /* alloc family */
#include <assert.h> /* assert       */
#include <unistd.h> /* ssize_t		*/

#include "avl_tree.h"

#include "utils.h"  /* PRNT_ERR, MAX */

#define LEFT_HEAVY (-2)
#define RIGHT_HEAVY (2)
#define SUCCESS (0)

typedef enum sides
{
	LEFT,
	RIGHT
} sides_t;

typedef struct avl_node_s avl_node_t;

struct avl_node_s
{
	void *data;
	avl_node_t *children[2];
	size_t height;
};

struct avl_tree_s
{
	avl_node_t *root;
	avl_cmp_t avl_cmp;
};

avl_t *AVLCreate(avl_cmp_t avl_cmp)
{
    avl_t *avl = (avl_t *)malloc(sizeof(avl_t));

    if (NULL == avl)
    {
        PRNT_ERR("Memory allocation error");
        return (NULL);
    }

	/* initialize avl */
    avl->root = NULL;
    avl->avl_cmp = avl_cmp;

    return (avl);
}

static void DestroyChildren(avl_node_t *root)
{
    if (NULL == root)
    {
        return;
    }

    DestroyChildren(root->children[LEFT]);
    DestroyChildren(root->children[RIGHT]);
    free(root); root = NULL;
}

void AVLDestroy(avl_t *avl)
{
    assert(NULL != avl);

    DestroyChildren(avl->root);
    free(avl); avl = NULL;
}

static void UpdateHeight(avl_node_t *root)
{
	size_t current_height = 0;
	avl_node_t *right_child = root->children[RIGHT];
	avl_node_t *left_child = root->children[LEFT];

	/* root's height is the max between right's and left's height +1*/
	if (NULL != left_child)
	{
		current_height = (left_child->height) + 1;
	}

	if (NULL != right_child)
	{
		current_height = MAX((right_child->height) + 1, current_height);
	}

	root->height = current_height;
}

static ssize_t CalcBalanceFactor(avl_node_t *root)
{
	ssize_t balance_factor = 0;
	ssize_t right_height = 0;
	ssize_t left_height = 0;
	avl_node_t *right_child = root->children[RIGHT];
	avl_node_t *left_child = root->children[LEFT];

	/**
	 * Balance factor is right's height - left's height
	 * Non-existent children are considered as having a height of -1
	 * A balance factor less than, equal to, or greater than 0 represents a left
	 * heavy, balanced, or right heavy subtree, respectively
	 */
	right_height = (NULL != right_child) ? (ssize_t)right_child->height : -1;
	left_height = (NULL != left_child) ? (ssize_t)left_child->height : -1;

	balance_factor = right_height - left_height;

	return (balance_factor);
}

static void RotateSubTree(avl_node_t *pivot_node, int light_side)
{
	int heavy_side = !light_side;
	void *swap_data = pivot_node->data;
	avl_node_t *swap_child = pivot_node->children[heavy_side];

	/* transfer pivot's heavy side child's data to pivot */
    pivot_node->data = swap_child->data;
    swap_child->data = swap_data;

    pivot_node->children[heavy_side] = swap_child->children[heavy_side];
    swap_child->children[heavy_side] = swap_child->children[light_side];
    swap_child->children[light_side] = pivot_node->children[light_side];
    pivot_node->children[light_side] = swap_child;

	UpdateHeight(swap_child);
	UpdateHeight(pivot_node);
}

static void RightHeavyRotationAVL(avl_node_t *root)
{
    ssize_t balance_factor = CalcBalanceFactor(root);

	/* if root's left child doesn't exist, no rotation is needed */
	if (NULL == root->children[LEFT])
	{
		return;
	}

	/* if root is left heavy, rotate right, otherwise don't rotate */
    if (-1 == balance_factor)
    {
        RotateSubTree(root, RIGHT);
	}
}

static void LeftHeavyRotationAVL(avl_node_t *root)
{
    ssize_t balance_factor = CalcBalanceFactor(root);

	/* if root's right child doesn't exist, no rotation is needed */
	if (NULL == root->children[RIGHT])
	{
		return;
	}

	/* if root is right heavy, rotate left, otherwise don't rotate */
	if (1 == balance_factor)
	{
		RotateSubTree(root, LEFT);
	}
}

static void BalanceSubTree(avl_node_t *root)
{
    ssize_t balance_factor = CalcBalanceFactor(root);

    switch(balance_factor)
    {
		/* rotate right if heavy side is left heavy, and then rotate left */
        case RIGHT_HEAVY:
            RightHeavyRotationAVL(root->children[RIGHT]);
            RotateSubTree(root, LEFT);
            break;
		/* rotate left if heavy side is right heavy, and then rotate right */
        case LEFT_HEAVY:
            LeftHeavyRotationAVL(root->children[LEFT]);
            RotateSubTree(root, RIGHT);
            break;
        default:
            break;
    }
}

static int CreateChild(avl_node_t **root_ptr, void *data)
{
    avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));

    if (NULL == new_node)
    {
        PRNT_ERR("Memory allocation error");
        return (1);
    }

    new_node->data = data;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->height = 0;

    *root_ptr = new_node;

    return (SUCCESS);
}

static int Insert(avl_node_t *root,
				  avl_node_t **root_ptr,
				  void *data,
				  avl_cmp_t avl_cmp)
{
    int insert_return = 0;
    int cmp = 0;

	/* place to insert was found */
	if (NULL == root)
	{
		return (CreateChild(root_ptr, data));
	}

	cmp = avl_cmp(root->data, data);

	/* node with same data was found, which is not supported */
	if (0 == cmp)
	{
		PRNT_ERR("Duplicate values not allowed");
		return (1);
	}

	/* if the place to insert wasn't found, try to find a place until found */
    insert_return = Insert(root->children[0 > cmp],
						   &root->children[0 > cmp],
						   data,
						   avl_cmp);

	/* if an insert occured, update height and balance the tree as needed */
    if (0 == insert_return)
    {
        UpdateHeight(root);
        BalanceSubTree(root);
    }

    return (insert_return);
}

int AVLInsert(avl_t *avl, void *data)
{
    assert(NULL != avl);

    return (Insert(avl->root, &avl->root, data, avl->avl_cmp));
}

static void SwapDataAndRemove(avl_node_t *to_remove, avl_node_t **ptr_current)
{
    avl_node_t *to_free = *ptr_current;

	/* transfer data needed to be saved */
    to_remove->data = (*ptr_current)->data;

	/* point to the child of the node being removed */
    *ptr_current = (*ptr_current)->children[LEFT];

	/* remove node */
    to_free->children[LEFT] = NULL;
    to_free->children[RIGHT] = NULL;
    free(to_free); to_free = NULL;
}

static void FindPrevAndRemove(avl_node_t *to_remove, avl_node_t **ptr_root)
{
	/* find node until it is NULL, and update height and balance on way back */
    if (NULL != (*ptr_root)->children[RIGHT])
    {
        FindPrevAndRemove(to_remove, &(*ptr_root)->children[RIGHT]);
		UpdateHeight(*ptr_root);
        BalanceSubTree(*ptr_root);
        return;
    }

	/* node to swap with was found, remove node */
    SwapDataAndRemove(to_remove, ptr_root);
}

static void RemoveNode(avl_node_t *to_remove, avl_node_t **ptr_current)
{
    int connect_side = (NULL == to_remove->children[LEFT]);

	/* *
	 * if one of the children exist, no need to swap data, just point to the
	 * existing node, or NULL if neither exist
	 */
    if (NULL == to_remove->children[RIGHT] || NULL == to_remove->children[LEFT])
    {
        *ptr_current = to_remove->children[connect_side];
        to_remove->children[LEFT] = NULL;
        to_remove->children[RIGHT] = NULL;
        free(to_remove); to_remove = NULL;
    }
	/* node has two children, need to swap data and remove correct node */
	else
	{
		FindPrevAndRemove(to_remove, &(*ptr_current)->children[LEFT]);
		UpdateHeight(*ptr_current);
		BalanceSubTree(*ptr_current);
	}

}

static void FindNodeToRemove(avl_node_t *root,
							 avl_node_t **ptr_current,
							 void *data,
							 avl_cmp_t avl_cmp)
{
    int cmp = 0;
    int child_side = 0;

    cmp = avl_cmp(root->data, data);

    child_side = 0 > cmp;

    if (0 == cmp)
    {
        RemoveNode(root, ptr_current);
    }
    else
    {
        FindNodeToRemove(root->children[child_side],
						 &root->children[child_side],
						 data,
						 avl_cmp);
        UpdateHeight(root);
        BalanceSubTree(root);
    }
}

void AVLRemove(avl_t *avl, void *data)
{
    assert(NULL != avl);

    FindNodeToRemove(avl->root, &avl->root, data, avl->avl_cmp);
}

size_t AVLHeight(const avl_t *avl)
{
    assert(NULL != avl);
	assert(NULL != avl->root);

    return (avl->root->height);
}

static int Size(avl_node_t *root)
{
	/* reached a leaf */
    if (root == NULL)
    {
        return (SUCCESS);
    }

    return (1 + Size(root->children[LEFT]) + Size(root->children[RIGHT]));
}

size_t AVLSize(const avl_t *avl)
{
    assert(NULL != avl);

    return (Size(avl->root));
}

int AVLIsEmpty(const avl_t *avl)
{
    assert(NULL != avl);

    return (NULL == avl->root);
}

static void *Find(avl_node_t *root, const void *data_to_find, avl_cmp_t avl_cmp)
{
    int cmp = 0;

	/* reached leaf */
    if (NULL == root)
    {
        return (NULL);
    }

	/* compare data's */
    cmp = avl_cmp(root->data, data_to_find);

	/* found data */
    if (0 == cmp)
    {
        return (root->data);
    }
	/* try to find it again */
    else
    {
        return (Find(root->children[0 > cmp], data_to_find, avl_cmp));
    }
}

void *AVLFind(avl_t *avl, const void *data_to_find)
{
    assert(NULL != avl);

    return (Find(avl->root, data_to_find, avl->avl_cmp));
}

static int ForEach(avl_node_t *root, act_t act, void *param)
{
    int act_return = 0;
    int for_each_return = 0;

	/* reached leaf */
    if (NULL == root)
    {
        return (SUCCESS);
    }

	/* unsuccessful action */
    if (0 != (act_return = act(root->data, param)))
    {
        return (act_return);
    }

	/* unsucessful action on the left child, exit now */
    if (0 != (for_each_return = ForEach(root->children[LEFT], act, param)))
    {
        return for_each_return;
    }

	/* unsucessful action on the right child, exit now */
    if (0 != (for_each_return = ForEach(root->children[RIGHT], act, param)))
    {
        return for_each_return;
    }

    return (SUCCESS);
}

int AVLForEach(avl_t *avl, act_t act, void *param)
{
    assert(NULL != avl);

    return (ForEach(avl->root, act, param));
}
