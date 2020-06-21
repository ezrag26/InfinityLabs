/*
*Developer: Lazy Frid
*Reviewer: Ezra Gordon
*Status: F
*/

#include <unistd.h>
#include <stdio.h> 			 			/* for printf */
#include <ctype.h>		 				/* for tolower etc */
#include <stdlib.h> 		 			/* for malloc */
#include <assert.h> 		 			/* for assrets */
#include <string.h> 		 			/* for strlen */

/***************** main *******************************************************/
int main()
{
	size_t GetSize(char**buffer);
	char *StrLowCpy(char *dest, const char *src);
	void MemClear(char**buffer);

	extern char **environ;
	size_t vars_num = 0;
	int i = 0;
	char **buffer = NULL;


	vars_num = GetSize(environ);
	printf("There are %ld environment variables:\n\n", vars_num);

	/* while I'm not a huge fan of comments myself, maybe add a line or two every
		so often explaining what's going on*/
	buffer = calloc((vars_num + 1), (sizeof(char*)));

	for (i = 0; (NULL != *(environ + i)); ++i)
	{

		*(buffer + i) = malloc(sizeof(char) * (strlen(*(environ+i)) + 1));

		if (NULL == *(buffer + i))
		{
			MemClear(buffer);
			printf("malloc failed in var #%d", i + 1);
			return 1;
		}

		StrLowCpy(*(buffer + i), *(environ + i));

		printf("%s\n\n", *(buffer + i));
	}
	*(buffer + i) = NULL;

	MemClear(buffer);

	return 0;

}
/***************** get size of char** excluding null **************************/

size_t GetSize(char **buffer)
{
	size_t i;

	for (i = 0; (NULL != *(buffer + i)); ++i)
		{ /*indented too far to right */
		}
	return i;
}

/***************** Clear char** recursively ***********************************/

void MemClear(char **buffer)
{
	int i;

	for (i = 0; (NULL != *(buffer + i)); ++i)
	{
		free(*(buffer + i));
		*(buffer + i) = NULL;
	}
	free(buffer);
}

/***************** Copy a string all lower case *******************************/

char *StrLowCpy(char *dest, const char *src)
{
	char *first_dest= dest;			/* save the first char location */

	assert(NULL != dest);  			/* dont accept NULL pointers */
	assert(NULL != src);

	while ('\0' != *src)		/* loop thru src till the end of the string */
	{
		*dest = tolower(*src);		/* copy the char from src to the dest */
		++dest;
		++src;
	}

	*dest = '\0';						/* add the closing '\0' to dest */

	return (first_dest);
}
