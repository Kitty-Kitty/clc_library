/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_IPC_PROC_INCLUDE_H_
#define _CP_IPC_PROC_INCLUDE_H_


#include "cp_ipc_core.h"



cp_int32_t init_ipc_other(cp_ipc_t *ipc, cp_app_info_t *app_info);
cp_int32_t start_ipc_other(cp_ipc_t *ipc, cp_app_info_t *app_info);
cp_int32_t stop_ipc_other(cp_ipc_t *ipc, cp_app_info_t *app_info);


#endif


