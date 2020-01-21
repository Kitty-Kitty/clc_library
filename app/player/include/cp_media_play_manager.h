/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-05

Description:

**************************************************************************/

#ifndef _CP_MEDIA_PLAY_MANAGER_INCLUDE_H_
#define _CP_MEDIA_PLAY_MANAGER_INCLUDE_H_



#include "cp_core.h"
#include "cp_channel_manager.h"




typedef struct cp_media_play_manager_s					cp_media_play_manager_t;




#pragma pack(1)


struct cp_media_play_manager_s
{
	cp_app_t						*app;																//表示当前的app
	cp_mpool_t						*mpool;																//channelmanager自带的简单内存管理
	cp_channel_manager_t			channel_manager;													//表示通道管理器信息
	cp_mutex_t						audio_play_mutex;													//音频播放互斥变量
	cp_mutex_t						video_play_mutex;													//音频播放互斥变量
};


#pragma pack()



/************************************************************************/
/* 通道管理器的处理方法                                                  */
/************************************************************************/
cp_media_play_manager_t* create_media_play_manager(cp_app_t *app);
int destroy_media_play_manager(cp_app_t *app, cp_media_play_manager_t *mpm);
int init_media_play_manager(cp_app_t *app, cp_media_play_manager_t *mpm, cp_int32_t max_size);
int start_media_play_manager(cp_media_play_manager_t *mpm);
int stop_media_play_manager(cp_media_play_manager_t *mpm);


#endif