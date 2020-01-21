/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SOCKET_MODULE_LIST_INCLUDE_H_
#define _CP_SOCKET_MODULE_LIST_INCLUDE_H_

#include "cp_socket_core.h"
#include "cp_module_dependent.h"


#include "libuv_socket/cp_uv_socket.h"




//定义两个模块处理函数
CP_SUB_MODULE_MANAGER_DEPENDENT_FUNCTION(socket);
CP_MODULE_DEPENDENT_FUNCTION(socket);



#endif


