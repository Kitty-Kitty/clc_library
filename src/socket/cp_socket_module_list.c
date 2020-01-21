/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#include "cp_socket_module_list.h"



/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(socket)

CP_ADD_SUB_MANAGER_DEPENDENT(
cp_module_manager_register_t,
CP_MANAGER_DEPENDENT_CALLBACK_NULL,
CP_MODULE_MANAGER_REGISTER(CP_MODULE_MANAGER_TYPE_SOCKET(1),
1, "uv_socket_module_manager", "uv socket module manager", create_uv_socket_manager, destroy_uv_socket_manager));

CP_MODULE_MANAGER_DEPENDENT_END()





/************************************************************************/
/* 添加内存模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(socket)

CP_ADD_MODULE_DEPENDENT(
cp_module_register_t,
CP_MODULE_MANAGER_TYPE_SOCKET(1),
CP_MODULE_DEPENDENT_CALLBACK_NULL,
CP_MODULE_REGISTER(CP_MODULE_TYPE_SOCKET(1),
1, "socket_module", "socket module", create_uv_socket, destroy_uv_socket));

CP_MODULE_DEPENDENT_END()
