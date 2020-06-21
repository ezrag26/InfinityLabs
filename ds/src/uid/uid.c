#include <unistd.h>	/* getpid */

#include "uid.h"

static size_t num = 0;

const u_id_t BAD_UID = {0, -1, 0};

u_id_t UIDCreate()
{
	u_id_t uid = {0};

	uid.num = ++num;
	uid.timestamp = time(NULL);
	uid.pid = getpid();

	return (uid);
}

int UIDIsSame(u_id_t uid1, u_id_t uid2)
{
	return (uid1.num == uid2.num &&
			uid1.timestamp == uid2.timestamp &&
			uid1.pid == uid2.pid);
}

int UIDIsBad(u_id_t uid)
{
	return (UIDIsSame(uid, BAD_UID));
}
