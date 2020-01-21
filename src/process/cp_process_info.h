/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_PROCESS_INFO_INCLUDE_H_
#define _CP_PROCESS_INFO_INCLUDE_H_

#include "cp_process_core.h"





//typedef	struct cp_process_info_s			cp_process_info_t;
typedef void(*cp_process_cb)(cp_process_t* th);



#pragma pack(1)



#define CP_PROCESS_INFO_FIELDS																							\
		CP_MODULE_INFO_FIELDS																						\
		cp_uint64_t		timeout;										/*表示超时时间，单位（毫秒）*/				\
		cp_uint64_t		repeat;											/*表示是否重做*/								\
		cp_process_cb		process_cb;										/*表示时间回调函数*/							\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_process_info_s {
	CP_PROCESS_INFO_FIELDS
};


#pragma pack()


#endif





