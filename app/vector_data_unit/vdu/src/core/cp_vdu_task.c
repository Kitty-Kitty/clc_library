/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_task.h"


void cp_vdu_timer_task(cp_timer_t* timer)
{
	cp_vdu_app_t							*tmp_vdu = (cp_vdu_app_t *)timer->data;
	cp_vdu_app_info_t						*tmp_vdu_info = (cp_vdu_app_info_t *)(tmp_vdu->app_info);
	cp_socket_t							*s = CP_NULL;


	cp_log_notice(timer->logger, "vdu timer task");


	return;
}
