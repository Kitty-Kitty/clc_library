/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#include "cp_ipc_core.h"
#include "cp_ipc_info.h"




cp_bool_t get_conf_int_prop(cp_int32_t *dest, cp_ipc_t *app,
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

cp_bool_t get_conf_double_prop(cp_double_t *dest, cp_ipc_t *app,
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

cp_bool_t get_conf_string_prop(cp_char_t *dest, cp_int32_t len, cp_ipc_t *app,
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

cp_bool_t get_conf_xml_int_prop(cp_int32_t *dest, cp_ipc_t *app,
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

cp_bool_t get_conf_xml_double_prop(cp_double_t *dest, cp_ipc_t *app,
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

cp_bool_t get_conf_xml_size_prop(cp_int64_t *dest, cp_ipc_t *app,
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

cp_bool_t get_conf_xml_string_prop(cp_char_t *dest, cp_int32_t len, cp_ipc_t *app,
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


cp_bool_t init_center_info(cp_ipc_t *ipc, cp_ipc_info_t *info) {

	//name
	if (!get_conf_string_prop(info->center_addr, cp_sizeof(info->center_addr),
		ipc, ipc->conf, CP_IPC_CONF_STRING_CENTER, CP_IPC_CONF_STRING_NVG_IP_ADDRESS, CP_NULL)) {
		return cp_false;
	}

	//NVG_POSTION = 80 - 03 - 01 �����б��01-02-03
	if (!get_conf_int_prop(&info->center_port, ipc,
		ipc->conf, CP_IPC_CONF_STRING_CENTER, CP_IPC_CONF_STRING_NVG_PORT, 0)) {
		return cp_false;
	}

	return cp_true;
}

cp_bool_t init_local_info(cp_ipc_t *ipc, cp_ipc_info_t *info) {

	//get network paraments from configure file
	if (!get_conf_string_prop(info->device_info->network.ip, cp_sizeof(info->device_info->network.ip), ipc, ipc->conf,
		CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_IP_ADDRESS, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&info->device_info->network.tcp_port, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_IP_TCP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&info->device_info->network.udp_port, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_IP_UDP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&info->heartbeat_manager.local_heartbeat_udp_port, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_IP_HEARTBEAT_UDP_PORT, 0)) {
		//return cp_false;
	}

	//��ʼ����������Ϣ������
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


cp_bool_t init_ipc_info_host(cp_ipc_t *ipc, cp_host_t *host)
{
	cp_char_t							tmp_type[CP_APP_DEFAULT_STRING_LENGTH] = { 0, };



	//��ȡ�豸�Ĺ�������
	if (!get_conf_xml_string_prop(tmp_type, cp_sizeof(tmp_type), ipc, ipc->conf,
		CP_IPC_CONF_STRING_GENERAL, CP_IPC_CONF_STRING_TYPE, CP_NULL)) {
		return cp_false;
	}

	host->status = 200;
	host->no = 0;//�豸���ֱ��
	memset(host->passwd, 0, sizeof(host->passwd));

	cp_sprintf(host->version, "%s", CP_VERSION);

	//name
	if (!get_conf_xml_string_prop(host->name, cp_sizeof(host->name),
		ipc, ipc->conf, CP_IPC_CONF_STRING_GENERAL, CP_IPC_CONF_STRING_NAME, CP_NULL)) {
		return cp_false;
	}

	//NVG_POSTION = 80 - 03 - 01 �����б��01-02-03
	if (!get_conf_string_prop(host->number, cp_sizeof(host->number),
		ipc, ipc->conf, CP_IPC_CONF_STRING_OTHER, CP_IPC_CONF_STRING_NVG_POSTION, CP_NULL)) {
		return cp_false;
	}

	//NVG_ID = 005 - 80 - 03 - 01 - 000000000001093075 - 1ee850bf7d6c404abbb71396c8ed9266
	if (!get_conf_string_prop(host->id, cp_sizeof(host->id),
		ipc, ipc->conf, CP_IPC_CONF_STRING_OTHER, CP_IPC_CONF_STRING_NVG_ID, CP_NULL)) {
		return cp_false;
	}

	//sn  
	if (!get_conf_xml_string_prop(host->sn, cp_sizeof(host->sn),
		ipc, ipc->conf, CP_IPC_CONF_STRING_GENERAL, CP_IPC_CONF_STRING_SN, CP_NULL)) {
		return cp_false;
	}

	return cp_true;
}

cp_bool_t init_ipc_info_network(cp_ipc_t *ipc, cp_interface_t *network)
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
		ipc, ipc->conf, CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_IP_ADDRESS, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&network->tcp_port, ipc,
		ipc->conf, CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_IP_TCP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_int_prop(&network->udp_port, ipc,
		ipc->conf, CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_IP_UDP_PORT, 0)) {
		return cp_false;
	}

	if (!get_conf_string_prop(network->gateway, cp_sizeof(network->gateway),
		ipc, ipc->conf, CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_GATEWAY, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_string_prop(network->netmask, cp_sizeof(network->netmask),
		ipc, ipc->conf, CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_NETMASK, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_string_prop(network->name, cp_sizeof(network->name),
		ipc, ipc->conf, CP_IPC_CONF_STRING_LOCAL, CP_IPC_CONF_STRING_NVG_DEVICE, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_xml_size_prop(&network->packet_length, ipc,
		ipc->conf, CP_CONF_STRING_NETWORK_CONFIGURE, CP_CONF_STRING_PACKET_LENGTH, 
		CP_IPC_HEARTBEAT_DEFAULT_DATA_LENGTH)) {
		return cp_false;
	}

	return cp_true;
}


cp_bool_t init_ipc_info_hardware(cp_ipc_t *ipc, cp_hardware_info_t *hardware)
{
	cp_int32_t						tmp_value = 0;


	/*
	hardware->limit_disk = cp_conf_getint(ipc->conf, CP_IPC_CONF_STRING_LIMIT, CP_IPC_CONF_STRING_DISK, 0);
	if (!hardware->limit_disk) {
		cp_log_error(ipc->logger, "get [%s:%s] failed!", CP_IPC_CONF_STRING_LIMIT, CP_IPC_CONF_STRING_DISK);
		return cp_false;
	}
	*/
	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LIMIT, CP_IPC_CONF_STRING_DISK, 0)) {
		return cp_false;
	}
	hardware->limit_disk = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LIMIT, CP_IPC_CONF_STRING_MEMORY, 0)) {
		return cp_false;
	}
	hardware->limit_memory = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LIMIT, CP_IPC_CONF_STRING_CPU, 0)) {
		return cp_false;
	}
	hardware->limit_cpu = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LIMIT, CP_IPC_CONF_STRING_NETWORK, 0)) {
		return cp_false;
	}
	hardware->limit_network = tmp_value;

	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_LIMIT, CP_IPC_CONF_STRING_PLAY_COUNT, 0)) {
		return cp_false;
	}
	hardware->limit_play_count = tmp_value;

	//����
	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_HARDWARE, CP_IPC_CONF_STRING_LUMINANCE, -1)) {
		return cp_false;
	}
	hardware->luminance = tmp_value;

	//�Աȶ�
	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_HARDWARE, CP_IPC_CONF_STRING_CONTRAST, -1)) {
		return cp_false;
	}
	hardware->contrast = tmp_value;

	if (!get_conf_xml_string_prop(hardware->background_color, cp_sizeof(hardware->background_color),
		ipc, ipc->conf, CP_IPC_CONF_STRING_HARDWARE, CP_IPC_CONF_STRING_BACKGROUND_COLOR, CP_NULL)) {
		return cp_false;
	}

	if (!get_conf_xml_int_prop(&tmp_value, ipc, ipc->conf,
		CP_IPC_CONF_STRING_HARDWARE, CP_IPC_CONF_STRING_COLOR_TEMP, -1)) {
		return cp_false;
	}
	hardware->color_temp = tmp_value;

	//NVG_H_R = 1920
	if (!get_conf_xml_int_prop(&hardware->resolution_height, ipc, ipc->conf,
		CP_IPC_CONF_STRING_RESOLUTION, CP_IPC_CONF_STRING_HEIGHT, CP_APP_DEFAULT_HEIGHT_MAX)) {
		return cp_false;
	}

	//NVG_V_R = 1080
	if (!get_conf_xml_int_prop(&hardware->resolution_width, ipc, ipc->conf, 
		CP_IPC_CONF_STRING_RESOLUTION, CP_IPC_CONF_STRING_WIDTH, CP_APP_DEFAULT_WIDTH_MAX)) {
		return cp_false;
	}

	//NVG_CCTV_SIZE
	if (!get_conf_xml_int_prop(&hardware->cctv_size, ipc, ipc->conf, 
		CP_IPC_CONF_STRING_HARDWARE, CP_IPC_CONF_STRING_CCTV_SIZE, -1)) {
		return cp_false;
	}

	set_default_cctv_parameter(hardware);

	return cp_true;
}

cp_bool_t init_ipc_info(cp_ipc_t *ipc, cp_ipc_info_t *info)
{
	cp_bool_t					ret_bool = cp_false;

	info->device_info = (cp_device_info_t *)cp_malloc(cp_sizeof(cp_device_info_t));
	if (info->device_info) {
		cp_memset(info->device_info, 0, cp_sizeof(cp_device_info_t));
	}
	else{
		cp_log_error(ipc->logger, "malloc device info failed!");
		return cp_false;
	}

	ret_bool = init_center_info(ipc, info);
	if (!ret_bool) {
		cp_log_error(ipc->logger, "init_center_info()  failed!");
		return cp_false;
	}

	ret_bool = init_local_info(ipc, info);
	if (!ret_bool) {
		cp_log_error(ipc->logger, "init_center_info()  failed!");
		return cp_false;
	}

	ret_bool = init_ipc_info_host(ipc, &(info->device_info->host));
	if (!ret_bool) {
		cp_log_error(ipc->logger, "init ipc info error reason init_ipc_info_host() failed!");
		return cp_false;
	}

	ret_bool = init_ipc_info_network(ipc, &(info->device_info->network));
	if (!ret_bool) {
		cp_log_error(ipc->logger, "init ipc info error reason init_ipc_info_network() failed!");
		return cp_false;
	}

	ret_bool = init_ipc_info_hardware(ipc, &(info->device_info->hardware));
	if (!ret_bool) {
		cp_log_error(ipc->logger, "init ipc info error reason init_ipc_info_hardware() failed!");
		return cp_false;
	}

	return cp_true;
}





