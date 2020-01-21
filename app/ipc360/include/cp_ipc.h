
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_ipc main include file 

**************************************************************************/


#ifndef _CP_IPC_INCLUDE_H_
#define _CP_IPC_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_ipc_info.h"
#include "cp_ipc_hook_core.h"





//typedef  struct cp_ipc_s						 cp_ipc_t;




//#pragma pack(1)


 /************************************************************************/
 /*定义一个ipc app内容                                                 */
 /************************************************************************/
 struct cp_ipc_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*表示定时任务*/
	 cp_socket_t					*tcp_listen;						/*表示TCP监听地址*/
	 cp_socket_t					*udp_listen;						/*表示UDP监听*/
	 cp_socket_t					*multicast_listen;					/*表示multicast监听*/
	 cp_ipc_hook_t					*request_hook;						/*表示请求使用的hook*/
 };


// #pragma pack()



cp_ipc_t *cp_ipc_create(cp_app_info_t *app_info);
int cp_ipc_destroy(cp_ipc_t *ipc);




#endif