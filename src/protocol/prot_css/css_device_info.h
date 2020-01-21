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
	cp_int32_t	 no;												//�豸���ֱ��
	cp_int32_t	 group;												//��ʾ�豸���ڵ����
	cp_int32_t	 row;												//�����豸���ڵ��к�
	cp_int32_t	 column;											//��ʾ�豸���ڵ��к�
	cp_char_t	 number[CP_APP_DEFAULT_LENGTH];						//�����б��01-02-03
	cp_char_t    id[CP_APP_DEFAULT_ID_LENGTH];
	cp_char_t    name[CP_APP_DEFAULT_STRING_LENGTH];
	cp_char_t	 passwd[CP_APP_DEFAULT_LENGTH];
	cp_char_t    version[CP_APP_DEFAULT_LENGTH];
	cp_char_t	 sn[CP_APP_DEFAULT_LENGTH];
}cp_host_t;

/************************************************************************/
/* ������Ϣ                                                             */
/************************************************************************/
typedef struct cp_return_info_s
{
	cp_char_t	host_id[CP_APP_DEFAULT_ID_LENGTH];					//��ʾ������id
	cp_char_t	passwd[CP_APP_DEFAULT_LENGTH];
	cp_char_t	reason[CP_APP_DEFAULT_BUFFER_LENGTH];				//��ʾ�����ԭ��
	cp_int32_t	status;												//��ʾ�豸��״̬����
}cp_return_info_t;

/************************************************************************/
/*  �鲥��ַ                                                            */
/************************************************************************/
typedef struct cp_multicast_addr_s
{
	cp_int32_t		port;											//��ʾ�鲥�˿ں�
	cp_char_t		ip[CP_APP_DEFAULT_STRING_LENGTH];				//��ʾ�鲥ip��ַ
}cp_multicast_addr_t;

typedef struct cp_play_addr_s
{
	cp_int32_t		udp_port;										//ý�����port
	cp_char_t		ip[CP_APP_DEFAULT_LENGTH];						//ý�����ip
}cp_play_addr_t;

typedef struct cp_center_addr_s
{
	cp_int32_t		tcp_port;										//����port
	cp_char_t		ip[CP_APP_DEFAULT_LENGTH];						//����ip
}cp_center_addr_t;

typedef struct cp_dev_offline_info_s
{
	cp_char_t		id[CP_APP_DEFAULT_ID_LENGTH];					//�豸ID
	cp_uchar_t		user_password;									//У���ʶ
}cp_dev_offline_info_t;

/************************************************************************/
/* ״̬��Ϣ                                                             */
/************************************************************************/
typedef struct cp_information_info_s
{
	cp_uint32_t		current_disk;				//��ǰ�Ĵ��̿ռ䣨�ٷֱȣ�0~100��
	cp_uint32_t		current_memory;				//��ǰ���ڴ�ռ䣨�ٷֱȣ�0~100��
	cp_uint32_t		current_cpu;				//��ǰ��cpuʹ���ʣ��ٷֱȣ�0~100��
	cp_uint32_t		current_network;			//��ǰ�����������λ���ֽڣ�
	cp_uint32_t		current_connect;			//��ǰ����������������λ������
}cp_information_info_t;

/************************************************************************/
/* ������Ϣ                                                             */
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
/* ��������                                                             */
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
/* ������Ϣ																*/
/************************************************************************/
typedef struct cp_heartbeats_info_s
{
	cp_int32_t		times;
	cp_int32_t		interval_ms;
}cp_heartbeats_info_t;

/************************************************************************/
/* Ӳ����Ϣ																*/
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

	cp_uint32_t		cctv_size;									//��ʾ��Ļ�ߴ� ��λ��Ӣ��

	cp_bool_t		cctv_switch;								//��ʾ��Ļ����

	cp_rect_t		border_size;								//��ʾ��Ļ�߿��������ҳߴ�
}cp_hardware_info_t;


/************************************************************************/
/* ͬ����Ϣ                                                             */
/************************************************************************/
typedef struct cp_sync_info_s
{
	cp_bool_t		flag;
	cp_int32_t		value;
	cp_uint32_t		time_stamps;
	cp_uint32_t		time_stampns;
}cp_sync_info_t;

/************************************************************************/
/* ������Ϣ                                                             */
/************************************************************************/
typedef struct cp_focus_info_s{

	cp_char_t		id[CP_APP_DEFAULT_ID_LENGTH];				//��ʾ������id
	cp_uchar_t		focus;										//��ʾ�Ƿ�Ϊ����
	cp_uchar_t		focus_type;									//��ʾ����ʱ��״̬��ʾ����
}cp_focus_info_t;

/************************************************************************/
/*�豸������Ϣ                                                          */
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



