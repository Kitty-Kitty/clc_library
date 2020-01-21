/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-01

Description:

**************************************************************************/

#ifndef _CP_FFMPEG_AV_CODEC_CONF_INCLUDE_H_
#define _CP_FFMPEG_AV_CODEC_CONF_INCLUDE_H_

#include "cp_ffmpeg_av_codec_core.h"




typedef struct cp_ffmpeg_av_codec_conf_s								cp_ffmpeg_av_codec_conf_t;




/************************************************************************/
/*编码器对应表                                                           */
/************************************************************************/
struct cp_ffmpeg_av_codec_conf_s
{
	cp_int32_t					css_codec_type;
	cp_int32_t					ffmpeg_codec_type;
	cp_char_t					description[CP_APP_DEFAULT_LENGTH];
};


/************************************************************************/
/* ffmpeg模块注册宏信息                                                  */
/************************************************************************/
#define CP_FFMPEG_AV_CODEC_REGISTER(css_type, ffmpeg_type, description)			\
	{(css_type), (ffmpeg_type), (description)},


//获取设备信息
cp_ffmpeg_av_codec_conf_t* get_codec_info(cp_int32_t css_codec_type);


#endif



