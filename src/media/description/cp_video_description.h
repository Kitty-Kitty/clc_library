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
/* ��ʾ��Ƶ������Ϣ                                                      */
/************************************************************************/
struct cp_video_description_s
{
	CP_MEDIA_DESCRIPTION_FIELDS																//ý�������Ϣ
	cp_int32_t								height;											//ý��߶�
	cp_int32_t								width;											//ý����
	cp_int32_t								fps;											//ý��֡��
	cp_int32_t								bps;											//ý������������Ϣ
	cp_char_t								url[CP_APP_DEFAULT_BUFFER_LENGTH];				//ý���ַ
};


#pragma pack()

/************************************************************************/
/* ��ʼ����Ƶ��Ϣ                                                        */
/************************************************************************/
cp_int32_t init_video_description(cp_media_description_t *md);



#endif