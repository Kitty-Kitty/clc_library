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
/* ��Ƶ֡�������ݰ�                                                      */
/* �����ʾһ��������������Դ֡����Ľ��                                */
/************************************************************************/
struct cp_video_frame_process_s
{
	CP_MEDIA_PROCESS_FIELDS											//ý��media process
	cp_queue_t									vfp_queue;			//��ʾ��Ƶ֡����,cp_video_frame_packet_tλ������
};




#pragma pack()



#endif //_CP_VIDEO_FRAME_PROCESS_H_


