#ifndef _POSIX_C_SOURCE
#define _XOPEN_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>		/* perror	  */
#include <sys/types.h>  /* fork, wait */
#include <unistd.h> 	/* fork, exec */
#include <sys/wait.h> 	/* wait 	  */
#include <stdlib.h> 	/* exit 	  */
#include <signal.h> 	/* sigaction  */
#include <string.h>		/* atoi 	  */

void SAHandler(int sig);
void ProcessFunc();

int main(int argc, char *argv[])
{
	(void)argc;
	ProcessFunc((pid_t)atoi(argv[1]));

	return (0);
}

void SAHandler(int sig)
{
	(void)sig;

	write(0, "PONG\n", 5);
}

void ProcessFunc(pid_t sending_pid)
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	act.sa_handler = SAHandler;

	if (0 > sigaction(SIGUSR2, &act, NULL))
	{
		perror("sigaction failed");
		exit(-1);
	}

	while (1)
	{
		sleep(1);

		kill((pid_t)sending_pid, SIGUSR1);

		pause();
	}
}

#endif /* _POSIX_C_SOURCE */
