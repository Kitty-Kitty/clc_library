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
/* ��ʾ��ptp����                                                         */
/************************************************************************/
struct cp_group_timestamp_s
{
	cp_int32_t						id;									//��ʾ��id
	cp_timespec_t					time;								//��ʾptpʱ��
};



struct cp_player_timestamp_s
{
	cp_group_timestamp_t			ptp_timestamp;					//
	struct timeval					system_timestamp;				//��ʾϵͳ��ǰʱ��
	cp_atomic_t						offset_sec;						//��ʾptp�͵�ǰ�����ֵ
	cp_atomic_t						offset_nsec;					//��ʾptp�͵�ǰ�������ֵ
	cp_atomic64_t					offset_ns;						//��ʾoffset_sec �� offset_nsec����Ľ��,��λ���룬����64λ��ԭ�Ӳ���ȫ
};


//����timestamp
cp_int32_t cp_player_update_timestamp(cp_player_timestamp_t *pt, cp_group_timestamp_t *gt);
cp_timespec_t cp_player_systoptp(cp_player_timestamp_t *pt, cp_timeval *sys_tv);
cp_timeval cp_player_ptptosys(cp_player_timestamp_t *pt, cp_timespec_t *ptp_ts);

//����ʱ����
cp_timespec_t cp_player_ptp_offset(cp_player_timestamp_t *pt, cp_timespec_t *ptp_ts);

#pragma pack()



#endif