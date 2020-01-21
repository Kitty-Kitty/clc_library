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
/* ǰ���豸������Ϣ                                                     */
/************************************************************************/
struct cp_player_info_s
{
	CP_APP_INFO_FIELDS
	cp_device_info_t				*device_info;							//���豸��Ϣ
	cp_queue_t						cener_server;							//��ʾ�豸�б�
	cp_queue_t						client_server;							//��ʾ�豸�б�
	cp_queue_t						player_server;							//��ʾ�豸�б�
	cp_queue_t						media_server;							//��ʾ�豸�б�
	cp_bool_t						registered_flag;						//ע���ʶ
	cp_char_t						center_addr[CP_APP_DEFAULT_LENGTH];		//���ĵ�ַ
	cp_int32_t						center_port;							//���Ķ˿�

	cp_multicast_addr_t				multicast_addr;							//�鲥��ַ


	cp_char_t						local_addr[CP_APP_DEFAULT_LENGTH];		//���ص�ַ
	cp_int32_t						local_tcp_port;							//����TCP�˿�
	cp_int32_t						local_udp_port;							//����TCP�˿�
};

#pragma pack()

cp_bool_t init_player_info(cp_player_t *player, cp_player_info_t *info);


#endif