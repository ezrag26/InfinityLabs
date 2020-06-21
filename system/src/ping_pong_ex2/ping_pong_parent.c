#include <stdio.h> 		/* printf 	  */
#include <sys/types.h>  /* fork, wait */
#include <unistd.h> 	/* fork, exec */
#include <sys/wait.h> 	/* wait 	  */
#include <stdlib.h> 	/* exit 	  */
#include <signal.h> 	/* sigaction  */

void sig_parent_hdl(int sig);
void parent_to_child(pid_t pid);

int main(int argc, char *argv[])
{

	pid_t child_ret = fork();
	int wstatus = 0;
	(void)argc;
	if (0 > child_ret)
	{
		perror("fork error");
		exit(-1);
	}
	else if (0 == child_ret)
	{
		execvp(argv[1], argv + 1);
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
