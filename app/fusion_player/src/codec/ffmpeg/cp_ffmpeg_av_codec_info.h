/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_FFMEPG_AV_CODEC_INFO_INCLUDE_H_
#define _CP_FFMEPG_AV_CODEC_INFO_INCLUDE_H_

#include "cp_ffmpeg_av_codec_core.h"




#define		CP_FFMEPG_AV_CODEC_NAME_MAX_LENGTH						32			//表示解码器最大的



typedef	struct cp_ffmpeg_av_dev_video_info_s						cp_ffmpeg_av_dev_video_info_t;
typedef	struct cp_ffmpeg_av_dev_audio_info_s						cp_ffmpeg_av_dev_audio_info_t;



//typedef	struct cp_ffmpeg_av_codec_info_s						cp_ffmpeg_av_codec_info_t;
typedef void(*cp_ffmpeg_av_codec_cb)(cp_ffmpeg_av_codec_t* th);




#pragma pack(1)


#define CP_FFMEPG_AV_CODEC_INFO_FIELDS														\
		CP_CODEC_INFO_FIELDS																\
		cp_char_t	av_name[CP_FFMEPG_AV_CODEC_NAME_MAX_LENGTH];	/*表示编码器名称*/		\
		cp_int32_t	av_type;										/*表示编码器类型*/		\
		cp_int32_t	css_type;										/*表示css编码器类型*/	\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ffmpeg_av_codec_info_s {
	CP_FFMEPG_AV_CODEC_INFO_FIELDS
};



/************************************************************************/
/*定义视频属性                                                           */
/************************************************************************/
struct cp_ffmpeg_av_dev_video_info_s
{
	cp_video_description_t			vd;								/*视频描述信息*/
	struct SwsContext				*video_convert_context;			/*视频转码器信息*/
};


/************************************************************************/
/*定义音频属性                                                              */
/************************************************************************/
struct cp_ffmpeg_av_dev_audio_info_s
{
	cp_audio_description_t			ad;								/*音频频描述信息*/
	struct SwrContext				*audio_convert_context;			/*音频转码器信息*/
	cp_int32_t						audio_out_linesize;				/*音频转码器linesize信息*/
	cp_int32_t						audio_samples_buffer_size;		/*音频转码器采样缓存信息*/
	cp_ffmepg_av_probe_info_t		*probe;							/*媒体探测器*/
	cp_buf_t						*buf;							/*缓存信息*/
	cp_bool_t						audio_convert;					/*表示音频是否重采样*/
	cp_bool_t						is_async;						/*表示是否采用异步方式*/
	cp_audio_description_t			cp_convert_ad;					/*音频重采样描述信息*/
	cp_audio_description_t			ffmpeg_convert_ad;				/*ffmpeg音频重采样描述信息*/
};



#pragma pack()




#endif





