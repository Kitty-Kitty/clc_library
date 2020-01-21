/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_FUNC_INFO_INCLUDE_H_
#define _CP_FUNC_INFO_INCLUDE_H_

#include "cp_func_core.h"





//typedef	struct cp_func_info_s			cp_func_info_t;
typedef void(*cp_func_cb)(cp_func_t* th);



#pragma pack(1)


#define CP_FUNC_INFO_FIELDS																							\
		CP_MODULE_INFO_FIELDS																						\
		cp_uint64_t		timeout;										/*表示超时时间，单位（毫秒）*/				\
		cp_uint64_t		repeat;											/*表示是否重做*/								\
		cp_func_cb		func_cb;										/*表示时间回调函数*/							\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_func_info_s {
	CP_FUNC_INFO_FIELDS
};


#pragma pack()


#endif





