/* developr: Tom
   reviewer: Ezra
   status: s
*/

#include <stdio.h> /* add reason for #include */
#include <string.h> /* add reason for #include */
#include "logger_lib.h"

#define UNUSED(x) (void)(x)

char str[50];
char *file_name = NULL;
int main (int argc, char *argv[])
{
	struct logger /* definition of struct */
	{
		char *string;
		int (*ptr_cmp) ( char *string1, char *string2);
		enum action (*ptr_action) ();

	} arr[5] =
	{
		/* the array elements should be indented from the arrays braces */
	{"-exit\n", StrCmp, FuncExit},     /* arr[1] */ /* => this is arr[0] */
	{"-remove\n", StrCmp, FuncRemove},/* arr[2] */ /* => this is arr[1] */
	{"-count\n", StrCmp, FuncCount}, /* arr[3] *//* => and so on... */
	{"<\n", PrependCmp, FunPrepend},/* arr[4] */
	{"", AppendCmp, FunApepend}    /* arr[5] */
	};

	int i = 0;
	int compare_check = 0;
	enum action act = 1;

	file_name = argv[1]; /* you should check if argv[1] exists (you can use
	argc to do that). If the user never added a file name after ./a.out, then
	you'll receive a segmentation fault error */

	UNUSED (argc);

	while (run == act)
	{
		printf("input a string:");
		fgets (str, 50, stdin); /* check if fgets returns NULL and return an
															error if it does */

		for (i = 0 ; i < 5; ++i)	/* size of array */
		{
			/* do the comperation:  */
			compare_check = arr[i].ptr_cmp(str, arr[i].string);

			if (compare_check == 0)
			{
				/* do the action:  */
				act = arr[i].ptr_action();
					/* Extra hint: this is where you should add an if statement that returns the action functions return value (see below comments) */
				break;
			}
		}

	}
	return (0); /* as of now, you're only ever returning 0. Try to return what
				the action fuctions return so that the user can know what erros
				are occurring if there are any. Hint: you already have that
				value store in 'act' */
}
