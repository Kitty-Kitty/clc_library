/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HOOK_HANDLE_INCLUDE_H_
#define _CP_HOOK_HANDLE_INCLUDE_H_


/************************************************************************/
/* ����һ������ջ����                                                  */
/************************************************************************/
#define CP_HOOK_MAX_STACK_COUNT					32


#include "cp_session_typedef.h"
#include "cp_hook_typedef.h"


// typedef	struct cp_session_s						cp_session_t;
// typedef	struct cp_hook_s						cp_hook_t;



typedef	cp_int32_t(*cp_hook_handle)(cp_hook_t *hook, cp_session_t *session, cp_void_t *arg);



/************************************************************************/
/* ����һ��hook��صĳ�����б�                                           */
/************************************************************************/
#define CP_HANDLE_SLAB_FIELDS																				\
		cp_hook_handle			hook_handle;				/*��ǰhook������*/								\
		cp_void_t				*arg;						/*��ǰhook�������Ĳ�����Ϣ*/					\
		cp_int32_t				stack_count;				/*��ʾ��ʷ��¼��ջ������*/						\
		cp_queue_t				hhsq;						/*��ʾ��ʷqueue�б�ڵ���Ϣ(history_hook_stack_queue),��Ҫ�������ݽṹΪcp_css_hook_stack_t����*/			\
		cp_queue_t				entry;						/*��ʾ��ǰhook����ǰ��Ҫִ�е�����hook�����ݽṹΪcp_css_hook_block_t*/			\
		cp_queue_t				right;						/*��ʾ��ǰhook����ɹ�����Ҫִ�е�����hook�����ݽṹΪcp_css_hook_block_t*/			\
		cp_queue_t				error;						/*��ʾ��ǰhook����ʧ�ܺ���Ҫִ�е�����hook�����ݽṹΪcp_css_hook_block_t*/			\
		cp_hook_t				*current_hook;				/*��ǰ��Ҫ��ִ�е�hook*/							\


/************************************************************************/
/* ��ʼ��slab��������                                                    */
/************************************************************************/
#define CP_INIT_HANDLE_SLAB_FILES(module)	do {															\
		(module)->hook_handle = CP_NULL;						/*��ǰhook������*/							\
		(module)->arg = CP_NULL;								/*��ǰhook�������Ĳ�����Ϣ*/				\
		(module)->stack_count = 0;								/*��ǰhook�����������ջ����*/				\
		cp_queue_init(&(module)->hhsq);							/*��ʾ��ʷqueue�б�ڵ���Ϣ*/					\
		cp_queue_init(&(module)->entry);						/*��ʾ��ǰhook����ǰ��Ҫִ�е�����hook*/		\
		cp_queue_init(&(module)->right);						/*��ʾ��ǰhook����ɹ�����Ҫִ�е�����hook*/	\
		cp_queue_init(&(module)->error);						/*��ʾ��ǰhook����ʧ�ܺ���Ҫִ�е�����hook*/	\
		(module)->current_hook = CP_NULL;						/*��ǰhook������*/							\
	} while (0);																							\

#endif


