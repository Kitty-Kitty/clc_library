/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_TIMER_INCLUDE_H_
#define _CP_TIMER_INCLUDE_H_

#include "cp_timer_core.h"



//typedef struct cp_timer_s				cp_timer_t;



#pragma pack(1)


#define CP_TIMER_FIELDS													\
		CP_MODULE_FIELDS												\
		cp_timer_cb	timer_cb;											\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_timer_s {
	CP_TIMER_FIELDS												/*表示时间模块信息*/
};

#pragma pack()



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_create_timer
*
* 函数说明: 创建一个定时器
*
*
* 返 回 值: cp_timer_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-27 14:52:50
******************************************************************************************************/
cp_timer_t *cp_create_timer(const cp_app_t *app);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_start_timer
*
* 函数说明: 启动一个定时器
*
* 参    数: cp_timer_t * timer						[in]定时器
* 参    数: cp_timer_cb timer_cb						[in]定时回调函数
* 参    数: cp_uint64_t timeout						[in]定时器超时时间
* 参    数: cp_uint64_t repeat						[in]是否重复
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-27 14:53:04
******************************************************************************************************/
cp_int32_t cp_start_timer(cp_timer_t *timer, cp_timer_cb timer_cb, cp_uint64_t timeout, cp_uint64_t repeat);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_stop_timer
*
* 函数说明: 停止一个定时器
*
* 参    数: cp_timer_t * timer						[in]定时器
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-27 14:53:48
******************************************************************************************************/
cp_int32_t cp_stop_timer(cp_timer_t *timer);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_destroy_timer
*
* 函数说明: 销毁定时器
*
* 参    数: cp_timer_t * timer						[in]定时器
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-27 14:54:06
******************************************************************************************************/
cp_int32_t cp_destroy_timer(cp_timer_t *timer);

#endif


