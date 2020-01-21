/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-30

Description:

**************************************************************************/

#ifndef _CP_FFMPEG_AV_AUDIO_CODEC_INCLUDE_H_
#define _CP_FFMPEG_AV_AUDIO_CODEC_INCLUDE_H_



#include "cp_ffmpeg_av_codec_core.h"


/*������Ƶ��������Ϣ*/
cp_ffmpeg_av_dev_audio_info_t *create_ffmpeg_av_audio_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md);

/*������Ƶ�ز�����Ϣ*/
cp_int32_t set_ffmpeg_av_audio_convert_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_audio_description_t *ad);

/*����ת������Ϣ*/
cp_int32_t set_ffmpeg_av_audio_convert_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_audio_description_t *ad, AVCodecContext *avctx, AVFrame *frame);

/*ȡ������ת������Ϣ*/
cp_int32_t unset_ffmpeg_av_audio_convert_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/*���ý�������*/
cp_int32_t set_ffmpeg_av_audio_codec_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_audio_description_t *ad, AVCodecContext *codec_context, AVCodec *codec);

/*�����ڴ淽ʽ�������*/
cp_int32_t fill_audio_packet_shared_memory(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame);

/*���ڴ淽ʽ�������*/
cp_int32_t fill_audio_packet_copy_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame);

/*������Ƶ��Ϣ*/
cp_int32_t set_receive_audio_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_audio_description_t *ad, AVCodecContext *avctx, AVFrame *frame);

/*��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��*/
cp_int32_t read_ffmpeg_audio_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame, cp_media_packet_t *mp, cp_int32_t len, cp_int32_t flag);




#endif



