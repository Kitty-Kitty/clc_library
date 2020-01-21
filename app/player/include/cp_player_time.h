/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-09

Description:

**************************************************************************/

#ifndef _CP_PLAYER_TIME_INCLUDE_H_
#define _CP_PLAYER_TIME_INCLUDE_H_


#include "cp_core.h"




typedef struct cp_group_timestamp_s					cp_group_timestamp_t;
typedef struct cp_player_timestamp_s				cp_player_timestamp_t;




#pragma pack(1)

/************************************************************************/
/* 表示组ptp数据                                                         */
/************************************************************************/
struct cp_group_timestamp_s
{
	cp_int32_t						id;									//表示组id
	cp_timespec_t					time;								//表示ptp时间
};



struct cp_player_timestamp_s
{
	cp_group_timestamp_t			ptp_timestamp;					//
	struct timeval					system_timestamp;				//表示系统当前时间
	cp_atomic_t						offset_sec;						//表示ptp和当前的秒差值
	cp_atomic_t						offset_nsec;					//表示ptp和当前的纳秒差值
	cp_atomic64_t					offset_ns;						//表示offset_sec 和 offset_nsec计算的结果,单位纳秒，数据64位，原子不安全
};


//更新timestamp
cp_int32_t cp_player_update_timestamp(cp_player_timestamp_t *pt, cp_group_timestamp_t *gt);
cp_timespec_t cp_player_systoptp(cp_player_timestamp_t *pt, cp_timeval *sys_tv);
cp_timeval cp_player_ptptosys(cp_player_timestamp_t *pt, cp_timespec_t *ptp_ts);

//计算时间间隔
cp_timespec_t cp_player_ptp_offset(cp_player_timestamp_t *pt, cp_timespec_t *ptp_ts);

#pragma pack()



#endif