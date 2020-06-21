#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif /* _POSIX_C_SOURCE */

#ifndef _XOPEN_SOURCE
#define _DEFAULT_SOURCE
#endif /* _XOPEN_SOURCE */

#define ENV_BUFFER_SIZE (26)

#include <stdio.h>		/* printf	  										*/
#include <semaphore.h> 	/* sem_wait, sem_post 								*/
#include <fcntl.h>      /* For O_* constants 								*/
#include <sys/stat.h>   /* For mode constants 								*/
#include <stdlib.h>		/* putenv, getenv, unsetenv, exit					*/
#include <signal.h> 	/* sigaction, kill									*/
#include <sys/types.h>  /* fork, kill										*/
#include <unistd.h> 	/* fork, exec 										*/
#include <sys/wait.h> 	/* wait 	  										*/
#include <pthread.h>	/* pthread_t										*/

#include "watchdog_user.h"
#include "scheduler.h" 	/* SchedulerCreate, SchedulerAdd, SchedulerRun 		*/
#include "utils.h"		/* PRNT_ERR 										*/

/* Link with -pthread*/

/***************************** Service Functions ******************************/
static void CleanUpWatchDogUser(void *param)
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

	pthread_join(args->wd->thread, NULL);
}

static void *WatchDogThread(void *param)
{
	args_t *args = (args_t *)param;
	scheduler_t *sched = SchedulerCreate();
	sem_t *sem1_ptr = InitSemaphore("/sem1");
	sem_t *sem2_ptr = InitSemaphore("/sem2");

	if (NULL == sched)
	{
		PRNT_ERR("SchedulerCreate");
		CleanUpWatchDogUser(args);
		return (NULL);
	}

	if (SEM_FAILED == sem1_ptr || SEM_FAILED == sem2_ptr)
	{
		PRNT_ERR("InitSemaphore");
		CleanUpWatchDogUser(args);
		return (NULL);
	}

	if (0 != InitSignalHandler(SIGUSR1, SAHandler))
	{
		PRNT_ERR("InitSignalHandler");
		CleanUpWatchDogUser(args);
		return (NULL);
	}

	args->sem_ptr = sem2_ptr;
	args->wd->sched_ptr = sched;

	if (UIDIsBad(SchedulerAdd(sched,
							  SignalAndRevive,
							  args,
							  args->sig_interval)))
	{
		PRNT_ERR("SchedulerAdd");
		CleanUpWatchDogUser(args);
		return (NULL);
	}

	/* WatchDog is not already running */
	if (NULL == getenv("IS_WATCHDOG_INIT"))
	{
		char sig_interval_e[ENV_BUFFER_SIZE] = {0};
		char interval_mul_e[ENV_BUFFER_SIZE] = {0};

		/* pass along sig_interval and interval_mult to WatchDog */
		sprintf(sig_interval_e, "SIG_INTERVAL_E=%u", args->sig_interval);
		sprintf(interval_mul_e, "INTERVAL_MUL_E=%u", args->interval_mult);

		putenv(sig_interval_e);
		putenv(interval_mul_e);

		args->target_pid = fork();
		if (0 > args->target_pid)
		{
			PRNT_ERR("fork");
			CleanUpWatchDogUser(args);
			exit(1);
		}
		else if (0 == args->target_pid)
		{
			execvp(args->file, args->argv);
			PRNT_ERR("execvp");
			CleanUpWatchDogUser(args);
			exit(1);
		}

		/* Wait for WatchDog to be fully initialized */
		if (0 != sem_wait(sem2_ptr))
		{
			PRNT_ERR("sem_wait");
			CleanUpWatchDogUser(args);
			return (NULL);
		}
	}
	else /* WatchDog is already running */
	{
		args->target_pid = getppid(); /* Watchdog must have revived UserApp */

		/* WatchDogThread is ready, WatchDog can continue */
		if (0 != sem_post(sem2_ptr))
		{
			PRNT_ERR ("sem_post");
			CleanUpWatchDogUser(args);
			return (NULL);
		}
	}

	/* Everyone is ready, let MMI continue */
	if (0 != sem_post(sem1_ptr))
	{
		PRNT_ERR("sem_post");
		CleanUpWatchDogUser(args);
		return (NULL);
	}

	/* Scheduler stopped, either it failed or DNR stopped it */
	if (0 != SchedulerRun(sched))
	{
		/* SchedulerRun failed */
		if (2 != SchedulerRun(sched))
		{
			PRNT_ERR("SchedulerRun");
			CleanUpWatchDogUser(args);
			return (NULL);
		}
		else /* Stopped by DNR */
		{
			/* Send signal to main WatchDog to clean up */
			kill(args->target_pid, SIGUSR2);

			SchedulerDestroy(sched);

			/* close open semaphores */
			sem_close(sem1_ptr);
			sem_close(sem2_ptr);
		}
	}


	return (NULL);
}

/************************************ MMI *************************************/
wd_t *MMI(unsigned int sig_interval, unsigned int interval_mult, char *argv[])
{
	static args_t args = {0};
	wd_t *wd_args = (wd_t *)malloc(sizeof(wd_t));
	sem_t *sem1_ptr = NULL;
	pthread_t thread = 0;

	if (SEM_FAILED == (sem1_ptr = InitSemaphore("/sem1")))
	{
		PRNT_ERR("InitSemaphore");
		return (NULL);
	}

	args.argv = argv;
	args.sig_interval = sig_interval;
	args.interval_mult = interval_mult;
	args.wd = wd_args;
	args.file = "./wd";

	if (0 != pthread_create(&thread, NULL, WatchDogThread, &args))
	{
		PRNT_ERR("pthread_create");
		CleanUpWatchDogUser(&args);
		return (NULL);
	}

	/* store thread for DNR use */
	args.wd->thread = thread;

	/* MMI is ready, wait for WatchDogThread to be fully initialized */
	if (0 != sem_wait(sem1_ptr))
	{
		PRNT_ERR("sem_wait");
		CleanUpWatchDogUser(&args);
		return (NULL);
	}

	/* close opened semaphore */
	sem_close(sem1_ptr);

	return (wd_args);
}

/************************************ DNR *************************************/
void DNR(wd_t *wd)
{
	/* stop WatchDogThread scheduler */
	SchedulerStop(wd->sched_ptr);

	if (0 != pthread_join(wd->thread, NULL))
	{
		PRNT_ERR("pthread_join");
	}

	free(wd); wd = NULL;
}
