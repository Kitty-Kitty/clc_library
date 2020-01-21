/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_demo_task.h"


void cp_vdu_demo_timer_task(cp_timer_t* timer)
{
	cp_vdu_demo_t							*tmp_vdu_demo = (cp_vdu_demo_t *)timer->data;
	cp_vdu_demo_info_t					*tmp_vdu_demo_info = (cp_vdu_demo_info_t *)(tmp_vdu_demo->app_info);
	cp_device_info_t					*tmp_vdu_demo_device_info = ((cp_vdu_demo_info_t*)(tmp_vdu_demo->app_info))->device_info;
	cp_socket_t							*s = CP_NULL;


	cp_log_notice(timer->logger, "vdu_demo timer task");


#if 0
	//向注册选择的中心，发送心跳
	if (!tmp_vdu_demo_info->registered_flag) {
		return;
	}

/*
	s = cp_create_socket(cp_socket_type_udp);
	if (!s) {
		return;
	}*/

	ret = send_rtp_center_life_heart(tmp_vdu_demo, NULL);
	ret = send_rtp_media_life_heart(tmp_vdu_demo, NULL);
	ret = send_rtp_vdu_demo_background_life_heart(tmp_vdu_demo, NULL);
	ret = send_rtp_client_background_life_heart(tmp_vdu_demo, NULL);

/*
	cp_close_socket(s);
	cp_destroy_socket(s);*/

#endif

	return;
}
