/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#ifndef _CP_LOCKFREE_QUEUE_INCLUDE_H_
#define _CP_LOCKFREE_QUEUE_INCLUDE_H_



#include <stdio.h>
#include <stdlib.h>
#include "cp_atomic.h"
#include "liblfds710.h"



//#define				_CP_LOCKFREE_QUEUE_SPPORT_UMM_



typedef struct cp_lockfree_queue_struct							cp_lockfree_queue_t;
typedef struct cp_lockfree_queue_element_struct					cp_lockfree_queue_element_t;
typedef int(*cp_lockfree_queue_cb)(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_element_t *fl_queue_element);



#pragma pack(1)

typedef enum cp_lockfree_queue_mode_enum
{
	cp_lockfree_queue_mode_none,
	//////////////////////////////////////////////////////////////////////////
	//定义各种队列类型


	cp_lockfree_queue_mode_qbmm,							/*表示有限制队列，需要注意控制队列的数量，操限制可能导致数据丢失。 该种队列需要set option cp_lockfree_queue_option_bounded*/
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
	cp_lockfree_queue_mode_qumm								/*无限制队列，该种队列可能导致内存不断增加*/
#endif
	cp_lockfree_queue_mode_qbss,							/*表示有限制队列，单生产者单销毁者*/


	//////////////////////////////////////////////////////////////////////////
	cp_lockfree_queue_mode_tail
}cp_lockfree_queue_mode_e;


typedef enum cp_lockfree_queue_option_enum
{
	cp_lockfree_queue_option_bounded = 1,					/*有限制队列需要使用该属性进行设置，限制数量*/
}cp_lockfree_queue_option_e;


typedef enum cp_lockfree_queue_status_enum
{
	cp_lockfree_queue_status_none,
	cp_lockfree_queue_status_init,
	cp_lockfree_queue_status_start,
	cp_lockfree_queue_status_stop,
	cp_lockfree_queue_status_destroy
}cp_lockfree_queue_status_e;




typedef union cp_lockfree_queue_state_union
{
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
	struct lfds710_queue_umm_state			m_lfds710_queue_umm_state;				/*表示无限制多生产者多消费者状态*/
#endif
	struct lfds710_queue_bmm_state			m_lfds710_queue_bmm_state;				/*表示有限制多生产者多消费者状态*/
	struct lfds710_queue_bss_state			m_lfds710_queue_bss_state;				/*表示有限制单生产者单消费者状态*/
}cp_lockfree_queue_state_u;




typedef union cp_lockfree_queue_element_union
{
#if defined(_CP_LOCKFREE_QUEUE_SPPORT_UMM_)
	struct lfds710_queue_umm_element			m_lfds710_queue_umm_element;		/*表示无限制多生产者多消费者元素内容*/
#endif
	struct lfds710_queue_bmm_element			m_lfds710_queue_bmm_element;		/*表示有限制多生产者多消费者元素内容*/
	struct lfds710_queue_bss_element			m_lfds710_queue_bss_element;		/*表示有限制单生产者单消费者元素内容*/
}cp_lockfree_queue_element_u;


struct cp_lockfree_queue_struct
{
	cp_lockfree_queue_state_u					m_lfds710_queue_state;
	void										*m_plfds710_queue_element;
	int											m_plfds710_queue_element_size;
	cp_lockfree_queue_mode_e					m_plfds710_queue_mode;
	cp_lockfree_queue_status_e					m_plfds710_queue_status;
	cp_atomic_t									size;

	cp_lockfree_queue_cb						clear_cb;
};


struct cp_lockfree_queue_element_struct
{
	cp_lockfree_queue_element_u					m_plfds710_queue_element;
	cp_lockfree_queue_t							*lf_queue;
	void										*key;
	void										*value;
};

#pragma pack()

int cp_lockfree_queue_init(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_mode_e lf_queue_mode);
int cp_lockfree_queue_set_option(cp_lockfree_queue_t *lf_queue, int optname, const void* optval);
int cp_lockfree_queue_start(cp_lockfree_queue_t *lf_queue);
int cp_lockfree_queue_clear(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_cb cb);
int cp_lockfree_queue_push(cp_lockfree_queue_t *lf_queue, 
	cp_lockfree_queue_element_t *fl_queue_element, int optname, const void* optval);
int cp_lockfree_queue_pop(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_element_t **fl_queue_element);
int cp_lockfree_queue_stop(cp_lockfree_queue_t *lf_queue);
int cp_lockfree_queue_destroy(cp_lockfree_queue_t *lf_queue);

int cp_lockfree_queue_size(cp_lockfree_queue_t *lf_queue);


int cp_lockfree_queue_element_init(cp_lockfree_queue_t *lf_queue, cp_lockfree_queue_element_t *fl_queue_elem, void *key, void *value);



#endif