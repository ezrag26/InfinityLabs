#ifndef __OL73_WATCHDOG_H__
#define __OL73_WATCHDOG_H__

#include "wd_main.h"	/* InitSemaphore, InitScheduler, InitSignalHandler 	*/
/**
 * This program watches over a specified area of code of a user program
 * indiciated by the user, communicating with the process spcecified interval,
 * and will rerun the user program automatically if the current process becomes
 * unresponsive.
 */
 
 /**
 * IMPORTANT NOTICE! The wd executable file should be placed within the same
 * folder that the user application is executed from and should remain with the
 * same file name for the watchdog program to work.
 */

/**
 * Starts watching over the code found after the function call
 * @param sig_interval, the interval at which the user's program and wd_main.c
 * should communicate with each other
 * @param interval_mult, a multiplier indicating how many intervals may pass
 * without receiving a signal before reviving the unresponsive program
 * @return returns a pointer to be passed in DNR() when the critical code has
 * ended and there is no longer a need for checking
 *
 * Multiple calls to MMI() before calling DNR() results in undefined behavior
 * An interval_mult less than 3 results in undefined behavior
 */
wd_t *MMI(unsigned int sig_interval, unsigned int interval_mult, char *argv[]);

/**
 * Ends watching over the critical code, cleaning up memory traces upon exit
 * @param wd, a pointer returned from MMI()
 * @return, does not return anything
 * A program that calls MMI() but does not call DNR() will not end unless
 * terminated
 */
void DNR(wd_t *wd);

#endif /* __OL73_WATCHDOG_H__ */
