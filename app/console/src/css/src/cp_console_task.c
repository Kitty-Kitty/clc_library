/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_player_task.h"


void cp_player_timer_task(cp_timer_t* timer)
{
	cp_player_t							*tmp_player = (cp_player_t *)timer->data;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(tmp_player->app_info))->device_info;
	cp_socket_t							*s = CP_NULL;
	cp_int32_t							ret;


	cp_log_notice(timer->logger, "player timer task");

	//向注册选择的中心，发送心跳
	if (!tmp_player_info->registered_flag){
		return;
	}

/*
	s = cp_create_socket(CP_SOCKET_UDP);
	if (!s){
		return;
	}*/

	ret = send_semh_center_life_heart(tmp_player, NULL);
	ret = send_semh_media_life_heart(tmp_player, NULL);
	ret = send_semh_player_background_life_heart(tmp_player, NULL);
	ret = send_semh_client_background_life_heart(tmp_player, NULL);

/*
	cp_close_socket(s);
	cp_destory_socket(s);*/

	return;
}
