/*
* Developer: Ezra Gordon
* Reviewer: Lazy Frid
* Status: S
*/

#include <stdio.h> 	/* printf  */
#include <string.h> /* strncmp */

#include "logger_lib.h"

/* Program that appends and prepends user input to files. User can also remove
the file or count the total lines written in the file */

/* create structure */
	struct logger_t
	{
		char *string;
		int (*cmp)(const char *, const char *);
		enum action_return_t (*act)(char *, const char *);
	} commands[] =   {
							{"-remove\n", StrCmp, Remove},
							{"-count\n", StrCmp, Count},
							{"-exit\n", StrCmp, Exit},
							{"<", PrependCmp, Prepend},
							{"", Always, Append}
					  };

int main(int argc, char *argv[])
{
	
	const char *file_name = NULL;
	char buffer[100] = "\0";

	enum action_return_t return_status = 0;
	size_t i = 0;

	if (2 > argc) /* didn't enter a file name as parameter */
	{
		printf("Error: No file name entered\n");
		return (FILE_NAME_ERROR);
	}

	file_name = argv[1];
	if (0 == strncmp(file_name, "tmp.txt", 7))
	{
		printf("Error: File name \"tmp.txt\" not allowed. Please use a \
				different name\n");
		return (FILE_NAME_ERROR);
	}

	printf("Program started. Enter input to append/prepend to the document\n");
	
	while (SUCCESS == return_status)
	{
		/* get input, up to 100 characters */
		if (NULL == fgets(buffer, 100, stdin))
		{
			return (FGETS_ERROR);
		}		
		/* for all elements of the structure */
		for (i = 0; i < sizeof(commands)/sizeof(*commands); ++i)
		{
			if (0 == commands[i].cmp(commands[i].string, buffer))
			{
				return_status = commands[i].act(buffer, file_name);
				break;
			}
		}
	}
	
	return (return_status);
}
