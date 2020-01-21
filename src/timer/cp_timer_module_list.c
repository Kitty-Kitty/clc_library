/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_timer_module_list.h"



/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(timer)

CP_ADD_SUB_MANAGER_DEPENDENT(
cp_module_manager_register_t,
CP_MANAGER_DEPENDENT_CALLBACK_NULL,
CP_MODULE_MANAGER_REGISTER(CP_MODULE_MANAGER_TYPE_TIMER(1),
1, "uv_timer_module_manager", "uv timer module manager", create_uv_timer_manager, destroy_uv_timer_manager));

CP_MODULE_MANAGER_DEPENDENT_END()





/************************************************************************/
/* 添加内存模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(timer)

CP_ADD_MODULE_DEPENDENT(
cp_module_register_t,
CP_MODULE_MANAGER_TYPE_TIMER(1),
CP_MODULE_DEPENDENT_CALLBACK_NULL,
CP_MODULE_REGISTER(CP_MODULE_TYPE_TIMER(1),
1, "timer_module", "timer module", create_uv_timer, destroy_uv_timer));

CP_MODULE_DEPENDENT_END()

