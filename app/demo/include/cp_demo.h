
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_demo main include file 

**************************************************************************/


#ifndef _CP_DEMO_INCLUDE_H_
#define _CP_DEMO_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_demo_info.h"
#include "cp_demo_hook_core.h"





//typedef  struct cp_demo_s						 cp_demo_t;




//#pragma pack(1)


 /************************************************************************/
 /*����һ��demo app����                                                 */
 /************************************************************************/
 struct cp_demo_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*��ʾ��ʱ����*/
	 cp_socket_t					*tcp_listen;						/*��ʾTCP������ַ*/
	 cp_socket_t					*udp_listen;						/*��ʾUDP����*/
	 cp_socket_t					*multicast_listen;					/*��ʾmulticast����*/
	 cp_demo_hook_t					*request_hook;						/*��ʾ����ʹ�õ�hook*/
 };


// #pragma pack()



cp_demo_t *cp_demo_create(cp_app_info_t *app_info);
int cp_demo_destroy(cp_demo_t *demo);




#endif