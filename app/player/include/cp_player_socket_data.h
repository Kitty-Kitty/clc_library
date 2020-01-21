/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-28

Description:

**************************************************************************/

#ifndef _CP_PLAYER_SOCKET_DATA_INCLUDE_H_
#define _CP_PLAYER_SOCKET_DATA_INCLUDE_H_


#include "cp_player_core.h"
#include "cp_min_heap.h"
#include "cp_safe_queue.h"




typedef struct	cp_min_heap											cp_min_heap_t;
typedef struct	cp_min_heap_node									cp_min_heap_node_t;
typedef enum	cp_socket_data_type_enum							cp_socket_data_type_e;


typedef struct	cp_css_socket_data_s								cp_css_socket_data_t;
typedef struct	cp_semh_socket_data_s								cp_semh_socket_data_t;
typedef struct	cp_memh_socket_data_s								cp_memh_socket_data_t;


typedef struct	cp_min_heap_socket_data_s							cp_min_heap_socket_data_t;
typedef struct	cp_socket_buffer_data_s								cp_socket_buffer_data_t;



/************************************************************************/
/* ��ʾĬ�ϵĶ��д�С                                                    */
/************************************************************************/
#define CP_PLAYER_SOCKET_DATA_QUEUE_LENGTH							1024



#pragma pack(1)


/************************************************************************/
/*��ʾsocket data������                                                  */
/************************************************************************/
enum cp_socket_data_type_enum
{
	cp_socket_data_semh = 1,
	cp_socket_data_memh,
};


/************************************************************************/
/* ��ʾcss socket data                                                  */
/************************************************************************/
struct cp_css_socket_data_s
{
	cp_int32_t							module_type;			//��ʾģ������
	cp_socket_data_type_e				type;					//��ʾ��������
	cp_void_t							*data;					//��ʾ������Ϣ
	cp_int32_t							max_cache_size;			//��ʾ��󻺴�����
	cp_atomic64_t						length;					//��ʾ������
	cp_safe_queue_t						*cache_sq;				//��ʾ���ݻ��������Ϣ
	cp_safe_queue_t						*data_sq;				//��ʾ���ݶ�����Ϣ
};


/************************************************************************/
/* ��ʾsocket semh data                                                 */
/************************************************************************/
struct cp_semh_socket_data_s
{
	cp_css_socket_data_t				sd;						//��ʾcss�������ݿ�����
};


/************************************************************************/
/* ��ʾsocket memh data                                                 */
/************************************************************************/
struct cp_memh_socket_data_s
{
	cp_css_socket_data_t				sd;						//��ʾcss�������ݿ�����
	cp_min_heap_t						data_mh;				//��ʾ������С��
};


/************************************************************************/
/* ��С��ʹ�õĽڹ�����                                                  */
/************************************************************************/
struct cp_min_heap_socket_data_s
{
	cp_min_heap_node_t					node;
	cp_int32_t							index;
	cp_socket_buffer_data_t				*sbd;
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_socket_buffer_data_s
{
	cp_min_heap_socket_data_t			mh_elemn;				//��С�ѽڹ�
	cp_buf_t							buf;					//������ڴ�����
};


#pragma pack()


//����socket data
cp_void_t*	create_socket_data(cp_pool_t *pool, cp_socket_data_type_e type);
cp_semh_socket_data_t*	create_semh_socket_data(cp_pool_t *pool);
cp_memh_socket_data_t*	create_memh_socket_data(cp_pool_t *pool);

//����socket data
cp_int32_t destroy_socket_data(cp_pool_t *pool, cp_void_t *socket_data);


/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_a_semh_socket_buffer
*
* ����˵��: ����һ��
*
* ��    ��: cp_pool_t * pool						[in]����˵��
* ��    ��: cp_semh_socket_data_t * ssd						[in]����˵��
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
cp_buf_t* create_a_semh_socket_buffer(cp_pool_t *pool, cp_semh_socket_data_t *ssd, cp_int32_t size);
cp_buf_t* create_a_memh_socket_buffer(cp_pool_t *pool, cp_memh_socket_data_t *msd, cp_int32_t size);


cp_int32_t destroy_a_semh_socket_buffer(cp_pool_t *pool, cp_semh_socket_data_t *ssd, cp_buf_t *buf);
cp_int32_t destroy_a_memh_socket_buffer(cp_pool_t *pool, cp_memh_socket_data_t *ssd, cp_buf_t *buf);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: push_a_semh_socket_buffer
*
* ����˵��: ����һ��get_a_xxxx_socket_buffer������buffer
*
* ��    ��: cp_semh_socket_data_t * ssd						[in]����˵��
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
cp_int32_t push_a_semh_socket_buffer(cp_semh_socket_data_t *ssd, cp_buf_t *buf);
cp_int32_t push_a_memh_socket_buffer(cp_memh_socket_data_t *msd, cp_buf_t *buf);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: pop_a_semh_socket_buffer
*
* ����˵��: �Ӷ����е���һ��socket buffer
*
* ��    ��: cp_semh_socket_data_t * ssd						[in]����˵��
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
cp_buf_t* pop_a_semh_socket_buffer(cp_semh_socket_data_t *ssd);
cp_buf_t* pop_a_memh_socket_buffer(cp_memh_socket_data_t *msd);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_semh_socket_buffer_length
*
* ����˵��: 
*
* ��    ��: cp_semh_socket_data_t * ssd						[in]����˵��
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
cp_int64_t get_semh_socket_buffer_length(cp_semh_socket_data_t *ssd);
cp_int64_t get_memh_socket_buffer_length(cp_memh_socket_data_t *msd);



/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: get_memh_socket_buffer_func
*
* ����˵��: ��ȡ����func���
*
* ��    ��: cp_memh_socket_data_t * msd						[in]����˵��
*
* �� �� ֵ: cp_func_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-05 15:14:01
******************************************************************************************************/
cp_func_t *get_memh_socket_buffer_func(cp_memh_socket_data_t *msd);
cp_int32_t set_memh_socket_buffer_func(cp_memh_socket_data_t *msd, cp_func_t *func);

#endif