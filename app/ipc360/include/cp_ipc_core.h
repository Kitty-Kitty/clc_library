
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_ipc main include file 

**************************************************************************/


#ifndef _CP_IPC_CORE_INCLUDE_H_
#define _CP_IPC_CORE_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>


typedef	struct cp_ipc_info_s							cp_ipc_info_t;
typedef	struct cp_media_server_info_s					cp_media_server_info_t;
typedef struct cp_media_play_manager_s					cp_media_play_manager_t;
typedef struct cp_ipc_s								cp_ipc_t;




#include "cp_core.h"
#include "cp_include.h"
#include "cp_ipc_version.h"
#include "cp_ipc_default.h"
#include "css_core.h"
#include "cp_ipc_module_type.h"
#include "cp_ipc_socket_data.h"
#include "cp_ipc_conf_string.h"
#include "cp_ipc_heartbeat.h"
#include "cp_channel_manager.h"
#include "cp_media_play.h"
#include "cp_ipc_info.h"
#include "cp_media_server_info.h"
#include "cp_ipc.h"



#include "cp_ipc_proc.h"



#endif