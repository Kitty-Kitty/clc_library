/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_media_process.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/20
*
*Description: create (cp_media_process.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_MEDIA_PROCESS_H_
#define _CP_MEDIA_PROCESS_H_



#include "cp_media_core.h"



//typedef struct cp_media_process_s			cp_media_process_t;



#pragma pack(1)



/************************************************************************/
/* 表示media process 成员内容                                            */
/************************************************************************/
#define CP_MEDIA_PROCESS_FIELDS																									\
	cp_media_surface_t						*ms;				/*媒体surface，表示最终输出内容。画布内容,即目标图片*/				\
	cp_media_packet_t						*mp;				/*表示媒体包基础。多个源数据图片内容。*/							\



/************************************************************************/
/* 媒体帧处理数据结构                                                    */
/* 主要内容是将源(cp_media_packet_t)处理到目的（cp_media_surface_t）中：  */
/*     1、cp_media_surface_t 画布内容,即目标图片                         */
/*     2、cp_media_packet_t 多个源数据图片内容                           */
/************************************************************************/
struct cp_media_process_s
{
	CP_MEDIA_PROCESS_FIELDS
};




#pragma pack()








#endif //_CP_MEDIA_PROCESS_H_


