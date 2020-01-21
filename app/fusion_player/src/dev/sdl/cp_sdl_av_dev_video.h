/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/

#ifndef _CP_SDL_AV_DEV_VIDEO_INCLUDE_H_
#define _CP_SDL_AV_DEV_VIDEO_INCLUDE_H_


#include "cp_sdl_av_dev_core.h"



/*打开视频设置*/
cp_int32_t open_sdl_video_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*写视频数据*/
cp_int32_t write_sdl_video_data(cp_sdl_av_dev_t *sdl_av_dev, cp_media_packet_t *mp);

/*关闭视频设备*/
cp_int32_t close_sdl_video_dev(cp_sdl_av_dev_t *sdl_av_dev);

/*设置*/
cp_int32_t set_rect_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*创建视频信息*/
cp_int32_t create_sdl_video_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*消毁视频信息*/
cp_int32_t destroy_sdl_video_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*保存视频设备信息*/
cp_int32_t save_video_device_info(cp_sdl_av_dev_t *sdl_av_dev);


#endif