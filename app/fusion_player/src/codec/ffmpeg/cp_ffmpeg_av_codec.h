/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FFMEPG_AV_CODEC_INCLUDE_H_
#define _CP_FFMEPG_AV_CODEC_INCLUDE_H_



#include "cp_ffmpeg_av_codec_core.h"



//typedef struct cp_ffmpeg_av_codec_s									cp_ffmpeg_av_codec_t;
#define		CP_FFMPEG_AV_CODEC_DEFAULT_CHANNELS							2




typedef		enum cp_ffmpeg_operation_type_s								cp_ffmpeg_operation_type_t;



/************************************************************************/
/* ffmpeg处理类型                                                       */
/************************************************************************/
enum cp_ffmpeg_operation_type_s
{
	cp_ffmpeg_operation_type_none,
	cp_ffmpeg_operation_type_decode_stream,
	cp_ffmpeg_operation_type_open_stream,
	cp_ffmpeg_operation_type_end
};


#pragma pack(1)


#define CP_FFMEPG_AV_CODEC_FIELDS																		\
		CP_FUSION_PLAYER_CODEC_FIELDS																	\
		AVFormatContext				*format_ctx;					/*格式上不文*/						\
		AVCodec						*codec;							/*解码器*/							\
		AVCodecContext				*codec_context;					/*解码器描述信息*/					\
		AVPacket					avpkt;							/*av packet信息*/					\
		AVFrame						decoded_frame;					/*解码帧数据*/						\
		AVFrame						decoded_convert_frame;			/*解码帧yuv数据*/					\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ffmpeg_av_codec_s {
	CP_FFMEPG_AV_CODEC_FIELDS										/*表示时间模块信息*/

#if defined(CP_FFMPEG_AV_CODEC_FILE_DEBUG)
		FILE											*file;		/*媒体文件*/
#endif
	cp_int32_t											decodec_failed_times;							//表示解码错误次数
	cp_int32_t											decodec_successed_times;						//表示解码成功次数
	cp_mutex_t											process_probe_mutex;							/*用于媒体探测的状态互斥的量*/
	cp_media_description_t								md;												/*表示媒体源描述信息*/
	cp_ffmpeg_operation_type_t							opera_type;										/*表示当前操作类型*/
	cp_ffmpeg_av_dev_video_info_t						*video_info;									/*表示视频相关描述信息*/
	cp_ffmpeg_av_dev_audio_info_t						*audio_info;									/*表示音频相关描述信息*/
	cp_ffmpeg_av_file_info_t							*file_info;										/*表示媒体文件描述信息*/
};


#pragma pack()



cp_ffmpeg_av_codec_t* create_ffmpeg_av_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_ffmpeg_av_codec_info_t *info);
cp_int32_t destroy_ffmpeg_av_codec(cp_codec_manager_t *manager, cp_ffmpeg_av_codec_t* ffmpeg_av_codec);



#endif


