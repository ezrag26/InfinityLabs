#include<stdio.h>
#include "binary_search_tree.h"
#include "utils.h"
#include "tests.h"

int TestBSTCreate();
int TestBSTInsertOne();
int TestBSTIsEmpty();
int TestBSTNextFull();
int TestBSTSize();
int TestBSTPrevFull();
int TestBSTRemove();
int TestBSTRemoveOneChildCase(bst_iter_t *iter_arranged);
int TestBSTRemoveTwoChildCaseNoDirect(bst_iter_t *iter_arranged);
int TestBSTRemoveNoChildCase(bst_iter_t *iter_arranged);
int TestBSTRemoveTwoChildCaseDirect(bst_iter_t *iter_arranged);
int TestBSTForEach();
int TestBSTFind();
int TestBSTFindNotExisted(bst_t *bst, const void *data_to_find, bst_iter_t iter_expected);
int TestBSTFindExisted(bst_t *bst, const void *data_to_find, bst_iter_t iter_expected);

#define COUNT 10 
/*
typedef struct bst_node_s bst_node_t;

struct bst_node_s
{
    void *data;
    bst_node_t *children[2];
    bst_node_t *parent;
} ;

struct binary_search_tree_s
{
    bst_node_t sentinel;
    bst_cmp_t bst_cmp;
    void *param;
} ;
*/
int main ()
{
	int errors = 0;

    RUNTEST(TestBSTCreate);
   	RUNTEST(TestBSTInsertOne);
    RUNTEST(TestBSTIsEmpty);
	RUNTEST(TestBSTNextFull);
    RUNTEST(TestBSTSize);
	RUNTEST(TestBSTPrevFull);
	RUNTEST(TestBSTRemove); 
	RUNTEST(TestBSTForEach);
	RUNTEST(TestBSTFind);
	
	return (errors);
}
/*
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
*/
int bst_cmp(const void *data1, const void *data2, void *param)
{
	(void) param;
    return(*(int *)data1 - *(int *)data2);
} 

int TestBSTCreate()
{
	int status = SUCCESS;
    void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);

	BSTDestroy(bst);

	return status;;
}


int TestBSTInsertOne()
{
	int status = SUCCESS;
    void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
    int data = 4;
    bst_iter_t iter = BSTInsert(bst, &data);
    int *data_to_check = BSTGetData(iter);

	REQUIRE(*data_to_check == 4)
    
	BSTDestroy(bst);

	return status;
}

int TestBSTIsEmpty()
{
	int status = SUCCESS;
    void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
	int data = 4;
/*    bst_iter_t iter;*/

	REQUIRE(BSTIsEmpty(bst) == 1);

    BSTInsert(bst, &data);

	REQUIRE(BSTIsEmpty(bst) == 0);

	BSTDestroy(bst);
	return status;
}

int TestBSTNextFull()
{
	int status = SUCCESS;
	void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
    int data[] = {8,4,2,3,1,12,13,10,11,9,6,5,7};
    int index [] = {4,2,3,1,11,10,12,0,9,7,8,5,6};
    bst_iter_t iter[13]={NULL};
    bst_iter_t iter_arranged[13]={NULL};
	size_t size = sizeof(data)/sizeof(data[0]);
	size_t i = 0;

	for(i = 0; i < size; ++i)
	{
		iter[i] = BSTInsert(bst, &data[i]); 
	}

	for(i = 0; i < size; ++i)
	{
		iter_arranged[i] = iter[index[i]]; 
	}


	for(i = 0; i < size - 1; ++i)
	{
		REQUIRE(iter_arranged[i + 1]== BSTNext(iter_arranged[i]));
	}
	
	REQUIRE(BSTEnd(bst) == BSTNext(iter_arranged[size - 1]));

	BSTDestroy(bst);
	return status;
}

int TestBSTPrevFull()
{
	int status = SUCCESS;
	void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
    int data[] = {8,4,2,3,1,12,13,10,11,9,6,5,7};
    int index [] = {4,2,3,1,11,10,12,0,9,7,8,5,6};
    bst_iter_t iter[13]={NULL};
    bst_iter_t iter_arranged[13]={NULL};
	size_t size = sizeof(data)/sizeof(data[0]);
	size_t i = 0;

	for(i = 0; i < size; ++i)
	{
		iter[i] = BSTInsert(bst, &data[i]); 
	}

	for(i = 0; i < size; ++i)
	{
		iter_arranged[i] = iter[index[i]]; 
	}


	for(i = 0; i < size - 1; ++i)
	{
		REQUIRE(iter_arranged[size - i - 2] == BSTPrev(iter_arranged[size - i - 1]));
	}

	BSTDestroy(bst);
	return status;
}

int TestBSTSize()
{
	int status = SUCCESS;
	void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
    int data[] = {8,4,2,3,1,12,13,10,11,9,6,5,7};
	size_t size = sizeof(data)/sizeof(data[0]);
	size_t i = 0;

	for(i = 0; i < size; ++i)
	{
		REQUIRE(i == BSTSize(bst));

		BSTInsert(bst, &data[i]); 
	}

	BSTDestroy(bst);
	return status;
}

int TestBSTRemove()
{
	int status = SUCCESS;
	void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
    int data[] = {8,4,2,3,1,12,13,10,11,9,6,5,7};
    int index [] = {4,2,3,1,11,10,12,0,9,7,8,5,6};
    bst_iter_t iter[13]={NULL};
    bst_iter_t iter_arranged[13]={NULL};
	size_t size = sizeof(data)/sizeof(data[0]);
	size_t i = 0;
/*	bst_node_t *root = NULL;*/

	for(i = 0; i < size; ++i)
	{
		iter[i] = BSTInsert(bst, &data[i]); 
	}

	for(i = 0; i < size; ++i)
	{
		iter_arranged[i] = iter[index[i]]; 
	}

/*	root = (bst->sentinel).children[0];*/
/*	print2DUtil(root, 0); */
/*	puts("##################################");*/
	REQUIRE(TestBSTRemoveTwoChildCaseNoDirect(iter_arranged));
/*	root = (bst->sentinel).children[0];*/
/*	puts("##################################");*/
/*	print2DUtil(root, 0);*/
/*	puts("##################################");	*/
	REQUIRE(TestBSTRemoveOneChildCase(iter_arranged));
/*		root = (bst->sentinel).children[0];*/
/*	puts("##################################");*/
/*	print2DUtil(root, 0);*/
	REQUIRE(TestBSTRemoveNoChildCase(iter_arranged));
/*	 	root = (bst->sentinel).children[0];*/
/*	puts("##################################");*/
/*	print2DUtil(root, 0);*/
	REQUIRE(TestBSTRemoveTwoChildCaseDirect(iter_arranged));
/*	 	root = (bst->sentinel).children[0];*/
/*	puts("##################################");*/
/*	print2DUtil(root, 0);*/
	 BSTDestroy(bst); 
	return status;
}

int TestBSTRemoveOneChildCase(bst_iter_t *iter_arranged)
{
	int status = 0;
	BSTRemove(iter_arranged[2]);

	if(iter_arranged[3] == BSTNext(iter_arranged[1]))
	{
		status = 1;
	}

	return status;
}

int TestBSTRemoveTwoChildCaseNoDirect(bst_iter_t *iter_arranged)
{
	int status = 0;
	BSTRemove(iter_arranged[7]);

	if (iter_arranged[8] == BSTNext(iter_arranged[6]))
	{
		status = 1;
	}

	return status;
}


int TestBSTRemoveTwoChildCaseDirect(bst_iter_t *iter_arranged)
{
	int status = 0;
	BSTRemove(iter_arranged[9]);

	if(iter_arranged[11] == BSTNext(iter_arranged[8]))
	{
		status = 1;
	}

	return status;
}

int TestBSTRemoveNoChildCase(bst_iter_t *iter_arranged)
{
	int status = 0;
	BSTRemove(iter_arranged[10]);

	if(iter_arranged[11] == BSTNext(iter_arranged[9]))
	{
		status = 1;
	}

	return status;
}

int act (void *data, void *param)
{	
	(void) param;
	*(int *)data += 1;

	return 0;
}

int TestBSTForEach()
{
	int status = SUCCESS;
	void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
    int data[] = {8,4,2,3,1,12,13,10,11,9,6,5,7};
    int index [] = {4,2,3,1,11,10,12,0,9,7,8,5,6};
    bst_iter_t iter[13]={NULL};
    bst_iter_t iter_arranged[13]={NULL};
	size_t size = sizeof(data)/sizeof(data[0]);
	size_t i = 0;

	for(i = 0; i < size; ++i)
	{
		iter[i] = BSTInsert(bst, &data[i]); 
	}

	for(i = 0; i < size; ++i)
	{
		iter_arranged[i] = iter[index[i]]; 
	}


	BSTForEach(BSTBegin(bst), BSTEnd(bst), act, param);

	for(i = 0; i < size; ++i)
	{
		REQUIRE((int)(i + 2) == *(int *)BSTGetData(iter_arranged[i]));	
	}

	BSTDestroy(bst);

	return status;
}

int TestBSTFind()
{
	int status = SUCCESS;
	void *param = NULL;
    bst_t *bst = BSTCreate(bst_cmp, param);
    int data[] = {8,4,2,3,1,12,13,10,11,9,6,5,7};
    int index [] = {4,2,3,1,11,10,12,0,9,7,8,5,6};
    bst_iter_t iter[13]={NULL};
    bst_iter_t iter_arranged[13]={NULL};
	size_t size = sizeof(data)/sizeof(data[0]);
	size_t i = 0;

	for(i = 0; i < size; ++i)
	{
		iter[i] = BSTInsert(bst, &data[i]); 
	}

	for(i = 0; i < size; ++i)
	{
		iter_arranged[i] = iter[index[i]]; 
	}

	REQUIRE(TestBSTFindExisted(bst, &data[7], iter_arranged[9]));
	BSTRemove(iter_arranged[9]);
 
	REQUIRE(TestBSTFindNotExisted(bst, &data[7], BSTEnd(bst)));

	BSTDestroy(bst);

	return status;	
}

int TestBSTFindExisted(bst_t *bst, const void *data_to_find, bst_iter_t iter_expected)
{
	int status = 1;
	if (!BSTIsSameIterator(BSTFind(bst, data_to_find), iter_expected))
	{
		return 0;
	}
	return status;
}

int TestBSTFindNotExisted(bst_t *bst, const void *data_to_find, bst_iter_t iter_expected)
{
	int status = 1;
	if (!BSTIsSameIterator(BSTFind(bst, data_to_find), iter_expected))
	{
		return 0;
	}

	return status;	
}
