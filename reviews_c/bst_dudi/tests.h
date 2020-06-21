/*
 * Developer: Yossi
 * textcolor() by Pradeep Padala https://www.linuxjournal.com/article/8603
 */

#ifndef __TESTS_H__
#define __TESTS_H__

#include <stdio.h>

#define RED		31
#define GREEN	32
#define	WHITE	37

/* Pradeep Padala */
void textcolor(int attr, int fg, int bg)
{
	char command[13];
	
	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg, bg);
	printf("%s", command);
}

enum test_status {SUCCESS, FAILURE};


#define RUNTEST(test) { \
	char *status = "passed."; \
	printf(#test":\n");  \
	textcolor(1, GREEN, 3); \
	if(SUCCESS != test()) { \
	++errors; \
	status = "failed."; \
	textcolor(1, RED, 3); } \
	printf("%s\n", status); \
	textcolor(0, WHITE, 0);  \
}	

#define REQUIRE(cond) { \
	if(!((cond))) { \
	status = FAILURE; \
	fprintf(stderr, "in %s:%d ("#cond")\n", __FILE__, __LINE__); } \
}	


#endif	/*	__TESTS_H__ */

