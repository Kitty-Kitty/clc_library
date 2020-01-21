/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-30

Description:

**************************************************************************/

#ifndef _CP_FFMPEG_AV_CODEC_GENERAL_INCLUDE_H_
#define _CP_FFMPEG_AV_CODEC_GENERAL_INCLUDE_H_



#include "cp_ffmpeg_av_codec_core.h"



#define		CP_FFMPEG_AV_CODEC_MAX_AUDIO_FRAME_SIZE						192000 * 4					// 1 second of 48khz 32bit audio

/* Calculate actual buffer size keeping in mind not cause too frequent audio callbacks */
#define		CP_FFMPEG_AV_CODEC_MAX_CALLBACKS_PER_SEC					30

//��ʾ��������ʧ�ܵĴ���
#define		CP_FFMPEG_AV_CODEC_MAX_DECODE_FAILED_TIMES					10



/*���÷�����Ϣ*/
cp_int32_t set_receive_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame);

/*���ó�����Ϣ*/
cp_int32_t set_receive_general_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md, AVCodecContext *avctx, AVFrame *frame);

/*��ʼ��ý���������Ϣ*/
cp_int32_t init_media_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md);

/*fmpeg���û�����Ϣ*/
cp_int32_t create_ffmpeg_buf_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame);

/*���ٻ�����Ϣ*/
cp_int32_t destroy_ffmpeg_buf_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/*���ô�����Ϣ*/
cp_int32_t set_ffmpeg_av_codec_error_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t error_no);

/*��������������*/
cp_int32_t proc_decode_failed_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/*�������ɹ�����*/
cp_int32_t proc_decode_successed_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/*ʹ��probe����Ϣ��������*/
cp_int32_t read_frame_by_probe_info(AVPacket *pkt, cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);


#endif





