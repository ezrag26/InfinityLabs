/*
* Developer: Ezra Gordon
* Reviewer: Naama
* Status: S
*/

#include <stdio.h> /* printf */

#include "ws6_ex.h"

int Pow2Test();
int IsPow2LoopTest();
int IsPow2Test();
int AddOneTest();
int Print3OneTest();
int ByteMirrorLoopTest();
int ByteMirrorTest();
int Bits2And6Test();
int Bits2Or6Test();
int SwapBitsTest();
int DividedBy16Test();
int SwapVarsTest();
int CountSetBitsLoopTest();
int CountSetBitsTest();
void PrintFloatBitsTest();

int main()
{

	Pow2Test();
	IsPow2LoopTest();
	IsPow2Test();
	AddOneTest();
	Print3OneTest();
	ByteMirrorLoopTest();
	ByteMirrorTest();
	Bits2And6Test();
	Bits2Or6Test();
	SwapBitsTest();
	DividedBy16Test();
	SwapVarsTest();
	CountSetBitsLoopTest();
	CountSetBitsTest();
	PrintFloatBitsTest();
	
	return (0);
}
/******************************* Pow2 Tests ***********************************/

int Pow2Test()
{
	int num_failures = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	unsigned int numbers_arr[256] = {0};
	unsigned int expected[256] = {0, 0, 0, 0, 0, 1, 2, 4, 8, 16, 2, 4, 8, 16, 32, 3,
							6, 12, 24, 48, 4, 8, 16, 32, 64};
	for (i = 0; i < 100; ++i)
	{
		numbers_arr[i] = i;
	}

	printf("Testing Pow2... ");
	for (i = 0; i < 5; ++i)
	{
		for (j = 0; j < 5; ++j)
		{
			if (expected[k] != Pow2(numbers_arr[i], numbers_arr[j]))
			{
				printf("Pow2 FAILED on %d. Expected %d, actual %lu\n", k, \
						expected[k], Pow2(numbers_arr[i], numbers_arr[j]));
				++num_failures;
			}
			++k;
		}
	}

	if (0 == num_failures)
	{
		printf("SUCCEEDED\n");
	}
	
	return (0);
}

/***************************** IsPow2Loop Tests *******************************/

int IsPow2LoopTest()
{

	unsigned int numbers_arr[256] = {0};
	unsigned int expected[100] = {0};
	int i = 0;
	int num_failures = 0;

	for (i = 0; i < 100; ++i)
	{
		numbers_arr[i] = i;
	}

	expected[1] = 1;
	expected[2] = 1;
	expected[4] = 1;
	expected[8] = 1;
	expected[16] = 1;
	expected[32] = 1;
	expected[64] = 1;

	printf("Testing IsPow2Loop... ");

	for (i = 0; i < 100; ++i)
	{
		if ((unsigned int)IsPow2Loop(numbers_arr[i]) != expected[i])
		{
			printf("IsPow2Loop FAILED on %d\n", i);
			++num_failures;
		}
	}

	if (0 == num_failures)
	{
		printf("SUCCEEDED\n");
	}
	
	return (0);
}

/**************************** IsPow2 Tests ************************************/
int IsPow2Test()
{

	unsigned int numbers_arr[256] = {0};
	unsigned int expected[100] = {0};
	int i = 0;
	int num_failures = 0;
	
	for (i = 0; i < 256; ++i)
	{
		numbers_arr[i] = i;
	}
	
	expected[1] = 1;
	expected[2] = 1;
	expected[4] = 1;
	expected[8] = 1;
	expected[16] = 1;
	expected[32] = 1;
	expected[64] = 1;


    for (i = 0; i < 100; ++i)
    {
        numbers_arr[i] = i;
    }

    printf("Testing IsPow2... ");

	for (i = 0; i < 100; ++i)
	{
		if ((unsigned int)IsPow2(numbers_arr[i]) != expected[i])
		{
			printf("IsPow2 FAILED on %d\n", i);
			++num_failures;
		}
	}

    if (0 == num_failures)
	{
		printf("SUCCEEDED\n");
	}
	
	return (0);
}

/***************************** AddOne Tests ***********************************/
int AddOneTest()
{

	unsigned int numbers_arr[256] = {0};
	int i = 0;
	int num_failures = 0;

	for (i = 0; i < 100; ++i)
	{
		numbers_arr[i] = i;
	}

	printf("Testing AddOne... ");

	for (i = 0; i < 100 - 1; ++i)
	{
		if ((numbers_arr[i] + 1) != AddOne(numbers_arr[i]))
		{
			printf("AddOne FAILED on %d\n", i);
			++num_failures;
		}
	}

	if (0 == num_failures)
	{
		printf("SUCCEEDED\n");
	}
	
	return (0);
}
/****************************** Print3One Tests *******************************/
int Print3OneTest()
{

	unsigned int numbers_arr[10] = {0, 4, 7, 10, 14, 18, 25, 35, 40, 52};
	unsigned int expected[10] = {0, 0, 1, 0, 1, 0, 1, 1, 0, 1};
	int i = 0;
	
    int num_failures = 0;
    
    printf("Testing Print3One... ");
	
    Print3One(numbers_arr, 10);

	for (i = 0; i < 10; ++i)
	{
		if (numbers_arr[i] != expected[i])
		{
			printf("Print3One FAILED on %d\n", i);
			++num_failures;
		}
	}

    if (0 == num_failures)
	{
		printf("SUCCEEDED\n");
	}
	
	return (0);
}

/*************************** ByteMirrorLoop Tests *****************************/
int ByteMirrorLoopTest()
{
	unsigned int n = 0;
	printf("Testing ByteMirrorLoop... ");

    n = 147;

    printf("%u is now %u\n", n, ByteMirrorLoop(n));
    
    return (0);

}

/***************************** ByteMirror Tests *******************************/

int ByteMirrorTest()
{
	unsigned int n = 0;
	printf("Testing ByteMirror... ");

    n = 147;

    printf("%u is now %u\n", n, ByteMirror(n));
    
    return (0);   
}

/****************************** Bits2And6 Tests *******************************/
int Bits2And6Test()
{
	unsigned int numbers_arr[256] = {0};
	int i = 0;
    int num_failures = 0;

    for (i = 0; i < 256; ++i)
    {
        numbers_arr[i] = i;
    }

    for (i = 0; i < 256; ++i)
    {
        if (((unsigned char)i & 0x22) == 0x22)
        {
            numbers_arr[i] = 1;
        }
        else
        {
            numbers_arr[i] = 0;
        }
    }

    printf("Testing Bits2And6... ");

    for (i = 0; i < 256; ++i)
	{
		if ((numbers_arr[i]) != Bits2And6((unsigned char)i))
		{
			printf("Bits2And6 FAILED on %d\n", i);
			++num_failures;
		}
	}

    if (0 == num_failures)
	{
		printf("SUCCEEDED\n");
	}
	
	return (0);
}
/******************************* Bits2Or6 Tests *******************************/
int Bits2Or6Test()
{
	unsigned int numbers_arr[256] = {0};
	int i = 0;
    int num_failures = 0;

    for (i = 0; i < 256; ++i)
    {
        if (((unsigned char)i & 0x22) == 0x22 || ((unsigned char)i & 0x22) == 0x20 || ((unsigned char)i & 0x22) == 0x02)
        {
            numbers_arr[i] = 1;
        }
        else
        {
            numbers_arr[i] = 0;
        }
    }

    printf("Testing Bits2Or6... ");

    for (i = 0; i < 256; ++i)
    {
        if ((numbers_arr[i]) != Bits2Or6((unsigned char)i))
        {
            printf("Bits2Or6 FAILED on %d\n", i);
            ++num_failures;
        }
    }

    if (0 == num_failures)
    {
        printf("SUCCEEDED\n");
    }
    
    return (0);
}
/******************************* SwapBits Tests *******************************/
int SwapBitsTest()
{
    unsigned char ch = 0x00;
	ch = 0x90;

	printf("Testing SwapBits... ");
	
    printf("%u is now %u\n", ch, SwapBits(ch));
    
    return (0);
}    
/****************************** DividedBy16 Tests *****************************/
int DividedBy16Test()
{
	unsigned int n = 0;
    n = 48;
    
   	printf("Testing SwapBits... ");
    
    printf("Closest number is %u\n", DividedBy16(n));
    
    return (0);
}    
    
/******************************* Swap2Vars Tests ******************************/
int SwapVarsTest()
{
    unsigned int n1 = 0;
    unsigned int n2 = 0;
    n1 = 10;
    n2 = 3;
    
    printf("n1 = %d\nn2 = %d\n", n1, n2); 
    Swap2Vars(&n1, &n2);
    printf("n1 = %d\nn2 = %d\n", n1, n2);
    
    return (0);
}    
 
/************************** CountSetBitsLoop Tests ****************************/
int CountSetBitsLoopTest()   
{
	unsigned int numbers_arr[256] = {0};
	int i = 0;
	int expected[100] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1};
    int num_failures = 0;

	for (i = 0; i < 16; ++i)
	{
		numbers_arr[i] = i;
	}
	
	
	printf("Testing CountSetBitsLoop... ");
    
    for (i = 0; i < 16; ++i)
    {
    	if (expected[i] != CountSetBitsLoop(numbers_arr[i]))
    	{
    		printf("CountSetBitsLoop FAILED on %d\n", i);
            ++num_failures;
		}
    }
    
    if (0 == num_failures)
    {
        printf("SUCCEEDED\n");
    }
    
    return (0);
}

/**************************** CountSetBits Tests ******************************/

int CountSetBitsTest()
{
	unsigned int numbers_arr[17] = {0};
	int expected[17] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1};
	int i = 0;
    int num_failures = 0;

	for (i = 0; i < 16; ++i)
	{
		numbers_arr[i] = i;
	}
	
	
	printf("Testing CountSetBits... ");
    
    for (i = 0; i < 16; ++i)
    {
    	if (expected[i] != CountSetBits(numbers_arr[i]))
    	{
    		printf("CountSetBits FAILED on %d\n", i);
            ++num_failures;
		}
    }
    
    if (0 == num_failures)
    {
        printf("SUCCEEDED\n");
    }
    
    return (0);
}

/************************* PrintFloatBits Tests *******************************/

void PrintFloatBitsTest()
{

	float numbers_arr[8] = {-15252.252, -10.325, -1.0, -0.0, 0.0, 1.0, 152.626, 472287.341798};
	int i = 0;
	printf("Testing PrintFloatBits... \n");
	
	for (i = 0; i < 8; ++i)
	{
		printf("%f = ", numbers_arr[i]);
		PrintFloatBits(*(numbers_arr + i));
	}
}

