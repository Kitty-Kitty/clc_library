/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_APP_ENTRY_INCLUDE_H_
#define _CP_APP_ENTRY_INCLUDE_H_


#include "cp_app_core.h"



///////////////////////////////////////////////����appȫ�ֱ���////////////////////////////////////////////////////////


/************************************************************************/
/*��ʼ��APP�������Ϣ                                                    */
/************************************************************************/
#define CP_APP_ENTRY(type, name, version, description, create_handle, destroy_handle)								\
	cp_app_t					*cp_global_app = NULL;																\
	cp_daemon_info_t			*cp_global_daemon_info = NULL;														\
	cp_app_info_t				cp_global_app_info = {type, name, version, description, NULL, 0};					\
	cp_app_create_handle		cp_global_app_create_handle = (cp_app_create_handle)(create_handle);				\
	cp_app_destroy_handle		cp_global_app_destroy_handle = (cp_app_destroy_handle)(destroy_handle);				\


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////����appȫ�ֱ���////////////////////////////////////////////////////////


/************************************************************************/
/*���������ļ�                                                           */
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
/*����app app_info                                                       */
/************************************************************************/
#define CP_UPDATE_APP_APP_INFO(in_app, in_app_info)			do {													\
		*((in_app)->app_info) = *(in_app_info);																		\
	}while(0);																										\



/************************************************************************/
/*����app register_info                                                       */
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
/*���������ļ�                                                           */
/************************************************************************/
#define CP_APP_ENTRY_CONFIG_PATH(in_config_path)				do {												\
		cp_memset(&cp_global_app_info.entry_config_path, 0, cp_sizeof(cp_global_app_info.entry_config_path));		\
		cp_sprintf(cp_global_app_info.entry_config_path, "%s", in_config_path);										\
	}while(0);																										\




/************************************************************************/
/* �ú���Ҫ������app����                                                 */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP()																						\
	extern cp_app_t				*cp_global_app;																		\




/************************************************************************/
/* �ú���Ҫ������app info����                                            */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP_INFO()																					\
	extern cp_app_info_t		cp_global_app_info;																	\


/************************************************************************/
/* �ú���Ҫ������app handle����                                            */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP_HANDLE()																				\
	extern cp_app_create_handle		cp_global_app_create_handle;													\
	extern cp_app_destroy_handle	cp_global_app_destroy_handle;													\


/************************************************************************/
/* �ú���Ҫ������app daemon����                                            */
/************************************************************************/
#define CP_EXTERN_GLOBAL_APP_DAEMON()																				\
	extern cp_daemon_info_t			*cp_global_daemon_info;															\





/************************************************************************/
/* �ú���Ҫ������app ����													*/
/************************************************************************/
#define CP_EXTERN_APP_PARAMETER()																					\
	CP_EXTERN_GLOBAL_APP();																							\
	CP_EXTERN_GLOBAL_APP_INFO();																					\
	CP_EXTERN_GLOBAL_APP_HANDLE();																					\
	CP_EXTERN_GLOBAL_APP_DAEMON();																					\


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif