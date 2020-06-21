#include <stdio.h> /* printf */
#include <sys/types.h> /* fork, wait */
#include <unistd.h>	   /* fork, exec */
#include <stdlib.h>
#include <signal.h> /* kill */
#include <string.h> /* strcmp */

void ChildProgram();

int main(int argc, char *argv[])
{
	(void)argc;
	ChildProgram(argv[1]);

	return (0);
}

void ChildProgram(char *argv)
{
	if (strcmp(argv, "stop") != 0)
	{
		printf("\tHi! I am process %d, child of process %d\n", getpid(), getppid());
		printf("\tI received the string \"%s\"\n", argv);
		printf("\tProcess %d now exiting. Goodbye!\n", getpid());
		abort();
	}

	return;
}
