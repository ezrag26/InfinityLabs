#include <stdio.h> /* printf */
#include <sys/types.h> /* fork, wait */
#include <unistd.h>	   /* fork, exec   */
#include <sys/wait.h>  /* wait */
#include <stdlib.h>    /* exit */

int RunShell();

int main(int argc, char *argv[])
{
	int ret = RunShell(argv);
	(void)argc;

	return (ret);
}

int RunShell(char *argv[])
{
	int status = 0;

	do
	{
		pid_t child_ret = fork();

		if (0 > child_ret)
		{
			perror("fork error");
			exit(-1);
		}
		else if (0 == child_ret)
		{
			execvp(argv[1], argv + 1);
			abort();
		}

		wait(&status);

	} while (0 == WIFEXITED(status));


	return (0);
}
