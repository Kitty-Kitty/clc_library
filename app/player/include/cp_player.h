
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
 /*定义一个player app内容                                                 */
 /************************************************************************/
 struct cp_player_s {
	 CP_APP_FIELDS
	 cp_timer_t						*timer_task;						/*表示定时任务*/
	 cp_socket_t					*tcp_listen;						/*表示TCP监听地址*/
	 cp_socket_t					*udp_listen;						/*表示UDP监听*/
	 cp_socket_t					*multicast_listen;					/*表示multicast监听*/
	 cp_css_hook_t					*request_hook;						/*表示请求使用的hook*/
 };


// #pragma pack()



cp_player_t *cp_player_create(cp_app_info_t *app_info);
int cp_player_destroy(cp_player_t *player);




#endif