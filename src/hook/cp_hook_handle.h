/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HOOK_HANDLE_INCLUDE_H_
#define _CP_HOOK_HANDLE_INCLUDE_H_


/************************************************************************/
/* 定义一个最大的栈层数                                                  */
/************************************************************************/
#define CP_HOOK_MAX_STACK_COUNT					32


#include "cp_session_typedef.h"
#include "cp_hook_typedef.h"


// typedef	struct cp_session_s						cp_session_t;
// typedef	struct cp_hook_s						cp_hook_t;



typedef	cp_int32_t(*cp_hook_handle)(cp_hook_t *hook, cp_session_t *session, cp_void_t *arg);



/************************************************************************/
/* 定义一个hook相关的出入口列表                                           */
/************************************************************************/
#define CP_HANDLE_SLAB_FIELDS																				\
		cp_hook_handle			hook_handle;				/*当前hook处理句柄*/								\
		cp_void_t				*arg;						/*当前hook处理句柄的参数信息*/					\
		cp_int32_t				stack_count;				/*表示历史纪录的栈最大层数*/						\
		cp_queue_t				hhsq;						/*表示历史queue列表节点信息(history_hook_stack_queue),主要保存数据结构为cp_css_hook_stack_t数据*/			\
		cp_queue_t				entry;						/*表示当前hook处理前需要执行的其他hook，数据结构为cp_css_hook_block_t*/			\
		cp_queue_t				right;						/*表示当前hook处理成功后需要执行的其他hook，数据结构为cp_css_hook_block_t*/			\
		cp_queue_t				error;						/*表示当前hook处理失败后需要执行的其他hook，数据结构为cp_css_hook_block_t*/			\
		cp_hook_t				*current_hook;				/*当前需要被执行的hook*/							\


/************************************************************************/
/* 初始化slab区域内容                                                    */
/************************************************************************/
#define CP_INIT_HANDLE_SLAB_FILES(module)	do {															\
		(module)->hook_handle = CP_NULL;						/*当前hook处理句柄*/							\
		(module)->arg = CP_NULL;								/*当前hook处理句柄的参数信息*/				\
		(module)->stack_count = 0;								/*当前hook处理句柄的最大栈数量*/				\
		cp_queue_init(&(module)->hhsq);							/*表示历史queue列表节点信息*/					\
		cp_queue_init(&(module)->entry);						/*表示当前hook处理前需要执行的其他hook*/		\
		cp_queue_init(&(module)->right);						/*表示当前hook处理成功后需要执行的其他hook*/	\
		cp_queue_init(&(module)->error);						/*表示当前hook处理失败后需要执行的其他hook*/	\
		(module)->current_hook = CP_NULL;						/*当前hook处理句柄*/							\
	} while (0);																							\

#endif


