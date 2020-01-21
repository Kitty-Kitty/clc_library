/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_HOOK_INFO_INCLUDE_H_
#define _CP_HOOK_INFO_INCLUDE_H_

#include "cp_hook_core.h"





//typedef	struct cp_hook_info_s			cp_hook_info_t;
typedef void(*cp_hook_cb)(cp_hook_t* th);




#pragma pack(1)


#define CP_HOOK_INFO_FIELDS																							\
		CP_MODULE_INFO_FIELDS																						\
		cp_session_t			*session;	/*表示当前的session信息*/												\
		cp_queue_t				*hhsq;		/*表示历史queue列表节点信息(history_hook_stack_queue),主要保存数据结构为cp_css_hook_stack_t数据*/										\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hook_info_s {
	CP_HOOK_INFO_FIELDS
};


#pragma pack()



/************************************************************************/
/* 设置sesion相关的信息												    */
/************************************************************************/
#define CP_HOOK_INFO_SET_SESSION_INFO(hook_info, in_session, in_hhsq) do {		\
		(hook_info)->session = (cp_session_t*)in_session;						\
		(hook_info)->hhsq = in_hhsq;											\
} while (0);																	\


#endif





