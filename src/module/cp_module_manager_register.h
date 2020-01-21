/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module

**************************************************************************/


#ifndef	_CP_MODULE_MANAGER_REGISTER_INCLUDE_H_
#define _CP_MODULE_MANAGER_REGISTER_INCLUDE_H_



#include "cp_module_core.h"



typedef struct cp_module_manager_register_s			cp_module_manager_register_t;
typedef cp_module_manager_t*(*manager_create_handle)(cp_module_manager_register_t *register_info, cp_app_t *app, cp_module_manager_info_t *info);
typedef cp_int32_t(*manager_destroy_handle)(cp_app_t *app, cp_module_manager_t *manager);




/************************************************************************/
/* 主要描述模块管理器注册的基础信息										*/
/************************************************************************/
#define  CP_MODULE_MANAGER_REGISTER_INFO_FIELDS											\
	cp_int32_t						type;				/*表示模块类型信息*/				\
	cp_int32_t						version;			/*表示模块版本号*/				\
	cp_char_t						*name;				/*表示模块名称*/					\
	cp_char_t						*description;		/*表示模块的描述*/				\



/************************************************************************/
/* 主要描述模块管理器注册的句柄信息                                     */
/************************************************************************/
#define  CP_MODULE_MANAGER_REGISTER_HANDLER_FIELDS										\
	manager_create_handle			manager_create;		/*表示模块管理器注册句柄*/		\
	manager_destroy_handle			manager_destroy;	/*表示模块取消注册句柄*/			\



struct cp_module_manager_register_s
{
	CP_MODULE_MANAGER_REGISTER_INFO_FIELDS
	CP_MODULE_MANAGER_REGISTER_HANDLER_FIELDS
};




#define CP_MODULE_MANAGER_REGISTER(type, version, name, description, create_handle, destroy_handle)		\
	{type, version, name, description, (manager_create_handle) create_handle, (manager_destroy_handle) destroy_handle},





#endif


