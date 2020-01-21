/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ipc_task.h"


void cp_ipc_timer_task(cp_timer_t* timer)
{
	cp_ipc_t							*tmp_ipc = (cp_ipc_t *)timer->data;
	cp_ipc_info_t					*tmp_ipc_info = (cp_ipc_info_t *)(tmp_ipc->app_info);
	cp_device_info_t					*tmp_ipc_device_info = ((cp_ipc_info_t*)(tmp_ipc->app_info))->device_info;
	cp_socket_t							*s = CP_NULL;


	cp_log_notice(timer->logger, "[%s] timer task. working now...", CP_IPC_VER);

#if 0
	//向注册选择的中心，发送心跳
	if (!tmp_ipc_info->registered_flag) {
		return;
	}

/*
	s = cp_create_socket(cp_socket_type_udp);
	if (!s) {
		return;
	}*/

	ret = send_rtp_center_life_heart(tmp_ipc, NULL);
	ret = send_rtp_media_life_heart(tmp_ipc, NULL);
	ret = send_rtp_ipc_background_life_heart(tmp_ipc, NULL);
	ret = send_rtp_client_background_life_heart(tmp_ipc, NULL);

/*
	cp_close_socket(s);
	cp_destroy_socket(s);*/

#endif

	return;
}
