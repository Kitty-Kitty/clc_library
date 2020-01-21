/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_THREAD_OPTION_INCLUDE_H_
#define _CP_THREAD_OPTION_INCLUDE_H_



#include "cp_module_option.h"


//typedef enum cp_thread_option_enum		cp_thread_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
typedef enum cp_thread_option_enum
{
	cp_thread_set_option_join = CP_MODULE_OPTION_MAKE_SET_FLAG(0x01),
	cp_thread_get_option_self = CP_MODULE_OPTION_MAKE_GET_FLAG(0x02),
}cp_thread_option_e;



#endif





