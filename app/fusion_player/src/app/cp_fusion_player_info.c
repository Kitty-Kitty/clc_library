/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_fusion_player_core.h"
#include "cp_fusion_player_info.h"




cp_bool_t get_conf_int_prop(cp_int32_t *dest, cp_fusion_player_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	tmp_value = cp_conf_getint(conf, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_double_prop(cp_double_t *dest, cp_fusion_player_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_double_t							tmp_value = 0;



	tmp_value = cp_conf_getdouble(conf, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_string_prop(cp_char_t *dest, cp_int32_t len, cp_fusion_player_t *app,
	cp_conf_t *conf, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	tmp_value = (cp_char_t *)cp_conf_getstring(conf, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	if ((cp_int32_t)cp_strlen(tmp_value) > len) {
		cp_log_error(app->logger, "get [%s:%s] failed! dest buffer length[%d] error.",
			context, key, cp_strlen(tmp_value));
		return cp_false;
	}
	cp_strncpy(dest, tmp_value, cp_strlen(tmp_value));
	return cp_true;
}

cp_bool_t get_conf_xml_int_prop(cp_int32_t *dest, cp_fusion_player_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int32_t							tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getint(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_xml_double_prop(cp_double_t *dest, cp_fusion_player_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_double_t							tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getdouble(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_xml_size_prop(cp_int64_t *dest, cp_fusion_player_t *app,
	cp_conf_t *conf, const char *context, const char *key, int def)
{
	cp_int64_t							tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = cp_conf_xml_getsize(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	*dest = tmp_value;
	return cp_true;
}

cp_bool_t get_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, cp_fusion_player_t *app,
	cp_conf_t *conf, const char *context, const char *key, const char* def)
{
	cp_char_t							*tmp_value = 0;



	if (!conf || !app) {
		return cp_false;
	}
	tmp_value = (cp_char_t*)cp_conf_xml_getstring(conf->conf_xml, context, key, def);
	if (!tmp_value) {
		cp_log_error(app->logger, "get [%s:%s] failed!", context, key);
		return cp_false;
	}
	if ((cp_int32_t)cp_strlen(tmp_value) > len) {
		cp_log_error(app->logger, "get [%s:%s] failed! dest buffer length[%d] error.", 
			context, key, cp_strlen(tmp_value));
		return cp_false;
	}
	cp_strncpy(dest, tmp_value, cp_strlen(tmp_value));
	return cp_true;
}


cp_bool_t init_center_info(cp_fusion_player_t *player, cp_fusion_player_info_t *info) {

	//name
	if (!get_conf_string_prop(info->center_addr, cp_sizeof(info->center_addr),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_CENTER, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_ADDRESS, CP_NULL)) {
		return cp_false;
	}

	//NVG_POSTION = 80 - 03 - 01 组行列编号01-02-03
	if (!get_conf_int_prop(&info->center_port, player,
		player->conf, CP_FUSION_PLAYER_CONF_STRING_CENTER, CP_FUSION_PLAYER_CONF_STRING_NVG_PORT, 0)) {
		return cp_false;
	}

	return cp_true;
}

cp_bool_t init_local_info(cp_fusion_player_t *player, cp_fusion_player_info_t *info) {

	//get network paraments from configure file
	if (!get_conf_string_prop(info->device_info->network.ip, cp_sizeof(info->device_info->network.ip), player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_ADDRESS, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&info->device_info->network.tcp_port, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_TCP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&info->device_info->network.udp_port, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_UDP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&info->heartbeat_manager.local_heartbeat_udp_port, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_HEARTBEAT_UDP_PORT, 0)) {
		//return cp_false;
	}

	//初始化服务器信息管理锁
	cp_mutex_init(&info->server_info_mutex);
	cp_mutex_init(&info->device_heartbeats_mutex);

	return cp_true;
}

cp_bool_t set_default_cctv_parameter(cp_hardware_info_t *hardware)
{
	hardware->cctv_switch = cp_true;

	hardware->border_size.left = 0;
	hardware->border_size.top = 0;
	hardware->border_size.right = 0;
	hardware->border_size.bottom = 0;

	return cp_true;
}


cp_bool_t init_player_info_host(cp_fusion_player_t *player, cp_host_t *host)
{
	cp_char_t							tmp_type[CP_APP_DEFAULT_STRING_LENGTH] = { 0, };



	//获取设备的工作类型
	if (!get_conf_xml_string_prop(tmp_type, cp_sizeof(tmp_type), player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_GENERAL, CP_FUSION_PLAYER_CONF_STRING_TYPE, CP_NULL)) {
		return cp_false;
	}

	if (!cp_strcmp(tmp_type, CP_FUSION_PLAYER_CONF_STRING_NVG_PLAYER_TYPE_VIDEO)) {
		host->type = css_device_type_css_video_player;
	}
	else if (!cp_strcmp(tmp_type, CP_FUSION_PLAYER_CONF_STRING_NVG_PLAYER_TYPE_AUDIO)) {
		host->type = css_device_type_css_audio_player;
	}
	else {
		cp_app_log(error, player, "unknow type[NVG_PLAYER_TYPE=%s] error.", tmp_type);
		return cp_false;
	}
	host->status = 200;
	host->no = 0;//设备数字编号
	memset(host->passwd, 0, sizeof(host->passwd));

	cp_sprintf(host->version, "%s", CP_FUSION_PLAYER_VERSION);

	//name
	if (!get_conf_xml_string_prop(host->name, cp_sizeof(host->name),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_GENERAL, CP_FUSION_PLAYER_CONF_STRING_NAME, CP_NULL)) {
		return cp_false;
	}

	//NVG_POSTION = 80 - 03 - 01 组行列编号01-02-03
	if (!get_conf_string_prop(host->number, cp_sizeof(host->number),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_OTHER, CP_FUSION_PLAYER_CONF_STRING_NVG_POSTION, CP_NULL)) {
		return cp_false;
	}

	//NVG_ID = 005 - 80 - 03 - 01 - 000000000001093075 - 1ee850bf7d6c404abbb71396c8ed9266
	if (!get_conf_string_prop(host->id, cp_sizeof(host->id),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_OTHER, CP_FUSION_PLAYER_CONF_STRING_NVG_ID, CP_NULL)) {
		return cp_false;
	}

	//sn  
	if (!get_conf_xml_string_prop(host->sn, cp_sizeof(host->sn),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_GENERAL, CP_FUSION_PLAYER_CONF_STRING_SN, CP_NULL)) {
		return cp_false;
	}

	return cp_true;
}

cp_bool_t init_player_info_network(cp_fusion_player_t *player, cp_interface_t *network)
{
	/*
	NVG_BOOT_PROTOCOL = 1
	NVG_IP_PORT = 65535
	NVG_TYPE =
	NVG_ON_BOOT =
	NVG_HWADDR =
	NVG_IP_VERSION =
	*/

	network->used = cp_true;

	if (!get_conf_string_prop(network->ip, cp_sizeof(network->ip),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_ADDRESS, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&network->tcp_port, player,
		player->conf, CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_TCP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&network->udp_port, player,
		player->conf, CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_IP_UDP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_string_prop(network->gateway, cp_sizeof(network->gateway),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_GATEWAY, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_string_prop(network->netmask, cp_sizeof(network->netmask),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_NETMASK, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_string_prop(network->name, cp_sizeof(network->name),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_LOCAL, CP_FUSION_PLAYER_CONF_STRING_NVG_DEVICE, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_xml_size_prop(&network->packet_length, player,
		player->conf, CP_CONF_STRING_NETWORK_CONFIGURE, CP_CONF_STRING_PACKET_LENGTH, 
		CP_FUSION_PLAYER_HEARTBEAT_DEFAULT_DATA_LENGTH)) {
		return cp_false;
	}

	return cp_true;
}


cp_bool_t init_player_info_hardware(cp_fusion_player_t *player, cp_hardware_info_t *hardware)
{
	cp_int32_t						tmp_value = 0;


	/*
	hardware->limit_disk = cp_conf_getint(player->conf, CP_FUSION_PLAYER_CONF_STRING_LIMIT, CP_FUSION_PLAYER_CONF_STRING_DISK, 0);
	if (!hardware->limit_disk) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_FUSION_PLAYER_CONF_STRING_LIMIT, CP_FUSION_PLAYER_CONF_STRING_DISK);
		return cp_false;
	}
	*/
	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LIMIT, CP_FUSION_PLAYER_CONF_STRING_DISK, 0)) {
		return cp_false;
	}
	hardware->limit_disk = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LIMIT, CP_FUSION_PLAYER_CONF_STRING_MEMORY, 0)) {
		return cp_false;
	}
	hardware->limit_memory = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LIMIT, CP_FUSION_PLAYER_CONF_STRING_CPU, 0)) {
		return cp_false;
	}
	hardware->limit_cpu = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LIMIT, CP_FUSION_PLAYER_CONF_STRING_NETWORK, 0)) {
		return cp_false;
	}
	hardware->limit_network = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_LIMIT, CP_FUSION_PLAYER_CONF_STRING_PLAY_COUNT, 0)) {
		return cp_false;
	}
	hardware->limit_play_count = tmp_value;

	//亮度
	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_HARDWARE, CP_FUSION_PLAYER_CONF_STRING_LUMINANCE, -1)) {
		return cp_false;
	}
	hardware->luminance = tmp_value;

	//对比度
	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_HARDWARE, CP_FUSION_PLAYER_CONF_STRING_CONTRAST, -1)) {
		return cp_false;
	}
	hardware->contrast = tmp_value;

	if (!get_conf_xml_string_prop(hardware->background_color, cp_sizeof(hardware->background_color),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_HARDWARE, CP_FUSION_PLAYER_CONF_STRING_BACKGROUND_COLOR, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_xml_int_prop(&tmp_value, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_HARDWARE, CP_FUSION_PLAYER_CONF_STRING_COLOR_TEMP, -1)) {
		return cp_false;
	}
	hardware->color_temp = tmp_value;

	//NVG_H_R = 1920
	if (!get_conf_xml_int_prop(&hardware->resolution_height, player, player->conf,
		CP_FUSION_PLAYER_CONF_STRING_RESOLUTION, CP_FUSION_PLAYER_CONF_STRING_HEIGHT, CP_APP_DEFAULT_HEIGHT_MAX)) {
		return cp_false;
	}

	//NVG_V_R = 1080
	if (!get_conf_xml_int_prop(&hardware->resolution_width, player, player->conf, 
		CP_FUSION_PLAYER_CONF_STRING_RESOLUTION, CP_FUSION_PLAYER_CONF_STRING_WIDTH, CP_APP_DEFAULT_WIDTH_MAX)) {
		return cp_false;
	}

	//NVG_CCTV_SIZE
	if (!get_conf_xml_int_prop(&hardware->cctv_size, player, player->conf, 
		CP_FUSION_PLAYER_CONF_STRING_HARDWARE, CP_FUSION_PLAYER_CONF_STRING_CCTV_SIZE, -1)) {
		return cp_false;
	}

	set_default_cctv_parameter(hardware);

	return cp_true;
}

cp_bool_t init_player_info_serials(cp_fusion_player_t *player, cp_serial_t *serials)
{
	cp_int32_t						tmp_value = 0;



	if (!get_conf_xml_string_prop(serials->name, cp_sizeof(serials->name), 
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_SERIAL, CP_FUSION_PLAYER_CONF_STRING_DEVICE, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_xml_int_prop(&serials->baudrate, player,
		player->conf, CP_FUSION_PLAYER_CONF_STRING_SERIAL, CP_FUSION_PLAYER_CONF_STRING_BAUD_RATE, 0)) {
		return cp_false;
	}

	if (!get_conf_xml_string_prop(serials->flowcontrol, cp_sizeof(serials->flowcontrol),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_SERIAL, CP_FUSION_PLAYER_CONF_STRING_FLOW_CONTROL, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_xml_string_prop(serials->parity, cp_sizeof(serials->parity),
		player, player->conf, CP_FUSION_PLAYER_CONF_STRING_SERIAL, CP_FUSION_PLAYER_CONF_STRING_NVG_PARITY, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_xml_int_prop(&tmp_value, player,
		player->conf, CP_FUSION_PLAYER_CONF_STRING_SERIAL, CP_FUSION_PLAYER_CONF_STRING_CHARACTER_SIZE, 0)) {
		return cp_false;
	}
	serials->character_size = tmp_value;

	if (!get_conf_xml_double_prop(&serials->stopbits, player,
		player->conf, CP_FUSION_PLAYER_CONF_STRING_SERIAL, CP_FUSION_PLAYER_CONF_STRING_STOP_BITS, 0)) {
		return cp_false;
	}

	return cp_true;
}

cp_int32_t init_player_info(cp_fusion_player_t *player, cp_fusion_player_info_t *info)
{
	cp_bool_t					ret_bool = cp_false;

	info->device_info = (cp_device_info_t *)cp_malloc(cp_sizeof(cp_device_info_t));
	if (info->device_info) {
		cp_memset(info->device_info, 0, cp_sizeof(cp_device_info_t));
	}
	else{
		cp_log_error(player->logger, "malloc device info failed!");
		return -1;
	}

	ret_bool = init_center_info(player, info);
	if (!ret_bool) {
		cp_log_error(player->logger, "init_center_info()  failed!");
		return -2;
	}

	ret_bool = init_local_info(player, info);
	if (!ret_bool) {
		cp_log_error(player->logger, "init_center_info()  failed!");
		return -3;
	}

	ret_bool = init_player_info_host(player, &(info->device_info->host));
	if (!ret_bool) {
		cp_log_error(player->logger, "init player info error reason init_player_info_host() failed!");
		return -4;
	}

	ret_bool = init_player_info_network(player, &(info->device_info->network));
	if (!ret_bool) {
		cp_log_error(player->logger, "init player info error reason init_player_info_network() failed!");
		return -5;
	}

	ret_bool = init_player_info_hardware(player, &(info->device_info->hardware));
	if (!ret_bool) {
		cp_log_error(player->logger, "init player info error reason init_player_info_hardware() failed!");
		return -6;
	}

	ret_bool = init_player_info_serials(player, &(info->device_info->serials));
	if (!ret_bool) {
		cp_log_error(player->logger, "init player info error reason init_player_info_serials() failed!");
		return -7;
	}

	return 0;
}






