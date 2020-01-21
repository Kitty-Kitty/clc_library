/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HOOK_MANAGER_INCLUDE_H_
#define _CP_HOOK_MANAGER_INCLUDE_H_

#include "cp_hook_core.h"




typedef struct cp_hook_manager_s					cp_hook_manager_t;



#pragma pack(1)


#define CP_HOOK_MANAGER_FIELDS																				\
		CP_MODULE_MANAGER_FIELDS																			\
		cp_hook_t							**hook_array;			/*表示创建的hook列表*/					\

struct cp_hook_manager_s
{
	CP_HOOK_MANAGER_FIELDS
};

#pragma pack()




cp_hook_manager_t* create_hook_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_hook_manager_info_t *info);
cp_int32_t destroy_hook_manager(cp_app_t *app, cp_hook_manager_t* manager);



#endif


