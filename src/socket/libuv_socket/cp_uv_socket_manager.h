/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_UV_SOCKET_MANAGER_INCLUDE_H_
#define _CP_UV_SOCKET_MANAGER_INCLUDE_H_




#include "cp_include.h"
#include "cp_uv_socket_core.h"





#define	CP_UV_SOCKET_MANAGER_DEFAULT_INTERVAL			1000

//typedef	struct cp_uv_socket_manager_handles_s			cp_uv_socket_manager_handles_t;
//typedef struct cp_uv_socket_manager_s					cp_uv_socket_manager_t;




#pragma pack(1)



/************************************************************************/
/*                                                                      */
/************************************************************************/

struct cp_uv_socket_manager_s
{
	CP_SOCKET_MANAGER_FIELDS
	uv_loop_t							loop;							/*当前处理loop*/
	cp_thread_t							*thread;						/*启动loop用的线程，避免阻塞*/
	uv_timer_t							uv_timer;						/*定义一个timer*/
};



#pragma pack()


cp_uv_socket_manager_t* create_uv_socket_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_uv_socket_manager_info_t *info);
cp_int32_t destroy_uv_socket_manager(cp_app_t *app, cp_uv_socket_manager_t* manager);

#endif


