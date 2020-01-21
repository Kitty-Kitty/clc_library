/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-30

Description:

**************************************************************************/
#include "cp_ffmpeg_av_audio_codec.h"
#include "cp_ffmpeg_av_video_codec.h"



//�����������
cp_inline cp_static cp_int32_t process_floating_point_formats(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame, cp_buf_t *buf);

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: create_ffmpeg_av_audio_codec_info
*
* ����˵��: ������Ƶ������Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: cp_media_description_t * md						[in]����˵��
*
* �� �� ֵ: cp_ffmpeg_av_dev_audio_info_t *
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-02-17 16:15:04
******************************************************************************************************/
cp_ffmpeg_av_dev_audio_info_t *create_ffmpeg_av_audio_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md)
{
	cp_ffmpeg_av_dev_audio_info_t				*tmp_codec_info = CP_NULL;


	tmp_codec_info = cp_palloc(ffmpeg_av_codec->pool, cp_sizeof(cp_ffmpeg_av_dev_audio_info_t));
	if (!tmp_codec_info) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "create_ffmpeg_av_audio_codec_info() error.");
		return CP_NULL;
	}
	cp_memset(tmp_codec_info, 0, cp_sizeof(cp_ffmpeg_av_dev_audio_info_t));

	return tmp_codec_info;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_ffmpeg_av_audio_convert_info
*
* ����˵��: ������Ƶ�ز�����Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: cp_audio_description_t * ad						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-20 15:41:19
******************************************************************************************************/
cp_int32_t set_ffmpeg_av_audio_convert_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_audio_description_t *ad)
{
	cp_int32_t					ret_int = 0;





	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_ffmpeg_av_audio_convert_context_info
*
* ����˵��: ������Ƶת������Ϣ
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
* �������ڣ�2016-12-19 18:07:15
******************************************************************************************************/
cp_int32_t set_ffmpeg_av_audio_convert_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_audio_description_t *ad, AVCodecContext *avctx, AVFrame *frame)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_bool_t										tmp_is_planar = cp_false;
	cp_void_t										*tmp_p = CP_NULL;
	struct SwrContext								*tmp_swr_ctx = CP_NULL;
	cp_ffmpeg_av_codec_audio_format_t				*tmp_af = CP_NULL;
	cp_ffmpeg_av_codec_audio_channel_layout_t		*tmp_acl = CP_NULL;
	int64_t											tmp_source_layout = frame->channel_layout;
	cp_int32_t										tmp_source_sample_fmt = frame->format;
	cp_int32_t										tmp_source_sample_rate = frame->sample_rate;
	int64_t											tmp_dest_layout = frame->channel_layout;
	cp_int32_t										tmp_dest_sample_fmt = frame->format;
	cp_int32_t										tmp_dest_sample_rate = frame->sample_rate;



	if (ffmpeg_av_codec->audio_info->audio_convert_context) {
		return 0;
	}

	//�ж��Ƿ�ƽ�������planar��
	tmp_ret_int = av_sample_fmt_is_planar(frame->format);
	if (tmp_ret_int) {
		tmp_is_planar = cp_true;
	}

	//������Ƶ�����Ϣ,ͬʱ����format��channel_layout��ת��
	if (ffmpeg_av_codec->audio_info->audio_convert) {
		tmp_af = get_ffmpeg_audio_format_info(ffmpeg_av_codec->audio_info->cp_convert_ad.sample_format);
		if (!tmp_af) {
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"css_sample_format[%d] not found ffmpeg audio sample_format",
				ffmpeg_av_codec->audio_info->cp_convert_ad.sample_format);
			return -1;
		}

		tmp_acl = get_ffmpeg_audio_channel_layout_info(ffmpeg_av_codec->audio_info->cp_convert_ad.channel_layout);
		if (!tmp_acl) {
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"css_channel_layout[%d] not found ffmpeg audio channel_layout",
				ffmpeg_av_codec->audio_info->cp_convert_ad.channel_layout);
			return -1;
		}
		tmp_dest_layout = tmp_acl->ffmpeg_audio_channel_layout_type;
		tmp_dest_sample_fmt = tmp_af->ffmpeg_audio_format_type;
		tmp_dest_sample_rate = ffmpeg_av_codec->audio_info->cp_convert_ad.sample_rate;
	}
	else {
		tmp_af = get_cp_audio_format_info(tmp_dest_sample_fmt);
		if (!tmp_af) {
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"ffmpeg audio sample_format[%d] not found css_sample_format",
				tmp_dest_sample_fmt);
			return -1;
		}
		tmp_acl = get_cp_audio_channel_layout_info(tmp_dest_layout);
		if (!tmp_acl) {
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"ffmpeg audio channel_layout[%d] not found css_channel_layout",
				tmp_dest_layout);
			return -1;
		}
		ffmpeg_av_codec->audio_info->cp_convert_ad.channel_layout = tmp_acl->cp_audio_channel_layout_type;
		ffmpeg_av_codec->audio_info->cp_convert_ad.sample_format = tmp_af->cp_audio_format_type;
		ffmpeg_av_codec->audio_info->cp_convert_ad.sample_rate = tmp_dest_sample_rate;
	}

	ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.sample_format = tmp_dest_sample_fmt;
	ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.sample_rate = tmp_dest_sample_rate;
	ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.channel_layout = tmp_dest_layout;
	ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.samples = ad->samples;
	// 	ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.samples = 
	// 		FFMAX(CP_FFMPEG_AV_CODEC_MIN_BUFFER_SIZE, 2 << av_log2(ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.sample_rate / CP_FFMPEG_AV_CODEC_MAX_CALLBACKS_PER_SEC));
	ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.channels = av_get_channel_layout_nb_channels(tmp_dest_layout);
	ffmpeg_av_codec->audio_info->cp_convert_ad.channels = av_get_channel_layout_nb_channels(tmp_dest_layout);
	ffmpeg_av_codec->audio_info->cp_convert_ad.samples = ad->samples;
	// 	ffmpeg_av_codec->audio_info->cp_convert_ad.samples = ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.samples;

	//�����ز�������ת������
	tmp_swr_ctx = swr_alloc();
	if (!tmp_swr_ctx) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "swr_alloc() failed!");
		return -1;
	}

	//�����ز���������
#if LIBSWRESAMPLE_VERSION_MINOR >= 17    // ���ݰ汾��ͬ��ѡ���ʵ�����  
	av_opt_set_int(tmp_swr_ctx, "och", tmp_dest_layout, 0);
	av_opt_set_sample_fmt(tmp_swr_ctx, "out_sample_fmt", tmp_dest_sample_fmt, 0);
	av_opt_set_int(tmp_swr_ctx, "out_sample_rate", tmp_dest_sample_rate, 0);
	av_opt_set_int(tmp_swr_ctx, "ich", tmp_source_layout, 0);
	av_opt_set_sample_fmt(tmp_swr_ctx, "in_sample_fmt", tmp_source_sample_fmt, 0);
	av_opt_set_int(tmp_swr_ctx, "in_sample_rate", tmp_source_sample_rate, 0);
#else  
	/* set options */
	// 	av_opt_set_int(tmp_swr_ctx, "in_channel_layout", tmp_source_layout, 0);
	// 	av_opt_set_int(tmp_swr_ctx, "in_sample_rate", tmp_source_sample_rate, 0);
	// 	av_opt_set_sample_fmt(tmp_swr_ctx, "in_sample_fmt", tmp_source_sample_fmt, 0);
	// 
	// 	av_opt_set_int(tmp_swr_ctx, "out_channel_layout", tmp_dest_layout, 0);
	// 	av_opt_set_int(tmp_swr_ctx, "out_sample_rate", tmp_dest_sample_rate, 0);
	// 	av_opt_set_sample_fmt(tmp_swr_ctx, "out_sample_fmt", tmp_dest_sample_fmt, 0);
	swr_alloc_set_opts(tmp_swr_ctx,
		tmp_dest_layout,
		(enum AVSampleFormat)tmp_dest_sample_fmt,
		tmp_dest_sample_rate,
		tmp_source_layout,
		(enum AVSampleFormat)tmp_source_sample_fmt,
		tmp_source_sample_rate,
		0,
		CP_NULL);
#endif  

	if (!tmp_swr_ctx) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "swr_alloc_set_opts() failed!");
		return -1;
	}

 	//��ʼ���ز�����
	tmp_ret_int = swr_init(tmp_swr_ctx);
	if (tmp_ret_int < 0) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "swr_init() failed! %s", ffmpeg_av_codec->error_text);
		return -2;
	}

	//�����ռ䲻һ��������
	if (ffmpeg_av_codec->audio_info->cp_convert_ad.samples != frame->nb_samples) {
		tmp_ret_int = swr_set_compensation(tmp_swr_ctx,
			(ffmpeg_av_codec->audio_info->cp_convert_ad.samples - frame->nb_samples)
			* ffmpeg_av_codec->audio_info->cp_convert_ad.sample_rate
			/ frame->sample_rate,
			ffmpeg_av_codec->audio_info->cp_convert_ad.samples * ffmpeg_av_codec->audio_info->cp_convert_ad.sample_rate
			/ frame->sample_rate);
		if (tmp_ret_int < 0) {
			set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "swr_set_compensation() failed! %s", ffmpeg_av_codec->error_text);
			//return -2;
		}
	}

	ffmpeg_av_codec->audio_info->audio_convert_context = tmp_swr_ctx;

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: unset_ffmpeg_av_audio_convert_context_info
*
* ����˵��: ȡ��������Ƶת������Ϣ
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-19 18:44:39
******************************************************************************************************/
cp_int32_t unset_ffmpeg_av_audio_convert_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (!ffmpeg_av_codec->audio_info->audio_convert ||
		!ffmpeg_av_codec->audio_info->audio_convert_context) {
		return 0;
	}

 	if (swr_is_initialized(ffmpeg_av_codec->audio_info->audio_convert_context)) {
 		swr_close(ffmpeg_av_codec->audio_info->audio_convert_context);
 	}
	
	swr_free(&(ffmpeg_av_codec->audio_info->audio_convert_context));
	ffmpeg_av_codec->audio_info->audio_convert_context = CP_NULL;
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: set_ffmpeg_av_audio_codec_context_info
*
* ����˵��: ������Ƶ����������
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: cp_audio_description_t * ad						[in]����˵��
* ��    ��: AVCodecContext * codec_context						[in]����˵��
* ��    ��: AVCodec * codec						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ�
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-23 10:00:15
******************************************************************************************************/
cp_int32_t set_ffmpeg_av_audio_codec_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_audio_description_t *ad, AVCodecContext *codec_context, AVCodec *codec)
{
	if (AV_CODEC_ID_PCM_ALAW == codec->id) {
		codec_context->sample_rate = ad->sample_rate;
		codec_context->channel_layout = ad->channel_layout;
		codec_context->channels = av_get_channel_layout_nb_channels(codec_context->channel_layout);
		codec_context->sample_fmt = ad->sample_format;
		AVRational ar = { 1, codec_context->sample_rate };
		codec_context->time_base = ar;
	}

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_audio_packet_shared_memory
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
* �������ڣ�2016-12-20 09:20:33
******************************************************************************************************/
cp_int32_t fill_audio_packet_shared_memory(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame)
{
	cp_int32_t								i = 0;



	if (!mp) {
		return -1;
	}

	if (!ffmpeg_av_codec->audio_info->buf) {
		return -1;
	}
	mp->mp_buf.buf[0] = *(ffmpeg_av_codec->audio_info->buf);
	if (mp->ccb_info_p) {
		mp->ccb_info_p->status_info.status = 0;
	}
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: fill_audio_packet_copy_data
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
* �������ڣ�2016-12-20 09:20:43
******************************************************************************************************/
cp_int32_t fill_audio_packet_copy_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame)
{
	cp_int32_t								ret_int = 0;


	if (!mp) {
		return -1;
	}

	//����Ѿ������㹻�ڴ���ֱ�Ӹ���
	if (cp_buf_get_length(&mp->mp_buf.buf[0]) >= cp_buf_get_length(ffmpeg_av_codec->audio_info->buf)) {
		cp_buf_strcat(&mp->mp_buf.buf[0], cp_buf_get_pos(ffmpeg_av_codec->audio_info->buf), cp_buf_get_length(ffmpeg_av_codec->audio_info->buf));
		return 0;
	}

	//����������㹻�ڴ��򴴽��ڴ�ֱ�Ӹ���
	if (!create_media_packet_channel_buffer(mp, 0, cp_buf_get_length(ffmpeg_av_codec->audio_info->buf))) {
		cp_buf_strcat(&mp->mp_buf.buf[0], cp_buf_get_pos(ffmpeg_av_codec->audio_info->buf), cp_buf_get_length(ffmpeg_av_codec->audio_info->buf));
		return 0;
	}
	else {
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
* ��������: set_receive_audio_media_description
*
* ����˵��: ������Ƶ�����Ϣ
*
* ��    ��: cp_video_description_t * vd						[in]����˵��
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
* �������ڣ�2016-12-08 11:11:41
******************************************************************************************************/
cp_int32_t set_receive_audio_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_audio_description_t *ad, AVCodecContext *avctx, AVFrame *frame)
{
	set_receive_general_media_description(ffmpeg_av_codec, (cp_media_description_t*)ad, avctx, frame);

	ad->sample_rate = ffmpeg_av_codec->audio_info->cp_convert_ad.sample_rate;
	ad->channel_layout = ffmpeg_av_codec->audio_info->cp_convert_ad.channel_layout;
	ad->sample_format = ffmpeg_av_codec->audio_info->cp_convert_ad.sample_format;
	ad->out_linesize = ffmpeg_av_codec->audio_info->audio_out_linesize;
	ad->samples_buffer_size = ffmpeg_av_codec->audio_info->audio_samples_buffer_size;
	ad->channels = ffmpeg_av_codec->audio_info->cp_convert_ad.channels;
	ad->samples = ffmpeg_av_codec->audio_info->cp_convert_ad.samples;

	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: read_ffmpeg_audio_data
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
* �������ڣ�2016-12-30 11:59:59
******************************************************************************************************/
cp_int32_t read_ffmpeg_audio_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame, cp_media_packet_t *mp, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t					ret_int = 0;
	cp_int32_t					tmp_buf_size = 0;
	cp_int32_t					tmp_out_linesize = 0;
	AVFrame						*tmp_av_frame = CP_NULL;
	uint8_t						*tmp_out_buf = CP_NULL;



	//�����ز�����Ϣ
	ret_int = set_ffmpeg_av_audio_convert_context_info(ffmpeg_av_codec, (cp_audio_description_t*)mp->md_p, avctx, frame);
	if (ret_int) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "set_ffmpeg_av_audio_convert_context_info() error.");
		return -1;
	}

	//��������
	ret_int = create_ffmpeg_buf_info(ffmpeg_av_codec, avctx, frame);
	if (ret_int) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "create_ffmpeg_buf_info() error.");
		return -2;
	}

	//����ý��������������
	ret_int = set_receive_media_description(ffmpeg_av_codec, mp, avctx, frame);
	if (ret_int) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "set_receive_media_description() error.");
		return -1;
	}

#if defined(CP_FFMPEG_AV_CODEC_FILE_DEBUG)
	if (ffmpeg_av_codec->file) {
		if (frame->data[0] && frame->data[1])
		{
			int size = av_get_bytes_per_sample(frame->format);
			for (int i = 0; i < avctx->frame_size; i++)
			{
				fwrite(frame->data[0] + i * size, 1, size, ffmpeg_av_codec->file);
				fwrite(frame->data[1] + i * size, 1, size, ffmpeg_av_codec->file);
			}
		}
		else if (frame->data[0])
		{
			fwrite(frame->data[0], 1, frame->linesize[0], ffmpeg_av_codec->file);
		}
	}
#endif

	cp_buf_clear(ffmpeg_av_codec->audio_info->buf);
	tmp_out_buf = (uint8_t*)cp_buf_get_pos(ffmpeg_av_codec->audio_info->buf);

	//�����������floating-point formats
	process_floating_point_formats(ffmpeg_av_codec, avctx, frame, ffmpeg_av_codec->audio_info->buf);

	//���²���
	ret_int = swr_convert(ffmpeg_av_codec->audio_info->audio_convert_context,
		&tmp_out_buf,
		ffmpeg_av_codec->audio_info->audio_out_linesize,
		(const uint8_t **)frame->data,
		frame->nb_samples);
	if (ret_int < 0) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, ret_int);
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);
		return -3;
	}
	else {
		//�������ݴ�С
		cp_buf_position(ffmpeg_av_codec->audio_info->buf, ffmpeg_av_codec->audio_info->audio_out_linesize);

		//����ʣ�ڻ������ݣ���������nb_samles�����˴�����nb_samplse��SwrContext�л��л��棬�ᵼ���ڴ�һֱ����
		while (cp_true) {
			//������л�����swrcontext��,�ڶ�������Ҫ��д0���ܻ�ȡ������������ 
			ret_int = swr_get_out_samples(ffmpeg_av_codec->audio_info->audio_convert_context, 0);
			if (ret_int >= ffmpeg_av_codec->audio_info->audio_out_linesize) {
				tmp_out_buf = (uint8_t*)cp_buf_get_pos(ffmpeg_av_codec->audio_info->buf);
				ret_int = swr_convert(ffmpeg_av_codec->audio_info->audio_convert_context,
					&tmp_out_buf,
					ffmpeg_av_codec->audio_info->audio_out_linesize,
					CP_NULL,
					0);
				if (ret_int) {
					cp_buf_position(ffmpeg_av_codec->audio_info->buf, ffmpeg_av_codec->audio_info->audio_out_linesize);
				}
			}
			else {
//  				ret_int = swr_convert(ffmpeg_av_codec->audio_info->audio_convert_context,
//  					&tmp_out_buf,
//  					ffmpeg_av_codec->audio_info->audio_out_linesize,
//  					CP_NULL,
//  					0);
				break;
			}
		}
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
			fill_audio_packet_shared_memory(ffmpeg_av_codec, mp, avctx, tmp_av_frame);
			ret_int = mp->ccb_info_p->handle.read_cb(mp->orgin_module, mp->ccb_info_p, mp);
			return ret_int;
		}
	}
	//���︴�����ݴ���
	fill_audio_packet_copy_data(ffmpeg_av_codec, mp, avctx, tmp_av_frame);
	return 0;
}

/******************************************************************************************************
* ��Ȩ����: fz & novigo
*
* ��������: process_floating_point_formats
*
* ����˵��: �����������
*
* ��    ��: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]����˵��
* ��    ��: AVCodecContext * avctx						[in]����˵��
* ��    ��: AVFrame * frame						[in]����˵��
* ��    ��: cp_buf_t * buf						[in]����˵��
*
* �� �� ֵ: cp_int32_t
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2017-01-04 13:34:52
******************************************************************************************************/
cp_int32_t process_floating_point_formats(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame, cp_buf_t *buf)
{
	cp_int32_t						i = 0;
	cp_int32_t						c = 0;
	cp_int32_t						tmp_nb_samples = frame->nb_samples;
	cp_int32_t						tmp_channels = frame->channels;
	int16_t*						tmp_output_buffer = (int16_t*)cp_buf_get_pos(buf);
	float*							tmp_extended_data = CP_NULL;
	float							tmp_sample = 0;
	double							tmp_max_value = 0.0f;



	if (AV_SAMPLE_FMT_FLTP != frame->format &&
		AV_SAMPLE_FMT_DBLP != frame->format) {
		return 0;
	}

	if (AV_SAMPLE_FMT_FLTP == frame->format) {
		//tmp_max_value = 32767.0f;
		tmp_max_value = 3.40282e+038;
	}
	else {
		tmp_max_value = 1.79769e+308;
	}

	for (i = 0; i < tmp_nb_samples; i++) {
		for (c = 0; c < tmp_channels; c++) {
			tmp_extended_data = (float*)frame->extended_data[c];
			if (!tmp_extended_data) {
				continue;
			}
			tmp_sample = tmp_extended_data[i];
			if (tmp_sample < -1.0f) {
				tmp_sample = -1.0f;
			}
			else if (tmp_sample > 1.0f) {
				tmp_sample = 1.0f;
			}
			tmp_output_buffer[i * tmp_channels + c] = (int16_t)round(tmp_sample * tmp_max_value);
		}
	}

	return 0;
}