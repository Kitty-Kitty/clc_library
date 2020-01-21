/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-05-26

Description: define module information

**************************************************************************/


#ifndef	_CP_SOCKET_MANAGER_INFO_INCLUDE_H_
#define _CP_SOCKET_MANAGER_INFO_INCLUDE_H_



#include "cp_socket_core.h"



//typedef struct cp_socket_manager_info_s			cp_socket_manager_info_t;




#pragma pack(1)


#define CP_SOCKET_MANAGER_INFO_FIELDS												\
	CP_MODULE_MANAGER_INFO_FIELDS													\
	cp_int32_t	timer_interval_ms;	/*����������г�ʱ��ʱ����ʱ����*/				\



/************************************************************************/
/* ��ʾģ�������Ϣ����ģ����Ϣ����̳и���Ϣ                              */
/************************************************************************/
struct cp_socket_manager_info_s
{
	CP_SOCKET_MANAGER_INFO_FIELDS
};



#pragma pack()




#endif


