#include <stdio.h> 		/* printf 			*/
#include <sys/types.h>  /* ftok, semaphore	*/
#include <sys/ipc.h>  	/* ftok, semaphore	*/
#include <sys/sem.h> 	/* semaphore family */
#include <stdlib.h> 	/* exit 	  */
#include <unistd.h>		/* sleep, write */

void Pong();

int main()
{
	Pong();
	return (0);
}

void Pong()
{
	size_t i = 4500;
	key_t key = ftok("semaphores_ping.c", 26);
	int sem_id = semget(key, 1, 0666 | IPC_CREAT);
	struct sembuf sb_add;
	struct sembuf sb_zero;

	sb_add.sem_num = 0;
	sb_add.sem_op = 2;
	sb_add.sem_flg = 0;

	sb_zero.sem_num = 0;
	sb_zero.sem_op = 0;
	sb_zero.sem_flg = 0;

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

	while (i--)
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
