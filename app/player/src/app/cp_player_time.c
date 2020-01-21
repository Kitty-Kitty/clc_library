/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-10

Description:

**************************************************************************/
#include "cp_player_time.h"



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_player_update_timestamp
*
* 函数说明: 更新ptp时间
*
* 参    数: cp_player_timestamp_t * pt						[in]参数说明
* 参    数: cp_group_timestamp_t * gt						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-10 18:06:59
******************************************************************************************************/
cp_int32_t cp_player_update_timestamp(cp_player_timestamp_t *pt, cp_group_timestamp_t *gt)
{
	cp_int64_t									tmp_offset_us = 0;


	pt->ptp_timestamp = *gt;
	cp_gettimeofday(&(pt->system_timestamp), CP_NULL);

	//更新ptp时间差
	tmp_offset_us = (pt->system_timestamp.tv_sec - gt->time.tv_sec) * CP_TIME_SEC_TO_USEC +
		(pt->system_timestamp.tv_usec - (gt->time.tv_nsec / CP_TIME_USEC_TO_NSEC));

	pt->offset_sec = (cp_int32_t)(tmp_offset_us / CP_TIME_SEC_TO_USEC);
	pt->offset_nsec = (cp_int32_t)((tmp_offset_us % CP_TIME_SEC_TO_USEC) * CP_TIME_USEC_TO_NSEC);
	pt->offset_ns = tmp_offset_us * CP_TIME_USEC_TO_NSEC;

	return 0;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_player_systoptp
*
* 函数说明: 系统时间转ptp时间
*
* 参    数: cp_player_timestamp_t * pt						[in]参数说明
* 参    数: cp_timeval * sys_tv						[in]参数说明
*
* 返 回 值: cp_timespec_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-10 18:07:15
******************************************************************************************************/
cp_timespec_t cp_player_systoptp(cp_player_timestamp_t *pt, cp_timeval *sys_tv)
{
	cp_int64_t						tmp_ns = 0;
	cp_timespec_t					tmp_ts = { 0, };



	tmp_ns = sys_tv->tv_sec * CP_TIME_SEC_TO_NSEC + sys_tv->tv_usec * CP_TIME_USEC_TO_NSEC;
	tmp_ns -= pt->offset_ns;
	tmp_ts.tv_sec = (cp_uint32_t)(tmp_ns / CP_TIME_SEC_TO_NSEC);
	tmp_ts.tv_nsec = tmp_ns % CP_TIME_SEC_TO_NSEC;

	return tmp_ts;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_player_ptptosys
*
* 函数说明: ptp时间转系统时间
*
* 参    数: cp_player_timestamp_t * pt						[in]参数说明
* 参    数: cp_timespec_t * ptp_ts						[in]参数说明
*
* 返 回 值: cp_timeval
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-10 18:07:38
******************************************************************************************************/
cp_timeval cp_player_ptptosys(cp_player_timestamp_t *pt, cp_timespec_t *ptp_ts)
{
	cp_int64_t						tmp_ns = 0;
	cp_timeval						tmp_tv = { 0, };



	tmp_ns = ptp_ts->tv_sec * CP_TIME_SEC_TO_NSEC + ptp_ts->tv_nsec;
	tmp_ns += pt->offset_ns;
	tmp_tv.tv_sec = (long)(tmp_ns / CP_TIME_SEC_TO_NSEC);
	tmp_tv.tv_usec = (tmp_ns % CP_TIME_SEC_TO_NSEC) / CP_TIME_USEC_TO_NSEC;

	return tmp_tv;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_player_ptp_offset
*
* 函数说明: 时间差值
*
* 参    数: cp_player_timestamp_t * pt						[in]参数说明
* 参    数: cp_timespec_t * ptp_ts						[in]参数说明
*
* 返 回 值: cp_timespec_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-10 18:07:57
******************************************************************************************************/
cp_timespec_t cp_player_ptp_offset(cp_player_timestamp_t *pt, cp_timespec_t *ptp_ts)
{
	cp_int64_t						tmp_ns = 0;
	cp_timespec_t					tmp_ts = { 0, };
	cp_timeval						tmp_sys_tv = { 0, };
	cp_timeval						tmp_current_sys_tv = { 0, };


	tmp_sys_tv = cp_player_ptptosys(pt, ptp_ts);
	cp_gettimeofday(&tmp_current_sys_tv, CP_NULL);

	tmp_ns = ((cp_int64_t)tmp_sys_tv.tv_sec - (cp_int64_t)tmp_current_sys_tv.tv_sec) * CP_TIME_SEC_TO_NSEC +
		((cp_int64_t)tmp_sys_tv.tv_usec - (cp_int64_t)tmp_current_sys_tv.tv_usec) * CP_TIME_USEC_TO_NSEC;

	if (tmp_ns > 0) {
		tmp_ts.tv_sec = (cp_uint32_t)(tmp_ns / CP_TIME_SEC_TO_NSEC);
		tmp_ts.tv_nsec = tmp_ns % CP_TIME_SEC_TO_NSEC;
	}

	return tmp_ts;
}
