/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-23

Description:

**************************************************************************/

#ifndef _CP_FFMPEG_AV_AUDIO_CHANNEL_LAYOUT_INCLUDE_H_
#define _CP_FFMPEG_AV_AUDIO_CHANNEL_LAYOUT_INCLUDE_H_




#include "cp_media_type.h"
#include "cp_ffmpeg_av_codec_core.h"



#define	CP_FFMPEG_AV_CODEC_AUDIO_CHANNEL_LAYOUT_DESCRIPTION_LENGTH			32		//��ʾ�����ַ�



typedef struct cp_ffmpeg_av_codec_audio_channel_layout_s					cp_ffmpeg_av_codec_audio_channel_layout_t;




/************************************************************************/
/*��ʽ��Ӧ��                                                           */
/************************************************************************/
struct cp_ffmpeg_av_codec_audio_channel_layout_s
{
	cp_audio_channel_layout_e					cp_audio_channel_layout_type;
	cp_int32_t									ffmpeg_audio_channel_layout_type;
	cp_char_t									description[CP_FFMPEG_AV_CODEC_AUDIO_CHANNEL_LAYOUT_DESCRIPTION_LENGTH];
};


/************************************************************************/
/* channel_layoutģ��ע�����Ϣ                                                  */
/************************************************************************/
#define CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(css_type, channel_layout_type, description)			\
	{(css_type), (channel_layout_type), (description)},


//��ȡ��Ƶ��ʽ��Ϣ
cp_ffmpeg_av_codec_audio_channel_layout_t* get_ffmpeg_audio_channel_layout_info(cp_int32_t cp_audio_channel_layout_type);
cp_ffmpeg_av_codec_audio_channel_layout_t* get_cp_audio_channel_layout_info(cp_int32_t ffmpeg_audio_channel_layout_type);



#endif