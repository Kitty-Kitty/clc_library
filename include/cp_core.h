/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CORE_INCLUDE_H_
#define _CP_CORE_INCLUDE_H_

#include <stdio.h>





				

typedef	struct cp_log_s								cp_log_t;
typedef struct cp_conf_s							cp_conf_t;
//typedef	struct cp_socket_manager_s					cp_socket_manager_t;
//typedef struct cp_thread_manager_s					cp_thread_manager_t;
//typedef struct cp_timer_s							cp_timer_t;
typedef struct cp_pool_s							cp_pool_t;
typedef	struct cp_app_s								cp_app_t;
typedef struct cp_app_info_s						cp_app_info_t;
typedef	struct cp_daemon_info_s						cp_daemon_info_t;



#ifdef __cplusplus
extern "C" {
#endif



#include "cp_version.h"
#include "cp_define.h"
#include "cp_bit.h"
#include "cp_typedef.h"
#include "cp_atomic.h"
#include "cp_default.h"
#include "cp_define_str.h"
#include "cp_define_func.h"
#include "cp_utils.h"
#include "cp_buf.h"
#include "cp_array.h"
#include "cp_list.h"
#include "cp_queue.h"
#include "cp_alloc.h"
#include "cp_gettimeofday.h"
#include "cp_time.h"
#include "cp_mpalloc.h"

#include "cp_mutex_core.h"
#include "cp_log.h"



#include "cp_string.h"












// #include "cp_log.h"
// #include "cp_conf.h"
// #include "cp_thread.h"
// #include "cp_timer.h"
// #include "cp_app_core.h"





#ifdef __cplusplus
}
#endif



#endif