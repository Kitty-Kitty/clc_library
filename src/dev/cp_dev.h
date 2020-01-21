/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_DEV_INCLUDE_H_
#define _CP_DEV_INCLUDE_H_

#include "cp_dev_core.h"



//typedef struct cp_dev_s				cp_dev_t;



#pragma pack(1)


#define CP_DEV_FIELDS																				\
		CP_MODULE_FIELDS																			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_dev_s {
	CP_DEV_FIELDS												/*表示时间模块信息*/
};

#pragma pack()



#endif


