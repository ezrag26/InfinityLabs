#include <stdio.h>   /* for the printf */
#include <string.h> /* for the strncmp */
#include "logger_lib.h"

extern char *file_name;
extern char str[50];
FILE *ptr_to_file = NULL;
int count = 0;

/*********************************compare functions****************************/

int StrCmp( char *string1,  char *string2)
{
	return (strcmp(string1, string2));
}

/******************************************************************************/
int PrependCmp(char *string1,  char *string2)
{
	return (strncmp(string1, string2, 1));
}

/******************************************************************************/
int AppendCmp(char *string1,  char *string2)
{
	(void)string1;
	(void)string2;

	return (0);
}
/******************************action functions:*******************************/
/* Exit */
enum action FuncExit ()
{
	printf("bye bye\n");

	return (stop);
}
/******************************************************************************/
/* Remove */
enum action FuncRemove ()
{
	remove (file_name); /* Convention is to not have any space between the
												  	 function name and its () */
						/* what happens if the remove failed? Find out what
				 remove returns upon success and return an error if it failed */

	return (run);
}
/******************************************************************************/
/* Count */
enum action FuncCount ()
{

	char currentchar = '0'; /* the zero for a char is '\0' and convention for variable names is snake_case */
	int total_lines = 0;

	ptr_to_file = fopen(file_name, "r+");

	if (NULL != ptr_to_file) /* You should return an error if it is '==' to
								NULL, not '!=' ... If you try to run your
								program, you can see that this function doesn't
								work as you probably expected it to because of
								this */
	{
		return (file_open_error);
	}

	do
	{
		currentchar = fgetc(ptr_to_file);

		if (currentchar == '\n')
		{
			++total_lines;
		}
	}
	while((currentchar) != EOF);

	printf("total_lines %d\n", total_lines);
	fclose (ptr_to_file);

	return (run);

}

/******************************************************************************/
/* Prepend */
enum action FunPrepend ()
{
  char currentchar = '0'; /* the zero for a char is '\0' */
  FILE *ptr_to_temp_file = fopen("temp", "a"); /* what happens if fopen failed? Find out what fopen returns
		  upon success and return an error if it failed */
  ptr_to_file = fopen(file_name, "a"); /* what happens if fopen failed? Find out what fopen returns
		  upon success and return an error if it failed */
  fputs (str, ptr_to_temp_file); /* what happens if fputs failed? Find out what fputs returns
		  upon success and return an error if it failed. Also, right now you're adding the str INCLUDING the '<', you should add the str NOT INCLUDING it */
  currentchar = fgetc(ptr_to_file);

  while (currentchar != EOF)
  {
    fputc (currentchar, ptr_to_temp_file);
  	currentchar = fgetc(ptr_to_file);
  }

  /* right now, you are supposedly adding the input to the temp file, as well
  as copying whatever is in the real file to the temp file (though if you look
  below in the FunApepend function that isn't working so you aren't copying
  anything). However, all the info is being stored in the temp file that the
  user didn't ask for. How can you now make the temp file with the same name as
  the real file? Hint: try getting rid of the real one and giving the temp file
  the name of the real file */

 	fclose(ptr_to_file);
 	fclose(ptr_to_temp_file);

    return (run);
}
/******************************************************************************/
/* Apepend */
enum action FunApepend ()
{
	ptr_to_file = fopen(file_name, "a");

	if (NULL != ptr_to_file) /* You should return an error if it is '==' to
								NULL, not '!=' ... If you try to run your
								program, you can see that this function doesn't
								work as you probably expected it to because of
								this */
	{
		return (file_open_error);
	}

	fputs (str, ptr_to_file); /* what happens if fputs failed? Find out what fputs returns
  		  upon success and return an error if it failed. */
	fclose (ptr_to_file);

	return (run);
}
