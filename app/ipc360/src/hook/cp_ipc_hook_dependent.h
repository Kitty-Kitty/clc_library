/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CSS_HOOK_DEPENDENT_INCLUDE_H_
#define _CP_CSS_HOOK_DEPENDENT_INCLUDE_H_


#include <stdarg.h>
#include "cp_ipc_hook_core.h"


/************************************************************************/
/* 定义各种处理函数的入口依赖关系                                         */
/************************************************************************/
#define CP_CSS_HOOK_SET_ENTRY_DEPENDENT_BEGIN										\
	cp_void_t cp_ipc_hook_entry_dependent(cp_ipc_hook_manager_t *manager) {			\


/************************************************************************/
/* 添加入口依赖函数                                                      */
/************************************************************************/
#define CP_CSS_ADD_ENTRY_DEPENDENT(type, ...)										\
	cp_css_add_entry_dependent(manager, type, __VA_ARGS__);									\





/************************************************************************/
/* 定义正确返回的依赖关系                                                */
/************************************************************************/
#define CP_CSS_HOOK_SET_RIGHT_DEPENDENT_BEGIN										\
	cp_void_t cp_ipc_hook_right_dependent(cp_ipc_hook_manager_t *manager) {			\


/************************************************************************/
/* 添加正确返回的依赖处理函数                                             */
/************************************************************************/
#define CP_CSS_ADD_RIGHT_DEPENDENT(type, ...)										\
	cp_css_add_right_dependent(manager, type, __VA_ARGS__);									\







/************************************************************************/
/* 定义错误返回的依赖关系                                                 */
/************************************************************************/
#define CP_CSS_HOOK_SET_ERROR_DEPENDENT_BEGIN										\
	cp_void_t cp_ipc_hook_error_dependent(cp_ipc_hook_manager_t *manager) {			\


/************************************************************************/
/* 添加错误返回的依赖处理函数                                             */
/************************************************************************/
#define CP_CSS_ADD_ERROR_DEPENDENT(type, ...)										\
	cp_css_add_error_dependent(manager, type, __VA_ARGS__);									\




#define CP_CSS_HOOK_DEPENDENT_END		}				




cp_int32_t cp_css_add_entry_dependent(cp_ipc_hook_manager_t *manager, cp_css_rtp_hook_type_e type, ...);
cp_int32_t cp_css_add_right_dependent(cp_ipc_hook_manager_t *manager, cp_css_rtp_hook_type_e type, ...);
cp_int32_t cp_css_add_error_dependent(cp_ipc_hook_manager_t *manager, cp_css_rtp_hook_type_e type, ...);



cp_void_t cp_ipc_hook_entry_dependent(cp_ipc_hook_manager_t *manager);
cp_void_t cp_ipc_hook_right_dependent(cp_ipc_hook_manager_t *manager);
cp_void_t cp_ipc_hook_error_dependent(cp_ipc_hook_manager_t *manager);
cp_int32_t cp_ipc_hook_dependent(cp_ipc_hook_manager_t *manager, cp_ipc_hook_t *hook, cp_queue_t *queue, va_list *args);



#endif


