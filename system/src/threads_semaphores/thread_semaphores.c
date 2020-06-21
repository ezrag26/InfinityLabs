#include <stdio.h>		/* printf  */
#include <pthread.h>	/* threads */
#include <sys/types.h>  /* ftok, semaphore	*/
#include <sys/ipc.h>  	/* ftok, semaphore	*/
#include <sys/sem.h> 	/* semaphore family */
#include <stdlib.h> 	/* exit 	  */
#include <unistd.h> 	/* fork, exec, sleep, write */

void PingPongThread();

int main()
{
	PingPongThread();
	return (0);
}

union semun
{
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    unsigned short *array; /* used for GETALL and SETALL */
};

struct sembuf sb_add;
struct sembuf sb_zero;
struct sembuf sb_sub;

void *Pong(void *sem_id)
{
	size_t i = 9999;

	while (--i)
	{
		if (0 != semop(*(int *)sem_id, &sb_zero, 1))
		{
			perror("semop_zero");
			exit(-1);
		}

		write(1, "pong\n", 5);

		if (0 != semop(*(int *)sem_id, &sb_add, 1))
		{
			perror("semop_add");
			exit(-1);
		}
	}
}

void *Ping(void *sem_id)
{
	size_t i = 9999;

	while (--i)
	{
		if (0 != semop(*(int *)sem_id, &sb_sub, 1))
		{
			perror("semop_sub");
			exit(-1);
		}

		write(0, "ping ", 5);

		if (0 != semop(*(int *)sem_id, &sb_sub, 1))
		{
			perror("semop_sub");
			exit(-1);
		}
	}
}

int InitSemaphore(char *file, int proj_id, size_t num_of_sems, int start_val)
{
	key_t key = ftok(file, proj_id);
	int sem_id = semget(key, num_of_sems, 0666 | IPC_CREAT);
	union semun s;

	s.val = start_val;

	if (-1 == key)
	{
		perror("ftok");
		exit(-1);
	}

	if (-1 == sem_id)
	{
		perror("semget");
		exit(-1);
	}

	if (-1 == semctl(sem_id, 0, SETVAL, s))
	{
		perror("semctl");
		exit(-1);
	}

	return (sem_id);
}

void PingPongThread()
{
	pthread_t thread_1;
	pthread_t thread_2;

	int sem_id = InitSemaphore("thread_semaphores.c", 26, 1, 2);

	sb_add.sem_num = 0;
	sb_add.sem_op = 2;
	sb_add.sem_flg = 0;

	sb_zero.sem_num = 0;
	sb_zero.sem_op = 0;
	sb_zero.sem_flg = 0;

	sb_sub.sem_num = 0;
	sb_sub.sem_op = -1;
	sb_sub.sem_flg = 0;

	if (0 != pthread_create(&thread_1, NULL, Ping, &sem_id))
	{
		perror("pthread_create");
		exit(1);
	}

	if (0 != pthread_create(&thread_2, NULL, Pong, &sem_id))
	{
		perror("pthread_create");
		exit(1);
	}

	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
}
