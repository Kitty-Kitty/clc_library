/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_CSS_HOOK_REGISTER_INCLUDE_H_
#define _CP_CSS_HOOK_REGISTER_INCLUDE_H_


#include "cp_ecam_hook_core.h"



typedef struct cp_ecam_hook_register_s			cp_ecam_hook_register_t;



/************************************************************************/
/* 主要描述模块注册的基础信息                                             */
/************************************************************************/
#define  CP_CSS_HOOK_REGISTER_INFO_FIELDS												\
	CP_MODULE_REGISTER_INFO_FIELDS														\



/************************************************************************/
/* 主要描述模块注册的句柄信息                                             */
/************************************************************************/
#define  CP_CSS_HOOK_REGISTER_HANDLER_FIELDS											\
	CP_MODULE_REGISTER_HANDLER_FIELDS													\
	cp_int32_t				command;			/*表示当前的指令编码*/					\
	cp_hook_handle			hook_hander;		/*表示模块取消注册句柄*/					\



/************************************************************************/
/* 模块注册信息结构体                                                    */
/************************************************************************/
struct cp_ecam_hook_register_s
{
	CP_CSS_HOOK_REGISTER_INFO_FIELDS
	CP_CSS_HOOK_REGISTER_HANDLER_FIELDS
};



/************************************************************************/
/* 模块注册宏信息                                                        */
/************************************************************************/
#define CP_CSS_HOOK_REGISTER(type, version, name, description, create_handle, destroy_handle, command, hook_handle)		\
	{type, version, name, description,																					\
		(module_create_handle)create_handle, (module_destroy_handle)destroy_handle,										\
		command, (cp_hook_handle)hook_handle},


#endif


