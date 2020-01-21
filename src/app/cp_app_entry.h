/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_APP_ENTRY_INCLUDE_H_
#define _CP_APP_ENTRY_INCLUDE_H_


#include "cp_app_core.h"



///////////////////////////////////////////////定义app全局变量////////////////////////////////////////////////////////


/************************************************************************/
/*初始化APP的入口信息                                                    */
/************************************************************************/
#define CP_APP_ENTRY(type, name, version, description, create_handle, destroy_handle)								\
	cp_app_t					*cp_global_app = NULL;																\
	cp_daemon_info_t			*cp_global_daemon_info = NULL;														\
	cp_app_info_t				cp_global_app_info = {type, name, version, description, NULL, 0};					\
	cp_app_create_handle		cp_global_app_create_handle = (cp_app_create_handle)(create_handle);				\
	cp_app_destroy_handle		cp_global_app_destroy_handle = (cp_app_destroy_handle)(destroy_handle);				\


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////引用app全局变量////////////////////////////////////////////////////////


/************************************************************************/
/*设置配置文件                                                           */
/************************************************************************/
#define CP_INIT_APP_INFO(in_type, in_name, in_version, in_description, in_create_handle, in_destroy_handle)	do {	\
		extern cp_app_info_t			cp_global_app_info;															\
		extern cp_app_create_handle		cp_global_app_create_handle;												\
		extern cp_app_destroy_handle	cp_global_app_destroy_handle;												\
																													\
		cp_memset(&cp_global_app_info, 0, cp_sizeof(cp_global_app_info));											\
		cp_global_app_info.type = in_type;																			\
		cp_global_app_info.version = in_version;																	\
		cp_sprintf(cp_global_app_info.name, "%s", in_name);															\
		cp_global_app_create_handle = in_create_handle;																\
		cp_global_app_destroy_handle = in_destroy_handle;															\
	}while(0);																										\



/************************************************************************/
/*更新app app_info                                                       */
/************************************************************************/
#define CP_UPDATE_APP_APP_INFO(in_app, in_app_info)			do {													\
		*((in_app)->app_info) = *(in_app_info);																		\
	}while(0);																										\



/************************************************************************/
/*更新app register_info                                                       */
/************************************************************************/
#define CP_UPDATE_APP_REGISTER_INFO(in_app, in_app_info, in_create_handle, in_destroy_handle)	do {				\
		(in_app)->register_info.type = (in_app_info)->type;															\
		(in_app)->register_info.version = (in_app_info)->version;													\
		(in_app)->register_info.name = (in_app_info)->name;															\
		(in_app)->register_info.description = (in_app_info)->description;											\
		(in_app)->register_info.manager_create = (manager_create_handle)(in_create_handle);							\
		(in_app)->register_info.manager_destroy = (manager_destroy_handle)(in_destroy_handle);						\
	}while(0);																										\



/************************************************************************/
/*设置配置文件                                                           */
/************************************************************************/
#define CP_APP_ENTRY_CONFIG_PATH(in_config_path)				do {												\
		cp_memset(&cp_global_app_info.entry_config_path, 0, cp_sizeof(cp_global_app_info.entry_config_path));		\
		cp_sprintf(cp_global_app_info.entry_config_path, "%s", in_config_path);										\
	}while(0);																										\




/************************************************************************/
/* 该宏主要是引入app变量                                                 */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP()																						\
	extern cp_app_t				*cp_global_app;																		\




/************************************************************************/
/* 该宏主要是引入app info变量                                            */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP_INFO()																					\
	extern cp_app_info_t		cp_global_app_info;																	\


/************************************************************************/
/* 该宏主要是引入app handle变量                                            */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP_HANDLE()																				\
	extern cp_app_create_handle		cp_global_app_create_handle;													\
	extern cp_app_destroy_handle	cp_global_app_destroy_handle;													\


/************************************************************************/
/* 该宏主要是引入app daemon变量                                            */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP_DAEMON()																				\
	extern cp_daemon_info_t			*cp_global_daemon_info;															\





/************************************************************************/
/* 该宏主要是引入app 变量													*/
/************************************************************************/
#define CP_EXTERN_APP_PARAMETER()																					\
	CP_EXTERN_GLOBAL_APP();																							\
	CP_EXTERN_GLOBAL_APP_INFO();																					\
	CP_EXTERN_GLOBAL_APP_HANDLE();																					\
	CP_EXTERN_GLOBAL_APP_DAEMON();																					\


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif