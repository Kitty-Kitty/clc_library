
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file 

**************************************************************************/


#ifndef _CP_FUSION_PLAYER_INCLUDE_H_
#define _CP_FUSION_PLAYER_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>





#include "cp_core.h"
#include "cp_include.h"
#include "cp_fusion_player_info.h"





//typedef  struct cp_fusion_player_s						 cp_fusion_player_t;




//#pragma pack(1)


 /************************************************************************/
 /*����һ��player app����                                                 */
 /************************************************************************/
 struct cp_fusion_player_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*��ʾ��ʱ����*/
	 cp_socket_t					*tcp_listen;						/*��ʾTCP������ַ*/
	 cp_socket_t					*udp_listen;						/*��ʾUDP����*/
	 cp_socket_t					*multicast_listen;					/*��ʾmulticast����*/
	 cp_func_t						*video_func;						/*��ʾ��Ƶ����func*/
 };


// #pragma pack()



cp_fusion_player_t *cp_fusion_player_create(cp_app_info_t *app_info);
int cp_fusion_player_destroy(cp_fusion_player_t *player);




#endif