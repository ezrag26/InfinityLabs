#include <stdio.h>    /* printf 							  */
#include <string.h>   /* strcmp, strcpy, strncpy, strdup etc. */
#include <strings.h>  /* strcasecmp 						  */
#include <stdlib.h>   /* free 								  */

#include "ws2_string.h"

int main ()
{
	char *str = "Hello World";
	char *str2 = " ";
	char *str3 = "";
	char *str4 = "Ezra Gordon";
/* char *str5 = NULL; */

	const char *string1 = "Hello World";
	char *string2 = "ehllo World";

	const char *str_src = "Hello World";
	char str_dest[15] = "";
	char str_dest1[100] = "Test ";
	char str_dest2[100] = "Another Test ";
	char str_dest3[100] = "Something ";
	char str_dest4[100] = "StrStri ";
	char str_dest5[100] = "StrStrString";
	char str_dest6[100] = "StrStrString";
	int has_failed = 0;

/*	char *duplicate_string = NULL;*/ /* StrDup */

/**************************** StrLen Tests ************************************/

	has_failed = 0;

	printf("Testing StrLen... ");

	if (StrLen(str) != strlen(str))
	{
		printf("StrLen Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrLen(str2) != strlen(str2))
	{
		printf("StrLen Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrLen(str3) != strlen(str3))
	{
		printf("StrLen Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrLen(str4) != strlen(str4))
	{
		printf("StrLen Failed on line %d\n", __LINE__);
		++has_failed;
	}

/*	if (StrLen(str5) != strlen(str5))
	{
		printf("StrLen Failed on line %d\n", __LINE__);
		++has_failed;
	} */

	if (0 == has_failed)
	{
		printf("StrLen Succeeded\n");
	}

/**************************** StrCmp Tests ************************************/

	has_failed = 0;

	printf("Testing StrCmp... ");

	if ('H' - 'e' != StrCmp(string1, string2))
	{
		printf("StrCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "Hello World";
	string2 = "Hello World";
	if ('H' - 'H' != StrCmp(string1, string2))
	{
		printf("StrCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "world";
	string2 = "ehllo World";
	if ('w' - 'e' != StrCmp(string1, string2))
	{
		printf("StrCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "";
	string2 = "ehllo World";
	if (StrCmp(string1, string2) != strcmp(string1, string2))
	{
		printf("StrCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}
/*
	string1 = NULL;
	string2 = "ehllo World";
	if (StrCmp(string1, string2) != strcmp(string1, string2))
	{
		printf("Failed on line %d\n", __LINE__);
		++has_failed;
	}

*/
	if (0 == has_failed)
	{
		printf("StrCmp Succeeded\n");
	}

/******************************* StrCpy Tests *********************************/

	has_failed = 0;

	printf("Testing StrCpy... ");

	if (StrCmp(str_src, StrCpy(str_dest, str_src)) != StrCmp(str_src, strcpy(str_dest, str_src)))
	{
		printf("StrCpy Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (0 == has_failed)
	{
		printf("StrCpy Succeeded\n");
	}

/******************************* StrNCpy Tests ********************************/

	has_failed = 0;

	printf("Testing StrNCpy... ");

	str_src = "Some test more than 12 bytes";
	if (StrCmp(str_src, StrNCpy(str_dest, str_src, 12)) != StrCmp(str_src, strncpy(str_dest, str_src, 12)))
	{
		printf("StrNCpy Failed on line %d\n", __LINE__);
		++has_failed;
	}

	str_src = "Some test more than 12 bytes";
	if (StrCmp(StrNCpy(str_dest5, str_src, 12), strncpy(str_dest6, str_src, 12)))
	{
		printf("StrNCpy Failed on line %d\n", __LINE__);
	}

	if (0 == has_failed)
	{
		printf("StrNCpy Succeeded\n");
	}

/***************************** StrCaseCmp Tests *******************************/

	has_failed = 0;

	printf("Testing StrCaseCmp... ");

	string1 = "Hello World";
	string2 = "hello World";
	if (StrCaseCmp(string1, string2) != strcasecmp(string1, string2))
	{
		printf("StrCaseCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "Hello World";
	string2 = "Hello World";
	if (StrCaseCmp(string1, string2) != strcasecmp(string1, string2))
	{
		printf("StrCaseCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "world";
	string2 = "ehllo World";
	if (StrCaseCmp(string1, string2) != strcasecmp(string1, string2))
	{
		printf("StrCaseCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}
/*
	string1 = NULL;
	string2 = "ehllo World";
	if (StrCaseCmp(string1, string2) != strcasecmp(string1, string2))
	{
		printf("Failed on line %d\n", __LINE__);
		++has_failed;
	}
*/
	string1 = "e";
	string2 = "ehllo World";
	if (StrCaseCmp(string1, string2) != strcasecmp(string1, string2))
	{
		printf("StrCaseCmp Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (0 == has_failed)
	{
		printf("StrCaseCmp Succeeded\n");
	}

/******************************* StrChr Tests *********************************/

	has_failed = 0;

	printf("Testing StrChr... ");

	string1 = "Ezra ordon";
	if (StrChr(string1, 'g') != strchr(string1, 'g'))
	{
		printf("StrChr failedon line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "abcd";
	if (StrChr(string1, 'a') != strchr(string1, 'a'))
	{
		printf("StrChr failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "abcd";
	if (StrChr(string1, 'A') != strchr(string1, 'A'))
	{
		printf("StrChr failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "abc a";
	if (StrChr(string1, ' ') != strchr(string1, ' '))
	{
		printf("StrChr failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "abc a";
	if (StrChr(string1, 22) != strchr(string1, 22))
	{
		printf("StrChr failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "abc a";
	if (StrChr(string1, 0) != strchr(string1, 0))
	{
		printf("StrChr failed on line %d\n", __LINE__);
		++has_failed;
	}

	string1 = "Hello";
	if (StrChr(string1, '\0') != strchr(string1, '\0'))
	{
		printf("StrChr failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (0 == has_failed)
	{
		printf("StrChr Succeeded\n");
	}


/**************************** StrDup Tests ************************************/

	has_failed = 0;
/*
	printf("Testing StrDup... ");

	string1 = "Hello";
	duplicate_string = StrDup(string1);

	if (0 != StrCmp(duplicate_string, string1))
	{
		printf("StrDup Failed on line %d\n", __LINE__);
	}
	else
	{
		printf("StrDup Succeeded\n");
	}

	free(duplicate_string);
	duplicate_string = NULL;

	if (0 == has_failed)
	{
		printf("StrDup Succeeded\n");
	}
}
*/

/**************************** StrCat Test *************************************/

	has_failed = 0;

	printf("Testing StrCat... ");
/*
	string1 = "Hello World";
	printf("%s\n", StrCat(str_dest1, string1));
*/
	if (0 != StrCmp(StrCat(str_dest1, string1), strcat(str_dest1, string1)))
	{
		printf("StrCat Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (0 == has_failed)
	{
		printf("StrCat Succeeded\n");
	}

/*************************** StrNCat Tests ************************************/

	has_failed = 0;

	printf("Testing StrNCat... ");
/*
	string1 = "Hello World";
	printf("%s\n", StrNCat(str_dest2, string1, 16));
*/
	if (0 != StrCmp(StrNCat(str_dest2, string1, 16), strncat(str_dest2, string1, 16)))
	{
		printf("StrNCat Failed on line %d\n", __LINE__);
		++has_failed;
	}
/*
	string1 = "Hello World";
	printf("%s\n", StrNCat(str_dest3, string1, 3));
*/
	if (0 != StrCmp(StrNCat(str_dest3, string1, 3), strncat(str_dest3, string1, 3)))
	{
		printf("StrNCat Failed on line %d\n", __LINE__);
		++has_failed;
	}
/*
	string1 = "Hello World";
	printf("%s\n", StrNCat(str_dest4, string1, 0));
*/
	if (0 != StrCmp(StrNCat(str_dest4, string1, 0), strncat(str_dest4, string1, 0)))
	{
		printf("StrNCat Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (0 == has_failed)
	{
		printf("StrNCat Succeeded\n");
	}

/********************************* StrStr Tests *******************************/

	has_failed = 0;

	printf("Testing StrStr... ");

	if (StrStr((const char*)str_dest2, (const char*)str_dest1) != strstr((const char*)str_dest2, (const char*)str_dest1))
	{
		printf("StrStr Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrStr((const char*)str_dest3, (const char*)str_dest1) != strstr((const char*)str_dest3, (const char*)str_dest1))
	{
		printf("StrStr Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrStr((const char*)str_dest3, (const char*)str_dest3) != strstr((const char*)str_dest3, (const char*)str_dest3))
	{
		printf("StrStr Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrStr((const char*)str_dest5, (const char*)str_dest4) != strstr((const char*)str_dest5, (const char*)str_dest4))
	{
		printf("StrStr Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrStr((const char*)str_dest5, "") != strstr((const char*)str_dest5, ""))
	{
		printf("StrStr Failed on line %d\n", __LINE__);
		++has_failed;
	}


	if (StrStr((const char*)str_dest5, "") != strstr((const char*)str_dest5, ""))
	{
		printf("StrStr Failed on line %d\n", __LINE__);
		++has_failed;
	}
	else
	{
		printf("strstr: %s\n", strstr((const char*)str_dest5, ""));
		printf("StrStr: %s\n", StrStr((const char*)str_dest5, ""));
	}

	if (0 == has_failed)
	{
		printf("StrStr Succeeded\n");
	}

/********************************* StrSpn Tests *******************************/

	has_failed = 0;

/*
	while (--tests + 1)
	{
		dest_test = dest[tests];
		/src_test = src + tests;/

		if (StrSpn(dest_test, dest_test + 1) != strspn(dest_test, dest_test + 1))
		{
			printf("StrSpn Failed on line %d, test number %d\n", __LINE__, 6 - tests);
			printf("%s with %s\n", dest_test, dest_test + 1);
			++has_failed;
		}
	}
*/
	printf("Testing StrSpn... ");

	if (StrSpn(str_dest5, str_dest6) != strspn(str_dest5, str_dest6))
	{
		printf("StrSpn Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (StrSpn(str_dest1, str_dest2) != strspn(str_dest1, str_dest2))
	{
		printf("StrSpn Failed on line %d\n", __LINE__);
		++has_failed;
	}

	if (0 == has_failed)
	{
		printf("StrSpn Succeeded\n");
	}
	else
	{
		printf("Failed %d times", has_failed);
	}

/********************************* StrTok Tests *******************************/


	printf("%c", string1[1] = 'z');
/********************************* ************ *******************************/

	return (0);
}
