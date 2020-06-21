#include <stdio.h> 		/* printf, perror	*/
#include <unistd.h> 	/* fork, exec, sleep */
#include <sys/types.h>  /* ftok, semaphore	*/
#include <sys/ipc.h>  	/* ftok, semaphore	*/
#include <sys/sem.h> 	/* semaphore family */
#include <stdlib.h> 	/* exit, write */

void Ping();

int main()
{
	Ping();
	return (0);
}

union semun
{
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    unsigned short *array;         /* used for GETALL and SETALL */
};

void Ping()
{
	size_t i = 4500;
	key_t key = ftok("semaphores_ping.c", 26);
	int sem_id = semget(key, 1, 0666 | IPC_CREAT);
	struct sembuf sb_sub;
	union semun s;

	sb_sub.sem_num = 0;
	sb_sub.sem_op = -1;
	sb_sub.sem_flg = 0;

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

	while (i--)
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
}
