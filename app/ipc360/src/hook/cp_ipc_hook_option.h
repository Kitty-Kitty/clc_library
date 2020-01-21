/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_CSS_HOOK_OPTION_INCLUDE_H_
#define _CP_CSS_HOOK_OPTION_INCLUDE_H_




#include "cp_bit.h"
#include "cp_module_option.h"




typedef enum cp_css_hoot_option_enum		cp_ipc_hook_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
enum cp_css_hoot_option_enum
{
	cp_ipc_hook_set_option_start_heartbeat	= CP_MODULE_OPTION_MAKE_SET_FLAG(B8(00000001)),
	cp_ipc_hook_set_option_stop_heartbeat	= CP_MODULE_OPTION_MAKE_SET_FLAG(B8(00000010)),
	cp_ipc_hook_set_option_send_register	= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000010, 00000000)),
};



#endif





