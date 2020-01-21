/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SEMH_HOOK_INCLUDE_H_
#define _CP_SEMH_HOOK_INCLUDE_H_

#include "cp_rtp_hook_core.h"



typedef struct cp_rtp_hook_s				cp_rtp_hook_t;



#pragma pack(1)


#define CP_SEMH_HOOK_FIELDS													\
		CP_CSS_HOOK_FIELDS													\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_rtp_hook_s {
	CP_SEMH_HOOK_FIELDS												/*表示时间模块信息*/
	cp_timer_t						*timer_task;					/*表示定时任务*/
};

#pragma pack()



cp_rtp_hook_t* create_rtp_hook(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_rtp_hook_info_t *info);
cp_int32_t destroy_rtp_hook(cp_ipc_hook_manager_t *manager, cp_rtp_hook_t* rtp_hook);


#endif


