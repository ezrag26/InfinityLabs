#include <stdio.h>		/* perror	  */
#include <sys/types.h>  /* fork, wait */
#include <unistd.h> 	/* fork, exec */
#include <sys/wait.h> 	/* wait 	  */
#include <stdlib.h> 	/* exit 	  */
#include <signal.h> 	/* sigaction  */

void sig_child_hdl(int sig);
void child_to_parent(pid_t pid);

int main()
{
	child_to_parent(getppid());

	return (0);
}

void sig_child_hdl(int sig)
{
	(void)sig;
	write(0, "PING\n", 5);
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
