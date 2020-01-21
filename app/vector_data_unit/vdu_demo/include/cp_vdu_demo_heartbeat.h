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



#define	CP_VDU_DEMO_HEARTBEAT_DEFAULT_INTERVAL_NS			10000000000LL			//��ʾĬ�ϵ�������ֵ
#define	CP_VDU_DEMO_HEARTBEAT_MIN_INTERVAL_NS				1000000000LL			//��ʾ��С��������ֵ


typedef struct cp_device_info_s							cp_device_info_t;
typedef struct cp_device_heartbeat_s					cp_device_heartbeat_t;
typedef struct cp_heartbeat_address_s					cp_heartbeat_address_t;
typedef struct cp_heartbeat_manager_s					cp_heartbeat_manager_t;


/************************************************************************/
/* �豸������Ϣ                                                          */
/************************************************************************/
struct cp_device_heartbeat_s
{
	cp_heartbeat_manager_t			*heartbeat_manager;							//��ʾ������Ӧ�Ĺ�������ַ
	cp_device_info_t				*di;										//��ʾ�豸��Ϣָ��
	cp_uchar_t						type;										//��ʾ�豸����
	cp_int32_t						udp_port;									//��ʾ���͵�Ŀ�Ķ˿�
	cp_atomic_t						send_times;									//��ʾ�������͵Ĵ���
	cp_sockaddr_in					hearbeat_address;							//�������͵�Ŀ�ĵ�ַ
	cp_char_t						ip[CP_APP_DEFAULT_LENGTH];					//��ʾ������Ҫ���͵�Ŀ��ip��ַ
	cp_char_t						id[CP_APP_DEFAULT_ID_LENGTH];				//��ʾ������id
	cp_char_t						device_info_data[CP_VDU_DEMO_HEARTBEAT_DEFAULT_BUFFER_LENGTH];							//���浱ǰ����ģ����ڴ�ӡ���豸��Ϣ
	cp_lockfree_queue_element_t		lf_queue_element;							//��ʾ�����ڵ���Ϣ
};



/************************************************************************/
/* �豸����������                                                        */
/************************************************************************/
struct cp_heartbeat_manager_s
{
	cp_app_t						*app;													//��ʾ����������������app��ַ
	cp_log_t						*logger;												//��ʾ��־loggerָ��
	cp_socket_t						*heartbeat_udp_listen;									//��ʾ����������UDP����
	cp_mpool_t						*mpool;													//heartbeatmanager�Դ��ļ��ڴ����
	//cp_device_heartbeat_t			*device_heartbeats[CP_VDU_DEMO_MAX_DEVICE_NUMBER];		//��Ҫ����������������Ӧ������������Ϣ
	cp_array_t						device_heartbeats;										//��Ҫ����������������Ӧ������������Ϣ
	cp_array_t						failed_device_heartbeats;								//��Ҫ���������豸��device�б�
	cp_buf_t						heartbeat_data;											//���浱ǰ���ɵ���������
	cp_int32_t						local_heartbeat_udp_port;								//���ط�������UDP�˿�
	cp_int64_t						heartbeat_interval_ms;									//��ʾ�������ʱ��
	cp_queue_t						heartbeat_addresses_queue;								//��ʾ��ַ����Ķ�����Ϣ
	cp_mutex_t						heartbeat_addresses_mutex;								//��ַʹ�õĶ���
	cp_lockfree_queue_t				lockfree_queue;											//��ʾ��ǰ�ķ��Ͷ���
};


/************************************************************************/
/* �����������Ĵ�����                                                  */
/************************************************************************/
int init_heartbeat_manager(cp_app_t	*app, cp_heartbeat_manager_t *hm);
int start_heartbeat_manager(cp_heartbeat_manager_t *hm);
int stop_heartbeat_manager(cp_heartbeat_manager_t *hm);

int init_device_heartbeat(cp_heartbeat_manager_t *hm, cp_device_heartbeat_t *dhb);
int send_device_heartbeat(cp_heartbeat_manager_t *hm, cp_device_heartbeat_t *dhb);
cp_device_heartbeat_t *get_device_heartbeat(cp_heartbeat_manager_t *hm);

#endif





