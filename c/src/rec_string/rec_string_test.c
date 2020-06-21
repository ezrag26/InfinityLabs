#include <stdio.h>  /* printf    */
#include <string.h> /* str funcs */
#include <stddef.h> /* size_t    */
#include <assert.h> /* assert    */

#include "rec_string.h"

#include "utils.h"
#include "tests.h"

int TestRecStrLen();
int TestRecStrCmp();
int TestRecStrCpy();
int TestRecStrCat();
int TestRecStrStr();
int TestRecStrNCpy();
int TestRecStrNCmp();


char *RecStrNCpy(char *dest, const char *src, size_t n)
{
    char ch = '\0';
    char *dest_ptr = NULL;

    assert(NULL != dest);
    assert(NULL != src);

    ch = *src;
    dest_ptr = dest;

    if (0 != n && '\0' != ch)
    {
        if ('\0' != ch)
        {
            *dest_ptr = ch;
            dest_ptr = RecStrNCpy((dest_ptr + 1), (src + 1), (n - 1));
        }
    }
    else if (0 != n)
    {
        *dest_ptr = '\0';
        dest_ptr = RecStrNCpy((dest_ptr + 1), (src + 1), (n - 1));
    }

    return (dest);
}

int RecStrNCmp(const char *s1, const char *s2, size_t n)
{
    assert(NULL != s1);
    assert(NULL != s2);

    if (0 != n && *s1 == *s2 && '\0' != *s1)
    {
        return (RecStrNCmp((s1 + 1), (s2 + 1), (n - 1)));
    }

    return (*s1 - *s2);
}

int main()
{
    size_t failures = 0;

    puts("Testing Recursive Strings...");
    TEST(TestRecStrLen(), "TestRecStrLen");
    TEST(TestRecStrCmp(), "TestRecStrCmp");
    TEST(TestRecStrCpy(), "TestRecStrCpy");
    TEST(TestRecStrCat(), "TestRecStrCat");
    TEST(TestRecStrStr(), "TestRecStrStr");
/*
    TEST(TestRecStrNCpy(), "TestRecStrNCpy");
    TEST(TestRecStrNCmp(), "TestRecStrNCmp");
*/

    PRNT_STATUS(failures);
    return (failures);
}

int TestRecStrLen()
{
    size_t failures = 0;
    char *str = "Hello World";
    char *str2 = " ";
    char *str3 = "";
    char *str4 = "Ezra Gordon";
    /* char *str5 = NULL; */

    REQUIRE(RecStrLen(str), !=, strlen(str), %lu, %lu);
    REQUIRE(RecStrLen(str2), !=, strlen(str2), %lu, %lu);
    REQUIRE(RecStrLen(str3), !=, strlen(str3), %lu, %lu);
    REQUIRE(RecStrLen(str4), !=, strlen(str4), %lu, %lu);
   /* REQUIRE(StrLen(str5), !=, strlen(str5), %lu, %lu); */

    return (failures);
}

int TestRecStrCmp()
{
    size_t failures = 0;

    char *string1 = "Hello World";
	char *string2 = "ello World";
    char *string3 = "Hello World";
    char *string4 = "Hello World";
    char *string5 = "world";
    char *string6 = "ehllo World";
    char *string7 = "";
    char *string8 = "ehllo World";

    REQUIRE(RecStrCmp(string1, string2), !=, strcmp(string1, string2), %d, %d);
    REQUIRE(RecStrCmp(string3, string4), !=, strcmp(string3, string4), %d, %d);
    REQUIRE(RecStrCmp(string5, string6), !=, strcmp(string5, string6), %d, %d);
    REQUIRE(RecStrCmp(string7, string8), !=, strcmp(string7, string8), %d, %d);

/*
	string1 = NULL;
	string2 = "ehllo World";
	if (StrCmp(string1, string2) != strcmp(string1, string2))
	{
		printf("Failed on line %d\n", __LINE__);
		++has_failed;
	}

*/
    return (failures);
}

int TestRecStrCpy()
{
    size_t failures = 0;
    const char *str_src = "Hello World";
	char str_dest[15] = "";
    char str_dest2[15] = "";
    const char *str_src2 = "";
    char str_dest3[15] = "";
    char str_dest4[15] = "";


    REQUIRE(RecStrCmp(str_src, RecStrCpy(str_dest, str_src)), !=, RecStrCmp(str_src, strcpy(str_dest2, str_src)), %d, %d);
    REQUIRE(RecStrCmp(str_src2, RecStrCpy(str_dest3, str_src2)), !=, RecStrCmp(str_src2, strcpy(str_dest4, str_src2)), %d, %d);

    return (failures);
}

int TestRecStrCat()
{
    size_t failures = 0;
    const char *str_src = "Gordon";
	char str_dest[15] = "Ezra ";
    char str_dest2[15] = "Ezra ";

    REQUIRE(RecStrCmp(RecStrCat(str_dest, str_src), strcat(str_dest2, str_src)), !=, 0, %d, %d);

    return (failures);
}

int TestRecStrNCpy()
{
    size_t failures = 0;

    const char *str_src = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    char str_dest1[100] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
    char str_dest2[100] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
    char str_dest3[100] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
    char str_dest4[100] = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";

	REQUIRE(RecStrCmp(str_src, RecStrNCpy(str_dest1, str_src, 20)), !=, RecStrCmp(str_src, strncpy(str_dest2, str_src, 20)), %d, %d);
	REQUIRE(RecStrNCpy(str_dest1, str_src, 20), ==, strncpy(str_dest2, str_src, 20), %s, %s);

	REQUIRE(RecStrCmp(RecStrNCpy(str_dest3, str_src, 100), strncpy(str_dest4, str_src, 100)), !=, 0, %d, %d);
    REQUIRE(RecStrNCpy(str_dest3, str_src, 100), ==, strncpy(str_dest4, str_src, 100), %s, %s);

    return (failures);
}

int TestRecStrNCmp()
{
    size_t failures = 0;

    const char *str1 = "Tester";
    const char *str2 = "Tester";
    const char *str3 = "Test";
    const char *str4 = "est";
    const char *str5 = "est";
    const char *str6 = "Test";
    const char *str7 = "Test";
    const char *str8 = "Tes";
    const char *str9 = "StrStrString";
    const char *str10 = "StrStrString";

    REQUIRE(RecStrNCmp(str1, str2, 6), !=, strncmp(str1, str2, 6), %d, %d);
    REQUIRE(RecStrNCmp(str3, str4, 4), !=, strncmp(str3, str4, 4), %d, %d);
    REQUIRE(RecStrNCmp(str5, str6, 4), !=, strncmp(str5, str6, 4), %d, %d);
    REQUIRE(RecStrNCmp(str7, str8, 4), !=, strncmp(str7, str8, 4), %d, %d);
    REQUIRE(RecStrNCmp(str9, str10, 12), !=, strncmp(str9, str10, 12), %d, %d);
    REQUIRE(RecStrNCmp(str9, str10, 5), !=, strncmp(str9, str10, 5), %d, %d);
    REQUIRE(RecStrNCmp(str9, str10, 20), !=, strncmp(str9, str10, 20), %d, %d);

    return (failures);
}

int TestRecStrStr()
{
    size_t failures = 0;

    char str_dest1[100] = "Test ";
    char str_dest2[100] = "Another Test ";
    char str_dest3[100] = "Something ";
    char str_dest4[100] = "StrStri ";
    char str_dest5[100] = "StrStrString";
    char str_dest6[100] = "";

    REQUIRE(RecStrStr((const char*)str_dest2, (const char*)str_dest1), !=, strstr((const char*)str_dest2, (const char*)str_dest1), %s, %s);
    REQUIRE(RecStrStr((const char*)str_dest3, (const char*)str_dest1), !=, strstr((const char*)str_dest3, (const char*)str_dest1), %s, %s);
    REQUIRE(RecStrStr((const char*)str_dest3, (const char*)str_dest3), !=, strstr((const char*)str_dest3, (const char*)str_dest3), %s, %s);
    REQUIRE(RecStrStr((const char*)str_dest5, (const char*)str_dest4), !=, strstr((const char*)str_dest5, (const char*)str_dest4), %s, %s);
    REQUIRE(RecStrStr((const char*)str_dest5, "St"), !=, strstr((const char*)str_dest5, "St"), %s, %s);
    REQUIRE(RecStrStr((const char*)str_dest5, ""), !=, strstr((const char*)str_dest5, ""), %s, %s);
    REQUIRE(RecStrStr((const char*)str_dest6, ""), !=, strstr((const char*)str_dest6, ""), %s, %s);

    return (failures);
}
