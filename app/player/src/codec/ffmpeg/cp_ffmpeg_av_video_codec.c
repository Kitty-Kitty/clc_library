/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-30

Description:

**************************************************************************/


#include "cp_ffmpeg_av_video_codec.h"




/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_ffmpeg_av_video_codec_info
*
* 函数说明: 创建ffmpeg 视频信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: cp_media_description_t * md						[in]参数说明
*
* 返 回 值: cp_ffmpeg_av_dev_video_info_t *
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-02-17 16:17:42
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
* 版权所有: fz & novigo
*
* 函数名称: set_ffmpeg_av_video_convert_context_info
*
* 函数说明: 设置转码器信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
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
* 创建日期：2016-12-08 17:14:18
******************************************************************************************************/
cp_int32_t set_ffmpeg_av_video_convert_context_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, AVCodecContext *avctx, AVFrame *frame)
{
	cp_void_t						*tmp_p = CP_NULL;



	if (ffmpeg_av_codec->video_info->video_convert_context) {
		return 0;
	}

	//创建一个转换用的缓存
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

	//创建转换器
	ffmpeg_av_codec->video_info->video_convert_context = sws_getContext(avctx->width, avctx->height, avctx->pix_fmt,
		avctx->width, avctx->height, CP_FFMPEG_AV_CODEC_DEFAULT_PIX_FMT, SWS_BICUBIC, NULL, NULL, NULL);
	if (!ffmpeg_av_codec->video_info->video_convert_context) {
		return -2;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: fill_video_packet_shared_memory
*
* 函数说明: 共享内存方式填充数据
*
* 参    数: cp_media_packet_t * mp						[in]参数说明
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
* 创建日期：2016-12-08 11:25:44
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
* 版权所有: fz & novigo
*
* 函数名称: fill_video_packet_shared_memory
*
* 函数说明: 复内存方式填充数据
*
* 参    数: cp_media_packet_t * mp						[in]参数说明
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
* 创建日期：2016-12-08 11:25:44
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

		//如果已经存在足够内存则直接复制
		if (cp_buf_get_length(&mp->mp_buf.buf[i]) >= frame->linesize[i]) {
			cp_buf_strcat(&mp->mp_buf.buf[i], frame->data[i], frame->linesize[i]);
			continue;
		}

		//如果不存在足够内存则创建内存直接复制
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
* 版权所有: fz & novigo
*
* 函数名称: set_receive_video_media_description
*
* 函数说明: 设置视频相关信息
*
* 参    数: cp_video_description_t * vd						[in]参数说明
* 参    数: AVCodecContext * avctx						[in]参数说明
* 参    数: AVFrame * frame						[in]参数说明
*
* 返 回 值: cp_inline cp_static cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-08 11:07:53
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
* 版权所有: fz & novigo
*
* 函数名称: read_ffmpeg_video_data
*
* 函数说明: 读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
* 参    数: AVCodecContext * avctx						[in]参数说明
* 参    数: AVFrame * frame						[in]参数说明
* 参    数: cp_media_packet_t * mp						[in]参数说明
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
* 创建日期：2016-12-30 11:59:25
******************************************************************************************************/
cp_int32_t read_ffmpeg_video_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	AVCodecContext *avctx, AVFrame *frame, cp_media_packet_t *mp, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t					ret_int = 0;
	AVFrame						*tmp_av_frame = CP_NULL;



	//设置媒体描述处理数据
	ret_int = set_receive_media_description(ffmpeg_av_codec, mp, avctx, frame);
	if (ret_int) {
		return -1;
	}

	if (CP_FFMPEG_AV_CODEC_DEFAULT_PIX_FMT != avctx->pix_fmt) {
		//初始化转码
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

	//这里处理同步操作
	if (mp->ccb_info_p) {
		//这里设置回调函数
		mp->ccb_info_p->module = (cp_module_t *)ffmpeg_av_codec;
		mp->ccb_info_p->buf = (cp_uchar_t**)&mp;
		mp->ccb_info_p->len = len;
		mp->ccb_info_p->flag = flag;

		//如果存在回调函数则直接处理
		if (mp->ccb_info_p->handle.read_cb) {
			fill_video_packet_shared_memory(ffmpeg_av_codec, mp, avctx, tmp_av_frame);
			ret_int = mp->ccb_info_p->handle.read_cb(mp->orgin_module, mp->ccb_info_p, mp);
			return ret_int;
		}
	}

	//这里复制数据处理
	fill_video_packet_copy_data(ffmpeg_av_codec, mp, avctx, tmp_av_frame);
	return 0;
}


