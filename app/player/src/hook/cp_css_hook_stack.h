/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_CSS_HOOK_STACK_INCLUDE_H_
#define _CP_CSS_HOOK_STACK_INCLUDE_H_


#include "cp_css_hook_core.h"



typedef struct cp_css_hook_stack_s			cp_css_hook_stack_t;



#pragma pack(1)

/************************************************************************/
/* ģ��hook����Ϣ	                                                    */
/************************************************************************/
struct cp_css_hook_stack_s
{
	cp_css_semh_hook_type_e		type;
	cp_css_hook_t				*hook;
	cp_session_t				*session;
	cp_void_t					*arg;
	cp_queue_t					queue;
};

#pragma pack()



/************************************************************************/
/* ��ʼ��css hook stack����ֵ                                              */
/************************************************************************/
#define CP_CSS_HOOK_STACK_INIT_FIELDS(stack) do {						\
	cp_memset(stack, 0, cp_sizeof(cp_css_hook_stack_t));				\
	cp_queue_init(&stack->queue);										\
} while (0);															\


/************************************************************************/
/* ����css hook stack����ֵ                                              */
/************************************************************************/
#define CP_CSS_HOOK_STACK_SET_VALUE(stack, css_hook, css_session, css_arg)		 do {	\
	(stack)->type = (css_hook)->register_info.type;										\
	(stack)->hook = (css_hook);															\
	(stack)->session = (css_session);													\
	(stack)->arg = (css_arg);															\
} while (0);																			\



#endif


