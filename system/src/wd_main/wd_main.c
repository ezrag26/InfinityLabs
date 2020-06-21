#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif /* _POSIX_C_SOURCE */

#ifndef _XOPEN_SOURCE
#define _DEFAULT_SOURCE
#endif /* _XOPEN_SOURCE */

#include <stdio.h>		/* printf	  					*/
#include <semaphore.h> 	/* sem_wait, sem_post 			*/
#include <fcntl.h>      /* For O_* constants 			*/
#include <sys/stat.h>   /* For mode constants 			*/
#include <stdlib.h>		/* putenv, getenv, exit, atoi	*/
#include <signal.h> 	/* sigaction, kill				*/
#include <sys/types.h>  /* fork, kill					*/
#include <unistd.h> 	/* fork, exec 					*/

#include "wd_main.h"
#include "utils.h"		/* PRNT_ERR 					*/

static sig_atomic_t signal_g = 0;
static sig_atomic_t dnr_was_called_g = 0;

/***************************** Service Functions ******************************/
static void DNRHandler(int sig)
{
	(void)sig;

	dnr_was_called_g = 1;
}

static void CleanUpWatchDog(void *param)
{
	args_t *args = (args_t *)param;

	if (NULL != args->wd->sched_ptr)
	{
		SchedulerDestroy(args->wd->sched_ptr);
	}

	if (NULL != args->sem_ptr)
	{
		sem_close(args->sem_ptr);
	}
}

/********************************* SAHandler **********************************/
void SAHandler(int sig)
{
	(void)sig;

	signal_g = 0;
}

/***************************** InitSignalHandler ******************************/
int InitSignalHandler(int SIG, void (*handler)(int))
{
	struct sigaction sa;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;

	if (0 > sigaction(SIG, &sa, NULL))
	{
		PRNT_ERR("sigaction");
		return (1);
	}

	return (0);
}

/******************************* InitSemaphore ********************************/
sem_t *InitSemaphore(char *sem_name)
{
	sem_t *sem_ptr = sem_open(sem_name, O_CREAT, 0666, 0);

	return (sem_ptr);
}

/************************************ Task ************************************/
int SignalAndRevive(void *param)
{
	args_t *args = (args_t *)param;

	if (1 == dnr_was_called_g)
	{
		return (2);
	}

	/* send signal to WatchDogThread indicating this program is still working */
	kill(args->target_pid, SIGUSR1);

	++signal_g;

	/* UserApp is no longer sending signals */
	if ((unsigned int)signal_g >= args->interval_mult)
	{
		args->target_pid = fork();
		if (0 > args->target_pid)
		{
			PRNT_ERR("fork");
			CleanUpWatchDog(args);
			exit(1);
		}
		else if (0 == args->target_pid) /* Revive with all original arguments */
		{
			execvp(args->file, args->argv);
			PRNT_ERR("execvp");
			CleanUpWatchDog(args);
			exit(1);
		}

		signal_g = 0; 								 /* Reset global variable */

		/* wait for WatchDog Thread to be fully initialized */
		if (0 != sem_wait(args->sem_ptr))
		{
			PRNT_ERR("sem_wait");
			CleanUpWatchDog(args);
			return (1);
		}
	}

	return (0);
}

/********************************** WatchDog **********************************/

int WatchDog(char *argv[])
{
	static args_t args = {0};
	scheduler_t *sched = SchedulerCreate();
	sem_t *sem2_ptr = NULL;
	pid_t target_pid = getppid();
	char *sig_interval_e = getenv("SIG_INTERVAL_E");
	char *interval_mul_e = getenv("INTERVAL_MUL_E");

	if (NULL == sched)
	{
		PRNT_ERR("SchedulerCreate");
		CleanUpWatchDog(&args);
		return (1);
	}

	if (SEM_FAILED == (sem2_ptr = InitSemaphore("/sem2")))
	{
		PRNT_ERR("InitSemaphore");
		CleanUpWatchDog(&args);
		return (1);
	}

	if (NULL == sig_interval_e || NULL == interval_mul_e)
	{
		PRNT_ERR("getenv");
		CleanUpWatchDog(&args);
		return (1);
	}

	args.argv = argv;
	args.sem_ptr = sem2_ptr;
	args.target_pid = target_pid;
	args.sig_interval = (unsigned int)atoi(sig_interval_e);
	args.interval_mult = (unsigned int)atoi(interval_mul_e);
	args.file = argv[0];

	/* if user process fails, it won't try to exec wd_main if this exists */
	putenv("IS_WATCHDOG_INIT=1");

	if (0 != InitSignalHandler(SIGUSR1, SAHandler) ||
		0 != InitSignalHandler(SIGUSR2, DNRHandler))
	{
		PRNT_ERR("InitSignalHandler");
		CleanUpWatchDog(&args);
		return (1);
	}

	if (UIDIsBad(SchedulerAdd(sched,
							  SignalAndRevive,
							  &args,
							  args.sig_interval)))
	{
		PRNT_ERR("SchedulerAdd");
		CleanUpWatchDog(&args);
		return (1);
	}

	/* WatchDog is ready, WatchDog Thread can continue */
	if (0 != sem_post(sem2_ptr))
	{
		PRNT_ERR("sem_post");
		CleanUpWatchDog(&args);
		return (1);
	}

	if (0 != SchedulerRun(sched))
	{
		PRNT_ERR("SchedulerRun");
		CleanUpWatchDog(&args);
		return (1);
	}

	SchedulerDestroy(sched);
	sem_close(sem2_ptr);

	return (0);
}
