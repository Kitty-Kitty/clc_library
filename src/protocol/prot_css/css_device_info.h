/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef _CSS_DEVICE_INFO_INCLUDE_H_
#define _CSS_DEVICE_INFO_INCLUDE_H_




#include "css_core.h"



#pragma pack(1)


/************************************************************************/
/* host                                                                 */
/************************************************************************/
typedef struct cp_host_s
{
	cp_uchar_t	 type;
	cp_int32_t	 status;
	cp_int32_t	 no;												//设备数字编号
	cp_int32_t	 group;												//表示设备缩在的组号
	cp_int32_t	 row;												//表是设备所在的行号
	cp_int32_t	 column;											//表示设备所在的列号
	cp_char_t	 number[CP_APP_DEFAULT_LENGTH];						//组行列编号01-02-03
	cp_char_t    id[CP_APP_DEFAULT_ID_LENGTH];
	cp_char_t    name[CP_APP_DEFAULT_STRING_LENGTH];
	cp_char_t	 passwd[CP_APP_DEFAULT_LENGTH];
	cp_char_t    version[CP_APP_DEFAULT_LENGTH];
	cp_char_t	 sn[CP_APP_DEFAULT_LENGTH];
}cp_host_t;

/************************************************************************/
/* 返回信息                                                             */
/************************************************************************/
typedef struct cp_return_info_s
{
	cp_char_t	host_id[CP_APP_DEFAULT_ID_LENGTH];					//表示主机的id
	cp_char_t	passwd[CP_APP_DEFAULT_LENGTH];
	cp_char_t	reason[CP_APP_DEFAULT_BUFFER_LENGTH];				//表示错误的原因
	cp_int32_t	status;												//表示设备的状态编码
}cp_return_info_t;

/************************************************************************/
/*  组播地址                                                            */
/************************************************************************/
typedef struct cp_multicast_addr_s
{
	cp_int32_t		port;											//表示组播端口号
	cp_char_t		ip[CP_APP_DEFAULT_STRING_LENGTH];				//表示组播ip地址
}cp_multicast_addr_t;

typedef struct cp_play_addr_s
{
	cp_int32_t		udp_port;										//媒体服务port
	cp_char_t		ip[CP_APP_DEFAULT_LENGTH];						//媒体服务ip
}cp_play_addr_t;

typedef struct cp_center_addr_s
{
	cp_int32_t		tcp_port;										//中心port
	cp_char_t		ip[CP_APP_DEFAULT_LENGTH];						//中心ip
}cp_center_addr_t;

typedef struct cp_dev_offline_info_s
{
	cp_char_t		id[CP_APP_DEFAULT_ID_LENGTH];					//设备ID
	cp_uchar_t		user_password;									//校验标识
}cp_dev_offline_info_t;

/************************************************************************/
/* 状态信息                                                             */
/************************************************************************/
typedef struct cp_information_info_s
{
	cp_uint32_t		current_disk;				//当前的磁盘空间（百分比：0~100）
	cp_uint32_t		current_memory;				//当前的内存空间（百分比：0~100）
	cp_uint32_t		current_cpu;				//当前的cpu使用率（百分比：0~100）
	cp_uint32_t		current_network;			//当前的网络带宽（单位：字节）
	cp_uint32_t		current_connect;			//当前的网络连接数（单位：个）
}cp_information_info_t;

/************************************************************************/
/* 串口信息                                                             */
/************************************************************************/
typedef struct cp_serial_s
{
	cp_int32_t		baudrate;
	cp_char_t		name[CP_APP_DEFAULT_LENGTH];
	cp_uchar_t		character_size;
	cp_uchar_t		flowcontrol[CP_APP_DEFAULT_LENGTH];
	cp_uchar_t		parity[CP_APP_DEFAULT_LENGTH];
	cp_double_t		stopbits;
}cp_serial_t;

/************************************************************************/
/* 网络配置                                                             */
/************************************************************************/
typedef struct cp_interface_s
{
	cp_int32_t		tcp_port;
	cp_int32_t		udp_port;
	cp_int64_t		packet_length;
	cp_uchar_t		used;
	cp_uchar_t		bootp;
	cp_char_t		ip[CP_APP_DEFAULT_LENGTH];
	cp_char_t		name[CP_APP_DEFAULT_LENGTH];
	cp_char_t		netmask[CP_APP_DEFAULT_LENGTH];
	cp_char_t		gateway[CP_APP_DEFAULT_LENGTH];
}cp_interface_t;

/************************************************************************/
/* 心跳信息																*/
/************************************************************************/
typedef struct cp_heartbeats_info_s
{
	cp_int32_t		times;
	cp_int32_t		interval_ms;
}cp_heartbeats_info_t;

/************************************************************************/
/* 硬件信息																*/
/************************************************************************/
typedef struct cp_hardware_info_s
{
	cp_uchar_t		limit_disk;
	cp_uchar_t		limit_memory;
	cp_uchar_t		limit_cpu;
	cp_uchar_t		limit_network;
	cp_uchar_t		limit_play_count;
	cp_uchar_t		luminance;
	cp_uchar_t		contrast;
	cp_uchar_t		color_temp;
	cp_uchar_t		background_color[CP_APP_DEFAULT_LENGTH];
	cp_int32_t		limit_connect;

	cp_uint32_t		resolution_width;
	cp_uint32_t		resolution_height;

	cp_uint32_t		cctv_size;									//表示屏幕尺寸 单位：英寸

	cp_bool_t		cctv_switch;								//表示屏幕开关

	cp_rect_t		border_size;								//表示屏幕边框上下左右尺寸
}cp_hardware_info_t;


/************************************************************************/
/* 同步信息                                                             */
/************************************************************************/
typedef struct cp_sync_info_s
{
	cp_bool_t		flag;
	cp_int32_t		value;
	cp_uint32_t		time_stamps;
	cp_uint32_t		time_stampns;
}cp_sync_info_t;

/************************************************************************/
/* 焦点信息                                                             */
/************************************************************************/
typedef struct cp_focus_info_s{

	cp_char_t		id[CP_APP_DEFAULT_ID_LENGTH];				//表示主机的id
	cp_uchar_t		focus;										//表示是否为焦点
	cp_uchar_t		focus_type;									//表示焦点时的状态显示类型
}cp_focus_info_t;

/************************************************************************/
/*设备基础信息                                                          */
/************************************************************************/
typedef struct cp_device_info_s
{
	cp_void_t						*data;
	cp_host_t						host;
	cp_serial_t						serials;
	cp_interface_t					network;
	cp_hardware_info_t				hardware;
	cp_multicast_addr_t				multicast_addr;
	cp_information_info_t			information;
	cp_sync_info_t					sync_info;
	cp_heartbeats_info_t			heart_info;
}cp_device_info_t;



#pragma pack()


#endif



