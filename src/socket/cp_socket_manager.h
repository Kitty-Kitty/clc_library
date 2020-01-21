/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SOCKET_MANAGER_INCLUDE_H_
#define _CP_SOCKET_MANAGER_INCLUDE_H_




#include "cp_timer_core.h"
#include "cp_socket_core.h"
#include "cp_module_manager.h"





//typedef struct cp_socket_manager_s						cp_socket_manager_t;




#pragma pack(1)




/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CP_SOCKET_MANAGER_FIELDS																					\
		CP_MODULE_MANAGER_FIELDS																					\
		cp_socket_t						*tcp_s;					/*表示TCP监听连接*/									\
		cp_socket_t						*udp_s;					/*表示UDPP监听连接*/									\
		cp_timer_t						*timer;					/*表示连接操作使用的定时器*/							\



struct cp_socket_manager_s {
	CP_SOCKET_MANAGER_FIELDS
};


#pragma pack()




cp_socket_manager_t* create_socket_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_socket_info_t *info);
cp_int32_t destroy_socket_manager(cp_app_t *app, cp_socket_manager_t* manager);

#endif


