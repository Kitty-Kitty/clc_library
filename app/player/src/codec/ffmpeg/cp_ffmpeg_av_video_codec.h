/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-30

Description:

**************************************************************************/

#ifndef _CP_FFMPEG_V_CODEC_INCLUDE_H_
#define _CP_FFMPEG_V_CODEC_INCLUDE_H_



#include "cp_ffmpeg_av_codec_core.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"



#ifndef		PIX_FMT_YUV420P
#define		PIX_FMT_YUV420P										AV_PIX_FMT_YUV420P
#endif



#define		CP_FFMPEG_AV_CODEC_DEFAULT_PIX_FMT					PIX_FMT_YUV420P				//默认的fix fmt内容


/*创建ffmpeg 视频信息*/
cp_ffmpeg_av_dev_video_info_t *create_ffmpeg_av_video_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md);

/*设置转码器信息*/
cp_int32_t set_ffmpeg_av_video_convert_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame);

/*共享内存方式填充数据*/
cp_int32_t fill_video_packet_shared_memory(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame);

/*拷备数据*/
cp_int32_t fill_video_packet_copy_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame);

/*复内存方式填充数据*/
cp_int32_t fill_video_packet_copy_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame);

/*设置视频信息*/
cp_int32_t set_receive_video_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_video_description_t *vd, AVCodecContext *avctx, AVFrame *frame);

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ffmpeg_video_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame, cp_media_packet_t *mp, cp_int32_t len, cp_int32_t flag);



#endif


