/*
*Developer: Ezra Gordon
*Reviewer: Tom Goldberg
*Status: A
*/

#include <stdio.h>	/* printf  */
#include <stdlib.h> /* malloc  */
#include <string.h>	/* strlen  */
#include <ctype.h>	/* tolower */

#define UNUSED(x) (void)(x)

void FreeAll(char **to_free);
void CopyAndLower(char *dest, char *src);
void PrintEnv(char **s);

/* Program that copies the environment variables to a new place in memory and
prints them in lowercase to stdout */

int main (int argc, char **argv, char **envp)
{
	int counter = 0;
	char **envp_start = envp;
	char **buffer = NULL;
	char **buffer_start = NULL;
	UNUSED(argc);
	UNUSED(argv);

	while (NULL != *envp_start)
	{
		++counter;
		++envp_start;
	}

	buffer = (char **)malloc(sizeof(char *) * (counter + 1));

	if ( NULL == buffer) 					   /* not enough memory available */
	{
		return (0);
	}

	buffer_start = buffer;
	envp_start = envp;

	while ('\0' != *envp_start)		  /* Haven't reached pointers to char end */
	{
		*buffer = (char *)malloc(sizeof(char) * (strlen(*envp_start)+1));

		if (NULL == *buffer) 				   /* not enough memory available */
		{
			FreeAll(buffer_start);
			free(buffer_start);			/* Free memory allocated to hold the
															 pointers to char */
			buffer_start = NULL;

			return (0);
		}

		CopyAndLower(*buffer, *envp_start);

		++envp_start;
		++buffer;
	}

	*buffer = '\0';

	PrintEnv(buffer_start);

	FreeAll(buffer - counter);
	free(buffer_start);					/* Free memory allocated to hold the
															 pointers to char */
	buffer_start = NULL;

	return (0);
}

/* Free all previously allocated memory for the strings */
void FreeAll(char **to_free)
{

	while (NULL != *to_free)
	{
		free(*to_free);
		*to_free = NULL;
		++to_free;
	}
}

/* Make lowercase and copy to dest */
void CopyAndLower(char *dest, char *src)
{

	while ('\0' != *src) 			/* Not at end of string */
	{
		*dest = tolower(*src);
		++src;
		++dest;
	}

	*dest = '\0'; 					/* add terminating null */
}

/* Print to screen */
void PrintEnv(char **s)
{

	while (NULL != *s)
	{
		printf("%s\n", *s);
		++s;
	}

}
