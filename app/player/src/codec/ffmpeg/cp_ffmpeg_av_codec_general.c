/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-30

Description:

**************************************************************************/

#include "cp_ffmpeg_av_codec_general.h"
#include "cp_ffmpeg_av_audio_codec.h"
#include "cp_ffmpeg_av_video_codec.h"





/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_receive_media_description
*
* 函数说明: 设置返回信息
*
* 参    数: cp_media_packet_t * mp				[in]参数说明
* 参    数: AVCodecContext * avctx				[in]参数说明
* 参    数: AVFrame * frame						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-07 17:21:17
******************************************************************************************************/
cp_int32_t set_receive_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_packet_t *mp, AVCodecContext *avctx, AVFrame *frame)
{
	if (mp->md_p) {
		switch (mp->md_p->type)
		{
			case cp_media_description_type_general:
			{
				set_receive_general_media_description(ffmpeg_av_codec, mp->md_p, avctx, frame);
			}
			break;
			case cp_media_description_type_video:
			{
				set_receive_video_media_description(ffmpeg_av_codec, (cp_video_description_t*)(mp->md_p), avctx, frame);
			}
			break;
			case cp_media_description_type_audio:
			{
				set_receive_audio_media_description(ffmpeg_av_codec, (cp_audio_description_t*)(mp->md_p), avctx, frame);
			}
			break;
		}
		mp->md_p->encodec_type;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_receive_general_media_description
*
* 函数说明: 设置常规相关信息
*
* 参    数: cp_media_description_t * md						[in]参数说明
* 参    数: AVCodecContext * avctx						[in]参数说明
* 参    数: AVFrame * frame						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-08 11:15:35
******************************************************************************************************/
cp_int32_t set_receive_general_media_description(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md, AVCodecContext *avctx, AVFrame *frame)
{
	if (!md) {
		return -1;
	}

	if (AV_PIX_FMT_YUV420P == avctx->pix_fmt) {
		md->pix_fmt = cp_codec_pixel_format_yuv420p;
		return 0;
	}

	//md->pix_fmt = avctx->pix_fmt;
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_media_codec_info
*
* 函数说明: 初始化媒体解码器信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: cp_media_description_t * md						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-17 16:10:50
******************************************************************************************************/
cp_int32_t init_media_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_media_description_t *md)
{

	ffmpeg_av_codec->md = *md;

	switch (md->type)
	{
		case cp_media_description_type_audio:
		{
			ffmpeg_av_codec->audio_info = create_ffmpeg_av_audio_codec_info(ffmpeg_av_codec, md);
			if (ffmpeg_av_codec->audio_info) {
				ffmpeg_av_codec->audio_info->ad = *((cp_audio_description_t*)md);
				return 0;
			}
		}
		break;
		case cp_media_description_type_video:
		{
			ffmpeg_av_codec->video_info = create_ffmpeg_av_video_codec_info(ffmpeg_av_codec, md);
			if (ffmpeg_av_codec->video_info) {
				ffmpeg_av_codec->video_info->vd = *((cp_video_description_t*)md);
				return 0;
			}
		}
		break;
		default:
		{
			return -1;
		}
		break;
	}
	return -1;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_ffmpeg_buf_info
*
* 函数说明: ffmpeg设置缓存信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: AVCodecContext * avctx						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-19 17:39:36
******************************************************************************************************/
cp_int32_t create_ffmpeg_buf_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, AVCodecContext *avctx, AVFrame *frame)
{
	cp_void_t						*tmp_p = CP_NULL;
	cp_int32_t						tmp_buf_size = 0;
	double							t = 0.0;



	if (ffmpeg_av_codec->audio_info->buf) {
		return 0;
	}

	ffmpeg_av_codec->audio_info->cp_convert_ad.samples = av_rescale_rnd(
		swr_get_delay(ffmpeg_av_codec->audio_info->audio_convert_context, frame->sample_rate) + frame->nb_samples,
		ffmpeg_av_codec->audio_info->cp_convert_ad.sample_rate, ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.sample_rate, AV_ROUND_UP);
	ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.samples = ffmpeg_av_codec->audio_info->cp_convert_ad.samples;
	//创建缓存
	tmp_buf_size = av_samples_get_buffer_size(&ffmpeg_av_codec->audio_info->audio_out_linesize,
		ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.channels,
		ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.samples,
		ffmpeg_av_codec->audio_info->ffmpeg_convert_ad.sample_format,
		1);
	if (tmp_buf_size <= 0) {
		tmp_buf_size = CP_FFMPEG_AV_CODEC_MAX_AUDIO_FRAME_SIZE;
	}

	//创建一个转换用的缓存
	tmp_p = cp_palloc(ffmpeg_av_codec->pool, tmp_buf_size + cp_sizeof(cp_buf_t));
	if (!tmp_p) {
		return -1;
	}

	ffmpeg_av_codec->audio_info->buf = (cp_buf_t*)tmp_p;
	cp_buf_assemble(ffmpeg_av_codec->audio_info->buf, (cp_uchar_t*)tmp_p + cp_sizeof(cp_buf_t), tmp_buf_size - cp_sizeof(cp_buf_t));
	ffmpeg_av_codec->audio_info->audio_samples_buffer_size = tmp_buf_size;

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_ffmpeg_buf_info
*
* 函数说明: 消毁缓存信息
*
* 参    数: cp_ffmpeg_av_codec_t		*ffmpeg_av_codec			[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-19 17:41:07
******************************************************************************************************/
cp_int32_t destroy_ffmpeg_buf_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (ffmpeg_av_codec->audio_info) {
		if (ffmpeg_av_codec->audio_info->buf) {
			cp_pfree(ffmpeg_av_codec->pool, ffmpeg_av_codec->audio_info->buf);
			ffmpeg_av_codec->audio_info->buf = CP_NULL;
		}
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_ffmpeg_av_codec_error_info
*
* 函数说明: 设置错误信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: cp_int32_t error_no						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-20 17:20:00
******************************************************************************************************/
cp_int32_t set_ffmpeg_av_codec_error_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t error_no)
{
	if (!ffmpeg_av_codec) {
		return -1;
	}

	ffmpeg_av_codec->error_no = error_no;
	cp_memset(ffmpeg_av_codec->error_text, 0, cp_sizeof(ffmpeg_av_codec->error_text));
	av_strerror(error_no, ffmpeg_av_codec->error_text, cp_sizeof(ffmpeg_av_codec->error_text));
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: proc_decode_failed_data
*
* 函数说明: 处理解码错误数据
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: const cp_uchar_t * * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
* 参    数: cp_int32_t flag						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-21 13:34:19
******************************************************************************************************/
cp_int32_t proc_decode_failed_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t						tmp_ret_int = 0;



	++ffmpeg_av_codec->decodec_failed_times;
	if (ffmpeg_av_codec->decodec_failed_times < CP_FFMPEG_AV_CODEC_MAX_DECODE_FAILED_TIMES) {
		return -1;
	}
	if (ffmpeg_av_codec->decodec_failed_times > CP_MAX_INT) {
		ffmpeg_av_codec->decodec_failed_times = CP_FFMPEG_AV_CODEC_MAX_DECODE_FAILED_TIMES;
	}

	//这里判断是否之前是成功的
	if (ffmpeg_av_codec->audio_info->probe &&
		cp_ffmepg_av_probe_status_start == ffmpeg_av_codec->audio_info->probe->status &&
		ffmpeg_av_codec->decodec_successed_times > 0) {
		return 0;
	}



	if (ffmpeg_av_codec->audio_info->probe && cp_ffmepg_av_probe_status_probe == ffmpeg_av_codec->audio_info->probe->status) {

		cp_mutex_lock(&ffmpeg_av_codec->process_probe_mutex);
		tmp_ret_int = cp_ffmpeg_av_codec_probe_media_data(ffmpeg_av_codec, buf, len, flag);

		if (ffmpeg_av_codec->audio_info->probe->media_codec_context) {

			if (ffmpeg_av_codec->codec_context) {
				avcodec_free_context(&ffmpeg_av_codec->codec_context);
			}

			ffmpeg_av_codec->codec_context = ffmpeg_av_codec->audio_info->probe->media_codec_context;
			ffmpeg_av_codec->codec = ffmpeg_av_codec->audio_info->probe->media_codec;
			ffmpeg_av_codec->decodec_failed_times = 0;
		}

		cp_mutex_unlock(&ffmpeg_av_codec->process_probe_mutex);
	}
	else {
		if (ffmpeg_av_codec->audio_info->probe) {
			cp_ffmpeg_av_codec_stop_media_probe(ffmpeg_av_codec);
			cp_ffmpeg_av_codec_exit_media_probe(ffmpeg_av_codec);
		}

		cp_mutex_lock(&ffmpeg_av_codec->process_probe_mutex);

		tmp_ret_int = cp_ffmpeg_av_codec_init_media_probe(ffmpeg_av_codec);
		if (tmp_ret_int) {
			cp_module_log(error, ffmpeg_av_codec, "cp_ffmpeg_av_codec_init_media_probe() failed!");
			cp_mutex_unlock(&ffmpeg_av_codec->process_probe_mutex);
			return -2;
		}
		tmp_ret_int = cp_ffmpeg_av_codec_start_media_probe(ffmpeg_av_codec);
		if (tmp_ret_int) {
			cp_module_log(error, ffmpeg_av_codec, "cp_ffmpeg_av_codec_start_media_probe() failed!");
			cp_mutex_unlock(&ffmpeg_av_codec->process_probe_mutex);
			return -2;
		}

		cp_mutex_unlock(&ffmpeg_av_codec->process_probe_mutex);
	}

	return tmp_ret_int;
}

/*处理解码成功数据*/
cp_int32_t proc_decode_successed_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	ffmpeg_av_codec->error_no = 0;
	ffmpeg_av_codec->decodec_failed_times = 0;

	++ffmpeg_av_codec->decodec_successed_times;
	if (ffmpeg_av_codec->decodec_successed_times > CP_MAX_INT) {
		ffmpeg_av_codec->decodec_successed_times = 1;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: read_frame_by_probe_info
*
* 函数说明: 使用probe的信息处理数据
*
* 参    数: AVPacket * pkt						[in]参数说明
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: const cp_uchar_t * * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
* 参    数: cp_int32_t flag						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-10 15:48:28
******************************************************************************************************/
cp_int32_t read_frame_by_probe_info(AVPacket *pkt, cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	if (ffmpeg_av_codec->audio_info->probe &&
		(ffmpeg_av_codec->audio_info->probe->status >= cp_ffmepg_av_probe_status_unprobe &&
		ffmpeg_av_codec->audio_info->probe->status <= cp_ffmepg_av_probe_status_start)) {
		if (cp_ffmepg_av_probe_status_start == ffmpeg_av_codec->audio_info->probe->status) {
			return cp_ffmpeg_av_codec_probe_read_frame(pkt, ffmpeg_av_codec, buf, len, flag);
		}
		else {
			cp_ffmpeg_av_codec_probe_media_data(ffmpeg_av_codec, buf, len, flag);
		}
	}
	return -1;
}