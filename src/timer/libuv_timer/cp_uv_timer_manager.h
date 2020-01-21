/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_UV_TIMER_MANAGER_INCLUDE_H_
#define _CP_UV_TIMER_MANAGER_INCLUDE_H_



#include "cp_uv_timer_core.h"
#include "cp_include.h"



#define	CP_UV_TIMER_MANAGER_BEGIN_INTERVAL				1000			//默认定时器第一次启动时间
#define	CP_UV_TIMER_MANAGER_DEFAULT_INTERVAL			10000			//默认定时器间隔时间,毫秒（ms）
#define	CP_UV_TIMER_MANAGER_DEFAULT_PRINT_COUNT			100				//默认定时器运行多少次后打印消息
//typedef struct cp_uv_timer_manager_s					cp_uv_timer_manager_t;



#pragma pack(1)



/************************************************************************/
/*                                                                      */
/************************************************************************/

struct cp_uv_timer_manager_s
{
	CP_TIMER_MANAGER_FIELDS
	uv_loop_t*							loop;						/*时间循环*/
	cp_thread_t							*thread;					/*启动loop用的线程，避免阻塞*/
	uv_timer_t							uv_timer;					/*表示默认的定时器*/
	cp_int32_t							times;						/*运行次数*/
};


#pragma pack()



cp_uv_timer_manager_t* create_uv_timer_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_uv_timer_manager_info_t *info);
cp_int32_t destroy_uv_timer_manager(cp_app_t *app, cp_uv_timer_manager_t* manager);

#endif


