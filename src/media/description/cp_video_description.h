/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-19

Description:

**************************************************************************/

#ifndef _CP_VIDEO_DESCRIPTION_INCLUDE_H_
#define _CP_VIDEO_DESCRIPTION_INCLUDE_H_


#include "cp_media_description.h"



typedef		struct cp_video_description_s				cp_video_description_t;


#pragma  pack(1)

/************************************************************************/
/* 表示视频描述信息                                                      */
/************************************************************************/
struct cp_video_description_s
{
	CP_MEDIA_DESCRIPTION_FIELDS																//媒体基本信息
	cp_int32_t								height;											//媒体高度
	cp_int32_t								width;											//媒体宽度
	cp_int32_t								fps;											//媒体帧率
	cp_int32_t								bps;											//媒体流的码率信息
	cp_char_t								url[CP_APP_DEFAULT_BUFFER_LENGTH];				//媒体地址
};


#pragma pack()

/************************************************************************/
/* 初始化视频信息                                                        */
/************************************************************************/
cp_int32_t init_video_description(cp_media_description_t *md);



#endif