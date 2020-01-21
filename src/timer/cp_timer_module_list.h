/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_TIMER_MODULE_LIST_INCLUDE_H_
#define _CP_TIMER_MODULE_LIST_INCLUDE_H_

#include "cp_timer_core.h"






//定义两个模块处理函数
CP_SUB_MODULE_MANAGER_DEPENDENT_FUNCTION(timer);
CP_MODULE_DEPENDENT_FUNCTION(timer);


#include "libuv_timer/cp_uv_timer_core.h"



#endif


