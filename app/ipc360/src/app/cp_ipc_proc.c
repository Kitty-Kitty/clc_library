/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ipc_proc.h"
#include "cp_ipc_task.h"


cp_int32_t init_ipc_other(cp_ipc_t *ipc, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_ipc_info_t			*tmp_ipc_info = (cp_ipc_info_t *)(ipc->app_info);


	//创建一个timer
	ipc->timer_task = cp_create_timer(ipc);
	if (!ipc->timer_task) {
		cp_log_error(ipc->logger, "init_ipc_other() error. cp_create_timer() error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(ipc->timer_task, ipc);
	}

	//创建一个tcp_listen
	ipc->tcp_listen = cp_create_socket(ipc, cp_socket_type_tcp);
	if (!ipc->tcp_listen) {
		cp_log_error(ipc->logger, "init_ipc_other() error. cp_create_socket() error. create tcp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(ipc->tcp_listen, ipc);
	}

	//创建一个udp_listen
	ipc->udp_listen = cp_create_socket(ipc, cp_socket_type_udp);
	if (!ipc->udp_listen) {
		cp_log_error(ipc->logger, "init_ipc_other() error. cp_create_socket() error. create udp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(ipc->udp_listen, ipc);
	}

	return 0;
}

cp_int32_t start_ipc_other(cp_ipc_t *ipc, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_sockaddr_in				tmp_tcp_addr;
	cp_sockaddr_in				tmp_udp_addr;
	cp_ipc_info_t				*tmp_ipc_info = (cp_ipc_info_t *)ipc->app_info;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	//启动定时器
	ret_int = cp_start_timer(ipc->timer_task, cp_ipc_timer_task, 1000, 10000);
	if (ret_int) {
		cp_log_error(ipc->logger, "start_ipc_other() error. cp_start_timer() error.");
		return -1;
	}
	//配置地址信息
	cp_ip4_addr(tmp_ipc_info->device_info->network.ip, tmp_ipc_info->device_info->network.tcp_port, &tmp_tcp_addr);
	cp_ip4_addr(tmp_ipc_info->device_info->network.ip, tmp_ipc_info->device_info->network.udp_port, &tmp_udp_addr);
	//启动tcp监听
	ret_int = cp_listen_socket(ipc->tcp_listen, &tmp_tcp_addr);
	if (ret_int) {
		cp_log_error(ipc->logger, "start_ipc_other() error. cp_listen_socket(tcp) error. [%s:%d]",
			tmp_ipc_info->device_info->network.ip,
			tmp_ipc_info->device_info->network.tcp_port);
		return -2;
	}
	else {
		cp_log_notice(ipc->logger, "listen tcp [%s:%d] successed!",
			tmp_ipc_info->device_info->network.ip,
			tmp_ipc_info->device_info->network.tcp_port);
	}

	//启动udp监听
	ret_int = cp_listen_socket(ipc->udp_listen, &tmp_udp_addr);
	if (ret_int) {
		cp_log_error(ipc->logger, "start_ipc_other() error. cp_listen_socket(udp) error.[%s:%d]",
			tmp_ipc_info->device_info->network.ip,
			tmp_ipc_info->device_info->network.udp_port);
		return -3;
	}
	else {
		cp_log_notice(ipc->logger, "listen udp [%s:%d] successed!",
			tmp_ipc_info->device_info->network.ip,
			tmp_ipc_info->device_info->network.udp_port);
	}

	return 0;
}

cp_int32_t stop_ipc_other(cp_ipc_t *ipc, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_ipc_info_t				*tmp_ipc_info = (cp_ipc_info_t *)ipc->app_info;


	cp_stop_timer(ipc->timer_task);
	cp_close_socket(ipc->tcp_listen);
	cp_close_socket(ipc->udp_listen);
	
	return 0;
}

