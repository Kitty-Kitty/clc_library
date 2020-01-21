/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-29

Description:

**************************************************************************/

#ifndef _CP_PLAYER_FUNC_THREAD_INCLUDE_H_
#define _CP_PLAYER_FUNC_THREAD_INCLUDE_H_



#include "cp_lockfree_queue.h"
#include "cp_player_func_manager_core.h"




#define		CP_PLAYER_FUNC_DEFAULT_THREAD_NUMBER											3					//��ʾ���������߳�����
#define		CP_PLAYER_FUNC_DEFAULT_INTERVAL_MS												10LL				//��ʾ�����߳�Ĭ�ϵ�����ʱ��
#define		CP_PLAYER_FUNC_DEFAULT_QUEUE_SIZE												1024				//��ʾ����Ĭ�ϵĶ��д�С
#define		CP_PLAYER_FUNC_DEFAULT_SLEEP_INTERVAL											10000000			//Ĭ�ϵ����߼��ʱ�䣬��λ����



//�������°�װ�˴�ӡ��Ϣ�ĸ�ʽ
#define	 cp_pftm_log(level, pftm, format, ...)												\
	do {																					\
		cp_module_log(level, (pftm)->func, format, ##__VA_ARGS__)							\
	;} while (0)																			\



//�������°�װ�˴�ӡ��Ϣ�ĸ�ʽ
#define	 cp_pft_log(level, pft, format, ...)												\
	do {																					\
			cp_module_log(level, (pft)->pftm->func, format, ##__VA_ARGS__)					\
	;} while (0)																			\



typedef struct cp_player_func_chunk_s									cp_player_func_chunk_t;
typedef enum cp_player_func_thread_status_enum							cp_player_func_thread_status_e;
typedef void(*cp_player_func_thread_cb)(cp_player_func_thread_t* pft);



#pragma pack(1)

enum cp_player_func_thread_status_enum
{
	cp_player_func_thread_status_init = 1,
	cp_player_func_thread_status_start,
	cp_player_func_thread_status_stop,
};

/************************************************************************/
/* ����func�̹߳�����                                                    */
/************************************************************************/
struct cp_player_func_thread_manager_s
{
	cp_int32_t							thread_number;					//��ʾ�߳�����
	cp_func_t							*func;							//��ʾ�ô����Ӧ��func�ṹ
	cp_buf_t							*precv_buf;						//��ʾ��һ����
	cp_array_t							thread_group;					//�߳���
	cp_int64_t							interval_ms;					//��ʾ����ʱ�䣬��λ΢�루ms��
	cp_pool_t							*pool;							//��ʾ������ʹ�õ��ڴ�ռ�
	cp_lockfree_queue_t					lq;								//��ʾ���
	cp_mutex_t							pfc_mutex;						//��ʾ������
	cp_mutex_t							pool_mutex;						//��ʾ�������ڴ�ռ���
};


/************************************************************************/
/* ����func�߳�                                                         */
/************************************************************************/
struct cp_player_func_thread_s
{
	cp_int32_t							index;							//��ʾ�����߳�������
	cp_player_func_thread_status_e		status;							//��ʾ�߳��˽�״̬
	cp_player_func_thread_manager_t		*pftm;							//��ʾ�����̹߳�����
	cp_thread_t							*thread;						//��ʾ��ǰ�߳�
	cp_int64_t							interval_ms;					//��ʾ����ʱ�䣬��λ΢�루ms��
	cp_player_func_thread_cb			pft_cb;							//��ʾ�����̵߳Ĵ���
};


/************************************************************************/
/* ���崦�����ݽṹ                                                      */
/************************************************************************/
struct cp_player_func_chunk_s
{
	cp_lockfree_queue_element_t			lq_elem;						//���нڵ�����
	cp_socket_t							*socket;						//��ǰ��
	cp_int32_t							nread;							//��ǰ�� ������
	cp_buf_t							*buf;							//
	cp_int32_t							status;
};

#pragma pack()

/************************************************************************/
/* ����                                                                 */
/************************************************************************/
cp_player_func_thread_manager_t* make_player_func_thread_manager(cp_func_t *func);
cp_int32_t unmake_player_func_thread_manager(cp_player_func_thread_manager_t *pftm);

/************************************************************************/
/* ����player func chunk����                                             */
/************************************************************************/
cp_int32_t push_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm, cp_socket_t *socket, gmp_gmph_semh_t *semh);
cp_player_func_chunk_t* pop_semh_player_func_chunk(cp_player_func_thread_manager_t *pftm);


#endif