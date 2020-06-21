#ifndef _POSIX_C_SOURCE
#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>		/* perror	  */
#include <sys/types.h>  /* fork, wait */
#include <unistd.h> 	/* fork, exec */
#include <sys/wait.h> 	/* wait 	  */
#include <stdlib.h> 	/* exit 	  */
#include <signal.h> 	/* sigaction  */

void SASigaction(int sig, siginfo_t *info, void *context);
void ProcessFunc();

volatile sig_atomic_t sending_pid = -1;

int main()
{
	ProcessFunc();

	return (0);
}

void SASigaction(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)context;

	sending_pid = info->si_pid;

	write(0, "PING\n", 5);
}

void ProcessFunc()
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = SASigaction;

	if (0 > sigaction(SIGUSR1, &act, NULL))
	{
		perror("sigaction failed");
		exit(-1);
	}

	while (1)
	{
		pause();

		sleep(1);

		kill((pid_t)sending_pid, SIGUSR2);
	}
}

#endif /* _POSIX_C_SOURCE */
