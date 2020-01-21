/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-26

Description:

**************************************************************************/
#include "cp_time.h"


int cp_sleep_ns(unsigned int tv_sec, unsigned int tv_nsec)
{
#if defined(__linux__)
	struct timespec requested = {0,};
	struct timespec remaining = {0,};
	requested.tv_sec = tv_sec;
	requested.tv_nsec = tv_nsec;

	while (nanosleep(&requested, &remaining) == -1)
		if (errno == EINTR)
			requested = remaining;
		else {
			break;
		}

		/*
		us_time = ns_time / 1000;
		if (us_time > 0)
		{
		struct timeval delay;
		delay.tv_sec = 0;
		delay.tv_usec = us_time;
		select(0, NULL, NULL, NULL, &delay);
		}
		*/

#else
	int				ms_time = 0;


	ms_time = (tv_sec * CP_TIME_SEC_TO_MSEC) + (unsigned int)(tv_nsec / CP_TIME_MSEC_TO_NSEC);
	if (ms_time < 1 || ms_time > 3600000) {
		cp_sleep_msec(10);
	}
	else {
		cp_sleep_msec(ms_time);
	}

#endif

	return 0;
}