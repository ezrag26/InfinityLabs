#include <stdio.h> 		/* printf 	  */
#include <sys/types.h>  /* fork, wait */
#include <unistd.h> 	/* fork, exec */
#include <sys/wait.h> 	/* wait 	  */
#include <stdlib.h> 	/* exit 	  */
#include <signal.h> 	/* sigaction  */

void sig_parent_hdl(int sig);
void sig_child_hdl(int sig);
void parent_to_child(pid_t sig);
void child_to_parent(pid_t sig);

int main()
{

	pid_t child_ret = fork();
	int wstatus = 0;

	if (0 > child_ret)
	{
		perror("fork error");
		exit(-1);
	}
	else if (0 == child_ret)
	{
		child_to_parent(getppid());
		exit(0);
	}

	parent_to_child(child_ret);

	wait(&wstatus);

	return (0);
}

void sig_parent_hdl(int sig)
{
	(void)sig;
	write(0, "PONG\n", 5);
}

void sig_child_hdl(int sig)
{
	(void)sig;
	write(0, "PING\n", 5);
}

void parent_to_child(pid_t pid)
{
	struct sigaction act_parent;

	act_parent.sa_flags = SA_SIGINFO;
	sigemptyset(&act_parent.sa_mask);
	act_parent.sa_handler = sig_parent_hdl;
	if (0 > sigaction(SIGUSR2, &act_parent, NULL))
	{
		perror("handle failed");
		exit(-1);
	}

	while (1)
	{
		sleep(1);

		kill(pid, SIGUSR1);

		pause();
	}
}

void child_to_parent(pid_t pid)
{
	struct sigaction act_child;

	act_child.sa_flags = SA_SIGINFO;
	sigemptyset(&act_child.sa_mask);
	act_child.sa_handler = sig_child_hdl;
	if (0 > sigaction(SIGUSR1, &act_child, NULL))
	{
		perror("handle failed");
		exit(-1);
	}

	while (1)
	{
		pause();

		sleep(1);

		kill(pid, SIGUSR2);
	}
}
