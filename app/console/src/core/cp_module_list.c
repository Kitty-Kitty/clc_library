/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_module_list.h"



/************************************************************************/
/* 这里模块的加载时有顺序的，可以根据需要按顺序初始化                                                                     */
/************************************************************************/

cp_module_manager_register_t m_module_manager_list[] = {
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_pool, 1, "pool_manager", "pool manager", create_pool_manager, destory_pool_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_thread, 1, "thread_manager", "thread manager", create_thread_manager, destory_thread_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_timer, 1, "timer_manager", "timer manager", create_timer_manager, destory_timer_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_hook, 1, "hook_manager", "hook manager", create_hook_manager, destory_hook_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_session, 1, "session_manager", "session manager", create_session_manager, destory_session_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_filter, 1, "filter_manager", "filter manager", create_filter_manager, destory_filter_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_process, 1, "process_manager", "process manager", create_process_manager, destory_process_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_func, 1, "func_manager", "func manager", create_func_manager, destory_func_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_socket, 1, "socket_manager", "socket manager", create_socket_manager, destory_socket_manager)
};


cp_int32_t m_module_manager_size = cp_array_size(m_module_manager_list);





