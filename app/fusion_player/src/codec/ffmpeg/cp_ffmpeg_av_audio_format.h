/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-21

Description:

**************************************************************************/

#ifndef _CP_FFMPEG_AV_AUDIO_FORMAT_INCLUDE_H_
#define _CP_FFMPEG_AV_AUDIO_FORMAT_INCLUDE_H_



#include "cp_media_type.h"
#include "cp_ffmpeg_av_codec_core.h"




typedef struct cp_ffmpeg_av_codec_audio_format_s					cp_ffmpeg_av_codec_audio_format_t;




/************************************************************************/
/*格式对应表                                                           */
/************************************************************************/
struct cp_ffmpeg_av_codec_audio_format_s
{
	cp_audio_format_e					cp_audio_format_type;
	cp_int32_t							ffmpeg_audio_format_type;
	cp_char_t							description[CP_APP_DEFAULT_LENGTH];
};


/************************************************************************/
/* format模块注册宏信息                                                  */
/************************************************************************/
#define CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(css_type, format_type, description)			\
	{(css_type), (format_type), (description)},


//获取音频格式信息
cp_ffmpeg_av_codec_audio_format_t* get_ffmpeg_audio_format_info(cp_int32_t cp_audio_format_type);
cp_ffmpeg_av_codec_audio_format_t* get_cp_audio_format_info(cp_int32_t ffmpeg_audio_format_type);



#endif