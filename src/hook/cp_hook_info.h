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
		cp_session_t			*session;	/*��ʾ��ǰ��session��Ϣ*/												\
		cp_queue_t				*hhsq;		/*��ʾ��ʷqueue�б�ڵ���Ϣ(history_hook_stack_queue),��Ҫ�������ݽṹΪcp_css_hook_stack_t����*/										\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hook_info_s {
	CP_HOOK_INFO_FIELDS
};


#pragma pack()



/************************************************************************/
/* ����sesion��ص���Ϣ												    */
/************************************************************************/
#define CP_HOOK_INFO_SET_SESSION_INFO(hook_info, in_session, in_hhsq) do {		\
		(hook_info)->session = (cp_session_t*)in_session;						\
		(hook_info)->hhsq = in_hhsq;											\
} while (0);																	\


#endif





