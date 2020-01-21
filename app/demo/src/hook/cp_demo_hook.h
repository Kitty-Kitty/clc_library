/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CSS_HOOK_INCLUDE_H_
#define _CP_CSS_HOOK_INCLUDE_H_

#include "cp_demo_hook_core.h"
#include "cp_demo_hook_info.h"
#include "cp_socket.h"



//typedef struct cp_demo_hook_s				cp_demo_hook_t;



#pragma pack(1)


#define CP_CSS_HOOK_FIELDS																	\
		CP_HOOK_FIELDS																		\
		cp_int32_t				command;			/*表示当前的指令编码*/					\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_demo_hook_s {
	CP_CSS_HOOK_FIELDS												/*表示时间模块信息*/
};

#pragma pack()



cp_demo_hook_t* create_demo_hook(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_demo_hook_info_t *info);
cp_int32_t destroy_demo_hook(cp_demo_hook_manager_t *manager, cp_demo_hook_t* demo_hook);






cp_int32_t cp_copy_hook(cp_hook_t *dest, cp_hook_t *src);





#endif


