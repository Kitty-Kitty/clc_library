/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-02-11

Description:

**************************************************************************/

#ifndef _CP_DAEMON_INCLUDE_H_
#define _CP_DAEMON_INCLUDE_H_

#include "cp_core.h"
#include "cp_thread_core.h"




#define			CP_DAEMON_SIGNAL_THREAD_SLEEP_INTERVAL_MS				500				//默认的休眠时间



/************************************************************************/
/*添加daemon info信息                                                   */
/************************************************************************/
struct cp_daemon_info_s
{
	cp_app_t				*app;
	cp_bool_t				is_daemon;
	cp_int32_t				master_pid;
	cp_int32_t				work_pid;
	cp_thread_t				*signal_thread;
	cp_thread_cb			signal_thread_cb;
};

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_daemon_start_app
*
* 函数说明: 表示守护方式启动app
*
* 参    数: cp_app_info_t *app_info						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-12 10:46:08
******************************************************************************************************/
int cp_daemon_start_app(cp_app_info_t *app_info);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_general_start_app
*
* 函数说明: 表示普通方式启动app
*
* 参    数: cp_app_info_t * app_info						[in]参数说明
*
* 返 回 值: int
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-12 10:53:27
******************************************************************************************************/
int cp_general_start_app(cp_app_info_t *app_info);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_daemon_signal_thread_cb
*
* 函数说明: 守护方式时，子进程监听父进程状态
*
* 参    数: void * argv						[in]参数说明
*
* 返 回 值: void
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-28 17:22:01
******************************************************************************************************/
void cp_daemon_signal_thread_cb(void *argv);


#endif

