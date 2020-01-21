/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-30

Description:

**************************************************************************/


#include "cp_ffmpeg_av_video_codec.h"




/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_ffmpeg_av_video_codec_info
*
* ����˵��: ����ffmpeg ��Ƶ��Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: cp_media_description_t * md						[in]����˵��
*
* �� �� ֵ: cp_ffmpeg_av_dev_video_info_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-02-17 16:17:42
******************************************************************************************************/
cp_ffmpeg_av_dev_video_info_t *create_ffmpeg_av_video_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md)
{
	cp_ffmpeg_av_dev_video_info_t				*tmp_codec_info = CP_NULL;


	tmp_codec_info = cp_palloc(ffmpeg_av_codec->pool, cp_sizeof(cp_ffmpeg_av_dev_video_info_t));
	if (!tmp_codec_info) {
		cp_module_log(error, ffmpeg_av_codec, "create_ffmpeg_av_video_codec_info() error.");
		return CP_NULL;
	}
	cp_memset(tmp_codec_info, 0, cp_sizeof(cp_ffmpeg_av_dev_video_info_t));
	return tmp_codec_info;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_ffmpeg_av_video_convert_context_info
*
* ����˵��: ����ת������Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: AVCodecContext * avctx						[in]����˵��
* ��    ��: AVFrame * frame						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-08 17:14:18
******************************************************************************************************/
cp_int32_t set_ffmpeg_av_video_convert_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, AVCodecContext *avctx, AVFrame *frame)
{
	cp_void_t						*tmp_p = CP_NULL;



	if (ffmpeg_av_codec->video_info->video_convert_context) {
		return 0;
	}

	//����һ��ת���õĻ���
	tmp_p = cp_palloc(ffmpeg_av_codec->pool,
		av_image_get_buffer_size(CP_FFMPEG_AV_CODEC_DEFAULT_PIX_FMT, frame->width, frame->height, 1));
	if (!tmp_p) {
		return -1;
	}

	av_image_fill_arrays(ffmpeg_av_codec->decoded_convert_frame.data,
		ffmpeg_av_codec->decoded_convert_frame.linesize,
		tmp_p,
		CP_FFMPEG_AV_CODEC_DEFAULT_PIX_FMT,
		frame->width,
		frame->height,
		1);

	//����ת����
	ffmpeg_av_codec->video_info->video_convert_context = sws_getContext(avctx->width, avctx->height, avctx->pix_fmt,
		avctx->width, avctx->height, CP_FFMPEG_AV_CODEC_DEFAULT_PIX_FMT, SWS_BICUBIC, NULL, NULL, NULL);
	if (!ffmpeg_av_codec->video_info->video_convert_context) {
		return -2;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_video_packet_shared_memory
*
* ����˵��: �����ڴ淽ʽ�������
*
* ��    ��: cp_media_packet_t * mp						[in]����˵��
* ��    ��: AVCodecContext * avctx						[in]����˵��
* ��    ��: AVFrame * frame						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-08 11:25:44
******************************************************************************************************/
cp_int32_t fill_video_packet_shared_memory(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame)
{
	cp_int32_t								i = 0;



	if (!mp) {
		return -1;
	}
	for (i = 0; i < cp_ary_size(frame->data); i++) {
		if (frame->linesize[i] <= 0) {
			break;
		}
		cp_buf_assemble(&mp->mp_buf.buf[i], frame->data[i], frame->linesize[i]);
		cp_buf_position(&mp->mp_buf.buf[i], frame->linesize[i]);
	}
	if (mp->ccb_info_p) {
		mp->ccb_info_p->status_info.status = 0;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_video_packet_shared_memory
*
* ����˵��: ���ڴ淽ʽ�������
*
* ��    ��: cp_media_packet_t * mp						[in]����˵��
* ��    ��: AVCodecContext * avctx						[in]����˵��
* ��    ��: AVFrame * frame						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-08 11:25:44
******************************************************************************************************/
cp_int32_t fill_video_packet_copy_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame)
{
	cp_int32_t								i = 0;
	cp_int32_t								ret_int = 0;



	if (!mp) {
		return -1;
	}
	for (i = 0; i < cp_ary_size(frame->data); i++) {
		if (frame->linesize[i] <= 0) {
			break;
		}

		//����Ѿ������㹻�ڴ���ֱ�Ӹ���
		if (cp_buf_get_length(&mp->mp_buf.buf[i]) >= frame->linesize[i]) {
			cp_buf_strcat(&mp->mp_buf.buf[i], frame->data[i], frame->linesize[i]);
			continue;
		}

		//����������㹻�ڴ��򴴽��ڴ�ֱ�Ӹ���
		if (!create_media_packet_channel_buffer(mp, i, frame->linesize[i])) {
			cp_buf_strcat(&mp->mp_buf.buf[i], frame->data[i], frame->linesize[i]);
			continue;
		}

		if (mp->ccb_info_p) {
			mp->ccb_info_p->status_info.status = 401;
			return -2;
		}
	}
	if (mp->ccb_info_p) {
		mp->ccb_info_p->status_info.status = 0;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_receive_video_media_description
*
* ����˵��: ������Ƶ�����Ϣ
*
* ��    ��: cp_video_description_t * vd						[in]����˵��
* ��    ��: AVCodecContext * avctx						[in]����˵��
* ��    ��: AVFrame * frame						[in]����˵��
*
* �� �� ֵ: cp_inline cp_static cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-08 11:07:53
******************************************************************************************************/
cp_int32_t set_receive_video_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_video_description_t *vd, AVCodecContext *avctx, AVFrame *frame)
{
	set_receive_general_media_description(ffmpeg_av_codec, (cp_media_description_t*)vd, avctx, frame);

	vd->width = frame->width;
	vd->height = frame->height;
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: read_ffmpeg_video_data
*
* ����˵��: ��ȡģ�����ݣ�flagΪ��ȡģʽ����չ��־��Ĭ��Ϊ0������ΪԤ��
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: AVCodecContext * avctx						[in]����˵��
* ��    ��: AVFrame * frame						[in]����˵��
* ��    ��: cp_media_packet_t * mp						[in]����˵��
* ��    ��: cp_int32_t len						[in]����˵��
* ��    ��: cp_int32_t flag						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-30 11:59:25
******************************************************************************************************/
cp_int32_t read_ffmpeg_video_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame, cp_media_packet_t *mp, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t					ret_int = 0;
	AVFrame						*tmp_av_frame = CP_NULL;



	//����ý��������������
	ret_int = set_receive_media_description(ffmpeg_av_codec, mp, avctx, frame);
	if (ret_int) {
		return -1;
	}

	if (CP_FFMPEG_AV_CODEC_DEFAULT_PIX_FMT != avctx->pix_fmt) {
		//��ʼ��ת��
		if (set_ffmpeg_av_video_convert_context_info(ffmpeg_av_codec, avctx, frame)) {
			return -2;
		}
		else {
			sws_scale(ffmpeg_av_codec->video_info->video_convert_context,
				(const uint8_t* const*)frame->data,
				frame->linesize,
				0,
				frame->height,
				ffmpeg_av_codec->decoded_convert_frame.data,
				ffmpeg_av_codec->decoded_convert_frame.linesize);

			tmp_av_frame = &ffmpeg_av_codec->decoded_convert_frame;
		}
	}
	else {
		tmp_av_frame = &ffmpeg_av_codec->decoded_frame;
	}

	if (!tmp_av_frame) {
		return -3;
	}

	//���ﴦ��ͬ������
	if (mp->ccb_info_p) {
		//�������ûص�����
		mp->ccb_info_p->module = (cp_module_t *)ffmpeg_av_codec;
		mp->ccb_info_p->buf = (cp_uchar_t**)&mp;
		mp->ccb_info_p->len = len;
		mp->ccb_info_p->flag = flag;

		//������ڻص�������ֱ�Ӵ���
		if (mp->ccb_info_p->handle.read_cb) {
			fill_video_packet_shared_memory(ffmpeg_av_codec, mp, avctx, tmp_av_frame);
			ret_int = mp->ccb_info_p->handle.read_cb(mp->orgin_module, mp->ccb_info_p, mp);
			return ret_int;
		}
	}

	//���︴�����ݴ���
	fill_video_packet_copy_data(ffmpeg_av_codec, mp, avctx, tmp_av_frame);
	return 0;
}


