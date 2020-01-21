/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-26

Description:

**************************************************************************/

#ifndef _CP_FORMAT_MEDIA_PLAY_INCLUDE_H_
#define _CP_FORMAT_MEDIA_PLAY_INCLUDE_H_





#include "cp_core.h"
#include "cp_media_play.h"
#include "css_media_info.h"





#define CP_FORMAT_DEFAULT_BUFFER_LENGTH												1024						//表示格式化缓存大小
#define CP_FORMAT_DEFAULT_LONG_BUFFER_LENGTH										1024 * 4					//表示格式化长缓存大小



//格式化媒体通道信息
cp_char_t* format_media_channel_info(cp_media_channel_info_t *mci, cp_char_t *buf, cp_int32_t len);

//格式化媒体通道信息
cp_char_t* format_channel_info(cp_channel_info_t *ci, cp_char_t *buf, cp_int32_t len);

//格式化媒体资源信息
cp_char_t* format_media_info(cp_media_info_t *mi, cp_char_t *buf, cp_int32_t len);

//格式化位置信息
cp_char_t* format_position(cp_play_position_t *pp, cp_char_t *buf, cp_int32_t len);

//格式化音频信息
cp_char_t* format_audio_info(cp_audio_source_info_t *a_info, cp_char_t *buf, cp_int32_t len);

//格式化视频信息
cp_char_t* format_video_info(cp_video_source_info_t *v_info, cp_char_t *buf, cp_int32_t len);


#endif