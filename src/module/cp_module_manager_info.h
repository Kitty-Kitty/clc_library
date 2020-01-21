/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module information

**************************************************************************/


#ifndef	_CP_MODULE_MANAGER_INFO_INCLUDE_H_
#define _CP_MODULE_MANAGER_INFO_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_manager_info.h"




//typedef struct cp_module_manager_info_s			cp_module_manager_info_t;





#pragma pack(1)


#define CP_MODULE_MANAGER_INFO_FIELDS																\
		CP_MODULE_MANAGER_REGISTER_INFO_FIELDS														\
		cp_app_t						*app;						/*��ʾӦ�ó���ָ��*/				\



/************************************************************************/
/* ��ʾģ�������Ϣ����ģ����Ϣ����̳и���Ϣ                              */
/************************************************************************/
struct cp_module_manager_info_s
{
	CP_MODULE_MANAGER_INFO_FIELDS
};

#pragma pack()


/************************************************************************/
/* ����ģ�����������Ϣ                                                  */
/************************************************************************/
#define CP_MODULE_MANAGER_INFO_SET_TYPE(module_manager_info, in_type)	do {						\
	(module_manager_info)->type = (in_type);														\
	}while(0);																						\


#endif


