/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-18

Description:

**************************************************************************/

#ifndef _CP_SDL_AV_DEV_DATA_INCLUDE_H_
#define _CP_SDL_AV_DEV_DATA_INCLUDE_H_


#include "cp_lockfree_queue.h"
#include "cp_sdl_av_dev_core.h"


typedef struct cp_sdl_av_dev_data_s						cp_sdl_av_dev_data_t;
//typedef struct cp_sdl_av_dev_data_element_s				cp_sdl_av_dev_data_element_t;


#pragma pack(1)

/************************************************************************/
/* ��ʾý����������                                                      */
/************************************************************************/
struct cp_sdl_av_dev_data_s {
	cp_int32_t						type;		/*��ʾ��������*/
	cp_int32_t						index;		/*��ʾ���ݵ�������*/
	cp_int32_t						volume;		/*��ʾ��������*/
	cp_timespec_t					ts;			/*��ʾ��Ƶ���ŵ�ʱ��*/
	cp_buf_t						buf;		/*��ʾ��������*/
};

/************************************************************************/
/* ��ʾý����������                                                      */
/************************************************************************/
struct cp_sdl_av_dev_data_element_s {
	cp_sdl_av_dev_data_t			data;		/*��ʾsdlý������*/
	cp_lockfree_queue_element_t		lfq_elem;	/*��ʾ���нڵ�����*/
};

#pragma pack()

/************************************************************************/
/* ����sdl_av_de_data����                                                */
/************************************************************************/
#define	cp_set_sdl_av_dev_data(sdl_av_dev_data, in_type, in_sec, in_nsec, in_data, in_len)		\
	do {																		\
		(sdl_av_dev_data)->type = (in_type);									\
		(sdl_av_dev_data)->ts.tv_sec = (in_sec);								\
		(sdl_av_dev_data)->ts.tv_nsec = (in_nsec);								\
		cp_buf_assemble(&((sdl_av_dev_data)->buf), (in_data), (in_len));		\
	;} while (0)																\



/************************************************************************/
/* ���sdl_av_de_data����                                                */
/************************************************************************/
#define	cp_clear_sdl_av_dev_data(sdl_av_dev_data)								\
	do {																		\
		(sdl_av_dev_data)->type = 0;											\
		(sdl_av_dev_data)->ts.tv_sec = 0;										\
		(sdl_av_dev_data)->ts.tv_nsec = 0;										\
		cp_buf_clear(&((sdl_av_dev_data)->buf))								\
	;} while (0)																\



/************************************************************************/
/* ����data element                                                      */
/************************************************************************/
cp_sdl_av_dev_data_element_t *create_sdl_av_dev_data_element(cp_pool_t *pool);

/************************************************************************/
/* ����data element �� data �е� buffer                                  */
/************************************************************************/
cp_sdl_av_dev_data_element_t *create_sdl_av_dev_data_element_and_buufer(cp_pool_t *pool, cp_int32_t buf_size);

/************************************************************************/
/* ����data element                                                      */
/************************************************************************/
cp_int32_t destroy_sdl_av_dev_data_element(cp_pool_t *pool, cp_sdl_av_dev_data_element_t *elem);

#endif