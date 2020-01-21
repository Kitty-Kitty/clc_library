/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CSS_HOOK_MODULE_LIST_INCLUDE_H_
#define _CP_CSS_HOOK_MODULE_LIST_INCLUDE_H_

#include "cp_hook_core.h"



#include "cp_demo_hook_core.h"
#include "rtp/cp_rtp_hook_core.h"


//定义两个模块处理函数
CP_SUB_MODULE_MANAGER_DEPENDENT_FUNCTION(demo_hook);
CP_MODULE_DEPENDENT_FUNCTION(demo_hook);



#endif


