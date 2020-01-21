/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ecam_proc.h"
#include "cp_ecam_task.h"


cp_int32_t init_ecam_other(cp_ecam_t *ecam, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_ecam_info_t			*tmp_ecam_info = (cp_ecam_info_t *)(ecam->app_info);


	//创建一个timer
	ecam->timer_task = cp_create_timer(ecam);
	if (!ecam->timer_task) {
		cp_log_error(ecam->logger, "init_ecam_other() error. cp_create_timer() error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(ecam->timer_task, ecam);
	}

	//创建一个tcp_listen
	ecam->tcp_listen = cp_create_socket(ecam, cp_socket_type_tcp);
	if (!ecam->tcp_listen) {
		cp_log_error(ecam->logger, "init_ecam_other() error. cp_create_socket() error. create tcp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(ecam->tcp_listen, ecam);
	}

	//创建一个udp_listen
	ecam->udp_listen = cp_create_socket(ecam, cp_socket_type_udp);
	if (!ecam->udp_listen) {
		cp_log_error(ecam->logger, "init_ecam_other() error. cp_create_socket() error. create udp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(ecam->udp_listen, ecam);
	}

	return 0;
}

cp_int32_t start_ecam_other(cp_ecam_t *ecam, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_sockaddr_in				tmp_tcp_addr;
	cp_sockaddr_in				tmp_udp_addr;
	cp_ecam_info_t				*tmp_ecam_info = (cp_ecam_info_t *)ecam->app_info;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//启动定时器
	ret_int = cp_start_timer(ecam->timer_task, cp_ecam_timer_task, 1000, 10000);
	if (ret_int) {
		cp_log_error(ecam->logger, "start_ecam_other() error. cp_start_timer() error.");
		return -1;
	}
	//配置地址信息
	cp_ip4_addr(tmp_ecam_info->device_info->network.ip, tmp_ecam_info->device_info->network.tcp_port, &tmp_tcp_addr);
	cp_ip4_addr(tmp_ecam_info->device_info->network.ip, tmp_ecam_info->device_info->network.udp_port, &tmp_udp_addr);
	//启动tcp监听
	ret_int = cp_listen_socket(ecam->tcp_listen, &tmp_tcp_addr);
	if (ret_int) {
		cp_log_error(ecam->logger, "start_ecam_other() error. cp_listen_socket(tcp) error. [%s:%d]",
			tmp_ecam_info->device_info->network.ip,
			tmp_ecam_info->device_info->network.tcp_port);
		return -2;
	}
	else {
		cp_log_notice(ecam->logger, "listen tcp [%s:%d] successed!",
			tmp_ecam_info->device_info->network.ip,
			tmp_ecam_info->device_info->network.tcp_port);
	}

	//启动udp监听
	ret_int = cp_listen_socket(ecam->udp_listen, &tmp_udp_addr);
	if (ret_int) {
		cp_log_error(ecam->logger, "start_ecam_other() error. cp_listen_socket(udp) error.[%s:%d]",
			tmp_ecam_info->device_info->network.ip,
			tmp_ecam_info->device_info->network.udp_port);
		return -3;
	}
	else {
		cp_log_notice(ecam->logger, "listen udp [%s:%d] successed!",
			tmp_ecam_info->device_info->network.ip,
			tmp_ecam_info->device_info->network.udp_port);
	}

	return 0;
}

cp_int32_t stop_ecam_other(cp_ecam_t *ecam, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_ecam_info_t				*tmp_ecam_info = (cp_ecam_info_t *)ecam->app_info;


	cp_stop_timer(ecam->timer_task);
	cp_close_socket(ecam->tcp_listen);
	cp_close_socket(ecam->udp_listen);
	
	return 0;
}

