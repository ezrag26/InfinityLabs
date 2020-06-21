#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
	printf("I am a process with pid %d\n", getpid());
	return (0);
}
