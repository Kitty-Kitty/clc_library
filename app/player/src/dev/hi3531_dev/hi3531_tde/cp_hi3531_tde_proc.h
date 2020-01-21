/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_hi3531_tde_proc.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/07/29
*
*Description: create (cp_hi3531_tde_proc.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_HI3531_TDE_PROC_H_
#define _CP_HI3531_TDE_PROC_H_



#include "cp_hi3531_tde_core.h"




//��ʼ���豸
cp_int32_t hi3531_tde_init_dev(cp_hi3531_tde_t *hi3531_tde, cp_hi3531_tde_configure_t *tde_conf);





//�����豸
cp_int32_t hi3531_tde_start_dev(cp_hi3531_tde_t *hi3531_tde, cp_hi3531_tde_configure_t *tde_conf);



//��Ƶ֡���ٿ���ͼ��
cp_int32_t hi3531_tde_video_frame_copy(cp_hi3531_tde_t *hi3531_tde,
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp);

//��Ƶ֡���ͼ��
cp_int32_t hi3531_tde_video_frame_fill(cp_hi3531_tde_t *hi3531_tde,
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp);

//��Ƶ֡�Ŵ���С
cp_int32_t hi3531_tde_video_frame_resize(cp_hi3531_tde_t *hi3531_tde, 
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp);

//��Ƶ֡����ͬʱ�Ŵ���С
cp_int32_t hi3531_tde_video_frame_copy_resize(cp_hi3531_tde_t *hi3531_tde,
	cp_media_surface_t *ms,
	cp_media_packet_t *mp,
	cp_video_frame_play_position_t *vfpp);

//ֹͣ�豸
cp_int32_t hi3531_tde_stop_dev(cp_hi3531_tde_t *hi3531_tde, cp_hi3531_tde_configure_t *tde_conf);


#endif //_CP_HI3531_TDE_PROC_H_


