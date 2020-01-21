/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-13

Description:

**************************************************************************/

#ifndef _CP_SAFE_QUEUE_INCLUDE_H_
#define _CP_SAFE_QUEUE_INCLUDE_H_


#include <stdio.h>
#include <stdlib.h>
#include "cp_lockfree_queue.h"



typedef struct cp_safe_queue_struct							cp_safe_queue_t;




#pragma pack(1)

typedef enum cp_safe_queue_mode_enum
{
	cp_safe_queue_mode_none,
	//////////////////////////////////////////////////////////////////////////
	//������ֶ�������

	cp_safe_queue_mode_qbmm,										/*��ʾ�����ƶ��У���Ҫע����ƶ��е������������ƿ��ܵ������ݶ�ʧ�� ���ֶ�����Ҫset option cp_safe_queue_option_bounded*/
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
	cp_safe_queue_mode_qumm											/*�����ƶ��У����ֶ��п��ܵ����ڴ治������*/
#endif
	cp_safe_queue_mode_qbss,										/*��ʾ�����ƶ��У��������ߵ�������*/

	//////////////////////////////////////////////////////////////////////////
	cp_safe_queue_mode_tail
}cp_safe_queue_mode_e;



struct cp_safe_queue_struct
{
	cp_safe_queue_mode_e					mode;					//��ʾ��������
	cp_lockfree_queue_t						free_lq;				//��ʾ���ݻ��������Ϣ
	cp_lockfree_queue_t						busy_lq;				//��ʾ���ݶ�����Ϣ
	cp_lockfree_queue_element_t				*lq_elem;				//��ʾ����Ԫ��
	int										lq_elem_size;			//��ʾ����Ԫ������
	unsigned char							is_genera:1;			//��ʾ���洴��
};


#pragma pack()

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_create_general_safe_queue
*
* ����˵��: ����һ���������
*
* ��    ��: cp_safe_queue_mode_e mode						[in]����˵��
* ��    ��: int size						[in]����˵��
*
* �� �� ֵ: cp_safe_queue_t*
*      �� null  : �ɹ� 
*         null  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:18:00
******************************************************************************************************/
cp_safe_queue_t* cp_create_general_safe_queue(cp_safe_queue_mode_e mode, int size);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_create_memory_safe_queue
*
* ����˵��: ��ָ���ڴ洴������
*
* ��    ��: void * memory						[in]����˵��
* ��    ��: int memory_size						[in]����˵��
* ��    ��: cp_safe_queue_mode_e mode			[in]����˵��
* ��    ��: int elem_size						[in]����˵��
*
* �� �� ֵ: cp_safe_queue_t*
*      �� null  : �ɹ�
*         null  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:41:46
******************************************************************************************************/
cp_safe_queue_t* cp_create_memory_safe_queue(void *memory, int memory_size, 
	cp_safe_queue_mode_e mode, int elem_size);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_safe_queue_get_memory_size
*
* ����˵��: ����safe queue��Ҫ���ڴ��С
*
* ��    ��: cp_safe_queue_mode_e mode						[in]����˵��
* ��    ��: int size						[in]����˵��
*
* �� �� ֵ: int
*         ����0��safe queueռ�õ��ڴ��С
*     С�ڵ���0��ʧ��
*
* ��    ע:��Ҫ��cp_create_memory_safe_queue()����safe queueʱ��Ҫ����memory�Ĵ�С
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:18:58
******************************************************************************************************/
int cp_safe_queue_get_memory_size(cp_safe_queue_mode_e mode, int size);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_safe_queue_check_mode
*
* ����˵��: У��mode�Ϸ���
*
* ��    ��: cp_safe_queue_mode_e mode						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:24:03
******************************************************************************************************/
int cp_safe_queue_check_mode(cp_safe_queue_mode_e mode);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_safe_queue_size
*
* ����˵��: ��ǰ������Ԫ������
*
* ��    ��: cp_safe_queue_t * sq						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:20:30
******************************************************************************************************/
int cp_safe_queue_size(cp_safe_queue_t* sq);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_safe_queue_push
*
* ����˵��: ��������
*
* ��    ��: cp_safe_queue_t * sq						[in]����˵��
* ��    ��: void * data						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:20:39
******************************************************************************************************/
int cp_safe_queue_push(cp_safe_queue_t* sq, void *data);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_safe_queue_pop
*
* ����˵��: ��������
*
* ��    ��: cp_safe_queue_t * sq						[in]����˵��
*
* �� �� ֵ: void*
*      �� null  : �ɹ�
*         null  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:20:52
******************************************************************************************************/
void* cp_safe_queue_pop(cp_safe_queue_t* sq);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_destroy_safe_queue
*
* ����˵��: ����һ������
*
* ��    ��: cp_safe_queue_t * sq						[in]����˵��
*
* �� �� ֵ: int
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����cp_create_memory_safe_queue()�����Ķ��У��ú��������ٴ����memory�ڴ棬��Ҫ��������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-13 14:21:57
******************************************************************************************************/
int cp_destroy_safe_queue(cp_safe_queue_t* sq);

#endif