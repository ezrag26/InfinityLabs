#include <stdio.h> 	/* printf */
#include <stddef.h> /* size_t */
#include <string.h>  /* strcmp */

#include "bit_array.h"
#include "tests.h"

#define CHAR_BIT (8)
#define SIZE_OF_LONG (__SIZEOF_LONG__)

#if SIZE_OF_LONG == 4
#define ALL_BITS ((bit_arr_t)0xFFFFFFFF)
#define NO_BITS ((bit_arr_t)0x00000000)
#define RIGHT_BIT ((bit_arr_t)0x00000001)
#define LEFT_BIT ((bit_arr_t)0x80000000)
#endif

#if SIZE_OF_LONG == 8
#define ALL_BITS ((bit_arr_t)0xFFFFFFFFFFFFFFFF)
#define NO_BITS ((bit_arr_t)0x0000000000000000)
#define RIGHT_BIT ((bit_arr_t)0x0000000000000001)
#define LEFT_BIT ((bit_arr_t)0x8000000000000000)
#endif

int TestBitArrSetAllOn();
int TestBitArrSetAllOff();
int TestBitArrSetOn();
int TestBitArrSetOff();
int TestBitArrSetBit();
int TestBitArrFlipBit();
int TestBitArrMirror();
int TestBitArrMirrorLUT();
int TestBitArrIsOn();
int TestBitArrIsOff();
int TestBitArrCountOn();
int TestBitArrCountOnLUT();
int TestBitArrCountOff();
int TestBitArrRotateRight();
int TestBitArrRotateLeft();
int TestBitArrToString();

int main()
{
	size_t failures = 0;

	puts("Testing Bit Array...");
	TEST(TestBitArrSetAllOn(), "BitArrSetAllOn");
	TEST(TestBitArrSetAllOff(), "BitArrSetAllOff");
	TEST(TestBitArrSetOn(), "BitArrSetOn");
	TEST(TestBitArrSetOff(), "BitArrSetOff");
	TEST(TestBitArrSetBit(), "BitArrSetBit");
	TEST(TestBitArrFlipBit(), "BitArrFlipBit");
	TEST(TestBitArrMirror(), "BitArrMirror");
	TEST(TestBitArrMirrorLUT(), "BitArrMirrorLUT");
	TEST(TestBitArrIsOn(), "BitArrIsOn");
	TEST(TestBitArrIsOff(), "BitArrIsOff");
	TEST(TestBitArrCountOn(), "BitArrCountOn");
	TEST(TestBitArrCountOnLUT(), "BitArrCountOnLUT");
	TEST(TestBitArrCountOff(), "BitArrCountOff");
	TEST(TestBitArrRotateRight(), "BitArrRotateRight");
	TEST(TestBitArrRotateLeft(), "BitArrRotateLeft");
	TEST(TestBitArrToString(), "BitArrToString");

	PRNT_STATUS(failures);

	return (failures);
}

/***************************** TestBitArrSetAllOn *****************************/

int TestBitArrSetAllOn()
{
#if SIZE_OF_LONG == 4
	unsigned long i = 0;
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
#endif

	bit_arr_t b[] = 		 {0x00, 	0x01, 	  0x02, 	ALL_BITS};
	bit_arr_t b_expected[] = {ALL_BITS, ALL_BITS, ALL_BITS, ALL_BITS};
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrSetAllOn(b[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/***************************** TestBitArrSetAllOff ****************************/
int TestBitArrSetAllOff()
{
#if SIZE_OF_LONG == 4
	unsigned long i = 0;
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
#endif

	bit_arr_t b[] = 		 {0x00,    0x01, 	0x02, 	 ALL_BITS};
	bit_arr_t b_expected[] = {NO_BITS, NO_BITS, NO_BITS, NO_BITS };
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrSetAllOff(b[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrSetOn ******************************/
int TestBitArrSetOn()
{
#if SIZE_OF_LONG == 4
	unsigned long i = 0;
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
#endif

	bit_arr_t b[] =  		 {NO_BITS, NO_BITS,  LEFT_BIT, 	   0xFE};
	size_t index[] = 		 {1, 	   63, 		 0, 	   	   0   };
	bit_arr_t b_expected[] = {0x02,    LEFT_BIT, LEFT_BIT + 1, 0xFF};
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrSetOn(b[i], index[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}
	return (failures);
}

/******************************* TestBitArrSetOff *****************************/
int TestBitArrSetOff()
{
#if SIZE_OF_LONG == 4
	unsigned long i = 0;
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
#endif

	bit_arr_t b[] =  		 {RIGHT_BIT, 0x02,    LEFT_BIT, 0x03};
	size_t index[] = 		 {0, 	     1, 	  63, 	   	0	};
	bit_arr_t b_expected[] = {NO_BITS,   NO_BITS, NO_BITS,  0x02};
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrSetOff(b[i], index[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrSetBit *****************************/
int TestBitArrSetBit()
{
#if SIZE_OF_LONG == 4
	unsigned long i = 0;
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
#endif

	bit_arr_t b[] =  		 {RIGHT_BIT, 0x02, LEFT_BIT, 0x03, 0x02, 0x02};
	size_t index[] = 		 {0, 	     1,    63, 	   	 0,	   1,    0 	 };
	int value[] = 			 {1, 		 1,    1, 		 0,	   0,    0 	 };
	bit_arr_t b_expected[] = {1,   		 0x02, LEFT_BIT, 0x02, 0,    0x02};
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrSetBit(b[i], index[i], value[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrFlipBit ****************************/
int TestBitArrFlipBit()
{
#if SIZE_OF_LONG == 4
	unsigned long i = 0;
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
#endif

	bit_arr_t b[] =  		 {RIGHT_BIT, 0x02, LEFT_BIT, 	 0x03};
	size_t index[] = 		 {0, 	     1,    1, 	   		 0	 };
	bit_arr_t b_expected[] = {NO_BITS,   0,    LEFT_BIT + 2, 0x02};
	size_t failures = 0;

	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrFlipBit(b[i], index[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrMirror *****************************/
int TestBitArrMirror()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDA8A4B55,   LEFT_BIT,  0x00};
	bit_arr_t b_expected[] = {LEFT_BIT,  0xAAD2515B, RIGHT_BIT, 0x00};
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0x94A09770A96A7CC5,   LEFT_BIT,  0x00};
	bit_arr_t b_expected[] = {LEFT_BIT,  0xA33E56950EE90529, RIGHT_BIT, 0x00};
#endif

	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrMirror(b[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrMirror *****************************/
int TestBitArrMirrorLUT()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDA8A4B55,   LEFT_BIT,  0x00};
	bit_arr_t b_expected[] = {LEFT_BIT,  0xAAD2515B, RIGHT_BIT, 0x00};
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0x94A09770A96A7CC5,   LEFT_BIT,  0x00};
	bit_arr_t b_expected[] = {LEFT_BIT,  0xA33E56950EE90529, RIGHT_BIT, 0x00};
#endif

	size_t failures = 0;



	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrMirrorLUT(b[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			printf("\tExpected %lu\n", b_expected[i]);
			printf("\tFunction Returned %lu\n", BitArrMirrorLUT(b[i]));
			++failures;
		}
	}

	return (failures);

}

/******************************* TestBitArrIsOn *******************************/
int TestBitArrIsOn()
{
#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {0xDA8A4B55, 0x02, LEFT_BIT, LEFT_BIT};
	size_t index[] = 		 {14, 	     		  0,    1, 	   	  31	  };
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {0xDDE31EAA3E041C00, 0x02, LEFT_BIT, LEFT_BIT};
	size_t index[] = 		 {18, 	     		  0,    1, 	   	  63	  };
#endif

	bit_arr_t b_expected[] = {1,   		 		  0,    0, 		  1		  };
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrIsOn(b[i], index[i]) != (int)b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrIsOff ******************************/
int TestBitArrIsOff()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {0xDA8A4B55, 0x02, LEFT_BIT, LEFT_BIT};
	size_t index[] = 		 {14, 	     		  0,    1, 	   	  31	  };
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {0xDDE31EAA3E041C00, 0x02, LEFT_BIT, LEFT_BIT};
	size_t index[] = 		 {18, 	     		  0,    1, 	   	  63	  };
#endif
	bit_arr_t b_expected[] = {0,   		 		  1,    1, 		  0		  };
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrIsOff(b[i], index[i]) != (int)b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrCountOn ****************************/
int TestBitArrCountOn()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDA8A4B55, 0xAAAAAAAA,  NO_BITS, ALL_BITS};
	bit_arr_t b_expected[] = {1,  		 16, 				 16, 			NO_BITS, 32};
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDDE31EAA3E041C00, 0xAAAAAAAAAAAAAAAA,  NO_BITS, ALL_BITS};
	bit_arr_t b_expected[] = {1,  		 28, 				 32, 			NO_BITS, 64};
#endif

	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrCountOn(b[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/***************************** TestBitArrCountOnLUT ***************************/
int TestBitArrCountOnLUT()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDA8A4B55, 0xAAAAAAAA, NO_BITS, ALL_BITS};
	bit_arr_t b_expected[] = {1,  		 16, 		 16,         NO_BITS, 32};
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDDE31EAA3E041C00, 0xAAAAAAAAAAAAAAAA,  NO_BITS, ALL_BITS};
	bit_arr_t b_expected[] = {1,  		 28, 				 32, 			   NO_BITS, 64};
#endif

	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrCountOnLUT(b[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			printf("\tExpected %lu\n", b_expected[i]);
			printf("\tFunction Returned %lu\n", BitArrCountOnLUT(b[i]));
			++failures;
		}
	}

	return (failures);
}

/******************************* TestBitArrCountOff ***************************/
int TestBitArrCountOff()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDA8A4B55, ALL_BITS,  NO_BITS};
	bit_arr_t b_expected[] = {31,  		 16, 		 0, 		32	   };
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0x38207C5578C7BB, ALL_BITS,  NO_BITS};
	bit_arr_t b_expected[] = {63,  		 36, 			   0, 		  64	 };
#endif
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrCountOff(b[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/***************************** TestBitArrRotateRight **************************/
int TestBitArrRotateRight()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDA8A4B55, ALL_BITS, NO_BITS};
	size_t n[] = 			 {33, 		 17,		 1,        24     };
	bit_arr_t b_expected[] = {LEFT_BIT,  0x25AAED45, ALL_BITS, NO_BITS};
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {RIGHT_BIT, 0xDDE31EAA3E041C00, ALL_BITS,  NO_BITS};
	size_t n[] = 			 {65, 		 17,				 1,         24     };
	bit_arr_t b_expected[] = {LEFT_BIT,  0xE006EF18F551F02,  ALL_BITS,	NO_BITS};
#endif

	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrRotateRight(b[i], n[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/***************************** TestBitArrRotateLeft ***************************/
int TestBitArrRotateLeft()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] =  		 {LEFT_BIT,  0xDA8A4B55, ALL_BITS,  NO_BITS};
	size_t n[] = 			 {1, 		 20,		 1,         24     };
	bit_arr_t b_expected[] = {RIGHT_BIT, 0xB55DA8A4, ALL_BITS,	NO_BITS};
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] =  		 {LEFT_BIT,  0xDDE31EAA3E041C00, ALL_BITS,  NO_BITS};
	size_t n[] = 			 {1, 		 20,				 1,         24     };
	bit_arr_t b_expected[] = {RIGHT_BIT, 0xEAA3E041C00DDE31, ALL_BITS,	NO_BITS};
#endif
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (BitArrRotateLeft(b[i], n[i]) != b_expected[i])
		{
			printf("\n\t**FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}

/***************************** TestBitArrToString *****************************/
int TestBitArrToString()
{

#if SIZE_OF_LONG == 4
	unsigned long i = 0;
	bit_arr_t b[] = {0xDA8A4B55, 0x01, 0x03, ALL_BITS, NO_BITS};
	char *b_expected[] =
	{
	"11011010100010100100101101010101",
	"00000000000000000000000000000001",
	"00000000000000000000000000000011",
	"11111111111111111111111111111111",
	"00000000000000000000000000000000"
	};
#endif

#if SIZE_OF_LONG == 8
	size_t i = 0;
	bit_arr_t b[] = {0xF0000000000000FF, 0x01, 0x03, ALL_BITS, NO_BITS};
	char *b_expected[] =
	{
	"1111000000000000000000000000000000000000000000000000000011111111", 	"0000000000000000000000000000000000000000000000000000000000000001", 	"0000000000000000000000000000000000000000000000000000000000000011", 	"1111111111111111111111111111111111111111111111111111111111111111", 	"0000000000000000000000000000000000000000000000000000000000000000"
	};
#endif
	char buffer[(sizeof(size_t) * CHAR_BIT) + 1] = {0};
	size_t failures = 0;


	for (i = 0; i < ARR_SIZE(b); ++i)
	{
		if (0 != strcmp(BitArrToString(b[i], buffer), b_expected[i]))
		{
			printf("BitArrToString **FAILED** at index %lu\n", i);
			++failures;
		}
	}

	return (failures);
}
