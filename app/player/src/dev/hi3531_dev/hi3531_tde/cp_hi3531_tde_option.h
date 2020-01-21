/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-13

Description:

**************************************************************************/

#ifndef _CP_HI3531_TDE_OPTION_INCLUDE_H_
#define _CP_HI3531_TDE_OPTION_INCLUDE_H_



#include "cp_module_option.h"
#include "cp_bit.h"




/************************************************************************/
/* 视频帧处理类型                                                          */
/************************************************************************/
enum cp_hi3531_tde_option_get_enum
{
	cp_hi3531_tde_option_get_none = 0,
	cp_hi3531_tde_option_get_fill = CP_MODULE_OPTION_MAKE_GET_FLAG(B16(00000000, 00000001)),
	cp_hi3531_tde_option_get_copy = CP_MODULE_OPTION_MAKE_GET_FLAG(B16(00000000, 00000010)),
	cp_hi3531_tde_option_get_resize = CP_MODULE_OPTION_MAKE_GET_FLAG(B16(00000000, 00000100)),

};



#endif


