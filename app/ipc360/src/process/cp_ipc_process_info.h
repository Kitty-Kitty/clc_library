/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_IPC_PROCESS_INFO_INCLUDE_H_
#define _CP_IPC_PROCESS_INFO_INCLUDE_H_

#include "cp_ipc_process_core.h"





//typedef	struct cp_ipc_process_info_s			cp_ipc_process_info_t;
typedef void(*cp_ipc_process_cb)(cp_ipc_process_t* th);



#pragma pack(1)


#define CP_IPC_PROCESS_INFO_FIELDS										\
		CP_PROCESS_INFO_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ipc_process_info_s {
	CP_IPC_PROCESS_INFO_FIELDS
};



#pragma pack()


#endif





