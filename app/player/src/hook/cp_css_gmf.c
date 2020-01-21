/**************************************************************************

* Copyright: novigo

* Author: tianhuiming@novigo.com.cn

* Date：2016-4-23
        
* Description:

**************************************************************************/


#include "cp_css_gmf.h"
// #include "cp_define_str.h"
// #include "cp_utils.h"
// #include "css_core.h"
// #include "prot_gmp_status.h"
// #include "cp_css_std.h"



cp_int32_t make_semh_header(gmp_gmph_semh_t *semh, cp_uint32_t cmd, cp_int32_t len, cp_int32_t p_no, cp_int32_t status, cp_char_t *session_id)
{
	semh->bmh.gmpv = GMP_GMPV_LITTLE_ENDIAN;
	semh->bmh.emht = 1;

	semh->command = cmd;
	semh->length = len;
	semh->packet_no = p_no;
	semh->status = status;

	cp_strncpy(semh->session_id, session_id, GMP_GMPH_SEMH_SESSION_ID_LEN);

	return 0;
}

gmp_gmdu_t *make_gmf_return(gmp_gmf_t *gmf, cp_return_info_t *ret, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*host_gmdu;
	gmp_gmdu_t						*object_gmdu;


	if (!gmf) {
		return CP_NULL;
	}

	//清空缓存
	cp_memset(buf, 0, len);

	//创建Object主节点
	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_snprintf(buf, len - 1, "gmp_create_gmdu Object error!");
		return CP_NULL;
	}

	//创建host主节点
	host_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST, CP_APP_STR_HOST,
		cp_strlen(CP_APP_STR_HOST), GMP_GMDT_O);
	if (!host_gmdu) {
		cp_snprintf(buf, len - 1, "gmp_create_gmdu Host error!");
		return CP_NULL;
	}

	//添加ID节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_ID, cp_strlen(CP_APP_STR_ID),
		GMP_GMDT_ST, ret->host_id, cp_strlen(ret->host_id)));

	//添加Host节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	//添加Status节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_STATUS, cp_strlen(CP_APP_STR_STATUS),
		GMP_GMDT_IN, ret->status));

	//添加Reason节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_REASON, cp_strlen(CP_APP_STR_REASON),
		GMP_GMDT_ST, ret->reason, cp_strlen(ret->reason)));

	//添加Return节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T",
		GMP_GMDT_ST, CP_APP_STR_RETURN, cp_strlen(CP_APP_STR_RETURN),
		GMP_GMDT_N));

	return object_gmdu;
}


gmp_gmdu_t *make_gmf_host(gmp_gmf_t *gmf, cp_host_t *host)
{
	gmp_gmdu_t						*host_gmdu;



	if (!gmf) {
		return CP_NULL;
	}
	//创建Host主节点
	host_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_HOST, strlen(CP_APP_STR_HOST), GMP_GMDT_O);
	if (!host_gmdu) {
		return CP_NULL;
	}

/*
	//添加PASSWD节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_PASSWD, strlen(CP_APP_STR_PASSWD),
		GMP_GMDT_ST, host->passwd, strlen(host->passwd)));
*/

	//添加ID节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_ID, strlen(CP_APP_STR_ID),
		GMP_GMDT_ST, host->id, strlen(host->id)));

	//添加Name节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_NAME, strlen(CP_APP_STR_NAME),
		GMP_GMDT_ST, host->name, strlen(host->name)));

	//添加Version节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_VERSION, strlen(CP_APP_STR_VERSION),
		GMP_GMDT_ST, host->version, strlen(host->version)));

	//添加Type节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%UC",
		GMP_GMDT_ST, CP_APP_STR_TYPE, strlen(CP_APP_STR_TYPE),
		GMP_GMDT_UC, host->type));

	//添加Status节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_STATUS, strlen(CP_APP_STR_STATUS),
		GMP_GMDT_IN, host->status));

	return host_gmdu;
}

gmp_gmdu_t *make_gmf_interfaces(gmp_gmf_t *gmf, cp_interface_t *network)
{
	gmp_gmdu_t						*interfaces_gmdu;
	gmp_gmdu_t						*interface_gmdu;


	if (!gmf) {
		return CP_NULL;
	}

	//创建Interfaces主节点
	interfaces_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_INTERFACES, strlen(CP_APP_STR_INTERFACES), GMP_GMDT_A);
	if (!interfaces_gmdu) {
		return CP_NULL;
	}
	
	//创建Interface主节点
	interface_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_INTERFACE, strlen(CP_APP_STR_INTERFACE), GMP_GMDT_O);
	if (!interface_gmdu) {
		return CP_NULL;
	}

	//创建Interface
	gmp_add_gmdu_child_gmdu(gmf, interface_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_NAME, strlen(CP_APP_STR_NAME),
		GMP_GMDT_ST, CP_APP_STR_IN_NAME, strlen(CP_APP_STR_IN_NAME)));

	//添加Used节点
	gmp_add_gmdu_child_gmdu(gmf, interface_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%UC",
		GMP_GMDT_ST, CP_APP_STR_USRD, strlen(CP_APP_STR_USRD),
		GMP_GMDT_UC, network->used));

	//添加IP节点
	gmp_add_gmdu_child_gmdu(gmf, interface_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_IP, strlen(CP_APP_STR_IP),
		GMP_GMDT_ST, network->ip, strlen(network->ip)));

	//添加TCPPort节点
	gmp_add_gmdu_child_gmdu(gmf, interface_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_TCPPORT, strlen(CP_APP_STR_TCPPORT),
		GMP_GMDT_IN, network->tcp_port));

	//添加UDPPort节点
	gmp_add_gmdu_child_gmdu(gmf, interface_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_UDPPORT, strlen(CP_APP_STR_UDPPORT),
		GMP_GMDT_IN, network->udp_port));

	//向Interfaces 节点中添加 interface信息
	gmp_add_gmdu_child_gmdu(gmf, interfaces_gmdu, interface_gmdu);

	return interfaces_gmdu;
}

gmp_gmdu_t *make_gmf_serials(gmp_gmf_t *gmf, cp_serial_t *serials)
{
	gmp_gmdu_t						*serials_gmdu;
	gmp_gmdu_t						*serial_gmdu;



	if (!gmf) {
		return CP_NULL;
	}

	//添加串口信息
	serials_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_SERIALS, strlen(CP_APP_STR_SERIALS), GMP_GMDT_A);

	serial_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_SERIAL, strlen(CP_APP_STR_SERIAL), GMP_GMDT_O);

	//添加串口名称节点
	gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_NAME, strlen(CP_APP_STR_NAME),
		GMP_GMDT_ST, serials->name, strlen(serials->name)));

	//添加波特率节点
	gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_BAUDRATE, strlen(CP_APP_STR_BAUDRATE),
		GMP_GMDT_IN, serials->baudrate));

	//添加数据位节点
	gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_CHARACTER_SIZE, strlen(CP_APP_STR_CHARACTER_SIZE),
		GMP_GMDT_UC, serials->character_size));

	//添加流控制类型
	if (!cp_strcmp(serials->flowcontrol, "none")) {
		gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_FLOW_CONTROL, strlen(CP_APP_STR_FLOW_CONTROL),
			GMP_GMDT_UC, 0));
	}
	else if (!cp_strcmp(serials->flowcontrol, "software")) {
		gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_FLOW_CONTROL, strlen(CP_APP_STR_FLOW_CONTROL),
			GMP_GMDT_UC, 1));
	}
	else if (!cp_strcmp(serials->flowcontrol, "hardware")) {
		gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_FLOW_CONTROL, strlen(CP_APP_STR_FLOW_CONTROL),
			GMP_GMDT_UC, 2));
	}

	//添加校验类型
	if (!cp_strcmp(serials->flowcontrol, "none")) {

		gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_PARITY, strlen(CP_APP_STR_PARITY),
			GMP_GMDT_UC, 0));
	}
	else if (!cp_strcmp(serials->flowcontrol, "odd")) {

		gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_PARITY, strlen(CP_APP_STR_PARITY),
			GMP_GMDT_UC, 1));
	}
	else if (!cp_strcmp(serials->flowcontrol, "event")) {

		gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_PARITY, strlen(CP_APP_STR_PARITY),
			GMP_GMDT_UC, 2));
	}

	//添加停止位
 	gmp_add_gmdu_child_gmdu(gmf, serial_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
 	GMP_GMDT_ST, CP_APP_STR_STOP_BITS, strlen(CP_APP_STR_STOP_BITS),
 	GMP_GMDT_F, serials->stopbits));

	gmp_add_gmdu_child_gmdu(gmf, serials_gmdu, serial_gmdu);

	return serials_gmdu;
}


gmp_gmdu_t *make_gmf_networks(gmp_gmf_t *gmf, cp_interface_t *network)
{
	gmp_gmdu_t						*networks_gmdu;
	gmp_gmdu_t						*network_gmdu;



	if (!gmf) {
		return CP_NULL;
	}

	//添加串口信息
	networks_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_NETWORKS, strlen(CP_APP_STR_NETWORKS), GMP_GMDT_A);

	network_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_NETWORK, strlen(CP_APP_STR_NETWORK), GMP_GMDT_O);

	//添加Name节点
	gmp_add_gmdu_child_gmdu(gmf, network_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_NAME, strlen(CP_APP_STR_NAME),
		GMP_GMDT_ST, network->name, strlen(network->name)));

	//添加BootProtocol节点
	gmp_add_gmdu_child_gmdu(gmf, network_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_BOOTPROTOCOL, strlen(CP_APP_STR_BOOTPROTOCOL),
		GMP_GMDT_UC, network->bootp));

	//添加IP节点
	gmp_add_gmdu_child_gmdu(gmf, network_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_IP, strlen(CP_APP_STR_IP),
		GMP_GMDT_ST, network->ip, strlen(network->ip)));

	//添加NetMask类型
	gmp_add_gmdu_child_gmdu(gmf, network_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_NETMASK, strlen(CP_APP_STR_NETMASK),
		GMP_GMDT_ST, network->netmask, strlen(network->netmask)));

	//添加Gateway类型
	gmp_add_gmdu_child_gmdu(gmf, network_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_GATEWAY, strlen(CP_APP_STR_GATEWAY),
		GMP_GMDT_ST, network->gateway, strlen(network->gateway)));

	gmp_add_gmdu_child_gmdu(gmf, networks_gmdu, network_gmdu);

	return networks_gmdu;
}

gmp_gmdu_t *make_gmf_register_information(gmp_gmf_t *gmf, cp_device_info_t *pi)
{
	gmp_gmdu_t						*information_gmdu = CP_NULL;
	gmp_gmdu_t						*resolution_gmdu = CP_NULL;
	gmp_gmdu_t						*backsize_gmdu = CP_NULL;
	gmp_gmdu_t						*sync_info_gmdu = CP_NULL;



	if (!gmf) {
		return CP_NULL;
	}

	//创建information主节点
	information_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST, 
		CP_APP_STR_INFORMATION, strlen(CP_APP_STR_INFORMATION), GMP_GMDT_O);
	if (!information_gmdu) {
		return CP_NULL;
	}

	if (strlen(pi->host.number) == 0) {
		//添加number节点
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_NUMBER, strlen(CP_APP_STR_NUMBER),
			GMP_GMDT_ST, "00-00-00", strlen("00-00-00")));
	}else{
		//添加number节点
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_NUMBER, strlen(CP_APP_STR_NUMBER),
			GMP_GMDT_ST, pi->host.number, strlen(pi->host.number)));
	}

	//添加limitdisk节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d", 
		GMP_GMDT_ST, CP_APP_STR_LIMITDISK, strlen(CP_APP_STR_LIMITDISK), 
		GMP_GMDT_UIN, pi->hardware.limit_disk));

	//添加limitmemory节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d", 
		GMP_GMDT_ST, CP_APP_STR_LIMITMEMORY, strlen(CP_APP_STR_LIMITMEMORY), 
		GMP_GMDT_UIN, pi->hardware.limit_memory));

	//添加limitcpu节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d", 
		GMP_GMDT_ST, CP_APP_STR_LIMITCPU, strlen(CP_APP_STR_LIMITCPU), 
		GMP_GMDT_UIN, pi->hardware.limit_cpu));

	//添加limitnetwork节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d", 
		GMP_GMDT_ST, CP_APP_STR_LIMITNETWORK, strlen(CP_APP_STR_LIMITNETWORK), 
		GMP_GMDT_UIN, pi->hardware.limit_network));

	//添加limitplaycount节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d", 
		GMP_GMDT_ST, CP_APP_STR_LIMITPLAYCOUNT, strlen(CP_APP_STR_LIMITPLAYCOUNT), 
		GMP_GMDT_UIN, pi->hardware.limit_play_count));

	//添加limitconnect节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LIMITCONNECTION, strlen(CP_APP_STR_LIMITCONNECTION),
		GMP_GMDT_IN, pi->hardware.limit_connect));

	//创建屏幕分辨率GMDU
	resolution_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", 
		GMP_GMDT_ST, CP_APP_STR_RESOLUTION, strlen(CP_APP_STR_RESOLUTION), 
		GMP_GMDT_O);
	if (resolution_gmdu) {
		//添加屏幕分辨率宽度像素节点
		gmp_add_gmdu_child_gmdu(gmf, resolution_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_WIDTH, strlen(CP_APP_STR_WIDTH),
			GMP_GMDT_UIN, pi->hardware.resolution_width));

		//添加屏幕分辨率宽度像素节点
		gmp_add_gmdu_child_gmdu(gmf, resolution_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_HEIGHT, strlen(CP_APP_STR_HEIGHT),
			GMP_GMDT_UIN, pi->hardware.resolution_height));

		//添加RESOLUTION节点
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, resolution_gmdu);
	}

/*
	//创建屏幕分辨率GMDU
	backsize_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T",
		GMP_GMDT_ST, CP_APP_STR_BACKSIZE, strlen(CP_APP_STR_BACKSIZE),
		GMP_GMDT_O);
	if (backsize_gmdu) {
		//添加屏幕分辨率宽度像素节点
		gmp_add_gmdu_child_gmdu(gmf, backsize_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_WIDTH, strlen(CP_APP_STR_WIDTH),
			GMP_GMDT_UIN, pi->hardware.resolution_width));

		//添加屏幕分辨率宽度像素节点
		gmp_add_gmdu_child_gmdu(gmf, backsize_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_HEIGHT, strlen(CP_APP_STR_HEIGHT),
			GMP_GMDT_UIN, pi->hardware.resolution_height));

		//添加BackSize节点
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, backsize_gmdu);
	}*/
	
	//添加BACKCOLOR节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_BACKCOLOR, strlen(CP_APP_STR_BACKCOLOR),
		GMP_GMDT_ST, pi->hardware.background_color, strlen(pi->hardware.background_color)));
	
	//添加size节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_SIZE, strlen(CP_APP_STR_SIZE),
		GMP_GMDT_UIN, pi->hardware.cctv_size));

	//添加border节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d%d%d%d",
		GMP_GMDT_ST, CP_APP_STR_BORDER, strlen(CP_APP_STR_BORDER),
		GMP_GMDT_R, pi->hardware.border_size.left, pi->hardware.border_size.top, 
		pi->hardware.border_size.right, pi->hardware.border_size.bottom));

	//添加luminance节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LUMINANCE, strlen(CP_APP_STR_LUMINANCE),
		GMP_GMDT_UC, pi->hardware.luminance));

	//添加contrast节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_CONTRAST, strlen(CP_APP_STR_CONTRAST),
		GMP_GMDT_UC, pi->hardware.contrast));

	//添加colortemperature节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_COLORTEMPERATURE, strlen(CP_APP_STR_COLORTEMPERATURE),
		GMP_GMDT_UC, pi->hardware.color_temp));

	//添加contrast节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%B",
		GMP_GMDT_ST, CP_APP_STR_SWITCH, strlen(CP_APP_STR_SWITCH),
		GMP_GMDT_B, pi->hardware.cctv_switch));

// 	//添加background节点
// 	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
// 		GMP_GMDT_ST, CP_APP_STR_BACKGROUND, strlen(CP_APP_STR_BACKGROUND),
// 		GMP_GMDT_ST, pi->hardware.imagenum, strlen(pi->hardware.imagenum)));

	//添加SyncInformation
	sync_info_gmdu = make_gmf_sync_information(gmf, pi);
	if (sync_info_gmdu) {
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, sync_info_gmdu);
	}

	return information_gmdu;
}

gmp_gmdu_t *make_gmf_life_heart_information(gmp_gmf_t *gmf, cp_device_info_t *pi)
{
	gmp_gmdu_t						*information_gmdu = CP_NULL;
	gmp_gmdu_t						*resolution_gmdu = CP_NULL;
	gmp_gmdu_t						*sync_info_gmdu = CP_NULL;



	if (!gmf) {
		return CP_NULL;
	}

	//创建information主节点
	information_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_INFORMATION, strlen(CP_APP_STR_INFORMATION), GMP_GMDT_O);
	if (!information_gmdu) {
		return CP_NULL;
	}

	//添加No节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_NO, strlen(CP_APP_STR_NO),
		GMP_GMDT_UIN, pi->host.no));

	//添加Disk节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_DISK, strlen(CP_APP_STR_DISK),
		GMP_GMDT_IN, 0));

	//添加Memory节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_MEMORY, strlen(CP_APP_STR_MEMORY),
		GMP_GMDT_IN, 0));

	//添加Cpu节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_CPU, strlen(CP_APP_STR_CPU),
		GMP_GMDT_IN, 0));

	//添加Network节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_NETWORK, strlen(CP_APP_STR_NETWORK),
		GMP_GMDT_UIN, 0));

	//添加Playcount节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_PLAYCOUNT, strlen(CP_APP_STR_PLAYCOUNT),
		GMP_GMDT_IN, 0));

	//添加SyncInformation
	sync_info_gmdu = make_gmf_sync_information(gmf, pi);
	if (sync_info_gmdu) {
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, sync_info_gmdu);
	}

	return information_gmdu;
}

gmp_gmdu_t *make_gmf_player_information(gmp_gmf_t *gmf, cp_device_info_t *pi, cp_center_addr_t *center_addr)
{
	gmp_gmdu_t						*information_gmdu = CP_NULL;
	gmp_gmdu_t						*resolution_gmdu = CP_NULL;
	gmp_gmdu_t						*serials_gmdu = CP_NULL;
	gmp_gmdu_t						*networks_gmdu = CP_NULL;
	gmp_gmdu_t						*center_gmdu = CP_NULL;



	if (!gmf) {
		return CP_NULL;
	}

	//创建Information主节点
	information_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_INFORMATION, strlen(CP_APP_STR_INFORMATION), GMP_GMDT_O);
	if (!information_gmdu) {
		return CP_NULL;
	}

	//添加No节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_NO, strlen(CP_APP_STR_NO),
		GMP_GMDT_IN, pi->host.no));

	if (strlen(pi->host.number) == 0) {
		//添加Number节点
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_NUMBER, strlen(CP_APP_STR_NUMBER),
			GMP_GMDT_ST, "00-00-00", strlen("00-00-00")));
	}
	else{
		//添加Number节点
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_NUMBER, strlen(CP_APP_STR_NUMBER),
			GMP_GMDT_ST, pi->host.number, strlen(pi->host.number)));
	}

	//添加Disk、Cpu、Memory、Metwork节点<设备当前状态>

	//添加Limitdisk节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LIMITDISK, strlen(CP_APP_STR_LIMITDISK),
		GMP_GMDT_UIN, pi->hardware.limit_disk));

	//添加Limitmemory节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LIMITMEMORY, strlen(CP_APP_STR_LIMITMEMORY),
		GMP_GMDT_UIN, pi->hardware.limit_memory));

	//添加Limitcpu节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LIMITCPU, strlen(CP_APP_STR_LIMITCPU),
		GMP_GMDT_UIN, pi->hardware.limit_cpu));

	//添加Limitnetwork节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LIMITNETWORK, strlen(CP_APP_STR_LIMITNETWORK),
		GMP_GMDT_UIN, pi->hardware.limit_network));

	//添加Limitplaycount节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LIMITPLAYCOUNT, strlen(CP_APP_STR_LIMITPLAYCOUNT),
		GMP_GMDT_UIN, pi->hardware.limit_play_count));

	//添加Resolution节点
	resolution_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T",
		GMP_GMDT_ST, CP_APP_STR_RESOLUTION, strlen(CP_APP_STR_RESOLUTION),
		GMP_GMDT_O);
	if (resolution_gmdu) {
		//添加屏幕分辨率宽度像素节点
		gmp_add_gmdu_child_gmdu(gmf, resolution_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_WIDTH, strlen(CP_APP_STR_WIDTH),
			GMP_GMDT_UIN, pi->hardware.resolution_width));

		//添加屏幕分辨率宽度像素节点
		gmp_add_gmdu_child_gmdu(gmf, resolution_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_HEIGHT, strlen(CP_APP_STR_HEIGHT),
			GMP_GMDT_UIN, pi->hardware.resolution_height));

		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, resolution_gmdu);
	}

	//添加Backcolor节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_BACKCOLOR, strlen(CP_APP_STR_BACKCOLOR),
		GMP_GMDT_ST, pi->hardware.background_color, strlen(pi->hardware.background_color)));

	//添加BackSize节点 <屏幕分辨率>

	//添加BackFps

	//添加Border节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d%d%d%d",
		GMP_GMDT_ST, CP_APP_STR_BORDER, strlen(CP_APP_STR_BORDER),
		GMP_GMDT_R, pi->hardware.border_size.left, pi->hardware.border_size.top,
		pi->hardware.border_size.right, pi->hardware.border_size.bottom));

	//添加Luminance节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_LUMINANCE, strlen(CP_APP_STR_LUMINANCE),
		GMP_GMDT_UC, pi->hardware.luminance));

	//添加Contrast节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_CONTRAST, strlen(CP_APP_STR_CONTRAST),
		GMP_GMDT_UC, pi->hardware.contrast));

	//添加Colortemperature节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_COLORTEMPERATURE, strlen(CP_APP_STR_COLORTEMPERATURE),
		GMP_GMDT_UC, pi->hardware.color_temp));

	//添加Contrast节点
	gmp_add_gmdu_child_gmdu(gmf, information_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%B",
		GMP_GMDT_ST, CP_APP_STR_SWITCH, strlen(CP_APP_STR_SWITCH),
		GMP_GMDT_B, pi->hardware.cctv_switch));

	//添加Center节点
	center_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST, CP_APP_STR_CENTER, strlen(CP_APP_STR_CENTER), GMP_GMDT_O);
	if (center_gmdu) {
		//中心IP地址
		gmp_add_gmdu_child_gmdu(gmf, center_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_IP, strlen(CP_APP_STR_IP),
			GMP_GMDT_ST, center_addr->ip, strlen(center_addr->ip)));

		//中心TCPPort
		gmp_add_gmdu_child_gmdu(gmf, center_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
			GMP_GMDT_ST, CP_APP_STR_TCPPORT, strlen(CP_APP_STR_TCPPORT),
			GMP_GMDT_IN, center_addr->tcp_port));

		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, center_gmdu);
	}

	//添加Serials
	serials_gmdu = make_gmf_serials(gmf, &pi->serials);
	if (serials_gmdu) {
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, serials_gmdu);
	}

	networks_gmdu = make_gmf_networks(gmf, &pi->network);
	if (networks_gmdu) {
		gmp_add_gmdu_child_gmdu(gmf, information_gmdu, networks_gmdu);
	}

	return information_gmdu;
}

gmp_gmdu_t *make_gmf_sync_information(gmp_gmf_t *gmf, cp_device_info_t *pi)
{
	gmp_gmdu_t						*sync_info_gmdu = CP_NULL;
	gmp_gmdu_t						*devices_gmdu = CP_NULL;
	gmp_gmdu_t						*device_gmdu = CP_NULL;



	if (!gmf) {
		return CP_NULL;
	}

	//创建sync_infomation主节点
	sync_info_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_PLYAER_STR_SYNCINFORMATION, strlen(CP_PLYAER_STR_SYNCINFORMATION), GMP_GMDT_O);
	if (!sync_info_gmdu) {
		return CP_NULL;
	}

	//创建Devices主节点
	devices_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_DEVICES, strlen(CP_APP_STR_DEVICES), GMP_GMDT_A);
	if (!devices_gmdu) {
		return sync_info_gmdu;
	}

	//创建Device主节点
	device_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_DEVICE, strlen(CP_APP_STR_DEVICE), GMP_GMDT_O);
	if (device_gmdu) {
		//添加Flag节点
		gmp_add_gmdu_child_gmdu(gmf, device_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_FLAG, strlen(CP_APP_STR_FLAG),
			GMP_GMDT_B, pi->sync_info.flag));

		//添加Value节点
		gmp_add_gmdu_child_gmdu(gmf, device_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_PLYAER_STR_VALUE, strlen(CP_PLYAER_STR_VALUE),
			GMP_GMDT_IN, pi->sync_info.value));

		//添加TimeStampS节点
		gmp_add_gmdu_child_gmdu(gmf, device_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_PLYAER_STR_TIMESTAMPS, strlen(CP_PLYAER_STR_TIMESTAMPS),
			GMP_GMDT_UIN, pi->sync_info.time_stamps));

		//添加TimeStampS节点
		gmp_add_gmdu_child_gmdu(gmf, device_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_PLYAER_STR_TIMESTAMPNS, strlen(CP_PLYAER_STR_TIMESTAMPNS),
			GMP_GMDT_UIN, pi->sync_info.time_stampns));

		gmp_add_gmdu_child_gmdu(gmf, devices_gmdu, device_gmdu);
	}

	gmp_add_gmdu_child_gmdu(gmf, sync_info_gmdu, devices_gmdu);

	return sync_info_gmdu;
}

gmp_gmdu_t *make_gmf_register(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_char_t *error_buf, cp_int32_t len)
{
	gmp_gmdu_t						*object_gmdu;
	gmp_gmdu_t						*host_gmdu;
	gmp_gmdu_t						*interface_gmdu;
	gmp_gmdu_t						*information_gmdu;


	
	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_register error gmp_create_gmdu() failed!");
		return CP_NULL;
	}

	host_gmdu = make_gmf_host(gmf, &(player_info->host));
	if (!host_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_register error make_gmf_host() failed!");
		return CP_NULL;
	}

	//添加HeartbeatTimes节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_HEARTBEAT_TIMES, strlen(CP_APP_STR_HEARTBEAT_TIMES),
		GMP_GMDT_IN, player_info->heart_info.times));

	//添加HeartbeatInterval节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_HEARTBEAT_INTERVAL, strlen(CP_APP_STR_HEARTBEAT_INTERVAL),
		GMP_GMDT_IN, player_info->heart_info.interval_ms));

	interface_gmdu = make_gmf_interfaces(gmf, &(player_info->network));
	if (!interface_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_register error make_gmf_interfaces() failed!");
		return CP_NULL;
	}

	information_gmdu = make_gmf_register_information(gmf, player_info);
	if (!information_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_register error make_gmf_register_information() failed!");
		return CP_NULL;
	}

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, information_gmdu);

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, interface_gmdu);

	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	return object_gmdu;
}




gmp_gmdu_t *make_gmf_life_heart(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_char_t *error_buf, cp_int32_t len)
{

	gmp_gmdu_t						*object_gmdu;
	gmp_gmdu_t						*host_gmdu;
	gmp_gmdu_t						*interface_gmdu;
	gmp_gmdu_t						*information_gmdu;



	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_life_heart error gmp_create_gmdu() failed!");
		return CP_NULL;
	}

	host_gmdu = make_gmf_host(gmf, &(player_info->host));
	if (!host_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_register error make_gmf_host() failed!");
		return CP_NULL;
	}

	//添加HeartbeatTimes节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_HEARTBEAT_TIMES, strlen(CP_APP_STR_HEARTBEAT_TIMES),
		GMP_GMDT_IN, player_info->heart_info.times));

	//添加HeartbeatInterval节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_HEARTBEAT_INTERVAL, strlen(CP_APP_STR_HEARTBEAT_INTERVAL),
		GMP_GMDT_IN, player_info->heart_info.interval_ms));

	interface_gmdu = make_gmf_interfaces(gmf, &(player_info->network));
	if (!interface_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_register error make_gmf_interfaces() failed!");
		return CP_NULL;
	}

	information_gmdu = make_gmf_life_heart_information(gmf, player_info);
	if (!information_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_register error make_gmf_life_heart_information() failed!");
		return CP_NULL;
	}

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, interface_gmdu);

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, information_gmdu);

	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	return object_gmdu;
}

gmp_gmdu_t *make_gmf_log_info(gmp_gmf_t *gmf, cp_log_info_t *log_info, cp_char_t *error_buf, cp_int32_t len)
{
	cp_char_t								tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_char_t								emh_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t								*log_gmdu = CP_NULL;
	gmp_gmdu_t								*gmdu = CP_NULL;


	//清空缓存
	cp_memset(error_buf, 0, len);

	//创建Log主节点
	log_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_LOG, cp_strlen(CP_APP_STR_LOG), GMP_GMDT_O);
	if (!log_gmdu) {
		cp_snprintf(error_buf, len - 1, "gmp_create_gmdu "CP_APP_STR_LOG" error!");
		return CP_NULL;
	}

	//添加FileName节点
	gmp_add_gmdu_child_gmdu(gmf, log_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_FILE_NAME, cp_strlen(CP_APP_STR_FILE_NAME),
		GMP_GMDT_ST, log_info->file_name, cp_strlen(log_info->file_name)));

	//添加FileExtension节点
	gmp_add_gmdu_child_gmdu(gmf, log_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_FILE_EXTENSION, cp_strlen(CP_APP_STR_FILE_EXTENSION),
		GMP_GMDT_ST, log_info->file_extension, cp_strlen(log_info->file_extension)));

	//添加FilePath节点
	gmp_add_gmdu_child_gmdu(gmf, log_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_FILE_PATH, cp_strlen(CP_APP_STR_FILE_PATH),
		GMP_GMDT_ST, log_info->file_path, cp_strlen(log_info->file_path)));

	//添加FileSize节点
	gmp_add_gmdu_child_gmdu(gmf, log_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_FILE_SIZE, cp_strlen(CP_APP_STR_FILE_SIZE),
		GMP_GMDT_UIN, log_info->file_size));

	//添加FileCreateTime节点
	gmp_add_gmdu_child_gmdu(gmf, log_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d%d%d%d%d%d%d%d",
		GMP_GMDT_ST, CP_APP_STR_FILE_CREATE_TIME, cp_strlen(CP_APP_STR_FILE_CREATE_TIME),
		GMP_GMDT_RP,
		log_info->file_create_time.x1,
		log_info->file_create_time.y1,
		log_info->file_create_time.x2,
		log_info->file_create_time.y2,
		log_info->file_create_time.x3,
		log_info->file_create_time.y3,
		log_info->file_create_time.x4,
		log_info->file_create_time.y4
		));

	//添加FileModifyTime节点
	gmp_add_gmdu_child_gmdu(gmf, log_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d%d%d%d%d%d%d%d",
		GMP_GMDT_ST, CP_APP_STR_FILE_MODIFY_TIME, cp_strlen(CP_APP_STR_FILE_MODIFY_TIME),
		GMP_GMDT_RP,
		log_info->file_modify_time.x1,
		log_info->file_modify_time.y1,
		log_info->file_modify_time.x2,
		log_info->file_modify_time.y2,
		log_info->file_modify_time.x3,
		log_info->file_modify_time.y3,
		log_info->file_modify_time.x4,
		log_info->file_modify_time.y4
		));

/*
	if (log_info->file_data_p)
	{
		tmp_file_data_p = (pc_flag_buf_p)log_info->file_data_p;
		//添加FileData节点
		gmp_add_gmdu_child_gmdu(gmf, log_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_FILE_DATA, cp_strlen(CP_APP_STR_FILE_DATA),
			GMP_GMDT_IOB, tmp_file_data_p->m_pos_p, tmp_file_data_p->size()));
	}
*/

	return log_gmdu;
}



gmp_gmdu_t *make_gmf_exceptions(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_exception_info_t *ex_info, cp_char_t *error_buf, cp_int32_t len)
{
	cp_char_t						tmp_error_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	gmp_gmdu_t						*object_gmdu = CP_NULL;
	gmp_gmdu_t						*host_gmdu = CP_NULL;
	gmp_gmdu_t						*exceptions_gmdu = CP_NULL;


	if (!gmf) {
		return CP_NULL;
	}

	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_sprintf(error_buf, "make_gmf_exceptions error reason gmp_create_gmdu root element error!");
		return CP_NULL;
	}

	host_gmdu = make_gmf_host(gmf, &(player_info->host));
	if (!host_gmdu) {
		cp_sprintf(error_buf, "make_gmf_exceptions error reason make_gmf_host() failed!");
		return CP_NULL;
	}

	exceptions_gmdu = make_gmf_exception(gmf, ex_info, tmp_error_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (!exceptions_gmdu) {
		cp_sprintf(error_buf, "make_gmf_exceptions error make_gmf_exception() reason %s", tmp_error_buf);
		return CP_NULL;
	}

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, exceptions_gmdu);

	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	return object_gmdu;
}




gmp_gmdu_t *make_gmf_exception(gmp_gmf_t *gmf, cp_exception_info_t *ex_info, cp_char_t *error_buf, cp_int32_t len)
{
	gmp_gmdu_t						*exceptions_gmdu = CP_NULL;
	gmp_gmdu_t						*exception_gmdu = CP_NULL;
	gmp_gmdu_t						*media_info_gmdu = CP_NULL;


	//创建Exceptions节点
	exceptions_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST, CP_APP_STR_EXCEPTIONS, 
		cp_strlen(CP_APP_STR_EXCEPTIONS), GMP_GMDT_A);
	if (!exceptions_gmdu) {
		cp_sprintf(error_buf, "make_gmf_exception error gmp_create_gmdu() %s element error!", CP_APP_STR_EXCEPTIONS);
		return CP_NULL;
	}

	//创建Exception主节点
	exception_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST, CP_APP_STR_EXCEPTION, 
		cp_strlen(CP_APP_STR_EXCEPTION), GMP_GMDT_O);
	if (!exception_gmdu) {
		cp_sprintf(error_buf, "make_gmf_exception error gmp_create_gmdu() %s element error!", CP_APP_STR_EXCEPTION);
		return CP_NULL;
	}

	gmp_add_gmdu_child_gmdu(gmf, exception_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_STATUS, strlen(CP_APP_STR_STATUS),
		GMP_GMDT_IN, ex_info->status));

	gmp_add_gmdu_child_gmdu(gmf, exception_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_PRIVATE_STATUS, strlen(CP_APP_STR_PRIVATE_STATUS),
		GMP_GMDT_IN, ex_info->private_status));

	gmp_add_gmdu_child_gmdu(gmf, exception_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_TIME, strlen(CP_APP_STR_TIME),
		GMP_GMDT_UL, ex_info->time));

	gmp_add_gmdu_child_gmdu(gmf, exception_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_DESCRIPTION, strlen(CP_APP_STR_DESCRIPTION),
		GMP_GMDT_ST, ex_info->description, strlen(ex_info->description)));

	media_info_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_INFORMATION, strlen(CP_APP_STR_INFORMATION), GMP_GMDT_O);
	if (!media_info_gmdu) {
		cp_sprintf(error_buf, "make_gmf_exception error gmp_create_gmdu() %s element error!", CP_APP_STR_INFORMATION);
		return CP_NULL;
	}

	if (ex_info->media_exception_type) {
		//添playsession节点
		gmp_add_gmdu_child_gmdu(gmf, media_info_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_PLAYSESSION, strlen(CP_APP_STR_PLAYSESSION),
			GMP_GMDT_ST, ex_info->play_session, strlen(ex_info->play_session)));

		//添媒体ID节点
		gmp_add_gmdu_child_gmdu(gmf, media_info_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_ID, strlen(CP_APP_STR_ID),
			GMP_GMDT_ST, ex_info->meidia_id, strlen(ex_info->meidia_id)));

		//添channelid 节点
		gmp_add_gmdu_child_gmdu(gmf, media_info_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
			GMP_GMDT_ST, CP_APP_STR_CHANNELID, strlen(CP_APP_STR_CHANNELID),
			GMP_GMDT_UIN, ex_info->index));
	}

	gmp_add_gmdu_child_gmdu(gmf, exception_gmdu, media_info_gmdu);
	gmp_add_gmdu_child_gmdu(gmf, exceptions_gmdu, exception_gmdu);

	return exceptions_gmdu;
}


gmp_gmdu_t *make_gmf_get_dev_info_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_char_t *error_buf, cp_int32_t len)
{
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	gmp_gmdu_t							*host_gmdu;
	gmp_gmdu_t							*interface_gmdu;
	gmp_gmdu_t							*information_gmdu;



	//创建Object节点
	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_sprintf(error_buf, "%s", "make gmf get dev info return error gmp_create_gmdu() failed!");
		return CP_NULL;
	}

	//创建Host节点
	host_gmdu = make_gmf_host(gmf, &(player_info->host));
	if (!host_gmdu) {
		cp_sprintf(error_buf, "%s", "make gmf get dev info return error make_gmf_host() failed!");
		return CP_NULL;
	}

	//创建Interface节点
	interface_gmdu = make_gmf_interfaces(gmf, &(player_info->network));
	if (!interface_gmdu) {
		cp_sprintf(error_buf, "%s", "make gmf interfaces return error make_gmf_host() failed!");
		return CP_NULL;
	}

	//创建Information节点
	information_gmdu = make_gmf_register_information(gmf, player_info);
	if (!information_gmdu) {
		cp_sprintf(error_buf, "%s", "make gmf interfaces return error make_gmf_register_information() failed!");
		return CP_NULL;
	}

	//向host节点中添加interface内容
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, interface_gmdu);

	//向host节点中添加information内容
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, information_gmdu);

	//向Object节点中添加Host内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	//向Object节点中添加Status内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_STATUS, cp_strlen(CP_APP_STR_STATUS),
		GMP_GMDT_IN, GMP_NORMAL_STATUS_200));

	//向Object节点中添加Reason内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_REASON, cp_strlen(CP_APP_STR_REASON),
		GMP_GMDT_ST, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED)));

	//向Object节点中添加Return内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T",
		GMP_GMDT_ST, CP_APP_STR_RETURN, cp_strlen(CP_APP_STR_RETURN),
		GMP_GMDT_N));

	return object_gmdu;
}



gmp_gmdu_t *make_gmf_get_log_info_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_log_info_t *log_info, cp_char_t *error_buf, cp_int32_t len)
{
	cp_char_t							buf[CP_APP_DEFAULT_ERROR_TEXT_BUFFER_LEN] = { 0, };
	gmp_gmdu_t							*object_gmdu = CP_NULL;
	gmp_gmdu_t							*host_gmdu;
	gmp_gmdu_t							*devices_gmdu;
	gmp_gmdu_t							*device_gmdu;
	gmp_gmdu_t							*logs_gmdu;



	//创建Object节点
	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_sprintf(error_buf, "%s", "make gmf get dev info return error gmp_create_gmdu() failed!");
		return CP_NULL;
	}

	//创建Host节点
	host_gmdu = make_gmf_host(gmf, &(player_info->host));
	if (!host_gmdu) {
		cp_sprintf(error_buf, "%s", "make gmf get dev info return error make_gmf_host() failed!");
		return CP_NULL;
	}

	//创建Devices主节点
	devices_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES), GMP_GMDT_A);
	if (!devices_gmdu) {
		cp_snprintf(error_buf, len - 1, "gmp_create_gmdu "CP_APP_STR_DEVICES" error!");
		return CP_NULL;
	}

	//创建Device主节点
	device_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_DEVICE, cp_strlen(CP_APP_STR_DEVICE), GMP_GMDT_O);
	if (!device_gmdu) {
		cp_snprintf(error_buf, len - 1, "gmp_create_gmdu "CP_APP_STR_DEVICE" error!");
		return CP_NULL;
	}

	//添加ID节点
	gmp_add_gmdu_child_gmdu(gmf, device_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_ID, cp_strlen(CP_APP_STR_ID),
		GMP_GMDT_ST, player_info->host.id, cp_strlen(player_info->host.id)));

	//添加Flag节点
	gmp_add_gmdu_child_gmdu(gmf, device_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%UC",
		GMP_GMDT_ST, CP_APP_STR_FLAG, cp_strlen(CP_APP_STR_FLAG),
		GMP_GMDT_UC, log_info->flag));

	//创建Logs主节点
	logs_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST,
		CP_APP_STR_LOGS, cp_strlen(CP_APP_STR_LOGS), GMP_GMDT_A);
	if (!logs_gmdu) {
		cp_snprintf(error_buf, len - 1, "gmp_create_gmdu "CP_APP_STR_LOGS" error!");
		return CP_NULL;
	}

	make_gmf_log_info(gmf, log_info, buf, CP_APP_DEFAULT_ERROR_TEXT_BUFFER_LEN);

	//向Object节点中添加Status内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_STATUS, cp_strlen(CP_APP_STR_STATUS),
		GMP_GMDT_IN, GMP_NORMAL_STATUS_200));

	//向Object节点中添加Reason内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_REASON, cp_strlen(CP_APP_STR_REASON),
		GMP_GMDT_ST, GMP_RETURN_SUCCESSED, cp_strlen(GMP_RETURN_SUCCESSED)));

	//向Object节点中添加Return内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T",
		GMP_GMDT_ST, CP_APP_STR_RETURN, cp_strlen(CP_APP_STR_RETURN),
		GMP_GMDT_N));

	//向Object节点中添加Host内容
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	return object_gmdu;
}

gmp_gmdu_t *make_gmf_offline_passwd_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_return_info_t *return_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*host_gmdu;
	gmp_gmdu_t						*object_gmdu;



	if (!gmf) {
		return CP_NULL;
	}

	//清空缓存
	cp_memset(buf, 0, len);

	//创建Object主节点
	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_snprintf(buf, len - 1, "gmp_create_gmdu Object error!");
		return CP_NULL;
	}

	//创建Object主节点
	host_gmdu = gmp_create_gmdu(gmf, "%T%p%d,%T", GMP_GMDT_ST, CP_APP_STR_HOST,
		cp_strlen(CP_APP_STR_HOST), GMP_GMDT_O);
	if (!host_gmdu) {
		cp_snprintf(buf, len - 1, "gmp_create_gmdu Host error!");
		return CP_NULL;
	}

	//添加ID节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_ID, cp_strlen(CP_APP_STR_ID),
		GMP_GMDT_ST, return_info->host_id, cp_strlen(return_info->host_id)));

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_PASSWD, cp_strlen(CP_APP_STR_PASSWD),
		GMP_GMDT_ST, return_info->passwd, cp_strlen(return_info->passwd)));

	//添加Host节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	//添加Status节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_STATUS, cp_strlen(CP_APP_STR_STATUS),
		GMP_GMDT_IN, return_info->status));

	//添加Reason节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_REASON, cp_strlen(CP_APP_STR_REASON),
		GMP_GMDT_ST, return_info->reason, cp_strlen(return_info->reason)));

	//添加Return节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T",
		GMP_GMDT_ST, CP_APP_STR_RETURN, cp_strlen(CP_APP_STR_RETURN),
		GMP_GMDT_N));

	return object_gmdu;
}


gmp_gmdu_t *make_gmf_offline_information_return(gmp_gmf_t *gmf, cp_device_info_t *player_info, cp_return_info_t *return_info, 
	cp_center_addr_t *center_addr, cp_char_t *error_buf, cp_int32_t len)
{
	gmp_gmdu_t						*object_gmdu;
	gmp_gmdu_t						*host_gmdu;
	gmp_gmdu_t						*interface_gmdu;
	gmp_gmdu_t						*information_gmdu;



	object_gmdu = gmp_create_gmdu(gmf, "%T,%T", GMP_GMDT_O, GMP_GMDT_N);
	if (!object_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_offline error gmp_create_gmdu() error!");
		return CP_NULL;
	}

	host_gmdu = make_gmf_host(gmf, &(player_info->host));
	if (!host_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_offline error make_gmf_host() failed!");
		return CP_NULL;
	}

	//添加HeartbeatTimes节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_HEARTBEAT_TIMES, strlen(CP_APP_STR_HEARTBEAT_TIMES),
		GMP_GMDT_IN, player_info->heart_info.times));

	//添加HeartbeatInterval节点
	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_HEARTBEAT_INTERVAL, strlen(CP_APP_STR_HEARTBEAT_INTERVAL),
		GMP_GMDT_IN, player_info->heart_info.interval_ms));

	interface_gmdu = make_gmf_interfaces(gmf, &(player_info->network));
	if (!interface_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_offline error make_gmf_interfaces() error!");
		return CP_NULL;
	}

	information_gmdu = make_gmf_player_information(gmf, player_info, center_addr);
	if (!information_gmdu) {
		cp_sprintf(error_buf, "%s", "make_gmf_offline error make_gmf_player_information() error!");
		return CP_NULL;
	}

	//添加Return节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T",
		GMP_GMDT_ST, CP_APP_STR_RETURN, cp_strlen(CP_APP_STR_RETURN),
		GMP_GMDT_N));

	//添加Reason节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%p%d",
		GMP_GMDT_ST, CP_APP_STR_REASON, cp_strlen(CP_APP_STR_REASON),
		GMP_GMDT_ST, return_info->reason, cp_strlen(return_info->reason)));

	//添加Status节点
	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, gmp_create_gmdu(gmf, "%T%p%d,%T%d",
		GMP_GMDT_ST, CP_APP_STR_STATUS, cp_strlen(CP_APP_STR_STATUS),
		GMP_GMDT_IN, return_info->status));

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, information_gmdu);

	gmp_add_gmdu_child_gmdu(gmf, host_gmdu, interface_gmdu);

	gmp_add_gmdu_child_gmdu(gmf, object_gmdu, host_gmdu);

	return object_gmdu;
}

gmp_gmdu_t *make_gmf_media_info(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *error_buf, cp_int32_t len)
{
	return CP_NULL;
}

gmp_gmdu_t *make_gmf_channel_info(gmp_gmf_t *gmf, cp_channel_info_t *channel_info, cp_char_t *error_buf, cp_int32_t len)
{
	return CP_NULL;
}

cp_bool_t parse_gmf_return(gmp_gmf_t *gmf, cp_return_info_t *ret, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;
	cp_bool_t						ret_bool;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "null gmf error.");
		return cp_false;
	}

	//设置顶级结点
	gmp_top_gmdu(gmf);

	//进入object节点
	gmp_into_gmdu(gmf);

	//查找Host节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_HOST, cp_strlen(CP_APP_STR_HOST));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "not %s element error.", CP_APP_STR_HOST);
		return cp_false;
	}

	//重设Host节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Host节点
	gmp_into_gmdu(gmf);

	//获取ID内容
	ret_bool = get_gmf_element(gmf, ret->host_id, CP_APP_DEFAULT_ID_LENGTH - 1, GMP_GMDT_ST, CP_APP_STR_ID, buf, len);
 	if (!ret_bool) {
 		return cp_false;
 	}

	//退出Host节点
	gmp_outof_gmdu(gmf);

	//获取Status内容
	ret_bool = get_gmf_element(gmf, &(ret->status), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_STATUS, buf, len);
 	if (!ret_bool) {
 		return cp_false;
 	}

	//获取Reason内容
	ret_bool = get_gmf_element(gmf, ret->reason, CP_APP_DEFAULT_BUFFER_LENGTH - 1, GMP_GMDT_ST, CP_APP_STR_REASON, buf, len);

	return cp_true;
}

cp_bool_t parse_gmf_host(gmp_gmf_t *gmf, cp_host_t *host, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool;
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len - 1, "parse gmf host error reason: null gmf error.");
		return cp_false;
	}

	//设置当前节点为object
	gmp_top_gmdu(gmf);

	//进入object
	gmp_into_gmdu(gmf);

	//查找Host节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_HOST, cp_strlen(CP_APP_STR_HOST));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len - 1, "not "CP_APP_STR_HOST" element error.");
		return cp_false;
	}

	//设置Host节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Host节点
	gmp_into_gmdu(gmf);

	//获取ID内容
	ret_bool = get_gmf_element(gmf, host->id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len - 1, "not "CP_APP_STR_ID" element error.");
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//获取Password内容
	ret_bool = get_gmf_element(gmf, host->passwd, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_PASSWD, buf, len);

	//退出host
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t parse_gmf_host_network(gmp_gmf_t *gmf, cp_host_t *host, cp_interface_t *network, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool;
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len - 1, "parse gmf host error reason: null gmf error.");
		return cp_false;
	}

	//设置当前节点为object
	gmp_top_gmdu(gmf);

	//进入object
	gmp_into_gmdu(gmf);

	//查找Host节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_HOST, cp_strlen(CP_APP_STR_HOST));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len - 1, "not "CP_APP_STR_HOST" element error.");
		return cp_false;
	}

	//设置Host节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Host节点
	gmp_into_gmdu(gmf);

	//获取ID内容
	ret_bool = get_gmf_element(gmf, host->id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len - 1, "not "CP_APP_STR_ID" element error.");
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//获取Name内容
	ret_bool = get_gmf_element(gmf, host->name, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NAME, buf, len);

	ret_bool = get_gmf_element(gmf, host->passwd, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_PASSWD, buf, len);

	//获取Version内容
	ret_bool = get_gmf_element(gmf, host->version, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_VERSION, buf, len);

	//获取Type内容
	ret_bool = get_gmf_element(gmf, &(host->type), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_TYPE, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len - 1, "not "CP_APP_STR_TYPE" element error.");
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//解析Interface节点内容
	parse_gmf_interfaces(gmf, network, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//退出host
	gmp_outof_gmdu(gmf);

	return cp_true;
}


cp_bool_t parse_gmf_device_host(gmp_gmf_t *gmf, cp_host_t *host, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t							ret_bool;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "parse device host error reasonl: null gmf error.");
		return cp_false;
	}

	//获取ID内容
	ret_bool = get_gmf_element(gmf, host->id, CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, len);
	if (!ret_bool) {
		return cp_false;
	}

	//获取Type内容
	ret_bool = get_gmf_element(gmf, &(host->type), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_TYPE, buf, len);
	if (!ret_bool) {
		return cp_false;
	}

	//获取Name内容
	ret_bool = get_gmf_element(gmf, host->name, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NAME, buf, len);

	//获取Version内容
	ret_bool = get_gmf_element(gmf, host->version, CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, CP_APP_STR_VERSION, buf, len);

	//解析id数据
	get_host_id_detail(host, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	return cp_true;
}



cp_bool_t parse_gmf_interfaces(gmp_gmf_t *gmf, cp_interface_t *network, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdu_t						*gmdu_array;
	gmp_gmdt_t						*gmdt;
	cp_bool_t						ret_bool;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "parse gmf interfaces error reason: null gmf error.");
		return cp_false;
	}

	//查找Interfaces节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INTERFACES, cp_strlen(CP_APP_STR_INTERFACES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "not "CP_APP_STR_INTERFACES" element error.");
		return cp_false;
	}

	//重设Interface节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_char_t			used;

			//重设节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入节点*/
			gmp_into_gmdu(gmf);

			//获取Used内容
			ret_bool = get_gmf_element(gmf, &(used), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_USRD, buf, len);
			if (!ret_bool) {
				continue;
			}

			if ((int)used != 1) {
				continue;
			}else{
				network->used = used;
			}

			//获取Name内容
			ret_bool = get_gmf_element(gmf, network->name, CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, CP_APP_STR_NAME, buf, len);

			//获取IP内容
			ret_bool = get_gmf_element(gmf, network->ip, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_IP, buf, len);
			if (!ret_bool) {
				continue;
			}

			//获取TCPPort内容
			ret_bool = get_gmf_element(gmf, &(network->tcp_port), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_TCPPORT, buf, len);
			if (!ret_bool) {
				continue;
			}

			//获取UDPPort内容
			ret_bool = get_gmf_element(gmf, &(network->udp_port), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_UDPPORT, buf, len);
			if (!ret_bool) {
				continue;
			}
			break;
		}
	}

	gmp_reset_gmdu(gmf, gmdu);

	return cp_true;
}


cp_bool_t get_gmf_hardware_info(gmp_gmf_t *gmf, cp_host_t *host, cp_hardware_info_t *hardware, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t					tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t					ret_bool;
	gmdt_rectpair_p_t			*rectpair_p = CP_NULL;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf hardware info error. reason: null gmf error.");
		return cp_false;
	}

	//获取No内容
	ret_bool = get_gmf_element(gmf, &(host->no), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_UC, CP_APP_STR_NO, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Number内容
	ret_bool = get_gmf_element(gmf, &(host->number), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NUMBER, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取LimitDisk内容
	ret_bool = get_gmf_element(gmf, &(hardware->limit_disk), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_LIMITDISK, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取LimitMemory内容
	ret_bool = get_gmf_element(gmf, &(hardware->limit_memory), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_LIMITMEMORY, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取LimitCPU内容
	ret_bool = get_gmf_element(gmf, &(hardware->limit_cpu), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_LIMITCPU, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取LimitNetWork内容
	ret_bool = get_gmf_element(gmf, &(hardware->limit_network), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_LIMITNETWORK, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取LimitPlayeCount内容
	ret_bool = get_gmf_element(gmf, &(hardware->limit_play_count), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_LIMITPLAYCOUNT, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Luminance内容
	ret_bool = get_gmf_element(gmf, &(hardware->luminance), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_LUMINANCE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Contrast内容
	ret_bool = get_gmf_element(gmf, &(hardware->contrast), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_CONTRAST, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取ColorTemperature内容
	ret_bool = get_gmf_element(gmf, &(hardware->color_temp), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_COLORTEMPERATURE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取BackColor内容
	ret_bool = get_gmf_element(gmf, hardware->background_color, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_BACKCOLOR, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Switch内容
	ret_bool = get_gmf_element(gmf, &(hardware->cctv_switch), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_IN, CP_APP_STR_SWITCH, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Size内容
	ret_bool = get_gmf_element(gmf, &(hardware->cctv_size), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_SIZE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	if (!parse_gmf_resolution_size(gmf, &(hardware->resolution_width), &(hardware->resolution_height), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		cp_snprintf(buf, len, "get gmf hardware info error. parse_gmf_resolution_size() %s", tmp_buf);
	}

	//获取Border
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, CP_APP_STR_BORDER, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool && rectpair_p) {
		hardware->border_size.top = *(rectpair_p->x1);
		hardware->border_size.left = *(rectpair_p->y1);
		hardware->border_size.top = *(rectpair_p->x2);
		hardware->border_size.right = *(rectpair_p->y2);
		hardware->border_size.bottom = *(rectpair_p->x3);
		hardware->border_size.left = *(rectpair_p->y3);
		hardware->border_size.bottom = *(rectpair_p->x4);
		hardware->border_size.right = *(rectpair_p->y4);
	}

	return cp_true;
}


cp_bool_t get_gmf_background_player_info(gmp_gmf_t *gmf, cp_player_background_info_t *player_background_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t							tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t							*info_gmdu = CP_NULL;
	gmp_gmdu_t							*devs_gmdu = CP_NULL;
	gmp_gmdu_t							*gmdu_array = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	gmp_gmdt_t							*info_gmdt = CP_NULL;
	gmp_gmdt_t							*devs_gmdt = CP_NULL;



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Information节点
	info_gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	info_gmdu = gmp_find_gmdu(gmf, info_gmdt);
	if (!info_gmdu) {
		cp_snprintf(buf, len, "get gmf background player info error. reason: not "CP_APP_STR_INFORMATION" element error.");
		return cp_false;
	}

	//设置Information节点
	gmp_reset_gmdu(gmf, info_gmdu);

	//进入Information
	gmp_into_gmdu(gmf);

	//查找Devices节点
	devs_gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	devs_gmdu = gmp_find_gmdu(gmf, devs_gmdt);
	if (!devs_gmdu) {
		cp_snprintf(buf, len, "get gmf background player info error. reason: not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, devs_gmdu);

	gmdt = gmp_get_gmdt(gmf, devs_gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//解析Host节点内容
			if (!parse_gmf_device_host(gmf, &(player_background_info->host_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_snprintf(buf, len, "get gmf background player info error. reason: %s", tmp_buf);
				return cp_true;
			}

			//获取当前设备信息
			if (!get_gmf_background_information(gmf, player_background_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_snprintf(buf, len, "get gmf background player info error. reason: get_gmf_background_information() error.");
				return cp_false;
			}

			//解析媒体信息
			if (!get_gmf_background_medias_info(gmf, &(player_background_info->media_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_snprintf(buf, len, "get gmf background player info error. reason: get_gmf_background_medias_info() error.");
				return cp_false;
			}
			break;
		}
	}

	//回到根节点
	gmp_top_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_background_information(gmp_gmf_t *gmf, cp_player_background_info_t *background_device_media_info, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool = cp_false;
	gmdt_rectpair_p_t				*rectpair_p = CP_NULL;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	//查找Information节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf background information error. not "CP_APP_STR_INFORMATION" element error.");
		return cp_false;
	}

	//设置Information节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Information节点
	gmp_into_gmdu(gmf);

	//获取Border内容
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, CP_APP_STR_BORDER, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool && rectpair_p) {
		background_device_media_info->border.x1 = *(rectpair_p->x1);
		background_device_media_info->border.y1 = *(rectpair_p->y1);
		background_device_media_info->border.x2 = *(rectpair_p->x2);
		background_device_media_info->border.y2 = *(rectpair_p->y2);
		background_device_media_info->border.x3 = *(rectpair_p->x3);
		background_device_media_info->border.y3 = *(rectpair_p->y3);
		background_device_media_info->border.x4 = *(rectpair_p->x4);
		background_device_media_info->border.y4 = *(rectpair_p->y4);
	}

#if 0
	//获取Size内容
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, CP_APP_STR_SIZE, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool && rectpair_p) {
		background_device_media_info->size.x1 = *(rectpair_p->x1);
		background_device_media_info->size.y1 = *(rectpair_p->y1);
		background_device_media_info->size.x2 = *(rectpair_p->x2);
		background_device_media_info->size.y2 = *(rectpair_p->y2);
		background_device_media_info->size.x3 = *(rectpair_p->x3);
		background_device_media_info->size.y3 = *(rectpair_p->y3);
		background_device_media_info->size.x4 = *(rectpair_p->x4);
		background_device_media_info->size.y4 = *(rectpair_p->y4);
	}

	//获取BackColor内容
	ret_bool = get_gmf_element(gmf, &(background_device_media_info->backcolor), CP_APP_DEFAULT_DOUBLE_LENGTH, GMP_GMDT_ST, CP_PLYAER_STR_BACK_COLOR, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取IsSet内容
	ret_bool = get_gmf_element(gmf, &(background_device_media_info->is_set), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_PLYAER_STR_IS_SET, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
#endif 

	return cp_true;
}

cp_bool_t get_gmf_background_player_reflesh_info(gmp_gmf_t *gmf, cp_player_background_info_t *player_background_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						  tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t						  *devs_gmdu = CP_NULL;
	gmp_gmdu_t						  *gmdu_array = CP_NULL;
	gmp_gmdt_t						  *gmdt = CP_NULL;
	gmp_gmdt_t						  *devs_gmdt = CP_NULL;



	//查找Devices节点
	devs_gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	devs_gmdu = gmp_find_gmdu(gmf, devs_gmdt);
	if (!devs_gmdu) {
		cp_snprintf(buf, len - 1, "get gmf background devices reflesh info error. not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, devs_gmdu);

	gmdt = gmp_get_gmdt(gmf, devs_gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//获取host信息
			if (!parse_gmf_device_host(gmf, &(player_background_info->host_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_snprintf(buf, len, "get gmf background devices reflesh info error. reason: %s", tmp_buf);
				return cp_true;
			}

			//获取information信息
			if (!get_gmf_background_information(gmf, player_background_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_snprintf(buf, len, "get gmf background devices reflesh info error. reason: %s", tmp_buf);
				return cp_false;
			}

			//获取reflresh信息
			if (!get_gmf_background_reflesh_info(gmf, &(player_background_info->reflesh_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_snprintf(buf, len, "get gmf background devices reflesh info error. reason: %s", tmp_buf);
				return cp_false;
			}
			break;
		}
	}

	//回到根节点
	gmp_top_gmdu(gmf);

	return cp_true;
}


cp_bool_t get_gmf_background_reflesh_info(gmp_gmf_t *gmf, cp_background_reflesh_info_t *reflesh_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Medias节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_MEDIAS, cp_strlen(CP_APP_STR_MEDIAS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf background device reflesh medias info error. not "CP_APP_STR_MEDIAS" element error.");
		return cp_false;
	}

	//设置Medias节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {

			//设置Media节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Media节点
			gmp_into_gmdu(gmf);

			//解析Media节点信息
			ret_bool = get_gmf_background_child_reflesh_info(gmf, reflesh_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (ret_bool) {
				break;
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_background_child_reflesh_info(gmp_gmf_t *gmf, cp_background_reflesh_info_t *reflesh_media_info, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t					ret_bool = cp_false;
	gmdt_rectpair_p_t			*rectpair_p = CP_NULL;



	//获取Type内容
	ret_bool = get_gmf_element(gmf, &(reflesh_media_info->type), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_TYPE, buf, len);

	//获取图片编码
	ret_bool = get_gmf_element(gmf, &(reflesh_media_info->background), cp_sizeof(reflesh_media_info->background), GMP_GMDT_ST, 
		CP_PLYAER_STR_BACKGROUND, buf, len);

	//获取size内容
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, CP_APP_STR_SIZE, buf, len);
	if (ret_bool && rectpair_p) {
		reflesh_media_info->size.x1 = *(rectpair_p->x1);
		reflesh_media_info->size.y1 = *(rectpair_p->y1);
		reflesh_media_info->size.x2 = *(rectpair_p->x2);
		reflesh_media_info->size.y2 = *(rectpair_p->y2);
		reflesh_media_info->size.x3 = *(rectpair_p->x3);
		reflesh_media_info->size.y3 = *(rectpair_p->y3);
		reflesh_media_info->size.x4 = *(rectpair_p->x4);
		reflesh_media_info->size.y4 = *(rectpair_p->y4);
	}

	//获取reflesh_time内容
	rectpair_p = CP_NULL;
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, CP_APP_STR_SIZE, buf, len);
	if (ret_bool && rectpair_p) {
		reflesh_media_info->reflesh_time.x1 = *(rectpair_p->x1);
		reflesh_media_info->reflesh_time.y1 = *(rectpair_p->y1);
		reflesh_media_info->reflesh_time.x2 = *(rectpair_p->x2);
		reflesh_media_info->reflesh_time.y2 = *(rectpair_p->y2);
		reflesh_media_info->reflesh_time.x3 = *(rectpair_p->x3);
		reflesh_media_info->reflesh_time.y3 = *(rectpair_p->y3);
		reflesh_media_info->reflesh_time.x4 = *(rectpair_p->x4);
		reflesh_media_info->reflesh_time.y4 = *(rectpair_p->y4);
	}

	return cp_true;
}


cp_bool_t get_gmf_background_medias_info(gmp_gmf_t *gmf, cp_background_media_info_t *background_meidas_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;




	//清空缓存
	cp_memset(buf, 0, len);

	//查找Medias节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_MEDIAS, cp_strlen(CP_APP_STR_MEDIAS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf background medias info error.not "CP_APP_STR_MEDIAS" element error.");
		return cp_false;
	}

	//设置Medias节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			//设置Media节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Media节点
			gmp_into_gmdu(gmf);

			ret_bool = get_gmf_background_media_info(gmf, background_meidas_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (ret_bool) {
				break;
			}
		}
	}

	return cp_true;
}


cp_bool_t get_gmf_background_media_info(gmp_gmf_t *gmf, cp_background_media_info_t *background_meidas_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	gmdt_rectpair_p_t				*rectpair_p = CP_NULL;
	gmdt_iobuffer_p_t				*iob_p = CP_NULL;



	//获取ID内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->id), CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf background media info error. not "CP_APP_STR_ID" element error.");
		return cp_false;
	}

	//获取Type内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->type), CP_APP_DEFAULT_CHAR_LENGTH,  
		GMP_GMDT_UC, CP_APP_STR_TYPE, buf, len);

	//获取Layer内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->layer), CP_APP_DEFAULT_CHAR_LENGTH, 
		GMP_GMDT_UC, CP_APP_STR_LAYER, buf, len);

	//获取Picture内容
	ret_bool = get_gmf_element(gmf, &iob_p, cp_sizeof(gmdt_iobuffer_p_t), 
		GMP_GMDT_IOB, CP_APP_STR_PICTURE, buf, len);
	if (ret_bool && iob_p) {
		if (*(iob_p->len) > 0) {
			background_meidas_info->picture_p = (cp_uchar_t *)cp_malloc(*(iob_p->len));
			if (background_meidas_info->picture_p) {
				cp_memcpy(background_meidas_info->picture_p, iob_p->data, *(iob_p->len));
			}
		}
	}

	//获取BackColor内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->back_color), CP_APP_DEFAULT_INT_LENGTH, 
		GMP_GMDT_ST, CP_PLYAER_STR_BACK_COLOR, buf, len);
	if (ret_bool && cp_strlen(background_meidas_info->back_color) == 6) {
		parse_string_color_value(background_meidas_info->back_color, 4, background_meidas_info->back_color);
	}
#if 0
	//获取Rows内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->rows), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_ROWS, buf, len);

	//获取Columns内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->columns), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_COLUMNS, buf, len);

	//获取ContentDiaphanity内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content_diaphanity), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_CONTENTDIAPHANITY, buf, len);

	//获取ContentStyle内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content_style), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_CONTENTSTYLE, buf, len);

	//获取ContentEncode内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content_encode), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_CONTENTENCODE, buf, len);

	//获取BackDiaphanity内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->back_diaphanity), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_BACKDIAPHANITY, buf, len);

	//获取ContentFontSize内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content_font_size), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_CONTENTFONTSIZE, buf, len);

	//获取ContentSpace内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content_space), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_CONTENTSPACE, buf, len);

	//获取RulerHeight内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->ruler_height), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_F, CP_APP_STR_RULERHEIGHT, buf, len);

	//获取RulerWidth内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->ruler_width), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_F, CP_APP_STR_RULERWIDTH, buf, len);

	//获取Content内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content), cp_strlen(background_meidas_info->content), GMP_GMDT_ST, CP_APP_STR_CONTENT, buf, len);

	//获取ContentFont内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content_font), cp_strlen(background_meidas_info->content_font), GMP_GMDT_ST, CP_APP_STR_CONTENTFONT, buf, len);

	//获取ContentColor内容
	ret_bool = get_gmf_element(gmf, &(background_meidas_info->content_color), cp_strlen(background_meidas_info->content_color), GMP_GMDT_ST, CP_APP_STR_CONTENTCOLOR, buf, len);
	if (ret_bool &&  cp_strlen(background_meidas_info->content_color) == 6) {
		parse_string_color_value(background_meidas_info->content_color, 4,  background_meidas_info->content_color);
	}
#endif
	//获取size内容
	rectpair_p = CP_NULL;
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, CP_APP_STR_SIZE, buf, len);
	if (ret_bool && rectpair_p) {
		background_meidas_info->size.x1 = *(rectpair_p->x1);
		background_meidas_info->size.y1 = *(rectpair_p->y1);
		background_meidas_info->size.x2 = *(rectpair_p->x2);
		background_meidas_info->size.y2 = *(rectpair_p->y2);
		background_meidas_info->size.x3 = *(rectpair_p->x3);
		background_meidas_info->size.y3 = *(rectpair_p->y3);
		background_meidas_info->size.x4 = *(rectpair_p->x4);
		background_meidas_info->size.y4 = *(rectpair_p->y4);
	}

	return cp_true;
}

cp_bool_t get_gmf_play_information(gmp_gmf_t *gmf, list_node **media_channel_list, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//清空缓存
	cp_memset(buf, 0, len);

	//查找PlayInformation节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_PLAY_INFORMATION, cp_strlen(CP_APP_STR_PLAY_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play information error. not "CP_APP_STR_PLAY_INFORMATION" element error.");
		return cp_false;
	}

	//设置PlayInformation节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入PlayInformation节点
	gmp_into_gmdu(gmf);

	//解析Medias节点内容
	return get_gmf_play_media_channel_info(gmf, media_channel_list, buf, len);
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_gmf_play_meida_channel_size
*
* 函数说明: 获取媒体通道的数量
*
* 参    数: gmp_gmf_t * gmf						[in]参数说明
* 参    数: cp_char_t * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-21 16:03:00
******************************************************************************************************/
cp_int32_t get_gmf_play_meida_channel_size(gmp_gmf_t *gmf, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Medias节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_MEDIAS, cp_strlen(CP_APP_STR_MEDIAS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play media channel info error. not "CP_APP_STR_MEDIAS" element error.");
		return cp_false;
	}
	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		return *(((gmdt_array_p_t*)gmdt)->nelts);
	}

	return 0;
}

cp_bool_t get_gmf_play_media_channel_array(gmp_gmf_t *gmf, cp_array_t *mci_array, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	cp_media_channel_info_t			media_channel_info = { 0, };



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Medias节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_MEDIAS, cp_strlen(CP_APP_STR_MEDIAS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play media channel info error. not "CP_APP_STR_MEDIAS" element error.");
		return cp_false;
	}

	//设置Medias节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_memset(&media_channel_info, 0, cp_sizeof(cp_media_channel_info_t));

			//设置Media节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Media节点
			gmp_into_gmdu(gmf);

			//解析Media节点信息，并添加入Child 列表中
			if (get_gmf_play_child_media_channel_info(gmf, &media_channel_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_array_set_back(mci_array, &media_channel_info);
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_play_media_channel_info(gmp_gmf_t *gmf, list_node **medias_channel_list, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	cp_media_channel_info_t			*media_channel_info = CP_NULL;



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Medias节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_MEDIAS, cp_strlen(CP_APP_STR_MEDIAS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play media channel info error. not "CP_APP_STR_MEDIAS" element error.");
		return cp_false;
	}

	//设置Medias节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			media_channel_info = (cp_media_channel_info_t *)cp_malloc(cp_sizeof(cp_media_channel_info_t));

			if (media_channel_info) {
				cp_memset(media_channel_info, 0, cp_sizeof(cp_media_channel_info_t));
			}else{
				cp_snprintf(buf, len, "get gmf play media channel info error. reason: malloc media channel error");
				break;
			}

			//设置Media节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Media节点
			gmp_into_gmdu(gmf);

			//解析Media节点信息，并添加入Child 列表中
			if (get_gmf_play_child_media_channel_info(gmf, media_channel_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				if (!(*medias_channel_list)) {
					*medias_channel_list = list_create(media_channel_info);
				}else{
					list_insert_after(*medias_channel_list, media_channel_info);
				}
			}
		}
	}

/*
	//设置Medias节点
	gmp_reset_gmdu(gmf, gmdu);

	//表示退出Medias节点
	gmp_outof_gmdu(gmf);*/

	return cp_true;
}


cp_bool_t get_gmf_play_child_media_channel_info(gmp_gmf_t *gmf, cp_media_channel_info_t *media_channel_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//获取GroupID内容
	ret_bool = get_gmf_element(gmf, &(media_channel_info->group_id), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_GROUPID, buf, len);

	ret_bool = get_gmf_media_info(gmf, &(media_channel_info->media_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf play child media channel info error. reason: get_gmf_media_info() %s", tmp_buf);
		return cp_false;
	}

	ret_bool = get_gmf_channel_info(gmf, &(media_channel_info->channel_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf play child media channel info error. reason: get_gmf_media_info() %s", tmp_buf);
		return cp_false;
	}
	
	return cp_true;
}


cp_bool_t get_gmf_media_info(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool = cp_false;
	gmdt_rectpair_p_t				*rectpair_p = CP_NULL;



	//获取ID内容
	ret_bool = get_gmf_element(gmf, media_info->id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf media info error. reason: not "CP_APP_STR_ID"element error");
		return cp_false;
	}

	//获取Name内容
	ret_bool = get_gmf_element(gmf, media_info->name, CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, CP_APP_STR_NAME, buf, len);

	//获取Type内容
	ret_bool = get_gmf_element(gmf, &(media_info->type), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_TYPE, buf, len);

	//视频信息
	//获取Height内容
	ret_bool = get_gmf_element(gmf, &(media_info->video_source.height), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_HEIGHT, buf, len);

	//获取Width内容
	ret_bool = get_gmf_element(gmf, &(media_info->video_source.width), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_WIDTH, buf, len);

	//获取Fps内容
	ret_bool = get_gmf_element(gmf, &(media_info->video_source.fps), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_UC, CP_APP_STR_FPS, buf, len);

	//获取Addr内容
	ret_bool = get_gmf_element(gmf, (media_info->addr), CP_APP_DEFAULT_BUFFER_LENGTH, GMP_GMDT_ST, CP_APP_STR_ADDR, buf, len);

	//音频信息
	//获取BitRate内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.bit_rate), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_BIT_RATE, buf, len);

	//获取SampleRate内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.sample_rate), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_SAMPLE_RATE, buf, len);

	//获取SoundChannelName内容
	ret_bool = get_gmf_element(gmf, media_info->audio_source.sound_channel_name, CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, CP_APP_STR_SOUND_CHANNEL_NAME, buf, len);

	//获取SoundChannelType内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.sound_channel_type), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_SOUND_CHANNEL_TYPE, buf, len);

	//获取Volume内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.volume), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_VOLUME, buf, len);

	ret_bool = get_gmf_audio_source(gmf, media_info, buf, len);

	ret_bool = get_gmf_video_source(gmf, media_info, buf, len);

	return cp_true;
}

cp_bool_t get_gmf_video_source(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*current_gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//清空缓存
	cp_memset(buf, 0, len);
	current_gmdu = gmf->current_gmdu;

	//查找VideoSource节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_VIDEO_SOURCE, cp_strlen(CP_APP_STR_VIDEO_SOURCE));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf video source error. not "CP_APP_STR_VIDEO_SOURCE" element error.");
		return cp_false;
	}

	//设置VideoSource节点
	//gmp_reset_gmdu(gmf, gmdu);

	gmp_reset_gmdu(gmf, current_gmdu);

	return cp_true;
}

cp_bool_t get_gmf_audio_source(gmp_gmf_t *gmf, cp_media_info_t *media_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*current_gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//清空缓存
	cp_memset(buf, 0, len);
	current_gmdu = gmf->current_gmdu;

	//查找AudioSource节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_AUDIO_SOURCE, cp_strlen(CP_APP_STR_AUDIO_SOURCE));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf video source error. not "CP_APP_STR_AUDIO_SOURCE" element error.");
		return cp_false;
	}

	//设置AudioSource节点
	gmp_reset_gmdu(gmf, gmdu);

	gmp_into_gmdu(gmf);

	//音频信息
	//获取BitRate内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.bit_rate), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_BIT_RATE, buf, len);

	//获取SampleRate内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.sample_rate), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_SAMPLE_RATE, buf, len);

	//获取SoundChannelName内容
	ret_bool = get_gmf_element(gmf, media_info->audio_source.sound_channel_name, CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, CP_APP_STR_SOUND_CHANNEL_NAME, buf, len);

	//获取SoundChannelType内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.sound_channel_type), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_SOUND_CHANNEL_TYPE, buf, len);

	//获取Volume内容
	ret_bool = get_gmf_element(gmf, &(media_info->audio_source.volume), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_VOLUME, buf, len);

	gmp_outof_gmdu(gmf);

	gmp_reset_gmdu(gmf, current_gmdu);

	return cp_true;
}

cp_bool_t get_gmf_channel_info(gmp_gmf_t *gmf, cp_channel_info_t *channel_info, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmdt_rectpair_p_t				*rectpair_p = CP_NULL;



	//获取PlaySession内容
	ret_bool = get_gmf_element(gmf, channel_info->play_session, CP_APP_DEFAULT_SESSION_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_PLAYSESSION, buf, len);

	//获取ChannelID内容
	ret_bool = get_gmf_element(gmf, &(channel_info->index), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_CHANNELID, buf, len);

	//获取Multicast内容
	ret_bool = get_gmf_multicast_info(gmf, &(channel_info->multicast_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取PlayAddress
	ret_bool = get_gmf_play_address_info(gmf, &(channel_info->play_addr_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Position内容
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rect_p_t), GMP_GMDT_RP, CP_APP_STR_POSITION, buf, len);
	if (ret_bool && rectpair_p) {
		cp_std_convert_position(rectpair_p, &channel_info->position);
	}

	//获取Layer内容
	ret_bool = get_gmf_element(gmf, &(channel_info->layer), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_LAYER, buf, len);

	return cp_true;
}

cp_bool_t get_gmf_play_information_info(gmp_gmf_t *gmf, list_node **group_list, cp_play_channel_info_t *pc_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	//设置当前节点为object
	gmp_top_gmdu(gmf);

	//进入object
	gmp_into_gmdu(gmf);

	//查找Infomation节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play information info error. not "CP_APP_STR_INFORMATION" element error.");
		return cp_false;
	}

	//设置Information节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Information节点
	gmp_into_gmdu(gmf);

	ret_bool = get_gmf_play_cmd_info(gmf, pc_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	ret_bool = get_gmf_play_groups_info(gmf, group_list, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf play information info error. reason: get_gmf_play_groups_info() %s", tmp_buf);
		return cp_false;
	}

	return cp_true;
}

cp_bool_t get_gmf_play_groups_info(gmp_gmf_t *gmf, list_node **group_list, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_media_group_info_t			*group_info_p = CP_NULL;



	//查找Groups节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_GROUPS, cp_strlen(CP_APP_STR_GROUPS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play groups info error. not "CP_APP_STR_GROUPS" element error.");
		return cp_false;
	}

	//设置Groups节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			group_info_p = (cp_media_group_info_t *)cp_malloc(cp_sizeof(cp_media_group_info_t));
			if (group_info_p) {
				cp_memset(group_info_p, 0, cp_sizeof(cp_media_group_info_t));
			}
			else{
				break;
			}

			//设置Group节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Group节点
			gmp_into_gmdu(gmf);

			ret_bool = get_gmf_element(gmf, &(group_info_p->group_id), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_ID, buf, len);

			ret_bool = get_gmf_play_group_info(gmf, group_info_p, buf, len);
			if (!(*group_list)) {
				*group_list = list_create(group_info_p);
			}
			else{
				list_insert_after(*group_list, group_info_p);
			}
		}
	}

	//设置Groups节点
	gmp_reset_gmdu(gmf, gmdu);

	//表示退出Groups节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_play_group_info(gmp_gmf_t *gmf, cp_media_group_info_t *group_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t				*gmdu = CP_NULL;
	gmp_gmdt_t				*gmdt = CP_NULL;
	gmp_gmdt_t				*dev_gmdt = CP_NULL;
	gmp_gmdu_t				*gmdu_array = CP_NULL;
	gmp_gmdu_t				*dev_gmdu_array = CP_NULL;
	cp_char_t				tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t				ret_bool = cp_false;



	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play group info error. not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			//设置媒体矩形列表
			gmp_reset_gmdu(gmf, gmdu_array);

			//获取设备编号
			ret_bool = get_gmf_element_key(gmf, gmdu_array, &(group_info->no), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, buf, len);

			dev_gmdt = gmp_get_gmdt(gmf, gmdu_array, gmp_gmdu_value);
			if (dev_gmdt) {
				//获取通道矩形信息
				for (dev_gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; dev_gmdu_array; dev_gmdu_array = (gmp_gmdu_t*)(dev_gmdu_array->next)) {
					cp_channel_rect_info_t *rect_info = (cp_channel_rect_info_t *)cp_malloc(cp_sizeof(cp_channel_rect_info_t));
					if (rect_info) {
						cp_memset(rect_info, 0, cp_sizeof(cp_channel_rect_info_t));
					}else{
						break;
					}

					ret_bool = get_gmf_element_key(gmf, gmdu, &(rect_info->index), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, buf, len);

					//获取矩形块信息
					//ret_bool = get_gmf_element(gmf, &(rect_info->rect_pair), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_RP, &(rect_info->index), buf, len);

//					group_info->chan_rect_list
				}
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_play_channel_stop_info(gmp_gmf_t *gmf, list_node **media_channel_stop_list, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	cp_channel_stop_info_t			*channel_stop_info = CP_NULL;



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Medias节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_MEDIAS, cp_strlen(CP_APP_STR_MEDIAS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play channel stop info error. not "CP_APP_STR_MEDIAS" element error.");
		return cp_false;
	}

	//设置Medias节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			channel_stop_info = (cp_channel_stop_info_t*)cp_malloc(sizeof(cp_channel_stop_info_t));

			if (channel_stop_info) {
				cp_memset(channel_stop_info, 0, cp_sizeof(cp_channel_stop_info_t));
			}
			else{
				cp_snprintf(buf, len, "get gmf play channel stop info error. reason: malloc media channel error");
				break;
			}

			//设置Media节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Media节点
			gmp_into_gmdu(gmf);

			//解析Media节点信息，并添加入Child 列表中
			if (get_gmf_play_child_channel_stop_info(gmf, channel_stop_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				if (!(*media_channel_stop_list)) {
					*media_channel_stop_list = list_create(media_channel_stop_list);
				}
				else{
					list_insert_after(*media_channel_stop_list, channel_stop_info);
				}
			}
		}
	}

	//设置Medias节点
	gmp_reset_gmdu(gmf, gmdu);

	//表示退出Medias节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_play_child_channel_stop_info(gmp_gmf_t *gmf, cp_channel_stop_info_t *media_channel_stop_info, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t		ret_bool = cp_false;



	//获取PlaySession内容
	ret_bool = get_gmf_element(gmf, media_channel_stop_info->play_session, CP_APP_DEFAULT_SESSION_ID_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_PLAYSESSION, buf, len);

	//获取ID内容
	ret_bool = get_gmf_element(gmf, media_channel_stop_info->id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_ID, buf, len);

	//获取ChannelID内容
	ret_bool = get_gmf_element(gmf, &(media_channel_stop_info->index), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_UIN, 
		CP_APP_STR_CHANNELID, buf, len);

	//获取Type内容
	ret_bool = get_gmf_element(gmf, &(media_channel_stop_info->type), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC,
		CP_APP_STR_TYPE, buf, len);

	//获取EncodeType内容
	ret_bool = get_gmf_element(gmf, &(media_channel_stop_info->encode_type), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC,
		CP_APP_STR_ENCODE_TYPE, buf, len);

	//获取ChannelID内容
	ret_bool = get_gmf_element(gmf, &(media_channel_stop_info->status), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN,
		CP_APP_STR_STATUS, buf, len);

	return cp_true;
}


cp_bool_t get_gmf_play_cmd_info(gmp_gmf_t *gmf, cp_play_channel_info_t *pc_info, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool = cp_false;
	gmdt_rectpair_p_t				*rectpair_p = CP_NULL;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//查找Infomation节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf play information info error. not "CP_APP_STR_INFORMATION" element error.");
		return cp_false;
	}

	//设置Information节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Information节点
	gmp_into_gmdu(gmf);

	//获取CommandTime内容
	ret_bool = get_gmf_element(gmf, &(rectpair_p), cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, CP_APP_STR_COMMANDTIME, buf, len);
	if (ret_bool) {
		if (rectpair_p) {
			pc_info->command_time.a_sec = *rectpair_p->x1;
			pc_info->command_time.a_nsec = *rectpair_p->y1;
			pc_info->command_time.r_sec = *rectpair_p->x2;
			pc_info->command_time.r_nsec = *rectpair_p->y2;
		}
	}

	//获取SequenceNumber内容
	ret_bool = get_gmf_element(gmf, &(pc_info->sequence_number), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_L, CP_APP_STR_SEQUENCENUMBER, buf, len);

	//设置Information节点
	gmp_reset_gmdu(gmf, gmdu);

	return cp_true;
}

cp_bool_t get_gmf_channels(gmp_gmf_t *gmf, list_node *channel_info_list, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Channels节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_CHANNELS, cp_strlen(CP_APP_STR_CHANNELS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len - 1, "get gmf channels error. not "CP_APP_STR_CHANNELS" element error.");
		return cp_true;
	}

	//设置Channels节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_channel_info_t		*channel_info = (cp_channel_info_t *)cp_malloc(sizeof(cp_channel_info_t));

			//设置Channel节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//解析Channel节点信息，并添加入Child 列表中
			if (get_gmf_channel(gmf, channel_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				if (channel_info_list) {
					channel_info_list = list_create(channel_info);
				}else{
					list_insert_after(channel_info_list, channel_info);
				}
			}
		}
	}

	//设置Channels节点
	gmp_reset_gmdu(gmf, gmdu);

	//表示退出Channels节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_channel(gmp_gmf_t *gmf, cp_channel_info_t *channel_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmdt_rectpair_p_t				*rectpair_p = CP_NULL;


	//进入Channel节点
	gmp_into_gmdu(gmf);

	//获取id内容
	ret_bool = get_gmf_element(gmf, &(channel_info->index), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_UIN, CP_APP_STR_ID, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取PlaySession内容
	ret_bool = get_gmf_element(gmf, &(channel_info->play_session), CP_APP_DEFAULT_SESSION_ID_LENGTH - 1, GMP_GMDT_ST, CP_APP_STR_PLAYSESSION, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Position内容
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rect_p_t), GMP_GMDT_RP, CP_APP_STR_POSITION, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool && rectpair_p) {
		cp_std_convert_position(rectpair_p, &channel_info->position);
	}

	ret_bool = get_gmf_multicast_info(gmf, &(channel_info->multicast_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	ret_bool = get_gmf_play_address_info(gmf, &(channel_info->play_addr_info), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	ret_bool = get_gmf_stream_description(gmf, &(channel_info->stream_description), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	return cp_true;
}

cp_bool_t get_gmf_device_update_info(gmp_gmf_t *gmf, cp_update_info_t *update_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t					tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t					ret_bool;
	gmp_gmdu_t					*gmdu = CP_NULL;
	gmp_gmdu_t					*gmdu_array = CP_NULL;
	gmp_gmdt_t					*gmdt = CP_NULL;
	gmdt_rectpair_p_t			*rectpair_p = CP_NULL;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get device update info error. reason null gmf error.");
		return cp_false;
	}

	//查找Update节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_PACKET_UPDATE, cp_strlen(CP_APP_STR_PACKET_UPDATE));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf device update info error. not "CP_APP_STR_PACKET_UPDATE" element error.");
		return cp_false;
	}

	//设置Update节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Update节点
	gmp_into_gmdu(gmf);

	//获取PacketName内容
	ret_bool = get_gmf_element(gmf, &(update_info->packet_name), CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_PACKET_NAME, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取OperationFlag内容
	ret_bool = get_gmf_element(gmf, &(update_info->operation_flag), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, 
		CP_APP_STR_OPERATION_FLAG, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Version内容
	ret_bool = get_gmf_element(gmf, &(update_info->version), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, 
		CP_APP_STR_VERSION, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取VersionAddtion内容
	ret_bool = get_gmf_element(gmf, &(update_info->version_addtion), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, 
		CP_APP_STR_VERSION_ADDTION, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取Time内容
	ret_bool = get_gmf_element(gmf, &rectpair_p, cp_sizeof(gmdt_rectpair_p_t), GMP_GMDT_RP, 
		CP_APP_STR_TIME, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool) {
		if (rectpair_p) {
			update_info->time_s = *(rectpair_p->x1);
			update_info->time_ns = *(rectpair_p->y1);
		}
	}

	//获取SerialMaster内容
	ret_bool = get_gmf_element(gmf, &(update_info->serial_master), CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_SERIAL_MASTER, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);


	//获取SerialSlave内容
	ret_bool = get_gmf_element(gmf, &(update_info->serial_slave), CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_SERIAL_SLAVE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);


	//获取PlatformHardware内容
	ret_bool = get_gmf_element(gmf, &(update_info->platform_hardware), CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_PLATFORM_HARDWARE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);


	//获取PlatformSoftware内容
	ret_bool = get_gmf_element(gmf, &(update_info->platform_software), CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_PLATFORM_SOFTWARE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);


	//获取ChangerLog内容
	ret_bool = get_gmf_element(gmf, &(update_info->change_log), CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_CHANGER_LOG, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	/*
	//获取ProgramFile内容
	ret_bool = get_gmf_element(gmf, &(iob_p), GMP_GMDT_IOB, DEV_MEDIA_SERVER_STR_PROGRAM_FILE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool)
	{
	if (iob_p)
	{
	if (*(iob_p->len) > 0)
	{
	update_info.m_program_file_p = iob_p->data;
	update_info.m_program_file_len = *(iob_p->len);
	}
	}
	}*/

	return cp_true;
}



cp_bool_t parse_gmf_resolution_size(gmp_gmf_t *gmf, cp_uint32_t *resolution_width, cp_uint32_t *resolution_height, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;
	cp_bool_t						ret_bool;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "parse gmf resolution size error reason: null gmf error.");
		return cp_false;
	}

	//查找Resolution节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_RESOLUTION, cp_strlen(CP_APP_STR_RESOLUTION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len - 1, "parse gmf resolution size error reason: not "CP_APP_STR_RESOLUTION" element error.");	
		return cp_false;
	}

	//重设Resolution节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Resolution节点
	gmp_into_gmdu(gmf);

	//获取Width内容
	ret_bool = get_gmf_element(gmf, resolution_width, CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_WIDTH, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "parse gmf resolution size error reason: %s", buf);
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//获取Height内容
	ret_bool = get_gmf_element(gmf, resolution_height, CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_HEIGHT, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "parse gmf resolution size error reason: %s", buf);
		gmp_outof_gmdu(gmf);	
		return cp_false;
	}

	//退出Resolution节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}



cp_bool_t parse_gmf_back_size(gmp_gmf_t *gmf, cp_uint32_t *width, cp_uint32_t *height, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;
	cp_bool_t						ret_bool;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len - 1, "parse gmf back size error reason: null gmf error.");
		return cp_false;
	}

	//查找BackSize节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_BACKSIZE, cp_strlen(CP_APP_STR_BACKSIZE));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len - 1, "not "CP_APP_STR_BACKSIZE" element error.");
		return cp_false;
	}

	//重设BackSize节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入BackSize节点
	gmp_into_gmdu(gmf);

	//获取Width内容
	ret_bool = get_gmf_element(gmf, width, CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_WIDTH, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf resolution error. reason: %s", buf);		
		return cp_false;
	}

	//获取Height内容
	ret_bool = get_gmf_element(gmf, height, CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_HEIGHT, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf resolution error. reason: %s", buf);
	}

	//退出BackSize节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_chunk_size_by_id(gmp_gmf_t *gmf, const cp_char_t *id, cp_int32_t *chunk_size, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdu_t							*gmdu_array = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	cp_bool_t							ret_bool = cp_false;



	cp_memset(buf, 0, len);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf chunk size by id error. not "CP_APP_STR_DEVICES" element error");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_char_t						str_id[CP_APP_DEFAULT_ID_LENGTH];

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//获取ID内容
			ret_bool = get_gmf_element(gmf, &(str_id), CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				continue;
			}
			
			//获取ChunkSize内容
			if (!cp_strcmp(str_id, id)) {
				ret_bool = get_gmf_element(gmf, &(chunk_size), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_CHUNKSIZE, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_log_info(gmp_gmf_t *gmf, cp_log_info_t *log_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmdt_rectpair_p_t				*rect_pair_p = CP_NULL;




	//进入Device节点
	gmp_into_gmdu(gmf);

	//清空缓存
	cp_memset(buf, 0, len);

	//获取ID内容
	ret_bool = get_gmf_element(gmf, log_info->id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_ID, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf log info error. not  "CP_APP_STR_FLAG" element error");
		return cp_false;
	}

	//获取Flag内容
	ret_bool = get_gmf_element(gmf, &(log_info->flag), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, 
		CP_APP_STR_FLAG, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf log info error. not "CP_APP_STR_FLAG" element error");
		return cp_false;
	}

	//获取FileName内容
	ret_bool = get_gmf_element(gmf, log_info->file_name, CP_APP_DEFAULT_STRING_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_NAME, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取FileExtension内容
	ret_bool = get_gmf_element(gmf, log_info->file_extension, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, 
		CP_APP_STR_FILE_EXTENSION, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf log info error. not "CP_APP_STR_FILE_EXTENSION" element error");
		return cp_false;
	}

	//获取FilePath内容
	ret_bool = get_gmf_element(gmf, (log_info->file_path), CP_APP_DEFAULT_STRING_LENGTH - 1,
		GMP_GMDT_ST, CP_APP_STR_FILE_PATH, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取FileSize内容
	ret_bool = get_gmf_element(gmf, &(log_info->file_size), CP_APP_DEFAULT_INT_LENGTH,
		GMP_GMDT_UIN, CP_APP_STR_FILE_SIZE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取FileCreateTime内容
	ret_bool = get_gmf_element(gmf, &rect_pair_p, cp_sizeof(gmdt_rectpair_p_t),
		GMP_GMDT_RP, CP_APP_STR_FILE_CREATE_TIME, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool) {
		if (rect_pair_p) {
			log_info->file_create_time.x1 = *(rect_pair_p->x1);
			log_info->file_create_time.y1 = *(rect_pair_p->y1);
			log_info->file_create_time.x2 = *(rect_pair_p->x2);
			log_info->file_create_time.y2 = *(rect_pair_p->y2);
			log_info->file_create_time.x3 = *(rect_pair_p->x3);
			log_info->file_create_time.y3 = *(rect_pair_p->y3);
			log_info->file_create_time.x4 = *(rect_pair_p->x4);
			log_info->file_create_time.y4 = *(rect_pair_p->y4);
		}
	}

	//获取FileModifyTime内容
	ret_bool = get_gmf_element(gmf, &rect_pair_p, cp_sizeof(gmdt_rectpair_p_t),
		GMP_GMDT_RP, CP_APP_STR_FILE_MODIFY_TIME, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (ret_bool) {
		if (rect_pair_p) {
			log_info->file_modify_time.x1 = *(rect_pair_p->x1);
			log_info->file_modify_time.y1 = *(rect_pair_p->y1);
			log_info->file_modify_time.x2 = *(rect_pair_p->x2);
			log_info->file_modify_time.y2 = *(rect_pair_p->y2);
			log_info->file_modify_time.x3 = *(rect_pair_p->x3);
			log_info->file_modify_time.y3 = *(rect_pair_p->y3);
			log_info->file_modify_time.x4 = *(rect_pair_p->x4);
			log_info->file_modify_time.y4 = *(rect_pair_p->y4);
		}
	}

	return cp_true;
}


cp_bool_t get_gmf_log_info_by_id(gmp_gmf_t *gmf, const cp_char_t *id, cp_log_info_t *log_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdu_t							*gmdu_array = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t							ret_bool = cp_false;



	cp_memset(buf, 0, len);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf log info by id error. reason not "CP_APP_STR_DEVICES" element error");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_char_t						str_id[CP_APP_DEFAULT_ID_LENGTH] = {0, };

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//获取ID内容
			ret_bool = get_gmf_element(gmf, str_id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				continue;
			}

			//判断获取的ID是否自己的ID
			if (cp_strcmp(str_id, id)) {
				continue;
			}

			ret_bool = get_gmf_log_info(gmf, log_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_chunk_size(gmp_gmf_t *gmf, cp_int32_t *chunk_size, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdu_t							*gmdu_array = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;


	//查找ChunkSize节点，处理全局的ChunkSize设置信息
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_CHUNKSIZE, cp_strlen(CP_APP_STR_CHUNKSIZE));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (gmdu) {
		gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
		if (gmp_gmdt_type_compare(gmdt, GMP_GMDT_IN) || gmp_gmdt_type_compare(gmdt, GMP_GMDT_UIN)) {
			if (*(((gmdt_int_p_t*)gmdt)->data) > 0) {
				//根据全局的ChunkSize设置成功
				chunk_size = (cp_int32_t *)*(((gmdt_int_p_t*)gmdt)->data);
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_devices_info(gmp_gmf_t *gmf, list_node **dev_info_list, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf devices info error.not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_device_info_t		*child_dev_info_p = (cp_device_info_t *)cp_malloc(sizeof(cp_device_info_t));

			if (!child_dev_info_p) {
				continue;
			}else{
				cp_memset(child_dev_info_p, 0, sizeof(cp_device_info_t));
			}

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//解析Device节点信息，并添加入Child 列表中
			if (get_gmf_child_device_info(gmf, child_dev_info_p, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				if (!(*dev_info_list)) {
					*dev_info_list = list_create(child_dev_info_p);
				} else{
					list_insert_after(*dev_info_list, child_dev_info_p);
				}
			}else{
				cp_free(child_dev_info_p);
				cp_snprintf(buf, len, "%s", tmp_buf);
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_devices_info_array(gmp_gmf_t *gmf, cp_array_t *dev_info_array, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_device_info_t				tmp_child_dev_info = { 0, };


	//清空缓存
	cp_memset(buf, 0, len);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf devices info error.not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			
			cp_memset(&tmp_child_dev_info, 0, sizeof(cp_device_info_t));

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//解析Device节点信息，并添加入Child 列表中
			if (get_gmf_child_device_info(gmf, &tmp_child_dev_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_array_set_back(dev_info_array, &tmp_child_dev_info);
			}
			else{
				cp_snprintf(buf, len, "%s", tmp_buf);
			}
		}
	}

	return cp_true;
}

cp_int32_t get_gmf_devices_info_size(gmp_gmf_t *gmf, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf devices info error.not "CP_APP_STR_DEVICES" element error.");
		return 0;
	}
	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		return *(((gmdt_array_p_t*)gmdt)->nelts);
	}
	return 0;
}

cp_bool_t get_gmf_child_device_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;


	//解析Host节点内容
	if (!parse_gmf_device_host(gmf, &(dev_info->host), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		cp_snprintf(buf, len, "get gmf child device info error. reason: %s", tmp_buf);
		return cp_false;
	}

	//解析Interface节点内容
	if (!parse_gmf_interfaces(gmf, &(dev_info->network), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		cp_snprintf(buf, len, "get gmf child device info error.reason: %s", tmp_buf);
		return cp_false;
	}

	//查找Information节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf child device info error. not "CP_APP_STR_INFORMATION" element error.");
		return cp_false;
	}

	//设置Information节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Information节点
	gmp_into_gmdu(gmf);

	//媒体服务组播信息"Multicast"
	if (dev_info->host.type == css_device_type_media_server) {
		ret_bool = get_gmf_multicast_info(gmf, &(dev_info->multicast_addr), tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	}

	//退出Information节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_gmf_host_device_info
*
* 函数说明: 获取host节点下的信息
*
* 参    数: gmp_gmf_t * gmf						[in]参数说明
* 参    数: cp_device_info_t * dev_info			[in]参数说明
* 参    数: cp_char_t * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
*
* 返 回 值: cp_bool_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-22 11:14:29
******************************************************************************************************/
cp_bool_t get_gmf_host_device_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu;
	gmp_gmdt_t							*gmdt;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };


	cp_memset(buf, 0, len);

	//设置当前节点为object
	gmp_top_gmdu(gmf);

	//进入object
	gmp_into_gmdu(gmf);

	//查找Host节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_HOST, cp_strlen(CP_APP_STR_HOST));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "not "CP_APP_STR_HOST" element error.");
		return cp_false;
	}

	//重设Host节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Host节点
	gmp_into_gmdu(gmf);

	//获取host节点中设备信息
	get_gmf_child_device_info(gmf, dev_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (cp_strlen(dev_info->host.id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		cp_snprintf(buf, len, "get_gmf_child_device_info() error. reason:%s", tmp_buf);
		return cp_false;
	}

	return cp_true;
}

cp_bool_t get_host_id_detail(cp_host_t *host, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						*tmp_begin = CP_NULL;
	cp_char_t						*tmp_pos = CP_NULL;
	cp_char_t						*tmp_end = CP_NULL;
	cp_int32_t						i = 0;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_SESSION_ID_LENGTH][CP_APP_DEFAULT_SESSION_ID_LENGTH] = { 0, };



	if (!host | !buf | !len) {
		return cp_false;
	}

	if (cp_strlen(host->id) != CP_APP_DEFAULT_ID_LENGTH - 1) {
		return cp_false;
	}

	tmp_begin = host->id;
	tmp_pos = tmp_begin;
	tmp_end = host->id + cp_strlen(host->id);

	for (; tmp_pos < tmp_end; tmp_pos++) {
		if (CP_APP_STR_SPLIT_FLAG == *tmp_pos) {
			if (tmp_pos > tmp_begin) {
				cp_strncpy(tmp_buf[i++], tmp_begin, (tmp_pos - tmp_begin));
				tmp_begin = tmp_pos + 1;
			}
		}
	}
	if (tmp_pos > tmp_begin) {
		cp_strncpy(tmp_buf[i++], tmp_begin, (tmp_pos - tmp_begin));
		tmp_begin = tmp_pos;
	}

	host->group = cp_atoi(tmp_buf[1]);
	host->row = cp_atoi(tmp_buf[2]);
	host->column = cp_atoi(tmp_buf[3]);

	return cp_true;
}

cp_bool_t get_gmf_multicast_info(gmp_gmf_t *gmf, cp_multicast_addr_t *multicast_addr, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//查找Multicast节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_MULTICAST, 
		cp_strlen(CP_APP_STR_MULTICAST));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (gmdu) {
		//设置Multicast节点
		gmp_reset_gmdu(gmf, gmdu);

		//进入Multicast节点
		gmp_into_gmdu(gmf);

		//获取IP内容
		ret_bool = get_gmf_element(gmf, multicast_addr->ip, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_IP, 
			buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

		//获取Port内容
		ret_bool = get_gmf_element(gmf, &(multicast_addr->port), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_PORT, 
			buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

		//退出Multicast节点
		gmp_outof_gmdu(gmf);
	}

	return cp_true;
}

cp_bool_t get_gmf_play_address_info(gmp_gmf_t *gmf, cp_play_addr_t *play_addr, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//查找PlayAddress节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_PLAYADDRESS, cp_strlen(CP_APP_STR_PLAYADDRESS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (gmdu) {
		//设置PlayAddress节点
		gmp_reset_gmdu(gmf, gmdu);

		//进入PlayAddress节点
		gmp_into_gmdu(gmf);

		//获取IP内容
		ret_bool = get_gmf_element(gmf, play_addr->ip, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, "Ip", buf, len);

		//获取Port内容
		ret_bool = get_gmf_element(gmf, &(play_addr->udp_port), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_PORT, buf, len);

		//退出PlayAddress节点
		gmp_outof_gmdu(gmf);
	}

	return cp_true;
}

cp_bool_t get_gmf_stream_description(gmp_gmf_t *gmf, cp_stream_description_t *stream_description, cp_char_t *buf, cp_int32_t len)
{
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;



	//查找StreamDescription节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_STREAM_DESCRIPTION, cp_strlen(CP_APP_STR_STREAM_DESCRIPTION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (gmdu) {
		//设置StreamDescription节点
		gmp_reset_gmdu(gmf, gmdu);

		//进入StreamDescription节点
		gmp_into_gmdu(gmf);

		//获取DistributionType内容
		ret_bool = get_gmf_element(gmf, &(stream_description->distribution_type), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_DISTRIBUTION_TYPE, 
			buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

		//获取TransportType内容
		ret_bool = get_gmf_element(gmf, &(stream_description->transport_type), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_TRANSPORT_TYPE, 
			buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

		//退出StreamDescription节点
		gmp_outof_gmdu(gmf);
	}

	return cp_true;
}

cp_bool_t get_gmf_device_groups_info(gmp_gmf_t *gmf, cp_host_t *host, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_bool_t						tmp_ret_bool = cp_false;
	cp_char_t						tmp_group_id[CP_APP_DEFAULT_ID_LENGTH] = { 0, };



	//查找Groups节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_GROUPS, cp_strlen(CP_APP_STR_GROUPS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf device groups info error. not "CP_APP_STR_GROUPS" element error.");
		return cp_false;
	}

	//设置Groups节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {

			//设置Group节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Group节点
			gmp_into_gmdu(gmf);

			//设置组信息
			ret_bool = get_gmf_element(gmf, &(host->group), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_ID, buf, len);
			if (ret_bool) {
				tmp_ret_bool = cp_true;
			}
			else {
				ret_bool = get_gmf_element(gmf, tmp_group_id, cp_sizeof(tmp_group_id), GMP_GMDT_ST, CP_APP_STR_ID, buf, len);
				if (ret_bool) {
					host->group = cp_atoi(tmp_group_id);
					tmp_ret_bool = cp_true;
				}
			}
		}
	}

	//设置Groups节点
	gmp_reset_gmdu(gmf, gmdu);

	//表示退出Groups节点
	//gmp_outof_gmdu(gmf);

	return tmp_ret_bool;
}

cp_bool_t get_gmf_sync_info(gmp_gmf_t *gmf, cp_sync_info_t *sync_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	//清空缓存
	cp_memset(buf, 0, len);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, 
		cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf sync devices info error. not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//解析Device节点信息，并添加入Child 列表中
			if (!get_gmf_child_sync_info(gmf, sync_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
				cp_snprintf(buf, len, "%s", tmp_buf);
				return cp_false;
			}else{
				break;
			}
		}
	}

	return cp_true;
}


cp_bool_t get_gmf_child_sync_info(gmp_gmf_t *gmf, cp_sync_info_t *sync_info, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						ret_bool = cp_false;
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	gmdt_rect_p_t					*rect_p = CP_NULL;




	//进入device节点
	gmp_into_gmdu(gmf);

	//获取Flag内容
	ret_bool = get_gmf_element(gmf, &(sync_info->flag), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_FLAG, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf sync device info error. not "CP_APP_STR_FLAG" element error.");
		//return cp_false;
	}

	//获取Value内容
	ret_bool = get_gmf_element(gmf, &(sync_info->value), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_PLYAER_STR_VALUE, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取TimeStampS内容
	ret_bool = get_gmf_element(gmf, &(sync_info->time_stamps), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_UIN, CP_PLYAER_STR_TIMESTAMPS, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	//获取TimeStampNS内容
	ret_bool = get_gmf_element(gmf, &(sync_info->time_stampns), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_UIN, CP_PLYAER_STR_TIMESTAMPNS, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

	return cp_true;
}

cp_bool_t get_gmf_device_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	cp_bool_t							ret_bool = cp_false;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	

	//查找Device节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICE, cp_strlen(CP_APP_STR_DEVICE));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf device info error reason: not element "CP_APP_STR_DEVICE" error");
		return cp_false;
	}

	//设置Device节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Device节点
	gmp_into_gmdu(gmf);

	//解析Host节点内容
	if (!parse_gmf_device_host(gmf, &(dev_info->host), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf device info error reason: %s", tmp_buf);
		return cp_false;
	}

	//获取HeartbeatTimes内容
	ret_bool = get_gmf_element(gmf, &(dev_info->heart_info.times), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_IN, CP_APP_STR_HEARTBEAT_TIMES, buf, len);
	
	ret_bool = get_gmf_element(gmf, &(dev_info->heart_info.interval_ms), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_IN, CP_APP_STR_HEARTBEAT_INTERVAL, buf, len);

	//获取Interface内容
	if (!parse_gmf_interfaces(gmf, &(dev_info->network), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf device info error reason: %s", tmp_buf);
	}

	//查找Information节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf device info error reason: not "CP_APP_STR_INFORMATION" element error");
	}

	//设置Information节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Information节点
	gmp_into_gmdu(gmf);

	if (dev_info->host.type == css_device_type_css_video_player) {
		ret_bool = get_gmf_element(gmf, &(dev_info->host.no), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_NO, buf, len);
		ret_bool = get_gmf_element(gmf, dev_info->host.number, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NUMBER, buf, len);
	}

	//获取硬件信息
	if (!get_gmf_hardware_info(gmf, &(dev_info->host), &(dev_info->hardware), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf device info error reason: %s", tmp_buf);
	}

	//获取设备组信息
	if (!get_gmf_device_groups_info(gmf, &(dev_info->host), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf device group error reason: %s", tmp_buf);
	}
	
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_player_info(gmp_gmf_t *gmf, cp_device_info_t *dev_info, cp_center_addr_t *center_addr, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t							*gmdu = CP_NULL;
	gmp_gmdt_t							*gmdt = CP_NULL;
	cp_bool_t							ret_bool = cp_false;
	cp_bool_t							reset = cp_false;
	cp_char_t							back_fps = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//查找Information节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_INFORMATION, cp_strlen(CP_APP_STR_INFORMATION));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf player info error. not "CP_APP_STR_INFORMATION" element error");
	}

	//设置Information节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Information节点
	gmp_into_gmdu(gmf);

	//获取no设备编号
	ret_bool = get_gmf_element(gmf, &(dev_info->host.no), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_IN, CP_APP_STR_NO, buf, len);

	//获取Number组编号
	ret_bool = get_gmf_element(gmf, dev_info->host.number, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NUMBER, buf, len);

	//获取BackFps背景帧率
	ret_bool = get_gmf_element(gmf, &back_fps, CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_BACKFPS, buf, len);

	//获取Reset重置开关
	ret_bool = get_gmf_element(gmf, &reset, CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_IN, CP_APP_STR_SWITCH, buf, len);

	//获取硬件信息
	if (!get_gmf_hardware_info(gmf, &(dev_info->host), &(dev_info->hardware), tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf player info error. reason: %s", tmp_buf);
	}

	//获取Center
	if (!get_gmf_center_info(gmf, center_addr, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf player info error. reason: %s", tmp_buf);
	}

	//获取Serials
	if (!get_gmf_serials_info(gmf, &dev_info->serials, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf player info error. reason: %s", tmp_buf);
	}

	//获取Networks
	if (get_gmf_networks_info(gmf, &dev_info->network, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH)) {
		cp_snprintf(buf, len, "get gmf player info error. reason: %s", tmp_buf);
	}

	//退出Information节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_checkcolor_info(gmp_gmf_t *gmf, cp_checkcolor_info_t *check_color, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;
	cp_bool_t						ret_bool;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf checkcolor info error reason: null gmf error.");
		return cp_false;
	}

	//查找CheckColor节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_CHECKCOLOR, cp_strlen(CP_APP_STR_CHECKCOLOR));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len - 1, "get gmf checkcolor info error reason: not "CP_APP_STR_RESOLUTION" element error.");
		return cp_false;
	}

	//重设CheckColor节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入CheckColor节点
	gmp_into_gmdu(gmf);

	//获取source_color内容
	ret_bool = get_gmf_element(gmf, check_color->source_color, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_SOURCECOLOR, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf checkcolor info error reason: %s", buf);
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//获取dest_color内容
	ret_bool = get_gmf_element(gmf, check_color->dest_color, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_DESTCOLOR, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf checkcolor info error reason: %s", buf);
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//退出CheckColor节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}


cp_bool_t get_gmf_center_info(gmp_gmf_t *gmf, cp_center_addr_t *center_addr, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;
	cp_bool_t						ret_bool;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf center info error reason: null gmf error.");
		return cp_false;
	}

	//查找Center节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_CENTER, cp_strlen(CP_APP_STR_CENTER));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf center info error. not "CP_APP_STR_CENTER" element error.");
		return cp_false;
	}

	//重设Center节点
	gmp_reset_gmdu(gmf, gmdu);

	//进入Center节点
	gmp_into_gmdu(gmf);

	//获取IP内容
	ret_bool = get_gmf_element(gmf, center_addr->ip, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_IP, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf center info error. reason: %s", buf);
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//获取TCPPort内容
	ret_bool = get_gmf_element(gmf, &(center_addr->tcp_port), CP_APP_DEFAULT_LENGTH, GMP_GMDT_IN, CP_APP_STR_TCPPORT, buf, len);
	if (!ret_bool) {
		cp_snprintf(buf, len, "get gmf center info error. reason: %s", buf);
		gmp_outof_gmdu(gmf);
		return cp_false;
	}

	//退出Center节点
	gmp_outof_gmdu(gmf);

	return cp_true;
}

cp_bool_t get_gmf_serials_info(gmp_gmf_t *gmf, cp_serial_t *serial_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf serials info error. reason: null gmf error.");
		return cp_false;
	}

	//查找Serials节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_SERIALS, cp_strlen(CP_APP_STR_SERIALS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf serials info error. not "CP_APP_STR_SERIALS" element error.");
		return cp_false;
	}

	//设置Serials节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			//设置Serial节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Serial节点
			gmp_into_gmdu(gmf);
			
			ret_bool = get_gmf_serial_info(gmf, serial_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (ret_bool) {
				break;
			}
		}
	}

	gmp_reset_gmdu(gmf, gmdu);

	return cp_true;
}

cp_bool_t get_gmf_serial_info(gmp_gmf_t *gmf, cp_serial_t *serial_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf serial info error reason: null gmf error.");
		return cp_false;
	}

	//获取Name内容
	ret_bool = get_gmf_element(gmf, serial_info->name, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NAME, buf, len);

	//获取BaudRate内容
	ret_bool = get_gmf_element(gmf, &(serial_info->baudrate), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_IN, CP_APP_STR_BAUDRATE, buf, len);

	//获取CharacterSize内容
	ret_bool = get_gmf_element(gmf, &(serial_info->character_size), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_CHARACTER_SIZE, buf, len);

	//获取FlowControl内容
	ret_bool = get_gmf_element(gmf, serial_info->flowcontrol, CP_APP_DEFAULT_LENGTH, GMP_GMDT_UC, CP_APP_STR_FLOW_CONTROL, buf, len);

	//获取Parity内容
	ret_bool = get_gmf_element(gmf, serial_info->parity, CP_APP_DEFAULT_LENGTH, GMP_GMDT_UC, CP_APP_STR_PARITY, buf, len);

	//获取StopBits内容
	ret_bool = get_gmf_element(gmf, &(serial_info->stopbits), CP_APP_DEFAULT_INT_LENGTH, GMP_GMDT_F, CP_APP_STR_STOP_BITS, buf, len);

	return cp_true;
}

cp_bool_t get_gmf_networks_info(gmp_gmf_t *gmf, cp_interface_t *network_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf networks info error. reason: null gmf error.");
		return cp_false;
	}

	//查找Networks节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_NETWORKS, cp_strlen(CP_APP_STR_NETWORKS));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf networks info error. not "CP_APP_STR_NETWORKS" element error.");
		return cp_false;
	}

	//设置Network节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			//设置Networks节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Networks节点
			gmp_into_gmdu(gmf);

			ret_bool = get_gmf_network_info(gmf, network_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (ret_bool) {
				break;
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_network_info(gmp_gmf_t *gmf, cp_interface_t *network_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf network info error. reason: null gmf error.");
		return cp_false;
	}

	//获取Name内容
	ret_bool = get_gmf_element(gmf, network_info->name, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NAME, buf, len);

	//获取BaudRate内容
	ret_bool = get_gmf_element(gmf, &(network_info->bootp), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_BOOTPROTOCOL, buf, len);

	//获取IP内容
	ret_bool = get_gmf_element(gmf, network_info->ip, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_IP, buf, len);

	//获取NetMask内容
	ret_bool = get_gmf_element(gmf, network_info->netmask, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_NETMASK, buf, len);

	//获取Gateway内容
	ret_bool = get_gmf_element(gmf, network_info->gateway, CP_APP_DEFAULT_LENGTH, GMP_GMDT_ST, CP_APP_STR_GATEWAY, buf, len);

	return cp_true;
}

cp_bool_t get_gmf_devices_focus_list(gmp_gmf_t *gmf, list_node **device_focus_list, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_focus_info_t					*device_focus_info = CP_NULL;


	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf devices focus list error. reason: null gmf error.");	
		return cp_false;
	}

	//设置当前节点为object
	gmp_top_gmdu(gmf);

	//进入object
	gmp_into_gmdu(gmf);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf devices focus list error. not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);
	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {

			device_focus_info = (cp_focus_info_t *)cp_malloc(cp_sizeof(cp_focus_info_t));

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//获取ID内容
			ret_bool = get_gmf_element(gmf, device_focus_info->id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				cp_snprintf(buf, len, "get gmf devices focus list error. not element "CP_APP_STR_ID" error .");				
				cp_free(device_focus_info);
				continue;
			}

			ret_bool = get_gmf_element(gmf, &(device_focus_info->focus), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_FOCUS, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				cp_snprintf(buf, len, "get gmf devices focus list error. not element "CP_APP_STR_FOCUS" error .");				
				cp_free(device_focus_info);				
				continue;
			}

			ret_bool = get_gmf_element(gmf, &(device_focus_info->focus_type), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_FOCUS_TYPE, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				cp_snprintf(buf, len, "get gmf devices focus list error. not element "CP_APP_STR_FOCUS_TYPE" error .");				
				cp_free(device_focus_info);				
				continue;
			}

			if (!(*device_focus_list)) {
				*device_focus_list = list_create(device_focus_info);
			}else{
				list_insert_after(*device_focus_list, device_focus_info);
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_offline_info_list(gmp_gmf_t *gmf, list_node **offline_info_list, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf offline info list error. reason: null gmf error.");
		return cp_false;
	}

	//设置当前节点为object
	gmp_top_gmdu(gmf);

	//进入object
	gmp_into_gmdu(gmf);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf offline info list error. not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_dev_offline_info_t           *offline_info_p = CP_NULL;
			offline_info_p = (cp_dev_offline_info_t *)cp_malloc(cp_sizeof(cp_dev_offline_info_t));
			if (!offline_info_p) {
				break;
			}else{
				cp_memset(offline_info_p, 0, cp_sizeof(cp_dev_offline_info_t));
			}

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//获取ID内容
			ret_bool = get_gmf_element(gmf, offline_info_p->id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool || cp_strlen(offline_info_p->id) < (CP_APP_DEFAULT_ID_LENGTH - 1)) {
				cp_free(offline_info_p);
				continue;
			}

			//获取校验标识
			ret_bool = get_gmf_element(gmf, &(offline_info_p->user_password), CP_APP_DEFAULT_CHAR_LENGTH, GMP_GMDT_UC, CP_APP_STR_USEDPASSWORD, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);

			if (!(*offline_info_list)) {
				*offline_info_list = list_create(offline_info_p);
			}
			else{
				list_insert_after(*offline_info_list, offline_info_p);
			}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_devices_id_exist(gmp_gmf_t *gmf, const cp_char_t *id, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf device id exist error. reason: null gmf error.");
		return cp_false;
	}

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf device id exist error. not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_char_t			str_id[CP_APP_DEFAULT_ID_LENGTH];

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//获取ID内容
			ret_bool = get_gmf_element(gmf, str_id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				continue;
			}else{
				cp_strncmp(id, str_id, CP_APP_DEFAULT_ID_LENGTH - 1);
				return cp_true;
			}
		}
	}

	return cp_false;
}

cp_bool_t get_gmf_update_info_by_id(gmp_gmf_t *gmf, const cp_char_t *id, cp_update_info_t *update_info, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu = CP_NULL;
	gmp_gmdu_t						*gmdu_array = CP_NULL;
	gmp_gmdt_t						*gmdt = CP_NULL;
	cp_bool_t						ret_bool = cp_false;
	cp_char_t						tmp_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };
	cp_bool_t						is_match = cp_false;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "get gmf update info by id error. reason: null gmf error.");
		return cp_false;
	}

	//设置当前节点为object
	gmp_top_gmdu(gmf);

	//进入object
	gmp_into_gmdu(gmf);

	//查找Devices节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, CP_APP_STR_DEVICES, cp_strlen(CP_APP_STR_DEVICES));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "get gmf update info by id error. not "CP_APP_STR_DEVICES" element error.");
		return cp_false;
	}

	//设置Devices节点
	gmp_reset_gmdu(gmf, gmdu);

	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (gmdt) {
		for (gmdu_array = ((gmdt_array_p_t*)gmdt)->elts; gmdu_array; gmdu_array = (gmp_gmdu_t*)(gmdu_array->next)) {
			cp_char_t						str_id[CP_APP_DEFAULT_ID_LENGTH] = { 0, };

			//设置Device节点
			gmp_reset_gmdu(gmf, gmdu_array);

			//进入Device节点
			gmp_into_gmdu(gmf);

			//获取ID内容
			ret_bool = get_gmf_element(gmf, str_id, CP_APP_DEFAULT_ID_LENGTH, GMP_GMDT_ST, CP_APP_STR_ID, buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				continue;
			}

			if (cp_strcmp(id, str_id)) {
				continue;
			}

			cp_snprintf(update_info->id, cp_sizeof(update_info->id), "%s", str_id);

			ret_bool = get_gmf_device_update_info(gmf, update_info, tmp_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN);
			if (!ret_bool) {
				cp_snprintf(buf, len, "%s", "get gmf update info by id error.  reason: %s", tmp_buf);
				continue;
			}
			return cp_true;
		}
	}
	return cp_false;
}

cp_bool_t get_gmf_element(gmp_gmf_t *gmf, cp_void_t *dest, cp_int32_t dest_len, gmp_gmdt gmdt_type, cp_char_t *name, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "null gmf error.");
		return cp_false;
	}

	if (!gmp_chk_gmdt(gmdt_type)) {
		cp_snprintf(buf, len, "gmf gmdt[0x%02X] error.", gmdt_type);
		return cp_false;
	}

	//查找指定节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, (name), strlen(name));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "not %s element error.", (name));
		return cp_false;
	}else{
		//获取gmdt的数值
		gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
		if (!gmdt) {
			cp_snprintf(buf, len, "element %s not value error.", name);

			return cp_false;
		}else{
			if (gmdt_type != GMP_GMDT_UC) {
				//判断gmdt的类型是否相同
				if (*(((gmdt_type_p_t*)gmdt)->gmdt) != gmdt_type) {
					cp_snprintf(buf, len, "element %s type[0x%02X] error.", (name), *(((gmdt_type_p_t*)gmdt)->gmdt));
					return cp_false;
				}
			}else{
				if (*(((gmdt_type_p_t*)gmdt)->gmdt) > GMP_GMDT_T || *(((gmdt_type_p_t*)gmdt)->gmdt) < GMP_GMDT_B) {
					cp_snprintf(buf, len, "element %s type[0x%02X] error.", (name), *(((gmdt_type_p_t*)gmdt)->gmdt));
					return cp_false;
				}
			}

			switch (gmdt_type) {
				//常用基础数据类型(0--63)
			case GMP_GMDT_B:
			{
				*((cp_bool_t *)dest) = *(((gmdt_bool_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_C:
			{
				*((cp_char_t*)dest) = *(((gmdt_char_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_UC:
			{
				if (*(((gmdt_type_p_t*)gmdt)->gmdt) == GMP_GMDT_IN)
				{
					*((cp_uchar_t *)dest) = (cp_uchar_t)(*(((gmdt_int_p_t*)gmdt)->data));
				}
				else
				{
					*((cp_uchar_t *)dest) = *(((gmdt_uchar_p_t*)gmdt)->data);
				}
			}
			break;
			case GMP_GMDT_S:
			{
				*((cp_short_t *)dest) = *(((gmdt_short_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_US:
			{
				*((cp_short_t *)dest) = *(((gmdt_ushort_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_IN:
			{
				*((cp_int32_t *)dest) = *(((gmdt_int_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_UIN:
			{
				*((cp_uint32_t *)dest) = *(((gmdt_uint_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_L:
			{
				*((cp_int64_t *)dest) = (cp_int64_t)(*(((gmdt_long_p_t*)gmdt)->data));
			}
			break;
			case GMP_GMDT_UL:
			{
				*((cp_uint64_t *)dest) = (cp_uint64_t)(*(((gmdt_ulong_p_t*)gmdt)->data));
			}
			break;
			case GMP_GMDT_F:
			case GMP_GMDT_UF:
			{
				*((cp_float_t *)dest) = *(((gmdt_float_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_D:
			case GMP_GMDT_UD:
			{
				*((cp_double_t *)dest) = *(((gmdt_double_p_t*)gmdt)->data);
			}
			break;
			case GMP_GMDT_T:
			{
				*((cp_uchar_t *)dest) = *(((gmdt_uchar_p_t*)gmdt)->data);
			}
			break;
			//容器类型(64--127):
			case GMP_GMDT_A:
			case GMP_GMDT_O:
			{
				*((gmp_gmdt_t**)dest) = gmdt;
			}
			break;
			case GMP_GMDT_X:
			case GMP_GMDT_JS:
			case GMP_GMDT_ST:
			{
				if (!((gmdt_string_p_t*)gmdt)->data || !(*(((gmdt_string_p_t*)gmdt)->len)))
				{
					cp_snprintf(buf, len, "element %s not value error.", name);
					return cp_false;
				}

				cp_char_t*				tmp_buf = (cp_char_t*)cp_malloc((*(((gmdt_string_p_t*)gmdt)->len)) + 1);

				if (tmp_buf) {
					cp_strncpy(tmp_buf, ((gmdt_string_p_t*)gmdt)->data, (*(((gmdt_string_p_t*)gmdt)->len)));
					tmp_buf[(*(((gmdt_string_p_t*)gmdt)->len))] = 0;
					cp_strncpy(dest, tmp_buf, dest_len);
					cp_free(tmp_buf);
					return cp_true;
				}
				else{
					cp_snprintf(buf, len, "element %s new error.", name);
					return cp_false;
				}
			}
			break;
			case GMP_GMDT_IOB:
			{
				*((gmp_gmdt_t**)dest) = gmdt;
			}
			break;
			//扩展类型(128--255):
			case GMP_GMDT_R:
			{
				*((gmp_gmdt_t**)dest) = gmdt;
			}
			break;
			case GMP_GMDT_RP:
			{
				*((gmp_gmdt_t**)dest) = gmdt;
			}
			break;
			default:
			{
				cp_snprintf(buf, len, "element %s unknow type[%d] error.", name, gmdt_type);
				return cp_false;
			}
			}
		}
	}

	return cp_true;
}


cp_bool_t get_gmf_element_key(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, cp_void_t *dest, cp_int32_t dest_len, gmp_gmdt gmdt_type, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdt_t						*gmdt;

	

	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "null gmf error.");
		return cp_false;
	}

	//获取gmdt的数值
	gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_key);
	if (!gmdt) {
		cp_snprintf(buf, len, "element get gmdu key error.");
		return cp_false;
	}
	else{
		if (gmdt_type != GMP_GMDT_UC) {
			//判断gmdt的类型是否相同
			if (*(((gmdt_type_p_t*)gmdt)->gmdt) != gmdt_type) {
				cp_snprintf(buf, len, "element type[0x%02X] error.",  *(((gmdt_type_p_t*)gmdt)->gmdt));
				return cp_false;
			}
		}
		else{
			if (*(((gmdt_type_p_t*)gmdt)->gmdt) > GMP_GMDT_T || *(((gmdt_type_p_t*)gmdt)->gmdt) < GMP_GMDT_B) {
				cp_snprintf(buf, len, "element type[0x%02X] error.", *(((gmdt_type_p_t*)gmdt)->gmdt));
				return cp_false;
			}
		}

		switch (gmdt_type) {
			//常用基础数据类型(0--63)
		case GMP_GMDT_B:
		{
			*((cp_bool_t *)dest) = *(((gmdt_bool_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_C:
		{
			*((cp_char_t*)dest) = *(((gmdt_char_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_UC:
		{
			if (*(((gmdt_type_p_t*)gmdt)->gmdt) == GMP_GMDT_IN) {
				*((cp_uchar_t *)dest) = (cp_uchar_t)(*(((gmdt_int_p_t*)gmdt)->data));
			}
			else{
				*((cp_uchar_t *)dest) = *(((gmdt_uchar_p_t*)gmdt)->data);
			}
		}
		break;
		case GMP_GMDT_S:
		{
			*((cp_short_t *)dest) = *(((gmdt_short_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_US:
		{
			*((cp_short_t *)dest) = *(((gmdt_ushort_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_IN:
		{
			*((cp_int32_t *)dest) = *(((gmdt_int_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_UIN:
		{
			*((cp_uint32_t *)dest) = *(((gmdt_uint_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_L:
		{
			*((cp_int64_t *)dest) = (cp_int64_t)(*(((gmdt_long_p_t*)gmdt)->data));
		}
		break;
		case GMP_GMDT_UL:
		{
			*((cp_uint64_t *)dest) = (cp_uint64_t)(*(((gmdt_ulong_p_t*)gmdt)->data));
		}
		break;
		case GMP_GMDT_F:
		case GMP_GMDT_UF:
		{
			*((cp_float_t *)dest) = *(((gmdt_float_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_D:
		case GMP_GMDT_UD:
		{
			*((cp_double_t *)dest) = *(((gmdt_double_p_t*)gmdt)->data);
		}
		break;
		case GMP_GMDT_T:
		{
			*((cp_uchar_t *)dest) = *(((gmdt_uchar_p_t*)gmdt)->data);
		}
		break;
		//容器类型(64--127):
		case GMP_GMDT_A:
		case GMP_GMDT_O:
		{
			*((gmp_gmdt_t**)dest) = gmdt;
		}
		break;
		case GMP_GMDT_X:
		case GMP_GMDT_JS:
		case GMP_GMDT_ST:
		{
			if (!((gmdt_string_p_t*)gmdt)->data || !(*(((gmdt_string_p_t*)gmdt)->len))) {
				cp_snprintf(buf, len, "element not key error.");
				return cp_false;
			}

			cp_char_t*				tmp_buf = (cp_char_t*)cp_malloc((*(((gmdt_string_p_t*)gmdt)->len)) + 1);

			if (tmp_buf) {
				cp_strncpy(tmp_buf, ((gmdt_string_p_t*)gmdt)->data, (*(((gmdt_string_p_t*)gmdt)->len)));
				tmp_buf[(*(((gmdt_string_p_t*)gmdt)->len))] = 0;
				cp_strncpy(dest, tmp_buf, dest_len);
				cp_free(tmp_buf);
				return cp_true;
			}
			else{
				cp_snprintf(buf, len, "element new error.");
				return cp_false;
			}
		}
		break;
		default:
		{
			cp_snprintf(buf, len, "element unknow type[%d] error.", gmdt_type);
			return cp_false;
		}
		}
	}

	return cp_true;
}

cp_bool_t get_gmf_element_str2char(gmp_gmf_t *gmf, cp_char_t *dest_buf, cp_int32_t dest_buf_len, gmp_gmdt gmdt_type, cp_char_t *name, cp_char_t *buf, cp_int32_t len)
{
	gmp_gmdu_t						*gmdu;
	gmp_gmdt_t						*gmdt;



	cp_memset(buf, 0, len);

	if (!gmf) {
		cp_snprintf(buf, len, "null gmf error.");
		return cp_false;
	}

	if (!gmp_chk_gmdt(gmdt_type)) {
		cp_snprintf(buf, len, "gmf gmdt[0x%02X] error.", gmdt_type);
		return cp_false;
	}

	//查找指定节点
	gmdt = gmp_create_gmdt(gmf, "%T%p%d", GMP_GMDT_ST, name, strlen(name));
	gmdu = gmp_find_gmdu(gmf, gmdt);
	if (!gmdu) {
		cp_snprintf(buf, len, "not %s element error.", name);
		return cp_false;
	}
	else{
		//获取gmdt的数值
		gmdt = gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
		if (!gmdt) {
			cp_snprintf(buf, len, "element %s not value error.", name);
			return cp_false;
		}
		else{
			if (gmdt_type != GMP_GMDT_UC) {
				//判断gmdt的类型是否相同
				if (*(((gmdt_type_p_t*)gmdt)->gmdt) != gmdt_type) {
					cp_snprintf(buf, len, "element %s type[0x%02X] error.", name, *(((gmdt_type_p_t*)gmdt)->gmdt));
					return cp_false;
				}
			}
			else{
				if (*(((gmdt_type_p_t*)gmdt)->gmdt) > GMP_GMDT_T || *(((gmdt_type_p_t*)gmdt)->gmdt) < GMP_GMDT_B) {
					cp_snprintf(buf, len, "element %s type[0x%02X] error.", name, *(((gmdt_type_p_t*)gmdt)->gmdt));
					return cp_false;
				}
			}

			switch (gmdt_type)
			{
				//常用基础数据类型(0--63)
			case GMP_GMDT_X:
			case GMP_GMDT_JS:
			case GMP_GMDT_ST:
			{
				if (!((gmdt_string_p_t*)gmdt)->data || !(*(((gmdt_string_p_t*)gmdt)->len))) {
					cp_snprintf(buf, len, "element %s not value error.", name);
					return cp_false;
				}

				if ((*(((gmdt_string_p_t*)gmdt)->len)) > 0 && (cp_int32_t)(*(((gmdt_string_p_t*)gmdt)->len)) < dest_buf_len) {
					cp_nbufstrncpy(dest_buf, dest_buf_len, ((gmdt_string_p_t*)gmdt)->data, (cp_int32_t)(*(((gmdt_string_p_t*)gmdt)->len)));
				}
				else{
					cp_snprintf(buf, len, "element %s new error. gmf len[%d] more than dest_buffer_length[%d]",
						name,
						(*(((gmdt_string_p_t*)gmdt)->len)),
						dest_buf_len);
					return cp_false;
				}
			}
			break;
			default:
			{
				cp_snprintf(buf, len, "element %s unknow type[%d] error.", name, gmdt_type);
				return cp_false;
			}
			}
		}
	}

	return cp_true;
}

cp_char_t *print_gmph_emh(cp_void_t *emh, cp_char_t *buf, cp_int32_t len, cp_bool_t is_show_all)
{
	cp_char_t				session_id[GMP_GMPH_SEMH_SESSION_ID_LEN + 1] = { 0, };
	gmp_gmph_bmh_t			*bmh;
	gmp_gmph_semh_t			*semh;
	gmp_gmph_ptpemh_t		*ptpemh;
	gmp_gmph_memh_t			*memh;



	cp_memset(buf, 0, len);
	bmh = (gmp_gmph_bmh_t*)emh;


	switch (bmh->emht)
	{
	case gmp_gmph_emh_type_null:
	{
		cp_snprintf(buf, len - 1, "emh0x%08X | 0x%02X]", bmh->gmpv, bmh->emht);
	}
	break;
	case gmp_gmph_emh_type_semh:
	{
		semh = (gmp_gmph_semh_t*)emh;
		cp_strncpy(session_id, semh->session_id, GMP_GMPH_SEMH_SESSION_ID_LEN);
		if (is_show_all) {
			cp_snprintf(buf, len - 1, "semh[0x%08X | 0x%02X - %d | %d | %d | %d | %s]"
				, semh->bmh.gmpv, semh->bmh.emht, semh->command, semh->length, semh->packet_no, semh->status, session_id);
		}
		else{
			cp_snprintf(buf, len - 1, "semh[-xx- %s -xx-]", session_id);
		}
	}
	break;
	case gmp_gmph_emh_type_ptpemh:
	{
		ptpemh = (gmp_gmph_ptpemh_t*)emh;
		cp_snprintf(buf, len - 1, "ptpemh[0x%08X | 0x%02X - %d | %d | 0x%02X | 0x%02X | %d/%d | %d/%d | %d/%d]"
			, ptpemh->bmh.gmpv, ptpemh->bmh.emht, ptpemh->command, ptpemh->status, ptpemh->device_type, ptpemh->heartbeat_interval
			, ptpemh->effective_precision_s, ptpemh->effective_precision_ns, ptpemh->current_precision_s, ptpemh->current_precision_ns, ptpemh->time_stamp_s, ptpemh->time_stamp_ns);
	}
	break;
	case gmp_gmph_emh_type_memh:
	{
		memh = (gmp_gmph_memh_t*)emh;
		cp_snprintf(buf, len - 1, "memh[0x%08X | 0x%02X - 0x%02X | 0x%02X | %d | %d | %d | %d | %d]"
			, memh->bmh.gmpv, memh->bmh.emht, memh->media_type, memh->packet_type, memh->field_id
			, memh->packet_no, memh->body_size, memh->time_stamp_s, memh->time_stamp_ns);
	}
	break;
	default:
	{
		cp_snprintf(buf, len - 1, "unknow gmph[0x%08X | 0x%02X]", bmh->gmpv, bmh->emht);
	}
	break;
	}

	return buf;
}


cp_char_t *print_gmf_version(gmp_gmf_t *gmf, cp_char_t *buf, cp_int32_t len)
{
	gm_std_int				ver;
	gm_std_char				ver_buf[CP_APP_DEFAULT_GMPH_BUFFER_LEN] = { 0, };



	cp_memset(buf, 0, len);

	if (gmp_get_version(gmf, &ver, ver_buf, CP_APP_DEFAULT_GMPH_BUFFER_LEN)) {
		cp_snprintf(buf, len - 1, "%s", ver_buf);
	}
	else{
		cp_snprintf(buf, len - 1, "GMF/unknow");
	}

	return buf;
}

cp_char_t *print_gmf_reason(gmp_gmf_t *gmf, gmp_gmdu_t *gmdu, cp_char_t *buf, cp_int32_t len)
{
	gmdt_string_p_t					*str = CP_NULL;
	cp_int32_t						num = len - 1;



	cp_memset(buf, 0, len);

	str = (gmdt_string_p_t*)gmp_get_gmdt(gmf, gmdu, gmp_gmdu_value);
	if (str && str->data) {
		if ((cp_int32_t)(*(str->len)) <= num) {
			cp_strncpy(buf, str->data, *(str->len));
		}
		else{
			cp_strncpy(buf, str->data, num);
		}
	}

	return buf;
}




