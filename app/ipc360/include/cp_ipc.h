
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
 /*����һ��ipc app����                                                 */
 /************************************************************************/
 struct cp_ipc_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*��ʾ��ʱ����*/
	 cp_socket_t					*tcp_listen;						/*��ʾTCP������ַ*/
	 cp_socket_t					*udp_listen;						/*��ʾUDP����*/
	 cp_socket_t					*multicast_listen;					/*��ʾmulticast����*/
	 cp_ipc_hook_t					*request_hook;						/*��ʾ����ʹ�õ�hook*/
 };


// #pragma pack()



cp_ipc_t *cp_ipc_create(cp_app_info_t *app_info);
int cp_ipc_destroy(cp_ipc_t *ipc);




#endif