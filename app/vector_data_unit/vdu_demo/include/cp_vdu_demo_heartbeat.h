/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-19

Description:heartbeat information

**************************************************************************/

#ifndef _CP_VDU_DEMO_HEARTBEAT_INCLUDE_H_
#define _CP_VDU_DEMO_HEARTBEAT_INCLUDE_H_


#include "cp_lockfree_queue.h"
#include "cp_vdu_demo_hook_core.h"



#define	CP_VDU_DEMO_HEARTBEAT_DEFAULT_INTERVAL_NS			10000000000LL			//表示默认的心跳数值
#define	CP_VDU_DEMO_HEARTBEAT_MIN_INTERVAL_NS				1000000000LL			//表示最小的心跳数值


typedef struct cp_device_info_s							cp_device_info_t;
typedef struct cp_device_heartbeat_s					cp_device_heartbeat_t;
typedef struct cp_heartbeat_address_s					cp_heartbeat_address_t;
typedef struct cp_heartbeat_manager_s					cp_heartbeat_manager_t;


/************************************************************************/
/* 设备心跳信息                                                          */
/************************************************************************/
struct cp_device_heartbeat_s
{
	cp_heartbeat_manager_t			*heartbeat_manager;							//表示心跳对应的管理器地址
	cp_device_info_t				*di;										//表示设备信息指针
	cp_uchar_t						type;										//表示设备类型
	cp_int32_t						udp_port;									//表示发送的目的端口
	cp_atomic_t						send_times;									//表示连续发送的次数
	cp_sockaddr_in					hearbeat_address;							//心跳发送的目的地址
	cp_char_t						ip[CP_APP_DEFAULT_LENGTH];					//表示心跳需要发送的目的ip地址
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];				//表示主机的id
	cp_char_t						device_info_data[CP_VDU_DEMO_HEARTBEAT_DEFAULT_BUFFER_LENGTH];							//保存当前保存的，用于打印的设备信息
	cp_lockfree_queue_element_t		lf_queue_element;							//表示心跳节点信息
};



/************************************************************************/
/* 设备心跳管理器                                                        */
/************************************************************************/
struct cp_heartbeat_manager_s
{
	cp_app_t						*app;													//表示心跳管理器所属的app地址
	cp_log_t						*logger;												//表示日志logger指针
	cp_socket_t						*heartbeat_udp_listen;									//表示发送心跳的UDP监听
	cp_mpool_t						*mpool;													//heartbeatmanager自带的简单内存管理
	//cp_device_heartbeat_t			*device_heartbeats[CP_VDU_DEMO_MAX_DEVICE_NUMBER];		//主要描述各个服务器对应的心跳发送信息
	cp_array_t						device_heartbeats;										//主要描述各个服务器对应的心跳发送信息
	cp_array_t						failed_device_heartbeats;								//主要描述错误设备的device列表
	cp_buf_t						heartbeat_data;											//保存当前生成的心跳数据
	cp_int32_t						local_heartbeat_udp_port;								//本地发送心跳UDP端口
	cp_int64_t						heartbeat_interval_ms;									//表示心跳间隔时间
	cp_queue_t						heartbeat_addresses_queue;								//表示地址保存的队列信息
	cp_mutex_t						heartbeat_addresses_mutex;								//地址使用的队列
	cp_lockfree_queue_t				lockfree_queue;											//表示当前的发送队列
};


/************************************************************************/
/* 心跳管理器的处理方法                                                  */
/************************************************************************/
int init_heartbeat_manager(cp_app_t	*app, cp_heartbeat_manager_t *hm);
int start_heartbeat_manager(cp_heartbeat_manager_t *hm);
int stop_heartbeat_manager(cp_heartbeat_manager_t *hm);

int init_device_heartbeat(cp_heartbeat_manager_t *hm, cp_device_heartbeat_t *dhb);
int send_device_heartbeat(cp_heartbeat_manager_t *hm, cp_device_heartbeat_t *dhb);
cp_device_heartbeat_t *get_device_heartbeat(cp_heartbeat_manager_t *hm);

#endif





