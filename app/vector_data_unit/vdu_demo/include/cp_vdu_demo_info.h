/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CP_VDU_DEMO_INFO_INCLUDE_H_
#define _CP_VDU_DEMO_INFO_INCLUDE_H_




#include "cp_vdu_demo_core.h"




//typedef struct cp_vdu_demo_info_s					cp_vdu_demo_info_t;




#pragma pack(1)

/************************************************************************/
/* 前端设备基础信息                                                     */
/************************************************************************/
struct cp_vdu_demo_info_s
{
	CP_APP_INFO_FIELDS
	cp_device_info_t				*device_info;																//本设备信息
	cp_device_info_t				*cener_server[CP_VDU_DEMO_MAX_CENTER_SERVER_NUMBER];							//表示中心设备列表
	cp_device_info_t				*client_background_server[CP_VDU_DEMO_MAX_CLIENT_SERVER_NUMBER];				//表示回显设备列表
	cp_device_info_t				*vdu_demo_background_server[CP_VDU_DEMO_MAX_IPC_SERVER_NUMBER];				//表示背景设备列表
	cp_device_info_t				*media_server[CP_VDU_DEMO_MAX_MEDIA_SERVER_NUMBER];							//表示媒体设备列表
	cp_media_play_manager_t			*media_play_manager;														//表示媒体播放信息
	cp_heartbeat_manager_t			heartbeat_manager;															//表示所有设备的心跳信息
	cp_channel_manager_t			channel_manager;															//表示通道管理器信息
	cp_timeval						registered_time;															//上次注册的时间
	cp_bool_t						registered_flag;															//注册标识,false表示注册失败；true表示注册成功
	cp_char_t						center_addr[CP_APP_DEFAULT_LENGTH];											//中心地址
	cp_int32_t						center_port;																//中心端口
	cp_mutex_t						server_info_mutex;															//服务信息更新使用的锁
	cp_mutex_t						device_heartbeats_mutex;													//设备心跳信息更新使用的锁

};

#pragma pack()

cp_bool_t init_vdu_demo_info(cp_vdu_demo_t *vdu_demo, cp_vdu_demo_info_t *info);


#endif