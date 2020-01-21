/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-17

Description:

**************************************************************************/

#ifndef _CP_MODULE_STATUS_INCLUDE_H_
#define _CP_MODULE_STATUS_INCLUDE_H_



#include "cp_bit.h"


#pragma pack(1)

enum cp_module_status_enum
{
	cp_module_status_none		= 0,

	/*该部分定义模块状态类型*/
	cp_module_status_create		= B32(00000000, 01000000, 00000000, 00000000),

	cp_module_status_registed	= B32(00000000, 00000000, 00000001, 00000000),
	cp_module_status_init		= B32(00000000, 00000000, 00000010, 00000000),
	cp_module_status_start		= B32(00000000, 00000000, 00000100, 00000000),
	cp_module_status_open		= B32(00000000, 00000000, 00010000, 00000000),
	cp_module_status_read		= B32(00000000, 00000000, 00100000, 00000000),
	cp_module_status_write		= B32(00000000, 00000000, 01000000, 00000000),
	//cp_module_status_stop		= B32(00000000, 00000000, 00001000, 00000000),
	//cp_module_status_close	= B32(00000000, 00000000, 10000000, 00000000),
	//cp_module_status_exit		= B32(00000000, 00000001, 00000000, 00000000),
	//cp_module_status_cancel	= B32(00000000, 10000000, 00000000, 00000000),

	//cp_module_status_destroy	= B32(00000000, 10000000, 00000000, 00000000),

	/*该部分定义状态类型*/
	//请不要在end后定义内容
	cp_module_status_end		= B32(00010000, 00000000, 00000000, 00000000)
};

#pragma pack()


/************************************************************************/
/* 设置模块的状态                                                        */
/************************************************************************/
#define CP_MODULE_SET_STATUS(in_module, in_status)	do {				\
		(in_module)->status |= (in_status);								\
	}while(0);															\


/************************************************************************/
/* 设置模块的状态                                                        */
/************************************************************************/
#define CP_MODULE_UNSET_STATUS(in_module, in_status)	do {			\
		(in_module)->status &= ~(in_status);							\
	}while(0);															\


/************************************************************************/
/* 获取模块的状态														*/
/************************************************************************/
#define	CP_MODULE_GET_STATUS(module, in_status)	((module)->status & (in_status))

#endif


