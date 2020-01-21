/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-29

Description:

**************************************************************************/

#ifndef _CP_IPC_FUNC_MANAGER_FLAG_INCLUDE_H_
#define _CP_IPC_FUNC_MANAGER_FLAG_INCLUDE_H_


#include "cp_core.h"



typedef	enum cp_ipc_func_flag_enum					cp_ipc_func_flag_e;



/************************************************************************/
/*                                                                      */
/************************************************************************/
enum cp_ipc_func_flag_enum
{
	cp_ipc_func_flag_socket_point = B8(10000000),
};

#endif