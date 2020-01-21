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
/* ��Ҫ����ģ�������ע��Ļ�����Ϣ										*/
/************************************************************************/
#define  CP_MODULE_MANAGER_REGISTER_INFO_FIELDS											\
	cp_int32_t						type;				/*��ʾģ��������Ϣ*/				\
	cp_int32_t						version;			/*��ʾģ��汾��*/				\
	cp_char_t						*name;				/*��ʾģ������*/					\
	cp_char_t						*description;		/*��ʾģ�������*/				\



/************************************************************************/
/* ��Ҫ����ģ�������ע��ľ����Ϣ                                     */
/************************************************************************/
#define  CP_MODULE_MANAGER_REGISTER_HANDLER_FIELDS										\
	manager_create_handle			manager_create;		/*��ʾģ�������ע����*/		\
	manager_destroy_handle			manager_destroy;	/*��ʾģ��ȡ��ע����*/			\



struct cp_module_manager_register_s
{
	CP_MODULE_MANAGER_REGISTER_INFO_FIELDS
	CP_MODULE_MANAGER_REGISTER_HANDLER_FIELDS
};




#define CP_MODULE_MANAGER_REGISTER(type, version, name, description, create_handle, destroy_handle)		\
	{type, version, name, description, (manager_create_handle) create_handle, (manager_destroy_handle) destroy_handle},





#endif


