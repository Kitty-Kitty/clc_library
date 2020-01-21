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
		cp_app_t						*app;						/*表示应用程序指针*/				\



/************************************************************************/
/* 表示模块基础信息，子模块信息必须继承该信息                              */
/************************************************************************/
struct cp_module_manager_info_s
{
	CP_MODULE_MANAGER_INFO_FIELDS
};

#pragma pack()


/************************************************************************/
/* 设置模块管理器的信息                                                  */
/************************************************************************/
#define CP_MODULE_MANAGER_INFO_SET_TYPE(module_manager_info, in_type)	do {						\
	(module_manager_info)->type = (in_type);														\
	}while(0);																						\


#endif


