/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_POOL_INCLUDE_H_
#define _CP_POOL_INCLUDE_H_


#include "cp_module.h"


//typedef struct cp_pool_s				cp_pool_t;



#pragma pack(1)



#define CP_POOL_FIELDS													\
		CP_MODULE_FIELDS


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_pool_s {
	CP_POOL_FIELDS												/*表示时间模块信息*/
};


#pragma pack()



#endif


