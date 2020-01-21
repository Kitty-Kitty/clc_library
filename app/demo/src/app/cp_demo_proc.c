/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_demo_proc.h"
#include "cp_demo_task.h"


cp_int32_t init_demo_other(cp_demo_t *demo, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_demo_info_t			*tmp_demo_info = (cp_demo_info_t *)(demo->app_info);


	//创建一个timer
	demo->timer_task = cp_create_timer(demo);
	if (!demo->timer_task) {
		cp_log_error(demo->logger, "init_demo_other() error. cp_create_timer() error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(demo->timer_task, demo);
	}

	//创建一个tcp_listen
	demo->tcp_listen = cp_create_socket(demo, cp_socket_type_tcp);
	if (!demo->tcp_listen) {
		cp_log_error(demo->logger, "init_demo_other() error. cp_create_socket() error. create tcp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(demo->tcp_listen, demo);
	}

	//创建一个udp_listen
	demo->udp_listen = cp_create_socket(demo, cp_socket_type_udp);
	if (!demo->udp_listen) {
		cp_log_error(demo->logger, "init_demo_other() error. cp_create_socket() error. create udp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(demo->udp_listen, demo);
	}

	return 0;
}

cp_int32_t start_demo_other(cp_demo_t *demo, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_sockaddr_in				tmp_tcp_addr;
	cp_sockaddr_in				tmp_udp_addr;
	cp_demo_info_t				*tmp_demo_info = (cp_demo_info_t *)demo->app_info;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//启动定时器
	ret_int = cp_start_timer(demo->timer_task, cp_demo_timer_task, 1000, 10000);
	if (ret_int) {
		cp_log_error(demo->logger, "start_demo_other() error. cp_start_timer() error.");
		return -1;
	}
	//配置地址信息
	cp_ip4_addr(tmp_demo_info->device_info->network.ip, tmp_demo_info->device_info->network.tcp_port, &tmp_tcp_addr);
	cp_ip4_addr(tmp_demo_info->device_info->network.ip, tmp_demo_info->device_info->network.udp_port, &tmp_udp_addr);
	//启动tcp监听
	ret_int = cp_listen_socket(demo->tcp_listen, &tmp_tcp_addr);
	if (ret_int) {
		cp_log_error(demo->logger, "start_demo_other() error. cp_listen_socket(tcp) error. [%s:%d]",
			tmp_demo_info->device_info->network.ip,
			tmp_demo_info->device_info->network.tcp_port);
		return -2;
	}
	else {
		cp_log_notice(demo->logger, "listen tcp [%s:%d] successed!",
			tmp_demo_info->device_info->network.ip,
			tmp_demo_info->device_info->network.tcp_port);
	}

	//启动udp监听
	ret_int = cp_listen_socket(demo->udp_listen, &tmp_udp_addr);
	if (ret_int) {
		cp_log_error(demo->logger, "start_demo_other() error. cp_listen_socket(udp) error.[%s:%d]",
			tmp_demo_info->device_info->network.ip,
			tmp_demo_info->device_info->network.udp_port);
		return -3;
	}
	else {
		cp_log_notice(demo->logger, "listen udp [%s:%d] successed!",
			tmp_demo_info->device_info->network.ip,
			tmp_demo_info->device_info->network.udp_port);
	}

	return 0;
}

cp_int32_t stop_demo_other(cp_demo_t *demo, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_demo_info_t				*tmp_demo_info = (cp_demo_info_t *)demo->app_info;


	cp_stop_timer(demo->timer_task);
	cp_close_socket(demo->tcp_listen);
	cp_close_socket(demo->udp_listen);
	
	return 0;
}

