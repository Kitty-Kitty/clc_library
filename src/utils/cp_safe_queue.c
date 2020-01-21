/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-13

Description:

**************************************************************************/
#include <string.h>
#include "cp_safe_queue.h"


#if defined(WIN32)
#define		cp_sq_inline					__inline
#else
#define		cp_sq_inline					inline
#endif

cp_sq_inline int cp_init_safe_queue(cp_safe_queue_t *sq);
cp_sq_inline int cp_start_safe_queue(cp_safe_queue_t *sq);
cp_sq_inline int cp_stop_safe_queue(cp_safe_queue_t *sq);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: cp_create_safe_queue
*
* ����˵��: ��������
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
* �������ڣ�2017-01-13 14:18:35
******************************************************************************************************/
cp_safe_queue_t* cp_create_safe_queue(void *memory, int memory_size,
	cp_safe_queue_mode_e mode, int elem_size, int is_genera)
{
	int							tmp_ret_int = 0;
	cp_safe_queue_t				*tmp_sq = NULL;


	if (elem_size <= 0) {
		return NULL;
	}

	//У��mode�Ϸ���
	tmp_ret_int = cp_safe_queue_check_mode(mode);
	if (tmp_ret_int) {
		return NULL;
	}
	//������Ҫ�ڴ��С
	tmp_ret_int = cp_safe_queue_get_memory_size(mode, elem_size);
	if (tmp_ret_int <= 0) {
		return NULL;
	}
	if (tmp_ret_int > memory_size) {
		return NULL;
	}
	memset(memory, 0, tmp_ret_int);

	tmp_sq = (cp_safe_queue_t *)memory;
	tmp_sq->is_genera = is_genera;
	tmp_sq->lq_elem = (cp_lockfree_queue_element_t *)(((unsigned char*)tmp_sq) + sizeof(cp_safe_queue_t));
	tmp_sq->lq_elem_size = elem_size;
	tmp_sq->mode = mode;

	tmp_ret_int = cp_init_safe_queue(tmp_sq);
	if (tmp_ret_int) {
		return NULL;
	}
	tmp_ret_int = cp_start_safe_queue(tmp_sq);
	if (tmp_ret_int) {
		return NULL;
	}

	return tmp_sq;
}






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
cp_safe_queue_t* cp_create_general_safe_queue(cp_safe_queue_mode_e mode, int size)
{
	int							tmp_ret_int = 0;
	void						*tmp_buf = NULL;


	//У��mode�Ϸ���
	tmp_ret_int = cp_safe_queue_check_mode(mode);
	if (tmp_ret_int) {
		return NULL;
	}
	//������Ҫ�ڴ��С
	tmp_ret_int = cp_safe_queue_get_memory_size(mode, size);
	if (tmp_ret_int <= 0) {
		return NULL;
	}
	tmp_buf = (cp_safe_queue_t*)malloc(tmp_ret_int);
	if (!tmp_buf) {
		return NULL;
	}

	return cp_create_safe_queue(tmp_buf, tmp_ret_int, mode, size, 1);
}

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
* �������ڣ�2017-01-13 14:18:35
******************************************************************************************************/
cp_safe_queue_t* cp_create_memory_safe_queue(void *memory, int memory_size,
	cp_safe_queue_mode_e mode, int elem_size)
{
	return cp_create_safe_queue(memory, memory_size, mode, elem_size, 0);
}

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
int cp_safe_queue_get_memory_size(cp_safe_queue_mode_e mode, int size)
{
	int							tmp_ret_int = 0;


	//У��mode�Ϸ���
	tmp_ret_int = cp_safe_queue_check_mode(mode);
	if (tmp_ret_int) {
		return 0;
	}
	tmp_ret_int = sizeof(cp_safe_queue_t) + sizeof(cp_lockfree_queue_element_t) * size;

	return tmp_ret_int;
}

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
int cp_safe_queue_check_mode(cp_safe_queue_mode_e mode)
{
	if (cp_safe_queue_mode_none < mode &&
		mode < cp_safe_queue_mode_tail) {
		return 0;
	}
	return -1;
}

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
int cp_safe_queue_size(cp_safe_queue_t* sq)
{
	if (!sq) {
		return 0;
	}

	return sq->busy_lq.size;
}

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
int cp_safe_queue_push(cp_safe_queue_t* sq, void *data)
{
	cp_lockfree_queue_element_t				*tmp_elem = NULL;


	if (cp_lockfree_queue_pop(&sq->free_lq, &tmp_elem) || !tmp_elem) {
		return -1;
	}

	cp_lockfree_queue_element_init(&sq->busy_lq, (cp_lockfree_queue_element_t*)tmp_elem, data, data);

	if (cp_lockfree_queue_push(&sq->busy_lq, (cp_lockfree_queue_element_t*)tmp_elem, 0, NULL)) {
		return -2;
	}

	return 0;
}

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
void* cp_safe_queue_pop(cp_safe_queue_t* sq)
{
	void									*tmp_ret = NULL;
	cp_lockfree_queue_element_t				*tmp_elem = NULL;


	if (cp_lockfree_queue_pop(&sq->busy_lq, &tmp_elem) || !tmp_elem) {
		return NULL;
	}
	tmp_ret = tmp_elem->value;

	cp_lockfree_queue_element_init(&sq->free_lq, (cp_lockfree_queue_element_t*)tmp_elem, NULL, NULL);
	if (cp_lockfree_queue_push(&sq->free_lq, (cp_lockfree_queue_element_t*)tmp_elem, 0, NULL)) {
		//return -2;
	}

	return tmp_ret;
}

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
int cp_destroy_safe_queue(cp_safe_queue_t* sq)
{
	if (!sq) {
		return -1;
	}

	cp_stop_safe_queue(sq);

	if (!sq->is_genera) {
		return 0;
	}
	free(sq);

	return 0;
}

int cp_init_safe_queue(cp_safe_queue_t *sq)
{
	int						i = 0;


	cp_lockfree_queue_init(&sq->busy_lq, sq->mode);
	cp_lockfree_queue_init(&sq->free_lq, sq->mode);

	cp_lockfree_queue_set_option(&sq->busy_lq, cp_lockfree_queue_option_bounded, &sq->lq_elem_size);
	cp_lockfree_queue_set_option(&sq->free_lq, cp_lockfree_queue_option_bounded, &sq->lq_elem_size);

	cp_lockfree_queue_start(&sq->busy_lq);
	cp_lockfree_queue_start(&sq->free_lq);

	for (i = 0; i < sq->lq_elem_size; i++) {
		cp_lockfree_queue_element_init(&sq->free_lq, (cp_lockfree_queue_element_t*)(sq->lq_elem), sq->lq_elem, NULL);
		cp_lockfree_queue_push(&sq->free_lq, (sq->lq_elem)++, 0, NULL);
	}

	return 0;
}

int cp_start_safe_queue(cp_safe_queue_t *sq)
{
	return 0;
}

int cp_stop_safe_queue(cp_safe_queue_t *sq)
{
	cp_lockfree_queue_destroy(&sq->busy_lq);
	cp_lockfree_queue_destroy(&sq->free_lq);

	return 0;
}
