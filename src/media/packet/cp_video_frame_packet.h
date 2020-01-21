/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_frame_packet.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/12
*
*Description: create (cp_video_frame_packet.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_FRAME_PACKET_H_
#define _CP_VIDEO_FRAME_PACKET_H_



#include "cp_media_packet.h"




typedef struct cp_video_frame_play_position_s		cp_video_frame_play_position_t;
typedef struct cp_video_frame_packet_s				cp_video_frame_packet_t;



#pragma pack(1)




/************************************************************************/
/* 视频帧播放位置信息                                                    */
/************************************************************************/
struct cp_video_frame_play_position_s
{
	//fpp表示媒体数据中需要被处理的宏块位置信息。
	//其中source表示媒体本身的全图位置信息；dest表示需要用于处理的图像区域；因此，source数据所表示的区域包含dest的数据所表示的区域；
	/************************************************************************/
	/* fpp数据使用说明                                                       */
	/*        .      __________________________________       .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxx  fpp->source  xxxxxxxxx |      .             */
	/*        .     | xxxxxxx ________________ xxxxxxx |      .             */
	/*        .     | xxxxxx |                | xxxxxx |      .             */
	/*        .     | xxxxxx |   fpp->dest    | xxxxxx |      .             */
	/*        .     | xxxxxx |________________| xxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | ________________________________ |      .             */
	/*                                                                      */
	/************************************************************************/
	cp_frame_play_position_t				fpp;				//表示媒体包基础
	cp_int32_t								layer;				//表示层次信息，取值[0, (cp_int32_t -1)]。数值越大，越靠顶层。
	//cp_media_packet_buf_t					mp_buf;				//媒体数据buf部分
	cp_queue_t								queue;				//表示视频帧播放位置列表
};


/************************************************************************/
/* 视频帧数据包                                                          */
/************************************************************************/
struct cp_video_frame_packet_s
{
	CP_MEDIA_PACKET_FIELDS										//表示媒体包基础

	//fpp表示媒体数据中需要被处理的宏块位置信息。
	//其中source表示媒体本身的全图位置信息；dest表示需要用于处理的图像区域；因此，source数据所表示的区域包含dest的数据所表示的区域；
	/************************************************************************/
	/* fpp数据使用说明                                                       */
	/*        .      __________________________________       .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxx  fpp->source  xxxxxxxxx |      .             */
	/*        .     | xxxxxxx ________________ xxxxxxx |      .             */
	/*        .     | xxxxxx |                | xxxxxx |      .             */
	/*        .     | xxxxxx |   fpp->dest    | xxxxxx |      .             */
	/*        .     | xxxxxx |________________| xxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx |      .             */
	/*        .     | ________________________________ |      .             */
	/*                                                                      */
	/************************************************************************/
	cp_frame_play_position_t				fpp;
	cp_queue_t								queue;				//表示视频帧数据队列,主要给cp_video_frame_process_t结构使用
	cp_queue_t								vfpp_queue;			//表示视频帧播放位置信息，即cp_video_frame_play_position_t位置链表
};




#pragma pack()




#endif //_CP_VIDEO_FRAME_PACKET_H_


