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
/* 表示媒体数据内容                                                      */
/************************************************************************/
struct cp_sdl_av_dev_data_s {
	cp_int32_t						type;		/*表示数据类型*/
	cp_int32_t						index;		/*表示数据的索引号*/
	cp_int32_t						volume;		/*表示音量数据*/
	cp_timespec_t					ts;			/*表示音频播放的时间*/
	cp_buf_t						buf;		/*表示数据内容*/
};

/************************************************************************/
/* 表示媒体数据内容                                                      */
/************************************************************************/
struct cp_sdl_av_dev_data_element_s {
	cp_sdl_av_dev_data_t			data;		/*表示sdl媒体数据*/
	cp_lockfree_queue_element_t		lfq_elem;	/*表示队列节点内容*/
};

#pragma pack()

/************************************************************************/
/* 设置sdl_av_de_data数据                                                */
/************************************************************************/
#define	cp_set_sdl_av_dev_data(sdl_av_dev_data, in_type, in_sec, in_nsec, in_data, in_len)		\
	do {																		\
		(sdl_av_dev_data)->type = (in_type);									\
		(sdl_av_dev_data)->ts.tv_sec = (in_sec);								\
		(sdl_av_dev_data)->ts.tv_nsec = (in_nsec);								\
		cp_buf_assemble(&((sdl_av_dev_data)->buf), (in_data), (in_len));		\
	;} while (0)																\



/************************************************************************/
/* 清空sdl_av_de_data数据                                                */
/************************************************************************/
#define	cp_clear_sdl_av_dev_data(sdl_av_dev_data)								\
	do {																		\
		(sdl_av_dev_data)->type = 0;											\
		(sdl_av_dev_data)->ts.tv_sec = 0;										\
		(sdl_av_dev_data)->ts.tv_nsec = 0;										\
		cp_buf_clear(&((sdl_av_dev_data)->buf))								\
	;} while (0)																\



/************************************************************************/
/* 创建data element                                                      */
/************************************************************************/
cp_sdl_av_dev_data_element_t *create_sdl_av_dev_data_element(cp_pool_t *pool);

/************************************************************************/
/* 创建data element 和 data 中的 buffer                                  */
/************************************************************************/
cp_sdl_av_dev_data_element_t *create_sdl_av_dev_data_element_and_buufer(cp_pool_t *pool, cp_int32_t buf_size);

/************************************************************************/
/* 消毁data element                                                      */
/************************************************************************/
cp_int32_t destroy_sdl_av_dev_data_element(cp_pool_t *pool, cp_sdl_av_dev_data_element_t *elem);

#endif