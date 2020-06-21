#include <stdio.h> 	   /* printf 	   */
#include <sys/types.h> /* fork, wait   */
#include <sys/wait.h>  /* wait  	   */
#include <unistd.h>	   /* fork, exec   */
#include <stdlib.h>    /* exit, system */
#include <time.h>	   /* time 		   */

int ForkExec(int argc, char *argv[]);
int System(char *command);

int main(int argc, char *argv[])
{
	char *command = "ls -a";
	ForkExec(argc, argv);
	System(command);

	return (0);
}

int ForkExec(int argc, char *argv[])
{
	int status = 1;
	int flag = 0;
	argc -= 1;
	while (0 == WIFEXITED(status) && --argc)
	{
		pid_t child_ret = fork();
		/*char *args[] = {"./child_process", "0", "1", "2", "3", "4", "5", NULL};*/
		++flag;
		if (0 > child_ret)
		{
			perror("fork error");
			return (1);
		}
		else if (0 == child_ret)
		{
			execvp(argv[1], argv + flag);
			abort();
		}

		printf("%d. I am process %d, waiting on child %d to complete..\n", flag, getpid(), child_ret);
		wait(&status);
		printf("Child %d has completed.\n", child_ret);

	}

	return (0);
}

int System(char *command)
{
	int status = 1;

	while (0 == WIFEXITED(status))
	{
		printf("%s\n", command);
		status = system(command);
	}

	printf("exiting.\n");

	return (0);
}
