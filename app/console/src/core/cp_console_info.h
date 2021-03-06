/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_PLAYER_INFO_INCLUDE_H_
#define _CP_PLAYER_INFO_INCLUDE_H_




#include "cp_player_core.h"




typedef struct cp_player_info_s					cp_player_info_t;


#pragma pack(1)

/************************************************************************/
/* 前端设备基础信息                                                     */
/************************************************************************/
struct cp_player_info_s
{
	CP_APP_INFO_FIELDS
	cp_device_info_t				*device_info;							//本设备信息
	cp_queue_t						cener_server;							//表示设备列表
	cp_queue_t						client_server;							//表示设备列表
	cp_queue_t						player_server;							//表示设备列表
	cp_queue_t						media_server;							//表示设备列表
	cp_bool_t						registered_flag;						//注册标识
	cp_char_t						center_addr[CP_APP_DEFAULT_LENGTH];		//中心地址
	cp_int32_t						center_port;							//中心端口

	cp_multicast_addr_t				multicast_addr;							//组播地址


	cp_char_t						local_addr[CP_APP_DEFAULT_LENGTH];		//本地地址
	cp_int32_t						local_tcp_port;							//本地TCP端口
	cp_int32_t						local_udp_port;							//本地TCP端口
};

#pragma pack()

cp_bool_t init_player_info(cp_player_t *player, cp_player_info_t *info);


#endif