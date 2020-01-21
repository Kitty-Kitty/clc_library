/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_func_media_process.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_video_func_frame_process.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_FUNC_FRAME_PROCESS_H_
#define _CP_VIDEO_FUNC_FRAME_PROCESS_H_



#include "cp_video_func_core.h"




typedef struct cp_video_func_frame_process_s			cp_video_func_frame_process_t;




#pragma pack(1)



/************************************************************************/
/* 视频帧处理数据包                                                      */
/************************************************************************/
struct cp_video_func_frame_process_s
{
	cp_media_surface_t							ms;					//媒体surface
	cp_media_packet_t							*mp;				//表示媒体包基础
	cp_video_frame_play_position_t				vfpp;				//表示媒体源处理位置信息
	cp_channel_info_t							chann_info;			//表示通道信息
};




#pragma pack()



#endif //_CP_VIDEO_FUNC_MEDIA_PROCESS_H_


