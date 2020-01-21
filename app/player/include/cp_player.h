
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file 

**************************************************************************/


#ifndef _CP_PLAYER_INCLUDE_H_
#define _CP_PLAYER_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_player_info.h"
#include "cp_css_hook_core.h"





//typedef  struct cp_player_s						 cp_player_t;




//#pragma pack(1)


 /************************************************************************/
 /*����һ��player app����                                                 */
 /************************************************************************/
 struct cp_player_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*��ʾ��ʱ����*/
	 cp_socket_t					*tcp_listen;						/*��ʾTCP������ַ*/
	 cp_socket_t					*udp_listen;						/*��ʾUDP����*/
	 cp_socket_t					*multicast_listen;					/*��ʾmulticast����*/
	 cp_css_hook_t					*request_hook;						/*��ʾ����ʹ�õ�hook*/
 };


// #pragma pack()



cp_player_t *cp_player_create(cp_app_info_t *app_info);
int cp_player_destroy(cp_player_t *player);




#endif