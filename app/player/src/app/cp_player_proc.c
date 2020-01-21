/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_player_proc.h"
#include "cp_player_task.h"


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

cp_int32_t create_request_hook(cp_player_t *player);

cp_int32_t start_player_func_proc(cp_player_t *player, cp_app_info_t *app_info)
{
	cp_func_t						*tmp_player_func = CP_NULL;
	cp_module_info_t				tmp_mi = { 0, };
	cp_int32_t						ret_int = 0;



	tmp_player_func = (cp_func_t *)cp_manager_get_sub_module(player, cp_player_manager_type_func, cp_player_module_type_func);
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

cp_int32_t start_ptp_func_proc(cp_player_t *player, cp_app_info_t *app_info)
{
	cp_func_t						*tmp_func = CP_NULL;
	cp_module_info_t				tmp_mi = { 0, };
	cp_int32_t						ret_int = 0;



	tmp_func = (cp_func_t *)cp_manager_get_sub_module(player, cp_player_manager_type_func, cp_player_module_type_ptp_func);
	if (!tmp_func) {
		cp_app_log(error, player, "start_ptp_func_proc() error. not found ptp func.");
		return -1;
	}
	//初始化模块
	ret_int = cp_init_module(tmp_func, &tmp_mi);
	if (ret_int) {
		cp_app_log(error, player, "start_ptp_func_proc() error. init ptp func module error.");
		return -1;
	}
	//初始化模块
	ret_int = cp_open_module(tmp_func, &tmp_mi);
	if (ret_int) {
		cp_app_log(error, player, "start_ptp_func_proc() error. start ptp func module error.");
		return -1;
	}
	return 0;
}

cp_int32_t stop_player_func_proc(cp_player_t *player)
{
	cp_func_t						*tmp_player_func = CP_NULL;
	cp_module_info_t				tmp_mi = { 0, };
	cp_int32_t						ret_int = 0;



	tmp_player_func = (cp_func_t *)cp_manager_get_sub_module(player, cp_player_manager_type_func, cp_player_module_type_func);
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

cp_int32_t stop_ptp_func_proc(cp_player_t *player)
{
	cp_func_t						*tmp_func = CP_NULL;
	cp_module_info_t				tmp_mi = { 0, };
	cp_int32_t						ret_int = 0;



	tmp_func = (cp_func_t *)cp_manager_get_sub_module(player, cp_player_manager_type_func, cp_player_module_type_ptp_func);
	if (!tmp_func) {
		cp_app_log(error, player, "stop_ptp_func_proc() error. not found ptp func.");
		return -1;
	}
	//初始化模块
	ret_int = cp_close_module(tmp_func);
	if (ret_int) {
		cp_app_log(error, player, "stop_ptp_func_proc() error. stop ptp func module error.");
		return -1;
	}
	return 0;
}

cp_int32_t init_player_other(cp_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_player_info_t			*tmp_player_info = (cp_player_info_t *)(player->app_info);


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

	//创建一个发送请求的semh hook
	ret_int = create_request_hook(player);
	if (ret_int) {
		cp_app_log(error, player, "init_player_other() error. create_request_hook() error.");
		return -1;
	}
	return 0;
}

cp_int32_t start_player_other(cp_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_sockaddr_in				tmp_tcp_addr;
	cp_sockaddr_in				tmp_udp_addr;
	cp_sockaddr_in				tmp_heartbeat_udp_addr;
	cp_player_info_t			*tmp_player_info = (cp_player_info_t *)player->app_info;
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

	//启动ptp func
	ret_int = start_ptp_func_proc(player, app_info);
	if (ret_int) {
		cp_app_log(error, player, "start_player_other() error. start_ptp_func_proc() error.");
		return -1;
	}

	//启动定时器
	ret_int = cp_start_timer(player->timer_task, cp_player_timer_task, 1000, 10000);
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

	//开始进行业务处理
	if (!player->request_hook) {
		cp_app_log(error, player, "player request_hook is null error!");
		return -3;
	}

	//启动心跳功能
	ret_int = cp_set_option_module(player->request_hook, cp_css_hook_set_option_start_heartbeat, CP_NULL);
	if (ret_int) {
		cp_app_log(error, player, "%s start heartbeat error!",
			cp_print_module_register_info(&(player->request_hook->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -4;
	}
	else {
		cp_log_notice(player->logger, "%s start heartbeat successed!",
			cp_print_module_register_info(&(player->request_hook->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}

	//发送注册指令
	ret_int = cp_set_option_module(player->request_hook, cp_css_hook_set_option_send_register, CP_NULL);
	if (ret_int) {
		cp_app_log(error, player, "%s send register error!",
			cp_print_module_register_info(&(player->request_hook->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -4;
	}
	else {
		cp_log_notice(player->logger, "%s send register successed!",
			cp_print_module_register_info(&(player->request_hook->register_info), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
	}
	//send_semh_center_register(player);

	return 0;
}

cp_int32_t stop_player_other(cp_player_t *player, cp_app_info_t *app_info)
{
	cp_int32_t					ret_int = 0;
	cp_player_info_t			*tmp_player_info = (cp_player_info_t *)player->app_info;


	cp_stop_timer(player->timer_task);
	cp_close_socket(player->tcp_listen);
	cp_close_socket(player->udp_listen);
	cp_close_socket(tmp_player_info->heartbeat_manager.heartbeat_udp_listen);

	stop_ptp_func_proc(player);

	stop_player_func_proc(player);

	stop_media_play_manager(tmp_player_info->media_play_manager);
	stop_heartbeat_manager(&tmp_player_info->heartbeat_manager);

	return 0;
}

cp_int32_t create_request_hook(cp_player_t *player)
{
	cp_module_manager_t							*tmp_module_manager = CP_NULL;
	cp_module_manager_info_t					tmp_module_manager_info = { 0, };
	cp_module_info_t							tmp_module_info = { 0, };
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };




	if (player->request_hook) {
		return 0;
	}
	tmp_module_manager_info.type = CP_MODULE_MANAGER_TYPE_HOOK(1);
	tmp_module_manager = cp_get_manager(player, &tmp_module_manager_info);
	if (!tmp_module_manager) {
		cp_app_log(error, player,
			"create_request_hook() error. get manager[%d] error.",
			tmp_module_manager_info.type);
		return -1;
	}
	tmp_module_info.type = CP_MODULE_TYPE_HOOK(1);
	player->request_hook = (cp_css_hook_t *)cp_manager_create_module(tmp_module_manager, &tmp_module_info);
	if (!player->request_hook) {
		cp_app_log(error, player,
			"create_request_hook() error. %s create module[%d] error.",
			cp_print_manager_register_info(&tmp_module_manager->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH),
			tmp_module_info.type);
		return -2;
	}
	return 0;
}

//查找一个设备信息
cp_int32_t select_device_info_index(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t *ret_index, cp_char_t *id)
{
	cp_int32_t						i = 0;


	for (i = 0; i < di_ary_size; i++) {
		if (!di_ary[i]) {
			continue;
		}
		if (!cp_strncmp(di_ary[i]->host.id, id, cp_sizeof(di_ary[i]->host.id))) {
			*ret_index = i;
			return 0;
		}
	}
	return -1;
}

//查找设备信息
cp_device_info_t *select_index_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t index)
{
	if (index > di_ary_size) {
		return CP_NULL;
	}
	return di_ary[index];
}

//查找一个心跳信息
cp_int32_t select_device_heartbeat(cp_player_t *player,
	cp_int32_t *ret_index, cp_char_t *id, cp_int32_t type)
{
	cp_int32_t							i = 0;
	cp_int32_t							tmp_device_number = 0;
	cp_device_heartbeat_t				**tmp_dh_p = CP_NULL;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);


	for (i = 0; tmp_device_number < (cp_int32_t)cp_array_length(&tmp_player_info->heartbeat_manager.device_heartbeats)
		&& i < CP_PLAYER_MAX_DEVICE_NUMBER; i++) {
		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.device_heartbeats, i);
		if (!tmp_dh_p || !(*tmp_dh_p)) {
			continue;
		}
		++tmp_device_number;
		if ((*tmp_dh_p)->type == type &&
			!cp_strncmp((*tmp_dh_p)->id, id, CP_APP_DEFAULT_ID_LENGTH)) {
			*ret_index = i;
			return 0;
		}
	}
	return -1;
}

//查找一个可用的网卡信息
cp_interface_t *select_a_used_interface(cp_player_t *player)
{
	return CP_NULL;
}

//插入一个新设备信息
cp_int32_t insert_new_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *src_di)
{
	cp_int32_t						i = 0;



	for (i = 0; i < di_ary_size; i++) {
		if (!di_ary[i]) {
			di_ary[i] = src_di;
			return 0;
		}
	}
	return -1;
}

//新增一个设备心跳信息
cp_int32_t insert_new_device_heartbeat(cp_player_t *player, cp_device_info_t *di)
{
	cp_int32_t							i = 0;
	cp_device_heartbeat_t				*tmp_dh_p = CP_NULL;
	cp_device_heartbeat_t				**tmp_find_dh_p = CP_NULL;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_heartbeat_manager_t				*tmp_hm_p = &(tmp_player_info->heartbeat_manager);



	//设置设备心跳信息
	tmp_dh_p = create_device_heartbeat_info(tmp_hm_p, di);
	if (!tmp_dh_p) {
		return -1;
	}

	cp_mutex_lock(&tmp_player_info->device_heartbeats_mutex);
	//先查找一下当前是否有空间可以存储心跳信息
	for (i = 0; i < (cp_int32_t)cp_array_max_size(&tmp_player_info->heartbeat_manager.device_heartbeats); i++) {
		tmp_find_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.device_heartbeats, i);
		if (tmp_find_dh_p && !(*tmp_find_dh_p)) {
			cp_array_set(&tmp_player_info->heartbeat_manager.device_heartbeats, &tmp_dh_p, i);
			tmp_dh_p = CP_NULL;
			break;
		}
	}
	cp_mutex_unlock(&tmp_player_info->device_heartbeats_mutex);

	if (tmp_dh_p) {
		//如果没有空间，则释放资源
		cp_mpfree(player->mpool, tmp_dh_p);
		return -2;
	}

	return 0;
}

cp_int32_t update_a_device_heartbeat(cp_player_t *player, cp_device_info_t *di)
{
	cp_int32_t							tmp_index = 0;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_heartbeat_t				**tmp_dh_p = CP_NULL;



	if (!select_device_heartbeat(player, &tmp_index, di->host.id, di->host.type)) {
		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.device_heartbeats, tmp_index);
		//先判断数据是否需要更新，然后再进行更新处理
		if ((*tmp_dh_p)->udp_port != di->network.udp_port ||
			cp_strncmp((*tmp_dh_p)->ip, di->network.ip,
			cp_sizeof((*tmp_dh_p)->ip))) {

			cp_mutex_lock(&tmp_player_info->device_heartbeats_mutex);

			//更新ip和端口数据
			cp_memset((*tmp_dh_p)->ip, 0, cp_sizeof((*tmp_dh_p)->ip));
			cp_strcpy((*tmp_dh_p)->ip, di->network.ip);
			(*tmp_dh_p)->udp_port = di->network.udp_port;

			cp_mutex_unlock(&tmp_player_info->device_heartbeats_mutex);
		}

		(*tmp_dh_p)->send_times = 0;

		cp_log_info(player->logger,
			"update_a_device_heartbeat() successed. device[id:%s type:%d send_times:%d].",
			di->host.id,
			di->host.type,
			(*tmp_dh_p)->send_times
			);
	}
	else {
		return insert_new_device_heartbeat(player, di);
	}

	return 0;
}

//创建设备心跳信息
cp_device_heartbeat_t* create_device_heartbeat_info(cp_heartbeat_manager_t *hm, cp_device_info_t *di)
{
	cp_sockaddr_in						tmp_addr = { 0, };
	cp_device_heartbeat_t				*tmp_dh_p = CP_NULL;



	if (!hm || !di) {
		return CP_NULL;
	}

	if (cp_ip4_addr(di->network.ip, di->network.udp_port, &tmp_addr)) {
		cp_log_error(hm->logger,
			"create_device_heartbeat_info () error reason:ip address[%s:%d] failed!",
			di->network.ip,
			di->network.udp_port);
		return CP_NULL;
	}

	tmp_dh_p = cp_mpalloc(hm->mpool, cp_sizeof(cp_device_heartbeat_t));
	if (!tmp_dh_p) {
		return CP_NULL;
	}

	cp_memset(tmp_dh_p, 0, cp_sizeof(cp_device_heartbeat_t));

	//更新id和type数据
	cp_memset(tmp_dh_p->id, 0, cp_sizeof(tmp_dh_p->id));
	cp_strncpy(tmp_dh_p->id, di->host.id, cp_sizeof(tmp_dh_p->id));
	tmp_dh_p->type = di->host.type;

	//更新ip和端口数据
	cp_memset(tmp_dh_p->ip, 0, cp_sizeof(tmp_dh_p->ip));
	cp_strcpy(tmp_dh_p->ip, di->network.ip);
	tmp_dh_p->udp_port = di->network.udp_port;

	tmp_dh_p->di = di;
	tmp_dh_p->heartbeat_manager = hm;
	tmp_dh_p->hearbeat_address = tmp_addr;

	//初始化设备心跳信息
	init_device_heartbeat(hm, tmp_dh_p);

	cp_snprintf(
		tmp_dh_p->device_info_data,
		CP_PLAYER_HEARTBEAT_DEFAULT_BUFFER_LENGTH,
		"di:0x%x id:%s type:%d addr:%s:%d ft:%d",
		tmp_dh_p->di,
		tmp_dh_p->id,
		tmp_dh_p->type,
		tmp_dh_p->ip,
		tmp_dh_p->udp_port,
		tmp_dh_p->send_times);

	return tmp_dh_p;
}

//更新指定位置的设备信息
cp_int32_t update_position_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_int32_t pos, cp_device_info_t *src_di)
{
	cp_void_t					*tmp_data = CP_NULL;

	if (pos < 0 || pos > di_ary_size) {
		return -1;
	}
	tmp_data = di_ary[pos]->data;
	*di_ary[pos] = *src_di;
	di_ary[pos]->data = tmp_data;
	return 0;
}

//更新一个设备信息
cp_int32_t update_dest_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *src_di)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_int32_t							tmp_index = 0;
	cp_device_info_t					*tmp_di = CP_NULL;



	//查找是否已经存在该设备信息
	tmp_ret_int = select_device_info_index(player, di_ary, di_ary_size, &tmp_index, src_di->host.id);
	if (tmp_ret_int) {
		//如果不存在则新增一个设备信息
		tmp_di = (cp_device_info_t*)cp_mpalloc(player->mpool, cp_sizeof(cp_device_info_t));
		if (!tmp_di) {
			cp_app_log(error, player,
				"update_dest_device_info() cp_mpalloc() error.");
			return -1;
		}
		*tmp_di = *src_di;
		return insert_new_device_info(player, di_ary, di_ary_size, tmp_di);
	}
	//如果已经存在，则更新设备信息
	return update_position_device_info(player, di_ary, di_ary_size, tmp_index, src_di);
}

//更新媒体服务器其他信息
cp_int32_t update_media_server_other_info(cp_player_t *player, cp_device_info_t *di)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_media_server_info_t				*tmp_ms_info = CP_NULL;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_sockaddr_in						tmp_multicast_addr = { 0, };


	//创建一个媒体服务器信息
	tmp_ms_info = (cp_media_server_info_t*)(di->data);
	if (!tmp_ms_info) {
		tmp_ms_info = (cp_media_server_info_t*)cp_mpalloc(player->mpool, cp_sizeof(cp_media_server_info_t));
		if (!tmp_ms_info) {
			cp_app_log(error, player,
				"%s() cp_mpalloc() error.",
				__FUNCTION__);
			return -1;
		}
		cp_memset(tmp_ms_info, 0, cp_sizeof(cp_media_server_info_t));

		//赋值信息
		di->data = tmp_ms_info;
		tmp_ms_info->dev_info = di;
	}

	//判断是否需要更新组播信息
	if (!di->multicast_addr.port || !cp_strlen(di->multicast_addr.ip)) {
		cp_app_log(error, player,
			"%s() error. socket address[%s:%d] error.",
			__FUNCTION__,
			di->multicast_addr.ip,
			di->multicast_addr.port);
		return -1;
	}

	//如果没有地址，则创建一个
	if (!tmp_ms_info->multicast_socket) {
		//更新网络信息
		tmp_ms_info->multicast_socket = cp_create_socket(player, cp_socket_type_multicast);
		if (!tmp_ms_info->multicast_socket) {
			cp_mpfree(player->mpool, tmp_ms_info);
			cp_app_log(error, player,
				"%s() error. cp_create_socket() error. create udp socket error.",
				__FUNCTION__);
			return -1;
		}
	}

	//更新连接信息，只要端口和地址变化都视为变化
	if (tmp_ms_info->multicast_addr.port != di->multicast_addr.port ||
		cp_strcmp(tmp_ms_info->multicast_addr.ip, di->multicast_addr.ip)) {

		//更新组播地址
		tmp_ms_info->multicast_addr = di->multicast_addr;

		//关闭原来的socket
		cp_close_socket(tmp_ms_info->multicast_socket);

		cp_ip4_addr(di->multicast_addr.ip, di->multicast_addr.port, &tmp_multicast_addr);
		//启动udp监听
		tmp_ret_int = cp_listen_socket(tmp_ms_info->multicast_socket, &tmp_multicast_addr);
		if (tmp_ret_int) {
			cp_app_log(error, player,
				"%s() error. cp_listen_socket() udp [%s:%d] error.",
				__FUNCTION__,
				di->multicast_addr.ip,
				di->multicast_addr.port);
			return -2;
		}

		if (set_socket_data(tmp_ms_info, tmp_ms_info->multicast_socket, cp_socket_data_semh)) {
			cp_app_log(notice, player,
				"%s() error. set_socket_data() udp [%s:%d] error.",
				__FUNCTION__,
				di->multicast_addr.ip,
				di->multicast_addr.port);
			return -4;
		}

		cp_app_log(notice, player,
			"%s() successed. listen udp [%s:%d] successed!",
			__FUNCTION__,
			di->multicast_addr.ip,
			di->multicast_addr.port);
	}

	return 0;
}

//更新设备信息
cp_int32_t update_device_info(cp_player_t *player, cp_array_t *device_info_array)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						i = 0;
	cp_device_info_t				*tmp_device_info;
	cp_player_info_t				*tmp_player_info = (cp_player_info_t *)(player->app_info);



	for (i = 0; i < (cp_int32_t)cp_array_max_size(device_info_array); i++) {
		tmp_device_info = cp_array_get(device_info_array, i);
		if (!tmp_device_info) {
			continue;
		}
		tmp_ret_int = update_a_device_info(player, tmp_device_info);
		if (tmp_ret_int) {
			cp_app_log(error, player, "update_a_device_info() error!");
		}
	}

	return 0;
}

//更新一个设备信息
cp_int32_t update_a_device_info(cp_player_t *player, cp_device_info_t *di)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_player_info_t				*tmp_player_info = (cp_player_info_t *)(player->app_info);



	if (!player || !di) {
		return -1;
	}

	cp_mutex_lock(&tmp_player_info->server_info_mutex);

	switch (di->host.type)
	{
		case css_device_type_center:
		{
			tmp_ret_int = update_center_server_info(player, di);
		}
		break;
		case css_device_type_media_server:
		{
			tmp_ret_int = update_media_server_info(player, di);
		}
		break;
		case css_device_type_access_server:
		{
			tmp_ret_int = update_access_server_info(player, di);
		}
		break;
		case css_device_type_player_background:
		{
			tmp_ret_int = update_player_background_server_info(player, di);
		}
		break;
		case css_device_type_client_background:
		{
			tmp_ret_int = update_client_background_server_info(player, di);
		}
		break;
		case css_device_type_css_video_player:
		case css_device_type_css_audio_player:
		{
			tmp_ret_int = update_other_player_info(player, di);
		}
		break;
		default:
		{
			cp_app_log(warn, player,
				"update_device_info() error. unsupport device type[%d].",
				di->host.type);
			tmp_ret_int = -1;
			//return -1;
		}
		break;
	}

	//如果处理成功，则更新一下心跳相关的信息
	if (!tmp_ret_int) {
		update_a_device_heartbeat(player, di);
	}
	else {
		cp_app_log(warn, player,
			"update_a_device_info() warning. device[id:%s type:%d]. ret[%d]",
			di->host.id,
			di->host.type,
			tmp_ret_int);
	}

	cp_mutex_unlock(&tmp_player_info->server_info_mutex);
	return 0;
}


//更新中心信息
cp_int32_t update_center_server_info(cp_player_t *player, cp_device_info_t *di)
{
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);


	return update_dest_device_info(player, tmp_player_info->cener_server,
		cp_ary_size(tmp_player_info->cener_server), di);
}

//更新媒体服务器信息
cp_int32_t update_media_server_info(cp_player_t *player, cp_device_info_t *di)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_int32_t							tmp_index = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_di = CP_NULL;



	tmp_ret_int = update_dest_device_info(player, tmp_player_info->media_server,
		cp_ary_size(tmp_player_info->media_server), di);
	if (tmp_ret_int) {
		cp_app_log(error, player,
			"update_media_server_info() error. %s",
			printf_device_info(player, di, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -1;
	}

	//查找是否已经存在该设备信息
	tmp_ret_int = select_device_info_index(player,
		tmp_player_info->media_server, cp_ary_size(tmp_player_info->media_server), &tmp_index, di->host.id);
	if (tmp_ret_int) {
		//如果不存在则新增一个设备信息
		cp_app_log(error, player,
			"update_media_server_info() error. select_device_info_index() error. %s",
			printf_device_info(player, di, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -2;
	}
	//根据索引获取设备信息
	tmp_di = select_index_device_info(player, tmp_player_info->media_server,
		cp_ary_size(tmp_player_info->media_server), tmp_index);
	if (!tmp_di) {
		cp_app_log(error, player,
			"update_media_server_info() error. select_index_device_info() error. %s",
			printf_device_info(player, di, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return -3;
	}

	//更新媒体服务器其他信息
	return update_media_server_other_info(player, tmp_di);
}

//更新中间件服务器信息
cp_int32_t update_access_server_info(cp_player_t *player, cp_device_info_t *di)
{
	return -1;
}

//更新背景服务器信息
cp_int32_t update_player_background_server_info(cp_player_t *player, cp_device_info_t *di)
{
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);


	return update_dest_device_info(player, tmp_player_info->player_background_server,
		cp_ary_size(tmp_player_info->player_background_server), di);
}

//更新回显服务器信息
cp_int32_t update_client_background_server_info(cp_player_t *player, cp_device_info_t *di)
{
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);


	return update_dest_device_info(player, tmp_player_info->client_background_server,
		cp_ary_size(tmp_player_info->client_background_server), di);
}

//更新其他前端信息
cp_int32_t update_other_player_info(cp_player_t *player, cp_device_info_t *di)
{
	return -1;
}

//删除一个设备心跳信息
cp_int32_t remove_a_device_heartbeat(cp_player_t *player, cp_device_info_t *di)
{
	cp_int32_t							tmp_index = 0;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_heartbeat_t				**tmp_dh_p = CP_NULL;



	if (!select_device_heartbeat(player, &tmp_index, di->host.id, di->host.type)) {
		cp_mutex_lock(&tmp_player_info->device_heartbeats_mutex);

		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.device_heartbeats, tmp_index);
		cp_mpfree(tmp_player_info->heartbeat_manager.mpool, (*tmp_dh_p));
		cp_array_remove(&tmp_player_info->heartbeat_manager.device_heartbeats, tmp_index);

		cp_mutex_unlock(&tmp_player_info->device_heartbeats_mutex);
	}

	return 0;
}

//删除一个设备信息
cp_int32_t remove_a_device_info(cp_player_t *player, cp_device_info_t **di_ary,
	cp_int32_t di_ary_size, cp_device_info_t *di)
{
	cp_int32_t							i = 0;


	//从心跳列表中删除心跳信息
	remove_a_device_heartbeat(player, di);

	//先将数组内的数据清除
	for (i = 0; i < di_ary_size; i++) {
		if (di_ary[i] == di) {
			di_ary[i] = CP_NULL;
		}
	}

	//释放资源
	cp_mpfree(player->mpool, di);

	return 0;
}

cp_int32_t remove_device_info(cp_player_t *player, cp_char_t *id, cp_int32_t type)
{
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);



	cp_mutex_lock(&tmp_player_info->server_info_mutex);
	switch (type)
	{
		case css_device_type_center:
		{
			remove_center_server_info(player, id, type);
		}
		break;
		case css_device_type_media_server:
		{
			remove_media_server_info(player, id, type);
		}
		break;
		case css_device_type_access_server:
		{
			remove_access_server_info(player, id, type);
		}
		break;
		case css_device_type_player_background:
		{
			remove_player_background_server_info(player, id, type);
		}
		break;
		case css_device_type_client_background:
		{
			remove_client_background_server_info(player, id, type);
		}
		break;
		default:
		{
			cp_app_log(warn, player,
				"remove_device_info() error. unsupport device type[%d].",
				type);
			//return -1;
		}
		break;
	}
	cp_mutex_unlock(&tmp_player_info->server_info_mutex);
	return 0;
}

//删除所有设备信息
cp_int32_t remove_all_device_info(cp_player_t *player)
{
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					*tmp_player_device_info = ((cp_player_info_t*)(player->app_info))->device_info;
	cp_device_heartbeat_t				**tmp_dh_p = CP_NULL;
	cp_int32_t							i = 0;
	cp_int32_t							tmp_device_number = 0;



	//遍历心跳列表
	for (i = 0; tmp_device_number < (cp_int32_t)cp_array_length(&tmp_player_info->heartbeat_manager.device_heartbeats)
		&& i < CP_PLAYER_MAX_DEVICE_NUMBER; i++) {

		tmp_dh_p = (cp_device_heartbeat_t**)cp_array_get(&tmp_player_info->heartbeat_manager.device_heartbeats, i);
		if (!tmp_dh_p || !(*tmp_dh_p)) {
			continue;
		}

		remove_device_info(player, (*tmp_dh_p)->id, (*tmp_dh_p)->type);

		++tmp_device_number;
	}

	return 0;
}

cp_int32_t remove_media_server_other_info(cp_player_t *player, cp_device_info_t *di)
{
	cp_media_server_info_t				*tmp_ms_info = CP_NULL;


	tmp_ms_info = (cp_media_server_info_t*)(di->data);
	if (!tmp_ms_info) {
		return 0;
	}

	//处理socket信息
	if (tmp_ms_info->multicast_socket) {
		//关闭原来的socket
		cp_close_socket(tmp_ms_info->multicast_socket);
		//消毁socket data数据
		destroy_socket_data(tmp_ms_info->multicast_socket->pool, tmp_ms_info->multicast_socket->data);
		//销毁socket信息
		cp_destroy_socket(tmp_ms_info->multicast_socket);
	}

	//删除内存
	cp_mpfree(player->mpool, tmp_ms_info);
	di->data = CP_NULL;

	return 0;
}

cp_int32_t remove_center_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type)
{
	cp_bool_t							tmp_ret_int = 0;
	cp_int32_t							tmp_index = 0;
	cp_device_info_t					*tmp_di = CP_NULL;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					**di_ary = tmp_player_info->cener_server;
	cp_int32_t							di_ary_size = cp_ary_size(tmp_player_info->cener_server);


	//查找是否已经存在该设备信息
	tmp_ret_int = select_device_info_index(player, di_ary, di_ary_size, &tmp_index, id);
	if (tmp_ret_int) {
		//如果不存在则新增一个设备信息
		return 0;
	}
	//删除一个设备心跳信息
	//remove_a_device_heartbeat(player, di_ary[tmp_index]);
	//简单的删除设备信息
	remove_a_device_info(player, di_ary, di_ary_size, di_ary[tmp_index]);
	return 0;
}

cp_int32_t remove_media_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type)
{
	cp_bool_t							tmp_ret_int = 0;
	cp_int32_t							tmp_index = 0;
	cp_device_info_t					*tmp_di = CP_NULL;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					**di_ary = tmp_player_info->media_server;
	cp_int32_t							di_ary_size = cp_ary_size(tmp_player_info->media_server);


	//查找是否已经存在该设备信息
	tmp_ret_int = select_device_info_index(player, di_ary, di_ary_size, &tmp_index, id);
	if (tmp_ret_int) {
		//如果不存在则新增一个设备信息
		return 0;
	}
	//删除一个设备心跳信息
	//remove_a_device_heartbeat(player, di_ary[tmp_index]);
	//简单的删除设备信息

	//删除媒体服务器其他信息
	remove_media_server_other_info(player, di_ary[tmp_index]);

	//删除设备信息
	remove_a_device_info(player, di_ary, di_ary_size, di_ary[tmp_index]);

	return 0;
}

cp_int32_t remove_access_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type)
{
	return 0;
}

cp_int32_t remove_player_background_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type)
{
	cp_bool_t							tmp_ret_int = 0;
	cp_int32_t							tmp_index = 0;
	cp_device_info_t					*tmp_di = CP_NULL;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					**di_ary = tmp_player_info->player_background_server;
	cp_int32_t							di_ary_size = cp_ary_size(tmp_player_info->player_background_server);


	//查找是否已经存在该设备信息
	tmp_ret_int = select_device_info_index(player, di_ary, di_ary_size, &tmp_index, id);
	if (tmp_ret_int) {
		//如果不存在则新增一个设备信息
		return 0;
	}
	//删除一个设备心跳信息
	//remove_a_device_heartbeat(player, di_ary[tmp_index]);
	//简单的删除设备信息
	remove_a_device_info(player, di_ary, di_ary_size, di_ary[tmp_index]);
	return 0;
}

cp_int32_t remove_client_background_server_info(cp_player_t *player, cp_char_t *id, cp_int32_t type)
{
	cp_bool_t							tmp_ret_int = 0;
	cp_int32_t							tmp_index = 0;
	cp_device_info_t					*tmp_di = CP_NULL;
	cp_player_info_t					*tmp_player_info = (cp_player_info_t *)(player->app_info);
	cp_device_info_t					**di_ary = tmp_player_info->client_background_server;
	cp_int32_t							di_ary_size = cp_ary_size(tmp_player_info->client_background_server);


	//查找是否已经存在该设备信息
	tmp_ret_int = select_device_info_index(player, di_ary, di_ary_size, &tmp_index, id);
	if (tmp_ret_int) {
		//如果不存在则新增一个设备信息
		return 0;
	}
	//删除一个设备心跳信息
	//remove_a_device_heartbeat(player, di_ary[tmp_index]);
	//简单的删除设备信息
	remove_a_device_info(player, di_ary, di_ary_size, di_ary[tmp_index]);
	return 0;
}

cp_char_t* printf_device_info(cp_player_t *player, cp_device_info_t *di, cp_char_t *buf, cp_int32_t len)
{
	if (!player || !di) {
		return CP_NULL;
	}

	cp_memset(buf, 0, len);
	cp_snprintf(buf, len, "di[id:%s name:%s socket:%s:%d]", di->host.id, di->host.name, di->network.ip, di->network.tcp_port);
	return buf;
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
