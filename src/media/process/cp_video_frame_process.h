/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_frame_process.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_video_frame_process.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_FRAME_PROCESS_H_
#define _CP_VIDEO_FRAME_PROCESS_H_




#include "cp_media_process.h"



typedef struct cp_video_frame_process_s			cp_video_frame_process_t;




#pragma pack(1)





/************************************************************************/
/* 视频帧处理数据包                                                      */
/* 这个表示一个处理包包括多个源帧处理的结果                                */
/************************************************************************/
struct cp_video_frame_process_s
{
	CP_MEDIA_PROCESS_FIELDS											//媒体media process
	cp_queue_t									vfp_queue;			//表示视频帧队列,cp_video_frame_packet_t位置链表
};




#pragma pack()



#endif //_CP_VIDEO_FRAME_PROCESS_H_


