/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-05

Description:

**************************************************************************/

#ifndef _CP_MEDIA_TYPE_INCLUDE_H_
#define _CP_MEDIA_TYPE_INCLUDE_H_





/************************************************************************/
/* 视频类型                                                             */
/************************************************************************/
typedef enum cp_media_type_enum
{
	cp_media_type_video_begin = 0,

	//////视频编码类型添加到begin--end之间/////////////////////////////////////
	cp_media_type_video_h264 = 1,

	//////////////////////////////////////////////////////////////////////////
	cp_media_type_video_end = 64,

	cp_media_type_audio_begin = 63,


	///////音频编码类型添加到begin--end之间////////////////////////////////////
	cp_media_type_audio_audio = 64,
	cp_media_type_audio_mp2 = 68,
	cp_media_type_audio_mp3 = 69,
	cp_media_type_audio_aac = 70,
	cp_media_type_audio_g711_pcm = 80,
	cp_media_type_audio_g722_1 = 81,
	cp_media_type_audio_g723_1 = 82,
	cp_media_type_audio_g729 = 83,
	//////////////////////////////////////////////////////////////////////////

	cp_media_type_audio_end = 96
}cp_media_type_e;


#endif