/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HOOK_INCLUDE_H_
#define _CP_HOOK_INCLUDE_H_

#include "cp_hook_core.h"
#include "cp_socket.h"



//typedef struct cp_hook_s	cp_hook_t;



#pragma pack(1)




#define CP_HOOK_FIELDS													\
		CP_SOCKET_FIELDS												\
		CP_HANDLE_SLAB_FIELDS											\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hook_s {
	CP_HOOK_FIELDS												/*��ʾʱ��ģ����Ϣ*/
};

#pragma pack()


/************************************************************************/
/* socket���ûص��������                                                */
/************************************************************************/
#define  CP_HOOK_MODULE_SET_CALLBACK_HANDLERS(module, name)						\
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(module, name)						\



/************************************************************************/
/* socket���ûص��������                                                */
/************************************************************************/
#define  CP_HOOK_MODULE_SET_CALLBACK_HANDLERS(module, name)						\
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(module, name)						\



/************************************************************************/
/* ����hook��һ����Ҫִ�е�hook											*/
/************************************************************************/
#define CP_HOOK_SET_NEXT_HOOK_INFO(hook, in_hook)	do {						\
		(hook)->current_hook = (in_hook);	/*���õ�ǰhook���*/					\
	} while (0);																\



#endif


