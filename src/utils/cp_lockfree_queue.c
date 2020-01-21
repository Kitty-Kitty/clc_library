/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "cp_lockfree_queue.h"



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_lockfree_queue_check_mode
*
* 函数说明: 校验队列的类型
*
* 参    数: cp_lockfree_queue_t * lf_queue						[in]参数说明
*
* 返 回 值: int
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-03 15:39:14
******************************************************************************************************/
int cp_lockfree_queue_check_mode(cp_lockfree_queue_t *lf_queue)
{
	if (!lf_queue) {
		return -1;
	}

	//判断类型是否正确
	if (lf_queue->m_plfds710_queue_mode > cp_lockfree_queue_mode_none &&
		lf_queue->m_plfds710_queue_mode < cp_lockfree_queue_mode_tail) {
		return 0;
	}

	return -2;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_lockfree_queue_bounded_element_size
*
* 函数说明: 根据给的个数，计算一个大于该数值的最小2指数
*
* 参    数: int s						[in]表示需要设定的数值
*
* 返 回 值: int
*           0  : 成功
*         非 0  :失败
*
* 备    注:这里需要计算，否则出现运行时可能奔溃
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-03 15:39:45
******************************************************************************************************/
int cp_lockfree_queue_bounded_element_size(int s)
{
	int						tmp_pow2 = 1;


	if (s <= 0) {
		return -2;
	}

	//判断是不是偶数，因为为2的指数可能2的偶数
	if (s % 2) {
		//取第一个偶数，解决为1的情况
		s += 1;
	}

	//判断tmp_size是不是2的指数
	if (s & (s - 1)) {
		//这几计算大于tmp_size的2的指数中的最小值
		for (tmp_pow2 = 1; tmp_pow2 < s; tmp_pow2 <<= 1) {
		}
		s = tmp_pow2;
	}

	return s;
}

void cp_lockfree_queue_bmm_element_cleanup_callback(struct lfds710_queue_bmm_state *qbmms, void *key, void *value)
{
	cp_lockfree_queue_t				*tmp_lf_queue = NULL;
	cp_lockfree_queue_element_t		*tmp_fl_queue_element = NULL;

	if (!value) {
		return;
	}

	tmp_fl_queue_element = (cp_lockfree_queue_element_t*)value;
	if (tmp_fl_queue_element->lf_queue && tmp_fl_queue_element->lf_queue->clear_cb) {
		tmp_fl_queue_element->lf_queue->clear_cb(tmp_fl_queue_element->lf_queue, tmp_fl_queue_element);
	}
}

void cp_lockfree_queue_bss_element_cleanup_callback(struct lfds710_queue_bss_state *qbsss, void *key, void *value)
{
	//这里为了方便，直接使用bmm的返回处理方法
	cp_lockfree_queue_bmm_element_cleanup_callback((struct lfds710_queue_bmm_state*)qbsss, key, value);
}

void cp_lockfree_queue_umm_element_cleanup_callback
(struct lfds710_queue_umm_state *qumms, struct lfds710_queue_umm_element *qumme, enum lfds710_misc_flag dummy_element_flag)
{
	cp_lockfree_queue_element_t		*tmp_fl_queue_element = NULL;


	tmp_fl_queue_element =
		(cp_lockfree_queue_element_t*)LFDS710_QUEUE_UMM_GET_VALUE_FROM_ELEMENT(*qumme);
	if (!tmp_fl_queue_element) {
		return;
	}
	if (tmp_fl_queue_element->lf_queue && tmp_fl_queue_element->lf_queue->clear_cb) {
		tmp_fl_queue_element->lf_queue->clear_cb(tmp_fl_queue_element->lf_queue, tmp_fl_queue_element);
	}
}


int cp_lockfree_queue_init(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_mode_e lf_queue_mode)
{
	if (!lf_queue) {
		return -1;
	}

	memset(lf_queue, 0, sizeof(cp_lockfree_queue_t));

	switch (lf_queue_mode)
	{
		case cp_lockfree_queue_mode_qbmm:
		case cp_lockfree_queue_mode_qbss:
		{
			/*lf_queue->m_plfds710_queue_state = malloc(sizeof(struct lfds710_queue_bmm_state));*/
			lf_queue->m_plfds710_queue_element = NULL;
		}
		break;
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
		case cp_lockfree_queue_mode_qumm:
		{
			/*lf_queue->m_plfds710_queue_state = malloc(sizeof(struct lfds710_queue_umm_state));*/
			lf_queue->m_plfds710_queue_element = malloc(sizeof(struct lfds710_queue_umm_element));
			if (!lf_queue->m_plfds710_queue_element) {
				return -2;
			}
		}
		break;
#endif
		default:
		{
			return -1;
		}
		break;
	}

	lf_queue->m_plfds710_queue_mode = lf_queue_mode;
	lf_queue->m_plfds710_queue_status = cp_lockfree_queue_status_init;
	lf_queue->size = 0;
	return 0;
}

int cp_lockfree_queue_set_option(cp_lockfree_queue_t *lf_queue, int optname, const void* optval)
{
	int						tmp_size = 0;
	int						tmp_pow2 = 1;



	if (cp_lockfree_queue_check_mode(lf_queue)) {
		return -1;
	}

	switch (optname)
	{
		case cp_lockfree_queue_option_bounded:
		{
			if (cp_lockfree_queue_mode_qbmm == lf_queue->m_plfds710_queue_mode ||
				cp_lockfree_queue_mode_qbss == lf_queue->m_plfds710_queue_mode) {
				tmp_size = *(int *)optval;
				//这里计算大于tmp_size的最小2指数
				tmp_size = cp_lockfree_queue_bounded_element_size(tmp_size);
				if (tmp_size <= 0) {
					return -2;
				}

				//判断时什么类型来创建各个元素的大小
				if (cp_lockfree_queue_mode_qbmm == lf_queue->m_plfds710_queue_mode) {
					lf_queue->m_plfds710_queue_element = malloc(sizeof(struct lfds710_queue_bmm_element) * tmp_size);
				}
				else {
					lf_queue->m_plfds710_queue_element = malloc(sizeof(struct lfds710_queue_bss_element) * tmp_size);
				}
				if (!lf_queue->m_plfds710_queue_element) {
					return -3;
				}
				lf_queue->m_plfds710_queue_element_size = tmp_size;
			}
		}
		break;
		default:
		{
			return -4;
		}
		break;
	}
	return 0;
}

int cp_lockfree_queue_start(cp_lockfree_queue_t *lf_queue)
{
	if (cp_lockfree_queue_check_mode(lf_queue)) {
		return -1;
	}

	switch (lf_queue->m_plfds710_queue_mode)
	{
		case cp_lockfree_queue_mode_qbmm:
		{
			lfds710_queue_bmm_init_valid_on_current_logical_core(
				&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bmm_state, lf_queue->m_plfds710_queue_element,
				lf_queue->m_plfds710_queue_element_size, NULL);
		}
		break;
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
		case cp_lockfree_queue_mode_qumm:
		{
			lfds710_queue_umm_init_valid_on_current_logical_core(
				&lf_queue->m_lfds710_queue_state.m_lfds710_queue_umm_state, lf_queue->m_plfds710_queue_element, NULL);
		}
		break;
#endif
		case cp_lockfree_queue_mode_qbss:
		{
			lfds710_queue_bss_init_valid_on_current_logical_core(
				&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bss_state, lf_queue->m_plfds710_queue_element,
				lf_queue->m_plfds710_queue_element_size, NULL);
		}
		break;
		default:
		{
			return -1;
		}
		break;
	}

	lf_queue->m_plfds710_queue_status = cp_lockfree_queue_status_start;
	return 0;
}

int cp_lockfree_queue_clear(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_cb cb)
{
	void											*key = NULL;
	void											*value = NULL;
	int												ret_int = -1;
	struct lfds710_queue_umm_element				*tmp_flq_elem = NULL;



	if (cp_lockfree_queue_check_mode(lf_queue)) {
		return ret_int;
	}

	lf_queue->clear_cb = cb;

	switch (lf_queue->m_plfds710_queue_mode)
	{
		case cp_lockfree_queue_mode_qbmm:
		{
			lfds710_queue_bmm_cleanup(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bmm_state,
				cp_lockfree_queue_bmm_element_cleanup_callback);
		}
		break;
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
		case cp_lockfree_queue_mode_qumm:
		{
			lfds710_queue_umm_cleanup(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_umm_state, 
				cp_lockfree_queue_umm_element_cleanup_callback);
		}
		break;
#endif
		case cp_lockfree_queue_mode_qbss:
		{
			lfds710_queue_bss_cleanup(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bss_state,
				cp_lockfree_queue_bss_element_cleanup_callback);
		}
		break;
		default:
		{
			return ret_int;
		}
		break;
	}

	return 0;
}

int cp_lockfree_queue_push(cp_lockfree_queue_t *lf_queue,
	cp_lockfree_queue_element_t *fl_queue_element, int optname, const void* optval)
{
	int							ret_int = -1;



	if (cp_lockfree_queue_check_mode(lf_queue)) {
		return ret_int;
	}

	//set lock free queue
	fl_queue_element->lf_queue = lf_queue;

	switch (lf_queue->m_plfds710_queue_mode)
	{
		case cp_lockfree_queue_mode_qbmm:
		{
			ret_int = lfds710_queue_bmm_enqueue(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bmm_state,
				&fl_queue_element->key, fl_queue_element);
		}
		break;
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
		case cp_lockfree_queue_mode_qumm:
		{
			lfds710_queue_umm_enqueue(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_umm_state,
				&fl_queue_element->m_plfds710_queue_element.m_lfds710_queue_umm_element);
		}
		break;
#endif
		case cp_lockfree_queue_mode_qbss:
		{
			ret_int = lfds710_queue_bss_enqueue(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bss_state,
				&fl_queue_element->key, fl_queue_element);
		}
		break;
		default:
		{
			return ret_int;
		}
		break;
	}
	if (ret_int > 0) {
		++(lf_queue->size);
		return 0;
	}
	return ret_int;
}

int cp_lockfree_queue_pop
(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_element_t **fl_queue_element)
{
	void											*key = NULL;
	void											*value = NULL;
	int												ret_int = -1;
	struct lfds710_queue_umm_element				*tmp_flq_elem = NULL;



	if (cp_lockfree_queue_check_mode(lf_queue)) {
		return ret_int;
	}

	switch (lf_queue->m_plfds710_queue_mode)
	{
		case cp_lockfree_queue_mode_qbmm:
		{
			ret_int = lfds710_queue_bmm_dequeue(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bmm_state,
				&key, (void**)fl_queue_element);
		}
		break;
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
		case cp_lockfree_queue_mode_qumm:
		{
			lfds710_queue_umm_dequeue(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_umm_state, &tmp_flq_elem);
			if (!tmp_flq_elem) {
				return -1;
			}
			*fl_queue_element = (cp_lockfree_queue_element_t*)
				LFDS710_QUEUE_UMM_GET_VALUE_FROM_ELEMENT(*tmp_flq_elem);
		}
		break;
#endif
		case cp_lockfree_queue_mode_qbss:
		{
			ret_int = lfds710_queue_bss_dequeue(&lf_queue->m_lfds710_queue_state.m_lfds710_queue_bss_state,
				&key, (void**)fl_queue_element);
		}
		break;
		default:
		{
			return ret_int;
		}
		break;
	}

	if (ret_int > 0) {
		--(lf_queue->size);
		return 0;
	}

	return ret_int;
}

int cp_lockfree_queue_stop(cp_lockfree_queue_t *lf_queue)
{
	lf_queue->m_plfds710_queue_status = cp_lockfree_queue_status_stop;
	return 0;
}

int cp_lockfree_queue_destroy(cp_lockfree_queue_t *lf_queue)
{
	lf_queue->m_plfds710_queue_status = cp_lockfree_queue_status_destroy;
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_lockfree_queue_size
*
* 函数说明: 或者队列当前的元素数量
*
* 参    数: cp_lockfree_queue_t * lf_queue						[in]参数说明
*
* 返 回 值: int
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-03 16:46:15
******************************************************************************************************/
int cp_lockfree_queue_size(cp_lockfree_queue_t *lf_queue)
{
	return lf_queue->size;
}

int cp_lockfree_queue_element_init
(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_element_t *fl_queue_elem, void *key, void *value)
{
	fl_queue_elem->lf_queue = lf_queue;
	fl_queue_elem->key = key;
	fl_queue_elem->value = value;
	return 0;
}