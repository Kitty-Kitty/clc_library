/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_THREAD_MODULE_LIST_INCLUDE_H_
#define _CP_THREAD_MODULE_LIST_INCLUDE_H_

#include "cp_thread_core.h"



//定义两个模块处理函数
CP_SUB_MODULE_MANAGER_DEPENDENT_FUNCTION(thread);
CP_MODULE_DEPENDENT_FUNCTION(thread);




#include "libuv_thread/cp_uv_thread_core.h"





#endif


