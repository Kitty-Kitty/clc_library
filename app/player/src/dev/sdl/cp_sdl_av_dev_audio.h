/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/

#ifndef _CP_SDL_AV_DEV_AUDIO_INCLUDE_H_
#define _CP_SDL_AV_DEV_AUDIO_INCLUDE_H_


#include "cp_sdl_av_dev_core.h"


/*打开音频设置*/
cp_int32_t open_sdl_audio_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*写音频数据*/
cp_int32_t write_sdl_audio_data(cp_sdl_av_dev_t *sdl_av_dev, cp_media_packet_t *mp);

/*关闭音频设备*/
cp_int32_t close_sdl_audio_dev(cp_sdl_av_dev_t *sdl_av_dev);

/*初始化音频信息*/
cp_int32_t init_sdl_audio_buffer_queue(cp_sdl_av_dev_t * sdl_av_dev, const cp_sdl_av_dev_info_t * sdl_av_dev_info);

/*更新音频缓存大小*/
cp_int32_t update_sdl_audio_buffer_queue(cp_sdl_av_dev_t * sdl_av_dev, cp_int32_t size);

/*创建音频信息*/
cp_int32_t create_sdl_audio_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*消毁音频信息*/
cp_int32_t destroy_sdl_audio_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*设置音频信息*/
cp_int32_t set_audio_spec(cp_sdl_av_dev_t *sdl_av_dev, cp_sdl_av_dev_audio_info_t *audio_info);

/*保存音频设备信息*/
cp_int32_t save_audio_device_info(cp_sdl_av_dev_t *sdl_av_dev);


#endif