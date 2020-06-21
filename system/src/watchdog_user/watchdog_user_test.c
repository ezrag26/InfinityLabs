#include <stdio.h>	/* puts */
#include <unistd.h>	/* sleep */
#include "watchdog_user.h"

int main(int argc, char *argv[])
{
	unsigned int sig_interval = 3;
	unsigned int interval_mult = 3;
	wd_t *wd = MMI(sig_interval, interval_mult, argv);
	int counter = 20;

	(void)argc;

	puts("----------UserApp Start----------");
	while(counter--)
	{
		sleep(1);
	}
	DNR(wd);
	puts("----------UserApp End----------");

	return (0);
}
