/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_IPC_PROCESS_INCLUDE_H_
#define _CP_IPC_PROCESS_INCLUDE_H_

#include "cp_ipc_process_core.h"
#include "cp_socket.h"



//typedef struct cp_ipc_process_s					cp_ipc_process_t;



#pragma pack(1)



#define CP_IPC_PROCESS_FIELDS											\
		CP_PROCESS_FIELDS													\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ipc_process_s {
	CP_IPC_PROCESS_FIELDS												/*表示时间模块信息*/
};


#pragma pack()


cp_ipc_process_t* create_ipc_process(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ipc_process_info_t *info);
cp_int32_t destroy_ipc_process(cp_ipc_process_manager_t *manager, cp_ipc_process_t* ipc_process);


#endif


