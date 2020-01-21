/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_player_proc.h"
#include "cp_player_task.h"
#include "cp_css_session_core.h"




cp_int32_t init_player_other(cp_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;


	//创建一个timer
	player->timer_task = cp_create_timer();
	if (!player->timer_task) {
		cp_log_error(player->logger, "init_player_other() error. cp_create_timer() error.");
		return -1;
	}

	player->timer_task->data = player;

	//创建一个tcp_listen
	player->tcp_listen = cp_create_socket(CP_SOCKET_TCP);
	if (!player->tcp_listen) {
		cp_log_error(player->logger, "init_player_other() error. cp_create_socket() error.");
		return -1;
	}
	//创建一个udp_listen
	player->udp_listen = cp_create_socket(CP_SOCKET_UDP);
	if (!player->udp_listen) {
		cp_log_error(player->logger, "init_player_other() error. cp_create_socket() error.");
		return -1;
	}

	return 0;
}

cp_int32_t start_player_other(cp_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_sockaddr_in				tmp_tcp_addr;
	cp_sockaddr_in				tmp_udp_addr;
	cp_player_info_t			*tmp_player_info = (cp_player_info_t *)player->app_info;



	//启动定时器
	ret_int = cp_start_timer(player->timer_task, cp_player_timer_task, 1000, 10000);
	if (ret_int) {
		cp_log_error(player->logger, "start_player_other() error. cp_start_timer() error.");
		return -1;
	}
	//配置地址信息
	cp_ip4_addr(tmp_player_info->local_addr, tmp_player_info->local_tcp_port, &tmp_tcp_addr);
	cp_ip4_addr(tmp_player_info->local_addr, tmp_player_info->local_udp_port, &tmp_udp_addr);
	//启动tcp监听
	ret_int = cp_listen_socket(player->tcp_listen, &tmp_tcp_addr);
	if (ret_int) {
		cp_log_error(player->logger, "start_player_other() error. cp_listen_socket(tcp) error. [%s:%d]",
			tmp_player_info->local_addr,
			tmp_player_info->local_tcp_port);
		return -2;
	} else {
		cp_log_notice(player->logger, "listen tcp [%s:%d] successed!",
			tmp_player_info->local_addr,
			tmp_player_info->local_tcp_port);
	}
	//启动udp监听
	ret_int = cp_listen_socket(player->udp_listen, &tmp_udp_addr);
	if (ret_int) {
		cp_log_error(player->logger, "start_player_other() error. cp_listen_socket(udp) error.[%s:%d]",
			tmp_player_info->local_addr,
			tmp_player_info->local_udp_port);
		return -3;
	} else {
		cp_log_notice(player->logger, "listen udp [%s:%d] successed!",
			tmp_player_info->local_addr,
			tmp_player_info->local_udp_port);
	}

	//发送注册指令
	send_semh_center_register(player);

	return 0;
}

cp_int32_t send_semh_connect_callback(cp_socket_t *s, cp_int32_t status)
{
	return 	cp_write_socket(s, s->nread, s->buf, &(s->remote_addr), 0);
}

cp_int32_t send_semh_write_callback(cp_socket_t *s, cp_int32_t status)
{
	return cp_process_write_cb(s, status);
}

cp_int32_t send_semh_center_register(cp_player_t *player)
{
	cp_sockaddr_in						tmp_tcp_addr;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_buf_t							*gmf_data = CP_NULL;
	cp_int32_t							gmf_data_len = 0;
	cp_socket_t							*center_socket = CP_NULL;


	
	//创建gmf_data
	gmf_data_len = make_semh_center_register(player, &gmf_data);
	if (!gmf_data || gmf_data_len <= 0){
		cp_log_error(player->logger, "make_semh_center_register() error. make_semh_center_register() error");
		return cp_false;
	}

	//创建socket
	cp_ip4_addr(tmp_player_info->center_addr, tmp_player_info->center_port, &tmp_tcp_addr);
	center_socket = cp_create_socket(CP_SOCKET_TCP);
	
	CP_SOCKET_SET_FIELDS(center_socket, gmf_data, gmf_data_len, 0, tmp_tcp_addr);

	cp_set_callback_socket(center_socket, send_semh_connect_callback, send_semh_write_callback);

	cp_connect_socket(center_socket, &tmp_tcp_addr);

	return 0;
}


cp_int32_t send_semh_center_life_heart(cp_player_t *player, cp_socket_t *s)
{
	cp_sockaddr_in						tmp_udp_addr;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_buf_t							*gmf_data = CP_NULL;
	cp_int32_t							gmf_len = 0;
	cp_queue_t							*center_server = &(tmp_player_info->cener_server);
	cp_queue_t							*current = CP_NULL;
	cp_device_info_t					*center_info_p = CP_NULL;


	cp_socket_t *alive_socket = CP_NULL;
	alive_socket = cp_create_socket(CP_SOCKET_UDP);
	alive_socket->flag |= CP_SOCKET_FLAG_LISTEN;

	//创建gmf_data
	gmf_len = make_semh_center_life_heart(player, &gmf_data);
	if (!gmf_data || gmf_len <= 0){
		cp_log_error(player->logger, "send_semh_center_life_heart() error. make_semh_center_register() error");
		return cp_false;
	}

	cp_set_callback_socket(alive_socket, send_semh_connect_callback, send_semh_write_callback);

	//遍历中心列表
	for (current = cp_queue_next(center_server); current != center_server;
		current = cp_queue_next(current)) {

		center_info_p = cp_queue_data(current, cp_device_info_t, queue);

		cp_ip4_addr(center_info_p->network.ip, center_info_p->network.udpport, &tmp_udp_addr);

		CP_SOCKET_SET_FIELDS(alive_socket, gmf_data, gmf_len, 0, tmp_udp_addr);

		cp_write_socket(alive_socket, gmf_len, gmf_data, &tmp_udp_addr, 0);
	}

	return 0;
}


cp_int32_t send_semh_media_life_heart(cp_player_t *player, cp_socket_t *s)
{
	cp_sockaddr_in						tmp_udp_addr;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_buf_t							*gmf_data = CP_NULL;
	cp_int32_t							gmf_len = 0;
	cp_queue_t							*media_server = &(tmp_player_info->media_server);
	cp_queue_t							*current = CP_NULL;
	cp_device_info_t					*media_info_p = CP_NULL;

	cp_socket_t *alive_socket = CP_NULL;
	alive_socket = cp_create_socket(CP_SOCKET_UDP);
	alive_socket->flag |= CP_SOCKET_FLAG_LISTEN;

	//创建gmf_data
	gmf_len = make_semh_media_life_heart(player, &gmf_data);
	if (!gmf_data || gmf_len <= 0){
		cp_log_error(player->logger, "send_semh_center_life_heart() error. make_semh_center_register() error");
		return cp_false;
	}

	cp_set_callback_socket(alive_socket, send_semh_connect_callback, send_semh_write_callback);

	//遍历中心列表
	for (current = cp_queue_next(media_server); current != media_server;
		current = cp_queue_next(current)) {

		media_info_p = cp_queue_data(current, cp_device_info_t, queue);

		cp_ip4_addr(media_info_p->network.ip, media_info_p->network.udpport, &tmp_udp_addr);

		CP_SOCKET_SET_FIELDS(alive_socket, gmf_data, gmf_len, 0, tmp_udp_addr);

		cp_write_socket(alive_socket, gmf_len, gmf_data, &tmp_udp_addr, 0);
	}

	return 0;
}

cp_int32_t send_semh_player_background_life_heart(cp_player_t *player, cp_socket_t *s)
{
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_queue_t							*player_server = &(tmp_player_info->player_server);
	cp_buf_t							*gmf_data = CP_NULL;
	cp_int32_t							gmf_len = 0;
	cp_sockaddr_in						tmp_udp_addr;
	cp_queue_t							*current = CP_NULL;
	cp_device_info_t					*player_info_p = CP_NULL;

	cp_socket_t *alive_socket = CP_NULL;
	alive_socket = cp_create_socket(CP_SOCKET_UDP);
	alive_socket->flag |= CP_SOCKET_FLAG_LISTEN;

	//创建gmf_data
	gmf_len = make_semh_player_background_life_heart(player, &gmf_data);
	if (!gmf_data || gmf_len <= 0){
		cp_log_error(player->logger, "player life heart() error. make_semh_player_background_life_heart() error");
		return cp_false;
	}

	cp_set_callback_socket(alive_socket, send_semh_connect_callback, send_semh_write_callback);

	//遍历中心列表
	for (current = cp_queue_next(player_server); current != player_server;
		current = cp_queue_next(current)) {

		player_info_p = cp_queue_data(current, cp_device_info_t, queue);

		cp_ip4_addr(player_info_p->network.ip, player_info_p->network.udpport, &tmp_udp_addr);

		CP_SOCKET_SET_FIELDS(alive_socket, gmf_data, gmf_len, 0, tmp_udp_addr);

		cp_write_socket(alive_socket, gmf_len, gmf_data, &tmp_udp_addr, 0);
	}

	return 0;
}

cp_int32_t send_semh_client_background_life_heart(cp_player_t *player, cp_socket_t *s)
{
	cp_sockaddr_in						tmp_udp_addr;
	cp_player_t							*tmp_player = player;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_queue_t							*client_server = &(tmp_player_info->client_server);
	cp_buf_t							*gmf_data = CP_NULL;
	cp_int32_t							gmf_len = 0;
	cp_queue_t							*current = CP_NULL;
	cp_device_info_t					*client_info_p = CP_NULL;

	cp_socket_t *alive_socket = CP_NULL;
	alive_socket = cp_create_socket(CP_SOCKET_UDP);
	alive_socket->flag |= CP_SOCKET_FLAG_LISTEN;

	//创建gmf_data
	gmf_len = make_semh_player_background_life_heart(player, &gmf_data);
	if (!gmf_data || gmf_len <= 0){
		cp_log_error(player->logger, "player life heart() error. make_semh_player_background_life_heart() error");
		return cp_false;
	}

	cp_set_callback_socket(alive_socket, send_semh_connect_callback, send_semh_write_callback);

	//遍历中心列表
	for (current = cp_queue_next(client_server); current != client_server;
		current = cp_queue_next(current)) {

		client_info_p = cp_queue_data(current, cp_device_info_t, queue);

		cp_ip4_addr(client_info_p->network.ip, client_info_p->network.udpport, &tmp_udp_addr);

		CP_SOCKET_SET_FIELDS(alive_socket, gmf_data, gmf_len, 0, tmp_udp_addr);

		cp_write_socket(alive_socket, gmf_len, gmf_data, &tmp_udp_addr, 0);
	}

	return 0;
}



