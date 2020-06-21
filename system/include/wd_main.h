#include <stddef.h> /* size_t */
#include <semaphore.h>

#include "scheduler_heap.h"

typedef struct wd_s
{
	scheduler_t *sched_ptr;
	pthread_t thread;
} wd_t;

typedef struct args_s
{
	char **argv;
	sem_t *sem_ptr;
	wd_t *wd;
	char *file;
	pid_t target_pid;
	unsigned int sig_interval;
	unsigned int interval_mult;
} args_t;

/**
 * Start the communication between the two processes
 * @param argv, pointer to an array of arguments that the user program was
 * executed with
 * @return returns 0 upon sucess, anything else otherwise
 */
int WatchDog(char *argv[]);

/**
 * Initializes a semaphore based on sem_name
 * @param sem_name, string that must start with "/"
 * @return returns a pointer to the created semaphore
 */
sem_t *InitSemaphore(char *sem_name);

/**
 * Initializes a signal handler based on the receiving signal and a handler func
 * @param sig, the receiving signal
 * @param handler, function to perform upon receiving signal sig
 * @return returns 0 upon success, anything else otherwise
 */
int InitSignalHandler(int sig, void (*handler)(int));

int SignalAndRevive(void *param);

void SAHandler(int sig);
