/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/

#ifndef _CP_SDL_AV_DEV_AUDIO_INCLUDE_H_
#define _CP_SDL_AV_DEV_AUDIO_INCLUDE_H_


#include "cp_sdl_av_dev_core.h"


/*����Ƶ����*/
cp_int32_t open_sdl_audio_dev(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*д��Ƶ����*/
cp_int32_t write_sdl_audio_data(cp_sdl_av_dev_t *sdl_av_dev, cp_media_packet_t *mp);

/*�ر���Ƶ�豸*/
cp_int32_t close_sdl_audio_dev(cp_sdl_av_dev_t *sdl_av_dev);

/*��ʼ����Ƶ��Ϣ*/
cp_int32_t init_sdl_audio_buffer_queue(cp_sdl_av_dev_t * sdl_av_dev, const cp_sdl_av_dev_info_t * sdl_av_dev_info);

/*������Ƶ�����С*/
cp_int32_t update_sdl_audio_buffer_queue(cp_sdl_av_dev_t * sdl_av_dev, cp_int32_t size);

/*������Ƶ��Ϣ*/
cp_int32_t create_sdl_audio_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*������Ƶ��Ϣ*/
cp_int32_t destroy_sdl_audio_info(cp_sdl_av_dev_t *sdl_av_dev, const cp_sdl_av_dev_info_t *sdl_av_dev_info);

/*������Ƶ��Ϣ*/
cp_int32_t set_audio_spec(cp_sdl_av_dev_t *sdl_av_dev, cp_sdl_av_dev_audio_info_t *audio_info);

/*������Ƶ�豸��Ϣ*/
cp_int32_t save_audio_device_info(cp_sdl_av_dev_t *sdl_av_dev);


#endif