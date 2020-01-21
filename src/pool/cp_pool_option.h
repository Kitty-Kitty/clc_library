/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_POOL_OPTION_INCLUDE_H_
#define _CP_POOL_OPTION_INCLUDE_H_


#include "cp_module_option.h"



//typedef	enum cp_pool_option_enum			cp_pool_option_e;



/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef	enum cp_pool_option_enum {
	CP_POOL_OPTION_FREE = CP_MODULE_OPTION_MAKE_SET_FLAG(0x01),
	CP_POOL_OPTION_ALLOC = CP_MODULE_OPTION_MAKE_GET_FLAG(0x02),
}cp_pool_option_e;



#endif





