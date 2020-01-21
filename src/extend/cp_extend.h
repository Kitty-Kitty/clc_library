/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_EXTEND_INCLUDE_H_
#define _CP_EXTEND_INCLUDE_H_

#include "cp_extend_core.h"



//typedef struct cp_extend_s				cp_extend_t;



#pragma pack(1)


#define CP_EXTEND_FIELDS												\
		CP_MODULE_FIELDS												\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_extend_s {
	CP_EXTEND_FIELDS												/*表示时间模块信息*/
};

#pragma pack()


#endif


