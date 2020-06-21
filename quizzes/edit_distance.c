#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "tests.h"

int WordOperations(char *s1, size_t n1, char *s2, size_t n2);
int TestEditDistance();

int main()
{
    size_t failures = 0;

    puts("Testing EditDistance");
    TEST(TestEditDistance(), "TestEditDistance");

    PRNT_STATUS(failures);
    return failures;
}

int WordOperations(char *s1, size_t n1, char *s2, size_t n2)
{
    size_t i = 0;
    size_t j = 0;
    int matrix[100][100] = {{0}, {0}};

    for (j = 0; j <= n2; ++j)
    {
        matrix[0][j] = j;
    }

    for (i = 1; i <= n1; ++i)
    {
        matrix[i][0] = i;
    }

    for (i = 1; i <= n1; ++i)
    {
        for (j = 1; j <= n2; ++j)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                matrix[i][j] = matrix[i - 1][j - 1];
            }
            else
            {
                int insert = 1 + matrix[i][j - 1];
                int delete = 1 + matrix[i - 1][j];
                int replace = 1 + matrix[i - 1][j - 1];
                matrix[i][j] = MIN(insert, MIN(delete, replace));
            }
        }
    }

    return (matrix[n1][n2]);

}

int TestEditDistance()
{
    size_t failures = 0;
    size_t i = 0;
    char *string[] = {"hello", "hey", "lehol", "hlole", "", "a", "h", "abcdf", "hfvfgbuapiev"};
    size_t size[] = {5, 3, 5, 5, 0, 1, 1, 5, 12};
    int exp[] = {0, 3, 4, 3, 5, 5, 4, 5, 11};

    for (i = 1; i < ARR_SIZE(string); ++i)
    {
        REQUIRE(WordOperations(string[0], size[0], string[i], size[i]), !=, exp[i], %d, %d);
    }

    return failures;
}
