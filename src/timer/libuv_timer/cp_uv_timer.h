/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_UV_TIMER_INCLUDE_H_
#define _CP_UV_TIMER_INCLUDE_H_

#include "cp_uv_timer_core.h"



//typedef struct cp_uv_timer_s				cp_uv_timer_t;



#pragma pack(1)


#define CP_UV_TIMER_FIELDS									\
		CP_TIMER_FIELDS


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_uv_timer_s {
	CP_UV_TIMER_FIELDS												/*表示时间模块信息*/
	uv_timer_t							uv_timer;
};

#pragma pack()




cp_uv_timer_t* create_uv_timer(cp_module_register_t *register_info, cp_timer_manager_t *manager, cp_uv_timer_info_t *info);
cp_int32_t destroy_uv_timer(cp_timer_manager_t *manager, cp_uv_timer_t* timer);


#endif


