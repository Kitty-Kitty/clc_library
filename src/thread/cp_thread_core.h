/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_THREAD_CORE_INCLUDE_H_
#define _CP_THREAD_CORE_INCLUDE_H_





// #ifdef WIN32
// 
// typedef void *cp_thread_t;
// 
// #else
// 
// typedef pthread_t cp_thread_t;
// 
// #endif
// 



typedef struct	cp_thread_info_s					cp_thread_info_t;
typedef	struct	cp_thread_s							cp_thread_t;
typedef	struct	cp_thread_handles_s					cp_thread_handles_t;
typedef	struct	cp_thread_manager_handles_s			cp_thread_manager_handles_t;
//typedef	enum	cp_thread_status_enum			cp_thread_status_e;




#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_thread_option.h"
#include "cp_thread_info.h"
#include "cp_thread_manager_info.h"
#include "cp_thread.h"
#include "cp_thread_manager.h"




#endif


