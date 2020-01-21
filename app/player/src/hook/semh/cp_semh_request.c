/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-21

Description:

**************************************************************************/

#include "cp_semh_request.h"




cp_int32_t send_semh_connect_callback(cp_socket_t *s, cp_int32_t status)
{
	return 	cp_write_socket(s, s->buf, s->nread, &(s->remote_addr), 0);
}

cp_int32_t send_semh_write_heartbeat_callback(cp_socket_t *s, cp_int32_t status)
{
	cp_int32_t							tmp_ret_int = 0;


	tmp_ret_int = send_heartbeat_data_cycle((cp_heartbeat_manager_t*)(s->data), s);

	return tmp_ret_int;
}

cp_int32_t send_semh_write_register_callback(cp_socket_t *s, cp_int32_t status)
{
	return cp_process_write_cb(s, status);
}

cp_int32_t send_heartbeat_data_cycle(cp_heartbeat_manager_t *hm, cp_socket_t *s)
{
	cp_device_heartbeat_t				*tmp_dhb = CP_NULL;
	cp_int32_t							tmp_ret_int = 0;



	tmp_dhb = get_device_heartbeat(hm);
	if (!tmp_dhb) {
		return -1;
	}

	tmp_ret_int = send_device_heartbeat_data(tmp_dhb, s);

	return tmp_ret_int;
}

cp_int32_t send_device_heartbeat_data(cp_device_heartbeat_t *dhb, cp_socket_t *s)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_heartbeat_manager_t				*tmp_hm = CP_NULL;



	if (!dhb || !dhb->heartbeat_manager) {
		return -1;
	}

	tmp_hm = dhb->heartbeat_manager;
	tmp_ret_int = cp_write_socket(s, 
		&(tmp_hm->heartbeat_data),
		cp_buf_get_length(&(tmp_hm->heartbeat_data)),
		&(dhb->hearbeat_address), 0);
	if (tmp_ret_int) {
		cp_log_error(tmp_hm->logger, "send heartbeat to [%s] failed.", dhb->device_info_data);
	} else {
		cp_log_info(tmp_hm->logger, "send heartbeat to [%s] successed.", dhb->device_info_data);
	}

	return tmp_ret_int;
}

//使用异步方式发送心跳
cp_int32_t send_semh_life_heart_async(cp_player_t *player)
{
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_buf_t							*gmf_data = CP_NULL;
	cp_device_heartbeat_t				**tmp_dh_p = CP_NULL;
	cp_device_heartbeat_t				**tmp_first_dh_p = CP_NULL;
	cp_int32_t							gmf_len = 0;
	cp_int32_t							i = 0;
	cp_int32_t							tmp_device_number = 0;
	cp_int32_t							tmp_command = 0;
	cp_bool_t							tmp_rw_sync = cp_true;
	

	if (css_device_type_css_video_player == tmp_player_device_info->host.type) {
		tmp_command = GMP_SEMH_PLAYER_CMD_LIFE_HEART;
	}
	else {
		tmp_command = GMP_SEMH_AUDIO_PLAYER_CMD_LIFE_HEART;
	}

	//创建gmf_data
	gmf_len = make_device_semh_life_heart_data(player, tmp_command, &gmf_data);
	if (!gmf_data || gmf_len <= 0) {
		cp_log_error(player->logger, "send_semh_center_life_heart() error. make_semh_center_register() error");
		return cp_false;
	} else {
		cp_buf_clear(&tmp_player_info->heartbeat_manager.heartbeat_data);
		cp_buf_strcat(&tmp_player_info->heartbeat_manager.heartbeat_data, gmf_data->pos, cp_buf_get_length(gmf_data));
	}

	cp_set_callback_socket(tmp_player_info->heartbeat_manager.heartbeat_udp_listen, 
		send_semh_connect_callback, send_semh_write_heartbeat_callback);
	
	//清空错误列表
	cp_array_clear(&tmp_player_info->heartbeat_manager.failed_device_heartbeats);

	//开始遍历发送心跳信息
	cp_mutex_lock(&tmp_player_info->device_heartbeats_mutex);

	//遍历心跳列表
	for (i = 0; tmp_device_number < (cp_int32_t)cp_array_length(&tmp_player_info->heartbeat_manager.device_heartbeats)
		&& i < CP_PLAYER_MAX_DEVICE_NUMBER; i++) {

		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.device_heartbeats, i);
		if (!tmp_dh_p || !(*tmp_dh_p)) {
			continue;
		}

		++tmp_device_number;

		//如果丢失次数已经大于最大丢失次数限制，则删除该设备
		if ((*tmp_dh_p)->send_times >= tmp_player_info->heartbeat_manager.heartbeat_interval_lost_times) {
			//这里判断是否为中心掉线，如果是中心掉线则重新注册
			//是其他设备掉线则直接删除该设备
			if (css_device_type_center == (*tmp_dh_p)->type) {
				tmp_player_info->registered_flag = cp_false;
			} else {
				//将设备加入到错误设备中，并且重正确列表中移除该设备
				cp_array_set_back(&tmp_player_info->heartbeat_manager.failed_device_heartbeats, tmp_dh_p);
				continue;
			}
		}

		//如果是第一个则在其他的设备插入后，直接发送
		if (!tmp_first_dh_p) {
			tmp_first_dh_p = tmp_dh_p;
		} else {
			if (send_device_heartbeat(&tmp_player_info->heartbeat_manager, (*tmp_dh_p))) {
				cp_log_error(player->logger,
					"add heartbeat device [%s] failed. send_device_heartbeat() error.",
					(*tmp_dh_p)->device_info_data);
			}
			else {
				cp_log_info(player->logger,
					"add heartbeat device [%s] successed.", (*tmp_dh_p)->device_info_data);
			}
		}
		++((*tmp_dh_p)->send_times);
	}

	//插入后发送第一个请求
	if (tmp_first_dh_p && (*tmp_first_dh_p)) {
		send_device_heartbeat_data((*tmp_first_dh_p), tmp_player_info->heartbeat_manager.heartbeat_udp_listen);
	}

	cp_mutex_unlock(&tmp_player_info->device_heartbeats_mutex);

	//这里处理错误的设备列表
	for (i = 0; i < (cp_int32_t)cp_array_length(&tmp_player_info->heartbeat_manager.failed_device_heartbeats); i++)	{
		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.failed_device_heartbeats, i);
		if (!tmp_dh_p || !(*tmp_dh_p)) {
			continue;
		}

		remove_device_info(tmp_player, (*tmp_dh_p)->id, (*tmp_dh_p)->type);
	}

	return 0;
}

cp_int32_t send_semh_life_heart_sync(cp_player_t *player)
{
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_device_heartbeat_t				**tmp_dh_p = CP_NULL;
	cp_int32_t							tmp_ret_int = 0;
	cp_int32_t							i = 0;
	cp_int32_t							tmp_device_number = 0;
	cp_int32_t							tmp_command = 0;
	cp_bool_t							tmp_rw_sync = cp_true;


	//创建gmf_data
	cp_buf_clear(&tmp_player_info->heartbeat_manager.heartbeat_data);

	if (css_device_type_css_video_player == tmp_player_device_info->host.type) {
		tmp_command = GMP_SEMH_PLAYER_CMD_LIFE_HEART;
	}
	else {
		//tmp_command = GMP_SEMH_AUDIO_PLAYER_CMD_LIFE_HEART;
		tmp_command = GMP_SEMH_PLAYER_CMD_LIFE_HEART;
	}

	tmp_ret_int = make_device_semh_life_heart_data(player, tmp_command, &tmp_player_info->heartbeat_manager.heartbeat_data);
	if (tmp_ret_int) {
		cp_log_error(player->logger, "send_semh_center_life_heart() error. make_semh_center_register() error");
		return cp_false;
	}

	//设置同步标志
	cp_set_option_module(tmp_player_info->heartbeat_manager.heartbeat_udp_listen, cp_socket_set_option_write_sync, &tmp_rw_sync);

	//清空错误列表
	cp_array_clear(&tmp_player_info->heartbeat_manager.failed_device_heartbeats);

	//开始遍历发送心跳信息
	cp_mutex_lock(&tmp_player_info->device_heartbeats_mutex);

	//遍历心跳列表
	for (i = 0; tmp_device_number < (cp_int32_t)cp_array_length(&tmp_player_info->heartbeat_manager.device_heartbeats)
		&& i < CP_PLAYER_MAX_DEVICE_NUMBER; i++) {

		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.device_heartbeats, i);
		if (!tmp_dh_p || !(*tmp_dh_p)) {
			continue;
		}

		++tmp_device_number;

		//如果丢失次数已经大于最大丢失次数限制，则删除该设备
		if ((*tmp_dh_p)->send_times >= tmp_player_info->heartbeat_manager.heartbeat_interval_lost_times) {
			//这里判断是否为中心掉线，如果是中心掉线则重新注册
			//是其他设备掉线则直接删除该设备
			if (css_device_type_center == (*tmp_dh_p)->type) {
				tmp_player_info->registered_flag = cp_false;

				cp_app_log(error, player,
					"center[id:%s type:%d addr:%s:%d send_times:%d] more than max_lost[%d], register now...",
					(*tmp_dh_p)->id,
					(*tmp_dh_p)->type,
					(*tmp_dh_p)->ip,
					(*tmp_dh_p)->udp_port,
					(*tmp_dh_p)->send_times,
					tmp_player_info->heartbeat_manager.heartbeat_interval_lost_times
					);
			}
			else {
				//将设备加入到错误设备中，并且重正确列表中移除该设备
				cp_array_set_back(&tmp_player_info->heartbeat_manager.failed_device_heartbeats, tmp_dh_p);

				continue;
			}
		}

		send_device_heartbeat_data((*tmp_dh_p), tmp_player_info->heartbeat_manager.heartbeat_udp_listen);
		++((*tmp_dh_p)->send_times);
	}

	cp_mutex_unlock(&tmp_player_info->device_heartbeats_mutex);

	//这里处理错误的设备列表
	for (i = 0; i < (cp_int32_t)cp_array_length(&tmp_player_info->heartbeat_manager.failed_device_heartbeats); i++)	{
		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.failed_device_heartbeats, i);
		if (!tmp_dh_p || !(*tmp_dh_p)) {
			continue;
		}

		cp_app_log(warn, player,
			"delete device[id:%s type:%d addr:%s:%d send_times:%d] more than max_lost[%d]",
			(*tmp_dh_p)->id,
			(*tmp_dh_p)->type,
			(*tmp_dh_p)->ip,
			(*tmp_dh_p)->udp_port,
			(*tmp_dh_p)->send_times,
			tmp_player_info->heartbeat_manager.heartbeat_interval_lost_times
			);

		remove_device_info(tmp_player, (*tmp_dh_p)->id, (*tmp_dh_p)->type);
	}

	return 0;
}


cp_int32_t send_semh_get_audio_channel_info(cp_player_t *player, cp_play_channel_info_t *cp_info)
{

	return 0;
}

void cp_semh_timer_task(cp_timer_t* timer)
{
	cp_player_t							*tmp_player = (cp_player_t *)timer->data;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);
	cp_int32_t							ret;
	cp_bool_t							ret_bool = cp_false;


	cp_log_notice(timer->logger, "semh timer send heartbeat");

	//ret = send_semh_life_heart_async(tmp_player);
	ret = send_semh_life_heart_sync(tmp_player);

	//处理是否需要重新注册
	ret_bool = check_is_registe_now(tmp_player);
	if (ret_bool) {
		cp_gettimeofday(&tmp_player_info->registered_time, CP_NULL);
		send_semh_center_register((cp_app_t*)tmp_player);
	}
	return;
}

cp_int32_t send_semh_center_register(cp_app_t *app)
{
	cp_sockaddr_in						tmp_tcp_addr;
	cp_player_t							*tmp_player = (cp_player_t*)app;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(app->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(app->app_info))->device_info;
	cp_buf_t							*gmf_data = CP_NULL;
	cp_int32_t							gmf_data_len = 0;
	cp_socket_t							*center_socket = CP_NULL;



	//创建gmf_data
	gmf_data_len = make_semh_center_register(tmp_player, &gmf_data);
	if (!gmf_data || gmf_data_len <= 0) {
		cp_log_error(tmp_player->logger, "make_semh_center_register() error. make_semh_center_register() error");
		return -1;
	}

	//创建socket
	cp_ip4_addr(tmp_player_info->center_addr, tmp_player_info->center_port, &tmp_tcp_addr);

	if (tmp_player_info->register_socket) {
		center_socket = tmp_player_info->register_socket;
	}
	else {
		center_socket = cp_create_socket(app, cp_socket_type_tcp);
		if (!center_socket) {
			cp_log_error(tmp_player->logger, "make_semh_center_register() error. cp_create_socket() error");
			return -2;
		}
		else {
			tmp_player_info->register_socket = center_socket;
		}
	}
	
	CP_SOCKET_SET_FIELDS(center_socket, gmf_data, gmf_data_len, 0, tmp_tcp_addr);

	cp_set_callback_socket(center_socket, send_semh_connect_callback, send_semh_write_register_callback);

	cp_connect_socket(center_socket, &tmp_tcp_addr);

	return 0;
}

cp_bool_t check_is_registe_now(cp_player_t *player)
{
	cp_timeval							tmp_tv = { 0, };
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_int32_t							ret_int = 0;



	//处理是否需要重新注册
	if (!tmp_player_info->registered_flag) {
		cp_gettimeofday(&tmp_tv, CP_NULL);
		ret_int = cp_abs(tmp_tv.tv_sec, tmp_player_info->registered_time.tv_sec);
		if (ret_int >= (tmp_player_info->heartbeat_manager.heartbeat_interval_ms / CP_CONF_XML_TIME_THOUND)) {
			return cp_true;
		}
	}

	return cp_false;
}