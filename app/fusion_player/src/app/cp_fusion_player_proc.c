/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_fusion_player_proc.h"
#include "cp_fusion_player_task.h"


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_player_socket_data
*
* 函数说明: 更新socket data 数据
*
* 参    数: cp_void_t *data						[in]参数说明
* 参    数: cp_socket_t * socket						[in]参数说明
* 参    数: cp_socket_data_type_e type						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-28 13:32:26
******************************************************************************************************/
cp_int32_t set_socket_data(cp_void_t *data, cp_socket_t *socket, cp_socket_data_type_e type);

cp_int32_t create_request_hook(cp_fusion_player_t *player);

cp_int32_t start_player_func_proc(cp_fusion_player_t *player, cp_app_info_t *app_info)
{
	cp_func_t						*tmp_player_func = CP_NULL;
	cp_module_info_t				tmp_mi = { 0, };
	cp_int32_t						ret_int = 0;



	tmp_player_func = (cp_func_t *)cp_manager_get_sub_module(player, cp_fusion_player_manager_type_func, cp_fusion_player_module_type_func);
	if (!tmp_player_func) {
		cp_app_log(error, player, "start_player_func() error. not found player func.");
		return -1;
	}
	//初始化模块
	ret_int = cp_init_module(tmp_player_func, &tmp_mi);
	if (ret_int) {
		cp_app_log(error, player, "start_player_func_proc() error. init player func module error.");
		return -1;
	}
	//初始化模块
	ret_int = cp_open_module(tmp_player_func, &tmp_mi);
	if (ret_int) {
		cp_app_log(error, player, "start_player_func() error. start player func module error.");
		return -1;
	}
	return 0;
}

cp_int32_t stop_player_func_proc(cp_fusion_player_t *player)
{
	cp_func_t						*tmp_player_func = CP_NULL;
	cp_module_info_t				tmp_mi = { 0, };
	cp_int32_t						ret_int = 0;



	tmp_player_func = (cp_func_t *)cp_manager_get_sub_module(player, cp_fusion_player_manager_type_func, cp_fusion_player_module_type_func);
	if (!tmp_player_func) {
		cp_app_log(error, player, "stop_player_func_proc() error. not found player func.");
		return -1;
	}
	//初始化模块
	ret_int = cp_close_module(tmp_player_func);
	if (ret_int) {
		cp_app_log(error, player, "stop_player_func_proc() error. stop player func module error.");
		return -1;
	}
	return 0;
}

cp_int32_t init_player_other(cp_fusion_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_fusion_player_info_t			*tmp_player_info = (cp_fusion_player_info_t *)(player->app_info);


	//创建一个timer
	player->timer_task = cp_create_timer(player);
	if (!player->timer_task) {
		cp_app_log(error, player, "init_player_other() error. cp_create_timer() error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(player->timer_task, player);
	}

	//创建一个tcp_listen
	player->tcp_listen = cp_create_socket(player, cp_socket_type_tcp);
	if (!player->tcp_listen) {
		cp_app_log(error, player, "init_player_other() error. cp_create_socket() error. create tcp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(player->tcp_listen, player);
	}

	//创建一个udp_listen
	player->udp_listen = cp_create_socket(player, cp_socket_type_udp);
	if (!player->udp_listen) {
		cp_app_log(error, player, "init_player_other() error. cp_create_socket() error. create udp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(player->udp_listen, player);
	}

	//创建一个heartbeat_udp_listen
	tmp_player_info->heartbeat_manager.heartbeat_udp_listen = cp_create_socket(player, cp_socket_type_udp);
	if (!tmp_player_info->heartbeat_manager.heartbeat_udp_listen) {
		cp_app_log(error, player, "init_player_other() error. cp_create_socket() error. create heartbeat udp socket error.");
		return -1;
	}
	else {
		CP_MODULE_SET_DATA(tmp_player_info->heartbeat_manager.heartbeat_udp_listen, (&tmp_player_info->heartbeat_manager));
	}

	//初始化心跳管理器
	ret_int = init_heartbeat_manager((cp_app_t*)player, &(tmp_player_info->heartbeat_manager));
	if (ret_int) {
		cp_app_log(error, player, "init_player_other() error. init_heartbeat_manager() error.");
		return -1;
	}

	//初始化播放管理器信息
	tmp_player_info->media_play_manager = create_media_play_manager((cp_app_t*)player);
	if (!tmp_player_info->media_play_manager) {
		cp_app_log(error, player, "init_player_other() error. create_media_play_manager() error.");
		return -1;
	}
	ret_int = init_media_play_manager((cp_app_t*)player, tmp_player_info->media_play_manager,
		tmp_player_info->device_info->hardware.limit_play_count);
	if (ret_int) {
		cp_app_log(error, player, "init_player_other() error. init_media_play_manager() error.");
		return -1;
	}
	
	return 0;
}

cp_int32_t start_player_other(cp_fusion_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_sockaddr_in				tmp_tcp_addr;
	cp_sockaddr_in				tmp_udp_addr;
	cp_sockaddr_in				tmp_heartbeat_udp_addr;
	cp_fusion_player_info_t			*tmp_player_info = (cp_fusion_player_info_t *)player->app_info;
	cp_char_t					tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//启动心跳管理器
	ret_int = start_heartbeat_manager(&tmp_player_info->heartbeat_manager);
	if (ret_int) {
		cp_app_log(error, player, "start_player_other() error. start_heartbeat_manager() error.");
		return -1;
	}

	//启动播放管理器信息
	ret_int = start_media_play_manager(tmp_player_info->media_play_manager);
	if (ret_int) {
		cp_app_log(error, player, "init_player_other() error. start_media_play_manager() error.");
		return -1;
	}

	//启动player func
	ret_int = start_player_func_proc(player, app_info);
	if (ret_int) {
		cp_app_log(error, player, "start_player_other() error. start_player_func_proc() error.");
		return -1;
	}

	//启动定时器
	ret_int = cp_start_timer(player->timer_task, cp_fusion_player_timer_task, 1000, 10000);
	if (ret_int) {
		cp_app_log(error, player, "start_player_other() error. cp_start_timer() error.");
		return -1;
	}
	//配置地址信息
	cp_ip4_addr(tmp_player_info->device_info->network.ip, tmp_player_info->device_info->network.tcp_port, &tmp_tcp_addr);
	cp_ip4_addr(tmp_player_info->device_info->network.ip, tmp_player_info->device_info->network.udp_port, &tmp_udp_addr);
	cp_ip4_addr(tmp_player_info->device_info->network.ip, tmp_player_info->heartbeat_manager.local_heartbeat_udp_port, &tmp_heartbeat_udp_addr);
	//启动tcp监听
	ret_int = cp_listen_socket(player->tcp_listen, &tmp_tcp_addr);
	if (ret_int) {
		cp_app_log(error, player, "start_player_other() error. cp_listen_socket(tcp) error. [%s:%d]",
			tmp_player_info->device_info->network.ip,
			tmp_player_info->device_info->network.tcp_port);
		return -2;
	}
	else {
		cp_log_notice(player->logger, "listen tcp [%s:%d] successed!",
			tmp_player_info->device_info->network.ip,
			tmp_player_info->device_info->network.tcp_port);
	}

	//启动udp监听
	ret_int = cp_listen_socket(player->udp_listen, &tmp_udp_addr);
	if (ret_int) {
		cp_app_log(error, player, "start_player_other() error. cp_listen_socket(udp) error.[%s:%d]",
			tmp_player_info->device_info->network.ip,
			tmp_player_info->device_info->network.udp_port);
		return -3;
	}
	else {
		//udp需要进行排序，初始socket data
		if (set_socket_data(player, player->udp_listen, cp_socket_data_semh)) {
			cp_app_log(error, player, "start_player_other() error. listen(udp) set_player_socket_data(udp) error.[%s:%d]",
				tmp_player_info->device_info->network.ip,
				tmp_player_info->device_info->network.udp_port);
			return -4;
		}

		cp_log_notice(player->logger, "listen udp [%s:%d] successed!",
			tmp_player_info->device_info->network.ip,
			tmp_player_info->device_info->network.udp_port);
	}

	//启动心跳处理udp监听
	ret_int = cp_listen_socket(tmp_player_info->heartbeat_manager.heartbeat_udp_listen, &tmp_heartbeat_udp_addr);
	if (ret_int) {
		cp_app_log(error, player, "start_player_other() error. cp_listen_socket(udp) error.[%s:%d]",
			tmp_player_info->device_info->network.ip,
			tmp_player_info->heartbeat_manager.local_heartbeat_udp_port);
		return -3;
	}
	else {
		//udp需要进行排序，初始socket data
		if (set_socket_data(player, tmp_player_info->heartbeat_manager.heartbeat_udp_listen, cp_socket_data_semh)) {
			cp_app_log(error, player, "start_player_other() error. heartbeat(udp) set_player_socket_data(udp) error.[%s:%d]",
				tmp_player_info->device_info->network.ip,
				tmp_player_info->heartbeat_manager.local_heartbeat_udp_port);
			return -4;
		}
		tmp_player_info->heartbeat_manager.heartbeat_udp_listen->data = CP_NULL;
		cp_log_notice(player->logger, "listen udp [%s:%d] successed!",
			tmp_player_info->device_info->network.ip,
			tmp_player_info->heartbeat_manager.local_heartbeat_udp_port);
	}

	//初始化video 播放器
	ret_int = init_video_player(player, app_info);
	if (ret_int) {
		cp_app_log(error, player, "init_video_player() error.");
		return -1;
	}

	//启动video 播放器
	ret_int = start_video_player(player, app_info);
	if (ret_int) {
		cp_app_log(error, player, "start_video_player() error.");
		return -1;
	}

	return 0;
}

cp_int32_t stop_player_other(cp_fusion_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_fusion_player_info_t			*tmp_player_info = (cp_fusion_player_info_t *)player->app_info;


	cp_stop_timer(player->timer_task);
	cp_close_socket(player->tcp_listen);
	cp_close_socket(player->udp_listen);
	cp_close_socket(tmp_player_info->heartbeat_manager.heartbeat_udp_listen);

	stop_player_func_proc(player);

	stop_media_play_manager(tmp_player_info->media_play_manager);
	stop_heartbeat_manager(&tmp_player_info->heartbeat_manager);

	//停止video 播放器
	ret_int = stop_video_player(player, app_info);
	if (ret_int) {
		cp_app_log(error, player, "stop_video_player() error.");
		return -1;
	}

	return 0;
}

cp_int32_t create_request_hook(cp_fusion_player_t *player)
{
	cp_module_manager_t							*tmp_module_manager = CP_NULL;
	cp_module_manager_info_t					tmp_module_manager_info = { 0, };
	cp_module_info_t							tmp_module_info = { 0, };
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	tmp_module_manager_info.type = CP_MODULE_MANAGER_TYPE_HOOK(1);
	tmp_module_manager = cp_get_manager(player, &tmp_module_manager_info);
	if (!tmp_module_manager) {
		cp_app_log(error, player,
			"create_request_hook() error. get manager[%d] error.",
			tmp_module_manager_info.type);
		return -1;
	}
	tmp_module_info.type = CP_MODULE_TYPE_HOOK(1);
	return 0;
}

cp_int32_t set_socket_data(cp_void_t *data, cp_socket_t *socket, cp_socket_data_type_e type)
{
	cp_semh_socket_data_t					*tmp_sd = CP_NULL;
	cp_memh_socket_data_t					*tmp_md = CP_NULL;



	if (!socket) {
		return -1;
	}

	switch (type)
	{
	case cp_socket_data_semh:
	{
		tmp_sd = create_semh_socket_data(socket->pool);
		if (!tmp_sd) {
			return -1;
		}
		tmp_sd->sd.data = data;
		socket->data = tmp_sd;
		cp_module_log(info, socket, "socket[0x%x] set_socket_data() socket_data[0x%x] succssed!",
			socket,
			tmp_sd);
		return 0;
	}
	break;
	case cp_socket_data_memh:
	{
		tmp_md = create_memh_socket_data(socket->pool);
		if (!tmp_md) {
			return -1;
		}
		tmp_md->sd.data = data;
		socket->data = tmp_md;
		return 0;
	}
	break;
	default:
		break;
	}
	return -2;
}

cp_int32_t init_video_player(cp_fusion_player_t *player, cp_app_info_t *app_info)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_codec_info_t								tmp_func_info = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, cp_fusion_player_manager_type_video_func);

	//获取视频处理管理器
	tmp_manager = cp_get_manager(player, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, player, "not found manager_type[%d] error.",
			cp_fusion_player_manager_type_video_func);
		return -1;
	}

	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_func_info, cp_fusion_player_module_type_video_func);

	//不存在则开始创建
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_func_info);
	if (!tmp_module) {
		cp_app_log(error, player, "create tmp_module_type[%d] error.",
			cp_fusion_player_module_type_video_func);
		return -2;
	}

	//初始化模块失败
	ret_int = cp_init_module(tmp_module, &tmp_func_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -3;
	}

	//启动模块失败
	ret_int = cp_open_module(tmp_module, &tmp_func_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_codec_module() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -4;
	}

	player->video_func = (cp_func_t *)tmp_module;

	return 0;
}

cp_int32_t start_video_player(cp_fusion_player_t *player, cp_app_info_t *app_info)
{
	cp_codec_info_t								tmp_func_info = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!player->video_func) {
		cp_app_log(error, player, "video func is null error.");
		return -1;
	}

	//启动模块失败
	ret_int = cp_open_module(player->video_func, &tmp_func_info);
	if (ret_int) {
		cp_app_log(error, player, "open %s error.",
			print_module_register_info(&player->video_func->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}

	return 0;
}

cp_int32_t stop_video_player(cp_fusion_player_t *player)
{
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!player->video_func) {
		cp_app_log(error, player, "video func is null error.");
		return -1;
	}

	//启动模块失败
	ret_int = cp_close_module(player->video_func);
	if (ret_int) {
		cp_app_log(error, player, "close %s error.",
			print_module_register_info(&player->video_func->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		//return -2;
	}
	else {
		cp_app_log(notice, player, "close %s successed.",
			print_module_register_info(&player->video_func->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	//退出模块失败
	ret_int = cp_exit_module(player->video_func);
	if (ret_int) {
		cp_app_log(error, player, "exit %s error.",
			print_module_register_info(&player->video_func->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		//return -3;
	}
	else {
		cp_app_log(notice, player, "exit %s successed.",
			print_module_register_info(&player->video_func->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	//退出模块失败
	ret_int = cp_manager_destroy_module(player->video_func->manager, player->video_func);
	if (ret_int) {
		cp_app_log(error, player, "destroy module[0x%p] error.", player->video_func);
		//return -3;
	}
	else {
		cp_app_log(notice, player, "destroy module[0x%p] successed.", player->video_func);
	}

	return 0;
}

