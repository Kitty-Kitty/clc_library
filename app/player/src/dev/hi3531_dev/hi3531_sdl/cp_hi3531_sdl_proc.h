/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_sdl_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/28
*
*Description: create (cp_hi3531_sdl_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3531_SDL_PROC_H_
#define _CP_HI3531_SDL_PROC_H_



#include "cp_hi3531_sdl_core.h"


//��ʼ��hi3531 vo �豸�б�
cp_int32_t	create_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);

//����hi3531 vo �豸�б�
cp_int32_t	start_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);

//ֹͣhi3531 vo �豸�б�
cp_int32_t	stop_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);

//����hi3531 vo �豸�б�
cp_int32_t	destory_hi3531_vo_dev_list(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);




//��ʼ��hi3531 tde �豸�б�
cp_int32_t	create_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);

//����hi3531 tde �豸�б�
cp_int32_t	start_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);

//ֹͣhi3531 tde �豸�б�
cp_int32_t	stop_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);

//����hi3531 tde �豸�б�
cp_int32_t	destory_hi3531_tde_dev(cp_hi3531_sdl_t *dev, cp_hi3531_dev_configure_t *conf);




//дhi3531����
cp_int32_t write_hi3531_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

//ѭ������hi3531����
cp_int32_t cycle_hi3531_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	cp_media_surface_t *surfact,
	cp_video_frame_packet_t *vfp);




//дffmpeg����
cp_int32_t write_ffmpeg_frame_data(cp_hi3531_sdl_t *hi3531_sdl,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);





#endif //_CP_HI3531_SDL_PROC_H_


