#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	pid_t pid = fork();

	if (0 > pid)
	{
		perror("fork error");
		return (-1);
	}
	else if (0 == pid)
	{
		pid_t child_pid = getpid();
		pid_t parent_pid = getppid();
		printf("I am a child process with pid %d\n", child_pid);
		printf("My parent's pid is %d\n", parent_pid);
		execlp("./fork_hello", "./fork_hello", NULL);
		printf("This will never show...\n");
		return (0);
	}

	printf("I am the parent process with pid %d\n", getpid());
	printf("Waiting on child process...\n");
	wait(NULL);
	printf("Child process has ended...\n");
	/*execlp("./fork_hello", "./fork_hello", NULL);
	printf("This will never show...\n");*/

	return (0);
}
