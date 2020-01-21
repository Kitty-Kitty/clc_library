/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_module_list.h"



cp_module_manager_register_t m_module_manager_list[] = {
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_pool, 1, "pool_manager", "pool manager", create_pool_manager, destroy_pool_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_thread, 1, "thread_manager", "thread manager", create_thread_manager, destroy_thread_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_timer, 1, "timer_manager", "timer manager", create_timer_manager, destroy_timer_manager)
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_socket, 1, "socket_manager", "socket manager", create_socket_manager, destroy_socket_manager)
};


cp_int32_t m_module_manager_size = cp_sizeof(m_module_manager_list) / cp_sizeof(cp_module_manager_register_t);


