/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_CSS_HOOK_STACK_INCLUDE_H_
#define _CP_CSS_HOOK_STACK_INCLUDE_H_


#include "cp_ipc_hook_core.h"



typedef struct cp_ipc_hook_stack_s			cp_ipc_hook_stack_t;



#pragma pack(1)

/************************************************************************/
/* 模块hook块信息	                                                    */
/************************************************************************/
struct cp_ipc_hook_stack_s
{
	cp_css_rtp_hook_type_e		type;
	cp_ipc_hook_t				*hook;
	cp_session_t				*session;
	cp_void_t					*arg;
	cp_queue_t					queue;
};

#pragma pack()



/************************************************************************/
/* 初始化css hook stack的数值                                              */
/************************************************************************/
#define CP_CSS_HOOK_STACK_INIT_FIELDS(stack) do {						\
	cp_memset(stack, 0, cp_sizeof(cp_ipc_hook_stack_t));				\
	cp_queue_init(&stack->queue);										\
} while (0);															\


/************************************************************************/
/* 设置css hook stack的数值                                              */
/************************************************************************/
#define CP_CSS_HOOK_STACK_SET_VALUE(stack, ipc_hook, ipc_session, css_arg)		 do {	\
	(stack)->type = (ipc_hook)->register_info.type;										\
	(stack)->hook = (ipc_hook);															\
	(stack)->session = (ipc_session);													\
	(stack)->arg = (css_arg);															\
} while (0);																			\



#endif


