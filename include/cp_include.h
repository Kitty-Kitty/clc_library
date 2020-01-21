/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_INCLUDE_INCLUDE_H_
#define _CP_INCLUDE_INCLUDE_H_

#include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
#if defined __linux__
#include <errno.h> 
#endif



#ifdef __cplusplus
extern "C" {
#endif



#include "cp_core.h"


#include "cp_file_system.h"
#include "cp_conf.h"
#include "cp_module_core.h"
#include "cp_app_core.h"
#include "cp_timer_core.h"
#include "cp_pool_core.h"
#include "cp_thread_core.h"
#include "cp_socket_core.h"
#include "cp_hook_core.h"
#include "cp_session_core.h"
#include "cp_process_core.h"
#include "cp_filter_core.h"
#include "cp_func_core.h"
#include "cp_codec_core.h"
#include "cp_dev_core.h"



#ifdef __cplusplus
}
#endif


#endif