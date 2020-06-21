#include <stdio.h> 		/* printf, perror	*/
#include <unistd.h> 	/* fork, exec */
#include <sys/types.h>  /* ftok, semaphore	*/
#include <sys/ipc.h>  	/* ftok, semaphore	*/
#include <sys/sem.h> 	/* semaphore family */
#include <sys/wait.h> 	/* wait 	  */
#include <stdlib.h> 	/* exit 	  */

void PingPongFork();

int main()
{
	PingPongFork();
	return (0);
}

union semun
{
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    unsigned short *array;         /* used for GETALL and SETALL */
};

void PingPongFork()
{
	pid_t pid = 0;
	key_t key = ftok("semaphores_ping.c", 26);
	int sem_id = semget(key, 1, 0666 | IPC_CREAT);
	struct sembuf sb_add;
	struct sembuf sb_zero;
	struct sembuf sb_sub;
	union semun s;

	sb_zero.sem_num = 0;
	sb_zero.sem_op = 0;
	sb_zero.sem_flg = 0;

	sb_sub.sem_num = 0;
	sb_sub.sem_op = -1;
	sb_sub.sem_flg = 0;

	sb_add.sem_num = 0;
	sb_add.sem_op = 2;
	sb_add.sem_flg = 0;

	s.val = 2;

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

	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(-1);
	}
	else if (0 == pid)
	{
		while (1)
		{
			if (0 != semop(sem_id, &sb_zero, 1))
			{
				perror("semop_zero");
				exit(-1);
			}

			write(1, "pong\n", 5);

			if (0 != semop(sem_id, &sb_add, 1))
			{
				perror("semop_add");
				exit(-1);
			}
		}
	}

	while (1)
	{
		if (0 != semop(sem_id, &sb_sub, 1))
		{
			perror("semop_sub");
			exit(-1);
		}

		write(0, "******************************************************\n", 55);

		if (0 != semop(sem_id, &sb_sub, 1))
		{
			perror("semop_sub");
			exit(-1);
		}


	}

	wait(NULL);
	exit(-1);
}
