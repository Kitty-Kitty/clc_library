/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_PLAYER_INFO_INCLUDE_H_
#define _CP_PLAYER_INFO_INCLUDE_H_




#include "cp_player_core.h"




//typedef struct cp_player_info_s					cp_player_info_t;




#pragma pack(1)

/************************************************************************/
/* 前端设备基础信息                                                     */
/************************************************************************/
struct cp_player_info_s
{
	CP_APP_INFO_FIELDS
	cp_device_info_t				*device_info;																//本设备信息
	cp_device_info_t				*cener_server[CP_PLAYER_MAX_CENTER_SERVER_NUMBER];							//表示中心设备列表
	cp_device_info_t				*client_background_server[CP_PLAYER_MAX_CLIENT_SERVER_NUMBER];				//表示回显设备列表
	cp_device_info_t				*player_background_server[CP_PLAYER_MAX_PLAYER_SERVER_NUMBER];				//表示背景设备列表
	cp_device_info_t				*media_server[CP_PLAYER_MAX_MEDIA_SERVER_NUMBER];							//表示媒体设备列表
	cp_media_play_manager_t			*media_play_manager;														//表示媒体播放信息
	cp_socket_t						*register_socket;															//表示注册用的socket
	cp_heartbeat_manager_t			heartbeat_manager;															//表示所有设备的心跳信息
	cp_player_timestamp_t			player_timestamp;															//表示组时间
	cp_timeval						registered_time;															//上次注册的时间
	cp_bool_t						registered_flag;															//注册标识,false表示注册失败；true表示注册成功
	cp_char_t						center_addr[CP_APP_DEFAULT_LENGTH];											//中心地址
	cp_int32_t						center_port;																//中心端口
	cp_mutex_t						server_info_mutex;															//服务信息更新使用的锁
	cp_mutex_t						device_heartbeats_mutex;													//设备心跳信息更新使用的锁

};

#pragma pack()

cp_int32_t init_player_info(cp_player_t *player, cp_player_info_t *info);


#endif