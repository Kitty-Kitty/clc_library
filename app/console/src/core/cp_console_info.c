/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_player_core.h"
#include "cp_player_info.h"


cp_bool_t init_center_info(cp_player_t *player, cp_player_info_t *info){

	const cp_char_t *tmp_center_addr = CP_NULL;


	//name
	tmp_center_addr = cp_conf_getstring(player->conf, CP_CONF_STRING_CENTER, CP_CONF_STRING_NVG_IP_ADDRESS, CP_NULL);
	if (!tmp_center_addr) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_CENTER, CP_CONF_STRING_NVG_IP_ADDRESS);
		return cp_false;
	}
	cp_sprintf(info->center_addr, "%s", tmp_center_addr);

	//NVG_POSTION = 80 - 03 - 01 组行列编号01-02-03
	info->center_port = cp_conf_getint(player->conf, CP_CONF_STRING_CENTER, CP_CONF_STRING_NVG_PORT, 0);
	if (info->center_port <= 0)
	{
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_CENTER, CP_CONF_STRING_NVG_PORT);
		return cp_false;
	}

	return cp_true;
}

cp_bool_t init_local_info(cp_player_t *player, cp_player_info_t *info){

	const cp_char_t				*tmp_ip = CP_NULL;
	cp_int32_t					tmp_tcp_port = 0;
	cp_int32_t					tmp_udp_port = 0;


	//get network paraments from configure file
	tmp_ip = cp_conf_getstring(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_ADDRESS, CP_NULL);
	if (!tmp_ip)
	{
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_ADDRESS);
		return cp_false;
	}
	cp_sprintf(info->local_addr, "%s", tmp_ip);
	info->local_tcp_port = cp_conf_getint(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_TCP_PORT, 0);
	if (!info->local_tcp_port) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_TCP_PORT);
		return cp_false;
	}
	info->local_udp_port = cp_conf_getint(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_UDP_PORT, 0);
	if (!info->local_udp_port) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_UDP_PORT);
		return cp_false;
	}

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


cp_bool_t init_player_info_host(cp_player_t *player, cp_host_t *host)
{

	const cp_char_t		*tmp_number = CP_NULL;
	const cp_char_t		*tmp_sn = CP_NULL;
	const cp_char_t		*tmp_id = CP_NULL;
	const cp_char_t		*tmp_name = CP_NULL;



	host->type = cp_device_type_cp_player;
	host->status = 200;
	host->no = 0;//设备数字编号
	memset(host->passwd, 0, sizeof(host->passwd));


	cp_sprintf(host->version, "%s", CP_VERSION);

	//name
	tmp_name = cp_conf_getstring(player->conf, CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_NAME, CP_NULL);
	if (!tmp_name) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_SYSTEM, CP_CONF_STRING_NVG_NAME);
		return cp_false;
	}
	cp_sprintf(host->name, "%s", tmp_name);

	//NVG_POSTION = 80 - 03 - 01 组行列编号01-02-03
	tmp_number = cp_conf_getstring(player->conf, CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_POSTION, CP_NULL);
	if (!tmp_number)
	{
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_POSTION);
		return cp_false;
	}
	cp_sprintf(host->number, "%s", tmp_number);


	//NVG_ID = 005 - 80 - 03 - 01 - 000000000001093075 - 1ee850bf7d6c404abbb71396c8ed9266
	tmp_id = cp_conf_getstring(player->conf, CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_ID, CP_NULL);
	if (!tmp_id) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_ID);
		return cp_false;
	}
	cp_sprintf(host->id, "%s", tmp_id);


	//NVG_SN =  
	tmp_sn = cp_conf_getstring(player->conf, CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_SN, CP_NULL);
	if (!tmp_sn) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_SN);
		return cp_false;
	}
	cp_sprintf(host->sn, "%s", tmp_sn);

	return cp_true;
}

cp_bool_t init_player_info_network(cp_player_t *player, cp_interface_t *network)
{
	const cp_char_t		*tmp_ip = CP_NULL;
	const cp_char_t		*tmp_gateway = CP_NULL;
	const cp_char_t		*tmp_netmask = CP_NULL;
	const cp_char_t		*tmp_name = CP_NULL;


	/*
	NVG_BOOT_PROTOCOL = 1
	NVG_IP_PORT = 65535
	NVG_TYPE =
	NVG_ON_BOOT =
	NVG_HWADDR =
	NVG_IP_VERSION =*/

	network->used = cp_true;

	tmp_ip = cp_conf_getstring(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_ADDRESS, CP_NULL);
	if (!tmp_ip) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_ADDRESS);
		return cp_false;
	}
	cp_sprintf(network->ip, "%s", tmp_ip);

	network->tcpport = cp_conf_getint(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_TCP_PORT, 0);
	if (!network->tcpport) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_TCP_PORT);
		return cp_false;
	}

	network->udpport = cp_conf_getint(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_UDP_PORT, 0);
	if (!network->udpport) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_IP_UDP_PORT);
		return cp_false;
	}

	tmp_gateway = cp_conf_getstring(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_GATEWAY, CP_NULL);
	if (!tmp_gateway) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_GATEWAY);
		return cp_false;
	}
	cp_sprintf(network->gateway, "%s", tmp_gateway);

	tmp_netmask = cp_conf_getstring(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_NETMASK, CP_NULL);
	if (!tmp_netmask) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_NETMASK);
		return cp_false;
	}
	cp_sprintf(network->netmask, "%s", tmp_netmask);

	tmp_name = cp_conf_getstring(player->conf, CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_DEVICE, CP_NULL);
	if (!tmp_name) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LOCAL, CP_CONF_STRING_NVG_DEVICE);
		return cp_false;
	}
	cp_sprintf(network->name, "%s", tmp_name);

	return cp_true;
}


cp_bool_t init_player_info_hardware(cp_player_t *player, cp_hardware_info_t *hardware)
{
	const cp_char_t *tmp_background_color = CP_NULL;




	hardware->limit_disk = cp_conf_getint(player->conf, CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_DISK, 0);
	if (!hardware->limit_disk) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_DISK);
		return cp_false;
	}

	hardware->limit_memory = cp_conf_getint(player->conf, CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_MEMORY, 0);
	if (!hardware->limit_memory) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_MEMORY);
		return cp_false;
	}

	hardware->limit_cpu = cp_conf_getint(player->conf, CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_CPU, 0);
	if (!hardware->limit_cpu) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_CPU);
		return cp_false;
	}

	hardware->limit_network = cp_conf_getint(player->conf, CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_NETWORK, 0);
	if (!hardware->limit_network) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LIMIT_NETWORK);
		return cp_false;
	}

	hardware->limit_play_count = cp_conf_getint(player->conf, CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LINIT_PLAY_COUNT, 0);
	if (!hardware->limit_play_count) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_LIMIT, CP_CONF_STRING_NVG_LINIT_PLAY_COUNT);
		return cp_false;
	}

	//亮度
	hardware->luminance = cp_conf_getint(player->conf, CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_LUMINANCE, -1);
	if (hardware->luminance < 0) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_LUMINANCE);
		return cp_false;
	}

	//对比度
	hardware->contrast = cp_conf_getint(player->conf, CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_CONTRAST, -1);
	if (hardware->contrast < 0) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_CONTRAST);
		return cp_false;
	}

	tmp_background_color = cp_conf_getstring(player->conf, CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_BACKGROUND_COLOR, CP_NULL);
	if (!tmp_background_color) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_BACKGROUND_COLOR);
		return cp_false;
	}
	cp_sprintf(hardware->background_color, "%s", tmp_background_color);

	hardware->color_temp = cp_conf_getint(player->conf, CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_COLOR_TEMP, -1);
	if (hardware->color_temp < 0) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_COLOR_TEMP);
		return cp_false;
	}

	//NVG_H_R = 1920
	hardware->resolution_width = cp_conf_getint(player->conf, CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_H_R, 0);
	if (!hardware->resolution_width) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_H_R);
		return cp_false;
	}

	if (hardware->resolution_width > CP_APP_DEFAULT_WIDTH_MAX)
	{
		cp_log_warn(player->logger, "get [%s] warning  value out width max [%d]!", CP_CONF_STRING_NVG_H_R, CP_APP_DEFAULT_WIDTH_MAX);
		hardware->resolution_width = CP_APP_DEFAULT_WIDTH_MAX;
	}

	//NVG_V_R = 1080
	hardware->resolution_height = cp_conf_getint(player->conf, CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_V_R, 0);
	if (!hardware->resolution_height) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_V_R);
		return cp_false;
	}

	if (hardware->resolution_height > CP_APP_DEFAULT_HEIGHT_MAX)
	{
		cp_log_warn(player->logger, "get [%s] warning  value out width max [%d]!", CP_CONF_STRING_NVG_V_R, CP_APP_DEFAULT_HEIGHT_MAX);
		hardware->resolution_height = CP_APP_DEFAULT_HEIGHT_MAX;
	}

	//NVG_CCTV_SIZE
	hardware->cctv_size = cp_conf_getint(player->conf, CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_CCTV_SIZE, 0);
	if (!hardware->cctv_size) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_HARDWARE, CP_CONF_STRING_NVG_CCTV_SIZE);
		return cp_false;
	}

	set_default_cctv_parameter(hardware);

	/*
	NVG_SYNC_VER = 16666666 同步精度，媒体使用
	*/
	/*
	hardware->resolution_height = cp_conf_getint(player->conf, CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_SYNC_VER, 0);
	if (!hardware->resolution_height) {
	cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_OTHER, CP_CONF_STRING_NVG_SYNC_VER);
	return -1;
	}
	*/

	return cp_true;
}

cp_bool_t init_player_info_serials(cp_player_t *player, cp_serial_t *serials)
{
	const cp_char_t	   *tmp_name = CP_NULL;
	const cp_uchar_t   *tmp_flowcontrol = CP_NULL;
	const cp_uchar_t   *tmp_parity = CP_NULL;



	tmp_name = cp_conf_getstring(player->conf, CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_SERIAL_NAME, CP_NULL);
	if (!tmp_name) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_SERIAL_NAME);
		return cp_false;
	}
	cp_sprintf(serials->name, "%s", tmp_name);


	serials->baudrate = cp_conf_getint(player->conf, CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_BAUD_RATE, 0);
	if (!serials->baudrate) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_BAUD_RATE);
		return cp_false;
	}

	tmp_flowcontrol = cp_conf_getstring(player->conf, CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_FLOW_CONTROL, CP_NULL);
	if (!tmp_flowcontrol) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_FLOW_CONTROL);
		return cp_false;
	}
	cp_sprintf(serials->flowcontrol, "%s", tmp_flowcontrol);

	tmp_parity = cp_conf_getstring(player->conf, CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_PARITY, CP_NULL);
	if (!tmp_parity) {
		cp_log_error(player->logger, "get [%s:%s] failed!", CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_PARITY);
		return cp_false;
	}
	cp_sprintf(serials->parity, "%s", tmp_parity);

	serials->charactersize = cp_conf_getint(player->conf, CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_CHARACTER_SIZE, 0);
	serials->stopbits = (cp_float_t)cp_conf_getdouble(player->conf, CP_CONF_STRING_NVG_SERIAL, CP_CONF_STRING_NVG_STOP_BITS, 0);

	return cp_true;
}

cp_bool_t init_player_info(cp_player_t *player, cp_player_info_t *info)
{
	cp_bool_t					ret_bool = cp_false;

	ret_bool = init_center_info(player, info);
	if (!ret_bool)
	{
		cp_log_error(player->logger, "init_center_info()  failed!");
		return cp_false;
	}

	ret_bool = init_local_info(player, info);
	if (!ret_bool)
	{
		cp_log_error(player->logger, "init_center_info()  failed!");
		return cp_false;
	}

	info->device_info = (cp_device_info_t *)cp_malloc(cp_sizeof(cp_device_info_t));
	if (info->device_info){
		cp_memset(info->device_info, 0, cp_sizeof(cp_device_info_t));
	}
	else{
		cp_log_error(player->logger, "malloc device info failed!");
		return cp_false;
	}

	//初始化队列
	cp_queue_init(&info->cener_server);
	cp_queue_init(&info->client_server);
	cp_queue_init(&info->player_server);
	cp_queue_init(&info->media_server);

	ret_bool = init_player_info_host(player, &(info->device_info->host));
	if (!ret_bool)
	{
		cp_log_error(player->logger, "init player info error reason init_player_info_host() failed!");
		return cp_false;
	}

	ret_bool = init_player_info_network(player, &(info->device_info->network));
	if (!ret_bool)
	{
		cp_log_error(player->logger, "init player info error reason init_player_info_network() failed!");
		return cp_false;
	}

	ret_bool = init_player_info_hardware(player, &(info->device_info->hardware));
	if (!ret_bool)
	{
		cp_log_error(player->logger, "init player info error reason init_player_info_hardware() failed!");
		return cp_false;
	}

	ret_bool = init_player_info_serials(player, &(info->device_info->serials));
	if (!ret_bool)
	{
		cp_log_error(player->logger, "init player info error reason init_player_info_serials() failed!");
		return cp_false;
	}

	return cp_true;
}






