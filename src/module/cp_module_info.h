/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module information

**************************************************************************/


#ifndef	_CP_MODULE_INFO_INCLUDE_H_
#define _CP_MODULE_INFO_INCLUDE_H_




#include "cp_core.h"



//typedef struct cp_module_info_s					cp_module_info_t;



#pragma pack(1)



#define CP_MODULE_INFO_FIELDS																		\
		CP_MODULE_REGISTER_INFO_FIELDS																\
		cp_app_t						*app;						/*��ʾӦ�ó���ָ��*/				\
		cp_pool_t						*pool;						/*��ʾģ���˽���ڴ��*/			\
		cp_void_t						*data;						/*��ʾ������Ϣ*/					\


/************************************************************************/
/* ��ʾģ�������Ϣ����ģ����Ϣ����̳и���Ϣ                              */
/************************************************************************/
struct cp_module_info_s
{
	CP_MODULE_INFO_FIELDS
};



#pragma pack()



/************************************************************************/
/* ����ģ�����Ϣ                                                        */
/************************************************************************/
#define CP_MODULE_INFO_SET_TYPE(module_info, in_type)	do {										\
		(module_info)->type = (in_type);															\
	}while(0);																						\


/************************************************************************/
/* ����ģ����û�����													    */
/************************************************************************/
#define CP_MODULE_INFO_SET_DATA(module_info, in_data)	do {										\
		(module_info)->data = (in_data);															\
	}while(0);																						\


/************************************************************************/
/* ����ע����Ϣ����ģ����û�����											*/
/************************************************************************/
#define CP_MODULE_INFO_SET_FROM_REGISTER(module_info, register_info)	do {						\
		(module_info)->type = (register_info)->type;												\
		(module_info)->version = (register_info)->version;											\
		(module_info)->name = (register_info)->name;												\
		(module_info)->description = (register_info)->description;									\
	}while(0);																						\


#endif


