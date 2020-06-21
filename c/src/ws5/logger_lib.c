#include <stdio.h> 	/* printf  */
#include <assert.h> /* assert  */
#include <string.h> /* strncmp */

#include "logger_lib.h"

#define UNUSED(x) (void)(x)

/******************************************************************************/
/************************ compares between two strings ************************/
/******************************************************************************/
int StrCmp (const char *s1, const char *s2)
{
	assert(NULL != s1);				/* Check for invalid memory address" */
	assert(NULL != s2);				/* Check for invalid memory address" */

	/* Still the same and haven't reach string's end */
	while ((*s1 == *s2) && '\0' != *s1)
	{
		++s1;
		++s2;
	}

	return (*s1 - *s2);
}

/******************************************************************************/
/******************** compares first character of the strings *****************/
/******************************************************************************/
int PrependCmp(const char *s1, const char *s2)
{
	assert(NULL != s1);				/* Check for invalid memory address" */
	assert(NULL != s2);				/* Check for invalid memory address" */

	return (strncmp(s1, s2, 1));
}

/******************************************************************************/
/******************************* does nothing special *************************/
/******************************************************************************/
int Always(const char *s1, const char *s2)
{
	UNUSED(s1);
	UNUSED(s2);

	return (0);
}

/******************************************************************************/
/****************************** deletes the file ******************************/
/******************************************************************************/
enum action_return_t Remove(char *string, const char *file_name)
{
	UNUSED(string);

	if (0 != remove(file_name)) 	/* check if file was successfully removed */
	{
		return (REMOVE_ERROR);
	}

	return (SUCCESS);
}

/******************************************************************************/
/******************** counts the number of lines in the file ******************/
/******************************************************************************/
enum action_return_t Count(char *string, const char *file_name)
{
	FILE *fp = NULL;
	char current_c = '\0';
	int lines = 0;
	UNUSED(string);

	fp = fopen(file_name, "r");
	if (NULL == fp) 						  /* check if open was successful */
    {
        return (FILE_OPEN_ERROR);
    }

	current_c = getc(fp);
	/* adds one to the count if the character reached a newline */
	while (current_c != EOF)
	{
		if (current_c == '\n')
		{
			++lines;
		}
		current_c = getc(fp);
	}
	fclose(fp); fp = NULL;

	/* print how many lines with text to match grammatically with the number  */
	switch (lines)
	{
		case 1:
			printf("There is %d line in the file\n", lines);
			break;
		default:
			printf("There are %d lines in the file\n", lines);
	}

	return (SUCCESS);
}

/******************************************************************************/
/*********************** doesn't actually do anything *************************/
/******************************************************************************/
enum action_return_t Exit(char *string, const char *file_name)
{
	UNUSED(string);
	UNUSED(file_name);

	return (EXIT);
}

/******************************************************************************/
/******************* add the input to the end of the file *********************/
/******************************************************************************/
enum action_return_t Append(char *string, const char *file_name)
{
	FILE *fp = fopen(file_name, "a");
	if (NULL == fp) 						  /* check if open was successful */
    {
        return (FILE_OPEN_ERROR);
    }

	if (EOF ==  fputs(string, fp))			  /* Append the input to the file */
	{
		fclose(fp); fp = NULL;
		return (FPUTS_ERROR);
	}
	fclose(fp); fp = NULL;

	return (SUCCESS);
}

/******************************************************************************/
/******* add the input to the beginning of the file instead of its end ********/
/******************************************************************************/
enum action_return_t Prepend(char *string, const char *file_name)
{
	FILE *fp = NULL;
	FILE *fp_copy = NULL;
	char *copy_file_name = "~tmp.txt";
	char current_c = '\0';


	fp_copy = fopen(copy_file_name, "a");
	if (NULL == fp_copy) 					  /* check if open was successful */
    {
        return (FILE_OPEN_ERROR);
    }

	/* add current input to tmp */
	if (SUCCESS != Append((string + 1), copy_file_name)) 
	{
		return (APPEND_ERROR);
	}

	fp = fopen(file_name, "r");
	if (NULL == fp) 						  /* check if open was successful */
    {
        return (FILE_OPEN_ERROR);
    }

	/* append contents of the current file to the tmp file */
	while ((current_c = fgetc(fp)) != EOF)
	{
		fputc(current_c, fp_copy);
	}

	fclose(fp_copy); fp_copy = NULL;
	fclose(fp); fp = NULL;

	/* remove in order to rename the tmp to the file name */
	if (0 != remove(file_name))
	{
		return (REMOVE_ERROR);
	}

	if (0 != rename(copy_file_name, file_name))
	{
		return (RENAME_ERROR);
	}

	return (SUCCESS);
}
