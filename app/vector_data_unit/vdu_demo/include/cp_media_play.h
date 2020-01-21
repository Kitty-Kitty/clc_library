/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-23

Description:主要实现媒体播放相关的内容

**************************************************************************/

#ifndef _CP_MEDIA_PLAY_INCLUDE_H_
#define _CP_MEDIA_PLAY_INCLUDE_H_



#include "cp_vdu_demo_core.h"



/************************************************************************/
/* 播放信息                                                              */
/************************************************************************/
cp_int32_t create_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);
cp_int32_t destroy_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);

cp_int32_t init_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);
cp_int32_t start_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);
cp_int32_t stop_media_play(cp_vdu_demo_t *vdu_demo, cp_play_channel_info_t *cp_info);


/************************************************************************/
/* 处理播放信息                                                          */
/************************************************************************/

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_audio_media_play
*
* 函数说明: 创建一个音频处理模块
*
* 参    数: cp_vdu_demo_t * vdu_demo						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-24 14:58:52
******************************************************************************************************/
cp_module_t* create_audio_media_play(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_video_media_play
*
* 函数说明: 创建一个视频处理模块
*
* 参    数: cp_vdu_demo_t * vdu_demo						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-24 14:59:20
******************************************************************************************************/
cp_module_t* create_video_media_play(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_av_media_play_module
*
* 函数说明: 创建音视频模块
*
* 参    数: cp_vdu_demo_t * vdu_demo						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
* 参    数: cp_int32_t manager_type						[in]参数说明
* 参    数: cp_int32_t module_type						[in]参数说明
*
* 返 回 值: cp_module_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-24 15:46:54
******************************************************************************************************/
cp_module_t* create_av_media_play_module(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci, cp_int32_t manager_type, cp_int32_t module_type);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_av_media_play_module
*
* 函数说明: 停止一个播放
*
* 参    数: cp_vdu_demo_t * vdu_demo						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 19:38:11
******************************************************************************************************/
cp_int32_t stop_av_media_play_module(cp_vdu_demo_t *vdu_demo, cp_media_channel_info_t *mci);

#endif



