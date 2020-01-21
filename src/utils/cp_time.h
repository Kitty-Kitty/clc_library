/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-06

Description:

**************************************************************************/

#ifndef _CP_TIME_INCLUDE_H_
#define _CP_TIME_INCLUDE_H_

#include "cp_core.h"



#define			CP_TIME_SEC_TO_MSEC				1000LL											//表示1秒所包含的毫秒
#define			CP_TIME_MSEC_TO_NSEC			1000000LL										//表示1毫秒所包含的纳秒
#define			CP_TIME_SEC_TO_NSEC				1000000000LL									//表示1秒所包含的纳秒
#define			CP_TIME_SEC_TO_USEC				1000000LL										//表示1秒所包含的微秒
#define			CP_TIME_USEC_TO_NSEC			1000LL											//表示1微秒所包含的纳秒



#if defined(WIN32)
typedef			struct cp_timespec_s			cp_timespec_t;
#else
typedef			struct timespec					cp_timespec_t;
#endif

#pragma  pack(1)

#if defined(WIN32)
struct cp_timespec_s
{
	cp_uint32_t			tv_sec;					//秒部分
	cp_uint32_t			tv_nsec;				//纳秒部分
};
#endif
#pragma  pack()


int cp_sleep_ns(unsigned int tv_sec, unsigned int tv_nsec);

#endif