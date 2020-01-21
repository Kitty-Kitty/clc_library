/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_thread_module_list.h"



/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(thread)

CP_ADD_SUB_MANAGER_DEPENDENT(
cp_module_manager_register_t,
CP_MANAGER_DEPENDENT_CALLBACK_NULL,
CP_MODULE_MANAGER_REGISTER(CP_MODULE_MANAGER_TYPE_THREAD(1),
1, "uv_thread_module_manager", "uv thread module manager", create_uv_thread_manager, destroy_uv_thread_manager));

CP_MODULE_MANAGER_DEPENDENT_END()





/************************************************************************/
/* 添加内存模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(thread)

CP_ADD_MODULE_DEPENDENT(
cp_module_register_t,
CP_MODULE_MANAGER_TYPE_THREAD(1),
CP_MODULE_DEPENDENT_CALLBACK_NULL,
CP_MODULE_REGISTER(CP_MODULE_TYPE_THREAD(1),
1, "thread_module", "thread module", create_uv_thread, destroy_uv_thread));

CP_MODULE_DEPENDENT_END()
