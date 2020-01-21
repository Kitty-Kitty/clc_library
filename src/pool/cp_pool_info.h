/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_POOL_INFO_INCLUDE_H_
#define _CP_POOL_INFO_INCLUDE_H_

#include "cp_core.h"
#include "cp_module.h"





//typedef	struct cp_pool_info_s			cp_pool_info_t;
typedef void(*cp_pool_cb)(cp_pool_t* th);



#pragma pack(1)



#define CP_POOL_INFO_FIELDS															\
		CP_MODULE_INFO_FIELDS														\
		cp_int32_t		size;							/*定义大小数值*/				\
		cp_void_t		*buf;							/*表示分配的内容地址*/		\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_pool_info_s {
	CP_POOL_INFO_FIELDS
};


#pragma pack()



#endif





