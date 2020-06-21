#ifndef __OL73_UID_H__
#define __OL73_UID_H__

#include <sys/types.h> /* pid_t  */
#include <time.h>	   /* time_t */
#include <stddef.h>	   /* size_t */

typedef struct uid u_id_t;

extern u_id_t bad_uid;

struct uid
{
	size_t num;
	time_t timestamp;
	pid_t pid;
};

/*
 * Creates a new UID
 * Returns new UID
 * Time Complexity: O(1)
 */
u_id_t UIDCreate();

/*
 * Checks if given uids, uid1 and uid2, are the same
 * Returns 1 if they are the same, 0 otherwise
 * Time Complexity: O(1)
 */
int UIDIsSame(u_id_t uid1, u_id_t uid2);

/*
 * Checks if a given uid is valid
 * Returns 1 if uid is bad, 0 otherwise
 * Time Complexity: O(1)
 */
int UIDIsBad(u_id_t uid);

#endif /* __OL73_UID_H__ */
