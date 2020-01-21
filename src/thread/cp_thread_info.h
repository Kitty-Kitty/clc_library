/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_THREAD_INFO_INCLUDE_H_
#define _CP_THREAD_INFO_INCLUDE_H_

#include "cp_thread_core.h"









//typedef	struct cp_thread_info_s			cp_thread_info_t;
typedef void(*cp_thread_cb)(void* arg);




#pragma pack(1)


#define CP_THREAD_INFO_FIELDS																						\
		CP_MODULE_INFO_FIELDS																						\
		cp_thread_t			*thread;										/*表示线程唯一id*/						\
		cp_thread_cb		thread_cb;										/*表示时间回调函数*/						\
		cp_void_t			*args;											/*表示参数信息*/							\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_thread_info_s {
	CP_THREAD_INFO_FIELDS
};


#pragma pack()




#endif





