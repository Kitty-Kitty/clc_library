/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module information

**************************************************************************/


#ifndef	_CP_SOCKET_INFO_INCLUDE_H_
#define _CP_SOCKET_INFO_INCLUDE_H_



#include "cp_module_info.h"



//typedef struct cp_socket_info_s					cp_socket_info_t;




#pragma pack(1)


#define CP_SOCKET_INFO_FIELDS												\
	CP_MODULE_INFO_FIELDS													\
	cp_socket_type_e			socket_type;		/*表示socket类型*/		\



/************************************************************************/
/* 表示模块基础信息，子模块信息必须继承该信息                              */
/************************************************************************/
struct cp_socket_info_s
{
	CP_SOCKET_INFO_FIELDS
};



#pragma pack()




#endif


