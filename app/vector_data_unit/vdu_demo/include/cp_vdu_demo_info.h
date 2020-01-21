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
/* ǰ���豸������Ϣ                                                     */
/************************************************************************/
struct cp_vdu_demo_info_s
{
	CP_APP_INFO_FIELDS
	cp_device_info_t				*device_info;																//���豸��Ϣ
	cp_device_info_t				*cener_server[CP_VDU_DEMO_MAX_CENTER_SERVER_NUMBER];							//��ʾ�����豸�б�
	cp_device_info_t				*client_background_server[CP_VDU_DEMO_MAX_CLIENT_SERVER_NUMBER];				//��ʾ�����豸�б�
	cp_device_info_t				*vdu_demo_background_server[CP_VDU_DEMO_MAX_IPC_SERVER_NUMBER];				//��ʾ�����豸�б�
	cp_device_info_t				*media_server[CP_VDU_DEMO_MAX_MEDIA_SERVER_NUMBER];							//��ʾý���豸�б�
	cp_media_play_manager_t			*media_play_manager;														//��ʾý�岥����Ϣ
	cp_heartbeat_manager_t			heartbeat_manager;															//��ʾ�����豸��������Ϣ
	cp_channel_manager_t			channel_manager;															//��ʾͨ����������Ϣ
	cp_timeval						registered_time;															//�ϴ�ע���ʱ��
	cp_bool_t						registered_flag;															//ע���ʶ,false��ʾע��ʧ�ܣ�true��ʾע��ɹ�
	cp_char_t						center_addr[CP_APP_DEFAULT_LENGTH];											//���ĵ�ַ
	cp_int32_t						center_port;																//���Ķ˿�
	cp_mutex_t						server_info_mutex;															//������Ϣ����ʹ�õ���
	cp_mutex_t						device_heartbeats_mutex;													//�豸������Ϣ����ʹ�õ���

};

#pragma pack()

cp_bool_t init_vdu_demo_info(cp_vdu_demo_t *vdu_demo, cp_vdu_demo_info_t *info);


#endif