#include "wd_main.h"
#include "utils.h"


int main(int argc, char *argv[])
{
	(void)argc;
	puts("WatchDog Start");
	WatchDog(argv);
	puts("WatchDog End");
	return 0;
}
