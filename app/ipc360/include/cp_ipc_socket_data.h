/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-28

Description:

**************************************************************************/

#ifndef _CP_IPC_SOCKET_DATA_INCLUDE_H_
#define _CP_IPC_SOCKET_DATA_INCLUDE_H_


#include "cp_ipc_core.h"
#include "cp_min_heap.h"
#include "cp_lockfree_queue.h"




typedef struct	cp_min_heap											cp_min_heap_t;
typedef struct	cp_min_heap_node									cp_min_heap_node_t;
typedef enum	cp_socket_data_type_enum							cp_socket_data_type_e;
typedef struct	cp_rtp_socket_data_s								cp_rtp_socket_data_t;
typedef struct cp_min_heap_socket_data_s							cp_min_heap_socket_data_t;
typedef struct	cp_socket_buffer_data_s								cp_socket_buffer_data_t;



/************************************************************************/
/* ��ʾĬ�ϵĶ��д�С                                                    */
/************************************************************************/
#define CP_IPC_SOCKET_DATA_QUEUE_LENGTH								512



#pragma pack(1)

/************************************************************************/
/*��ʾsocket data������                                                  */
/************************************************************************/
enum cp_socket_data_type_enum
{
	cp_socket_data_rtp = 1,
};


/************************************************************************/
/* ��ʾsocket rtp data                                                 */
/************************************************************************/
struct cp_rtp_socket_data_s
{
	cp_int32_t							module_type;			//��ʾģ������
	cp_socket_data_type_e				type;					//��ʾ��������
	cp_void_t							*data;					//��ʾ������Ϣ
	cp_int32_t							max_cache_size;			//��ʾ��󻺴�����
	cp_int64_t							length;					//��ʾ������
	cp_lockfree_queue_t					cache_lq;				//��ʾ���ݻ��������Ϣ
	cp_lockfree_queue_t					data_lq;				//��ʾ���ݶ�����Ϣ
};


/************************************************************************/
/* ��С��ʹ�õĽڹ�����                                                  */
/************************************************************************/
struct cp_min_heap_socket_data_s
{
	cp_min_heap_node_t					node;
	int									index;
	cp_socket_buffer_data_t				*sbd;
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_socket_buffer_data_s
{
	cp_lockfree_queue_element_t			lq_elem;				//���нڵ�����
	cp_min_heap_socket_data_t			mh_elemn;				//��С�ѽڹ�
	cp_buf_t							buf;					//������ڴ�����
};


#pragma pack()


//����socket data
cp_void_t*	create_socket_data(cp_pool_t *pool, cp_socket_data_type_e type);
cp_rtp_socket_data_t*	create_rtp_socket_data(cp_pool_t *pool);

//����socket data
cp_int32_t destroy_socket_data(cp_pool_t *pool, cp_void_t *socket_data);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_a_rtp_socket_buffer
*
* ����˵��: ����һ��
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_rtp_socket_data_t * ssd						[in]����˵��
* ��    ��: cp_int32_t size						[in]����˵��
*
* �� �� ֵ: cp_buf_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-28 15:11:32
******************************************************************************************************/
cp_buf_t* create_a_rtp_socket_buffer(cp_pool_t *pool, cp_rtp_socket_data_t *ssd, cp_int32_t size);


cp_int32_t destroy_a_rtp_socket_buffer(cp_pool_t *pool, cp_rtp_socket_data_t *ssd, cp_buf_t *buf);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: push_a_rtp_socket_buffer
*
* ����˵��: ����һ��get_a_xxxx_socket_buffer������buffer
*
* ��    ��: cp_rtp_socket_data_t * ssd						[in]����˵��
* ��    ��: cp_buf_t * buf						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����Ĳ����֧��get_a_xxxx_socket_buffer������buffer
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-28 15:14:45
******************************************************************************************************/
cp_int32_t push_a_rtp_socket_buffer(cp_rtp_socket_data_t *ssd, cp_buf_t *buf);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: pop_a_rtp_socket_buffer
*
* ����˵��: �Ӷ����е���һ��socket buffer
*
* ��    ��: cp_rtp_socket_data_t * ssd						[in]����˵��
*
* �� �� ֵ: cp_buf_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-28 15:26:58
******************************************************************************************************/
cp_buf_t* pop_a_rtp_socket_buffer(cp_rtp_socket_data_t *ssd);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_rtp_socket_buffer_length
*
* ����˵��: 
*
* ��    ��: cp_rtp_socket_data_t * ssd						[in]����˵��
*
* �� �� ֵ: cp_int64_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-11-28 18:44:57
******************************************************************************************************/
cp_int64_t get_rtp_socket_buffer_length(cp_rtp_socket_data_t *ssd);


#endif