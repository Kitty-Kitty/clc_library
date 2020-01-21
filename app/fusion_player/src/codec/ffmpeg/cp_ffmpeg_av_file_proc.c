/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_file_codec.c
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/06
*
*Description: create (cp_ffmpeg_av_file_codec.c)
*
*Others:
*
*History:
*******************************************************************************/

#include "cp_ffmpeg_av_file_proc.h"

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_ffmpeg_av_file_info
*
* 函数全名: create_ffmpeg_av_file_info
*
* 函数访问: public
*
* 函数说明: 创建file info信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:18:28
********************************************************************************/
cp_int32_t create_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (!ffmpeg_av_codec) {
		return -1;
	}

	//创建file info
	ffmpeg_av_codec->file_info = (cp_ffmpeg_av_file_info_t *)cp_palloc(
		ffmpeg_av_codec->pool, cp_sizeof(cp_ffmpeg_av_file_info_t));
	if (!ffmpeg_av_codec->file_info) {
		return -2;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_ffmpeg_av_file_info
*
* 函数全名: init_ffmpeg_av_file_info
*
* 函数访问: public
*
* 函数说明: 初始化file info信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:18:45
********************************************************************************/
cp_int32_t init_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	cp_ffmpeg_av_file_conf_t					tmp_fafc = { 0, };



	//解析配置文件
	ffmpeg_av_file_parse_configure(ffmpeg_av_codec, &tmp_fafc);

	//创建消息列表
	if (tmp_fafc.min_cache_size <= 0) {
		ffmpeg_av_codec->file_info->min_cache_size = CP_FFMPEG_AV_FILE_SQ_DEFAULT_CACHE_SIZE / 2;
	}
	else {
		ffmpeg_av_codec->file_info->min_cache_size = tmp_fafc.min_cache_size;
	}
	ffmpeg_av_codec->file_info->max_cache_size = ffmpeg_av_codec->file_info->min_cache_size * 2;

	ffmpeg_av_codec->file_info->data_sq = cp_create_general_safe_queue(cp_safe_queue_mode_qbss,
		ffmpeg_av_codec->file_info->max_cache_size);
	if (!ffmpeg_av_codec->file_info->data_sq) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "cp_create_general_safe_queue() failed!");
		return -1;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: open_ffmpeg_av_file_info
*
* 函数全名: open_ffmpeg_av_file_info
*
* 函数访问: public
*
* 函数说明: 打开file info信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
* 参    数: cp_media_description_t *md									[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:19:12
********************************************************************************/
cp_int32_t open_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md)
{
	cp_int32_t						tmp_ret_int = 0;



	if (!ffmpeg_av_codec || !md) {
		return -1;
	}

	tmp_ret_int = open_ffmpeg_av_file_stream(ffmpeg_av_codec, md);
	if (tmp_ret_int) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "open_ffmpeg_av_file_stream() failed!");
		return -1;
	}

	tmp_ret_int = start_ffmpeg_av_decode_thread_process(ffmpeg_av_codec);
	if (tmp_ret_int) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "start_ffmpeg_av_decode_thread_process() failed!");
		return -1;
	}

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: read_ffmpeg_av_file_data
*
* 函数全名: read_ffmpeg_av_file_data
*
* 函数访问: public
*
* 函数说明: 读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
* 参    数: cp_uchar_t * * buf						[in/out]参数说明
* 参    数: cp_int32_t len						[in/out]参数说明
* 参    数: cp_int32_t flag						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:32:40
********************************************************************************/
cp_int32_t read_ffmpeg_av_file_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t						tmp_ret_int = 0;
	AVFrame							*tmp_av_frame = CP_NULL;
	cp_media_packet_t				*tmp_mp = CP_NULL;



	//转换媒体数据，并校验数据合法性
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
			"unsupport media packet type[%d].", tmp_mp->type);
		return -2;
	}

	tmp_av_frame = cp_safe_queue_pop(ffmpeg_av_codec->file_info->data_sq);
	if (!tmp_av_frame) {
		return -1;
	}

	switch (tmp_mp->md_p->type) {
		case cp_media_description_type_general:
		{
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, 
				"unsupport media description type[%d].", tmp_mp->md_p->type);
			return -1;
		}
		break;
		case cp_media_description_type_video:
		{
			//视频处理
			tmp_ret_int = read_ffmpeg_video_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
				tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
			break;
		}
		break;
		case cp_media_description_type_audio:
		{
			//音频处理
			tmp_ret_int = read_ffmpeg_audio_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
				tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
		}
		break;
		default:
		{
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "unsupport media description type[%d].", tmp_mp->md_p->type);
			tmp_ret_int = -3;
		}
		break;
	}

	return tmp_ret_int;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: write_ffmpeg_av_file_data
*
* 函数全名: write_ffmpeg_av_file_data
*
* 函数访问: public
*
* 函数说明: 写模块数据，flag为写模式的扩展标志。默认为0，其他为预留
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
* 参    数: const cp_uchar_t * * buf						[in/out]参数说明
* 参    数: cp_int32_t len						[in/out]参数说明
* 参    数: cp_int32_t flag						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:32:51
********************************************************************************/
cp_int32_t write_ffmpeg_av_file_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: close_ffmpeg_av_file_info
*
* 函数全名: close_ffmpeg_av_file_info
*
* 函数访问: public
*
* 函数说明: 关闭file info信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:19:22
********************************************************************************/
cp_int32_t close_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	return close_ffmpeg_av_file_stream(ffmpeg_av_codec);
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: exit_ffmpeg_av_file_info
*
* 函数全名: exit_ffmpeg_av_file_info
*
* 函数访问: public
*
* 函数说明: 退出file info信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:19:32
********************************************************************************/
cp_int32_t exit_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (!ffmpeg_av_codec) {
		return -1;
	}

	if (ffmpeg_av_codec->file_info->data_sq) {
		cp_destroy_safe_queue(ffmpeg_av_codec->file_info->data_sq);
		ffmpeg_av_codec->file_info->data_sq = CP_NULL;
	}
	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_ffmpeg_av_file_info
*
* 函数全名: destroy_ffmpeg_av_file_info
*
* 函数访问: public
*
* 函数说明: 消毁file info
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 12:19:42
********************************************************************************/
cp_int32_t destroy_ffmpeg_av_file_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (!ffmpeg_av_codec) {
		return -1;
	}

	close_ffmpeg_av_file_info(ffmpeg_av_codec);
	exit_ffmpeg_av_file_info(ffmpeg_av_codec);

	if (ffmpeg_av_codec->file_info) {
		cp_pfree(ffmpeg_av_codec->pool, ffmpeg_av_codec->file_info);
		ffmpeg_av_codec->file_info = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: open_ffmpeg_av_file_stream
*
* 函数说明: 打开url指定的媒体源信息
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
* 创建日期：2016-12-22 11:07:37
******************************************************************************************************/
cp_int32_t open_ffmpeg_av_file_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md)
{
	cp_int32_t									i = 0;
	cp_int32_t									tmp_ret_int = 0;
	cp_char_t									*tmp_video_url = CP_NULL;
	cp_ffmpeg_av_codec_conf_t					*tmp_codec_conf = CP_NULL;
	cp_ffmpeg_av_codec_audio_channel_layout_t	*tmp_ffmpeg_channel_layout = CP_NULL;
	cp_video_description_t						*tmp_vd = CP_NULL;



	if (!ffmpeg_av_codec) {
		return -1;
	}

	if (ffmpeg_av_codec->codec) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"open_ffmpeg_av_file_stream() warning. repeat operation.");
		return 0;
	}

	switch (md->type)
	{
		case cp_media_description_type_video:
		{
			tmp_vd = (cp_video_description_t *)md;
			tmp_video_url = tmp_vd->url;
		}
		break;
		default:
		{
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"unspport media type[%d]",
				md->type);
			return -2;
		}
		break;
	}

	//avcodec register
	//avcodec_register_all();
	av_register_all();
	avformat_network_init();

	//创建format ctx
	ffmpeg_av_codec->format_ctx = avformat_alloc_context();
	if (!ffmpeg_av_codec->format_ctx) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"avformat_alloc_context() not found.");
		return -2;
	}

	//打开媒体源
	tmp_ret_int = avformat_open_input(&ffmpeg_av_codec->format_ctx, tmp_video_url, NULL, NULL);
	if (tmp_ret_int != 0) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"avformat_open_input() error. couldn't open input stream[%s] reason:[%s].",
			tmp_video_url,
			ffmpeg_av_codec->error_text);
		return -1;
	}
	else {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"avformat_open_input() successed. open input stream[%s] successed.",
			tmp_video_url);
	}

	//查找流信息
	tmp_ret_int = avformat_find_stream_info(ffmpeg_av_codec->format_ctx, NULL);
	if (tmp_ret_int < 0) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"avformat_find_stream_info() error. couldn't find stream[%s] info. reason:[%s].",
			tmp_video_url,
			ffmpeg_av_codec->error_text);
		return -2;
	}
	else {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"avformat_find_stream_info() successed.");
	}

	for (i = 0; i < ffmpeg_av_codec->format_ctx->nb_streams; i++) {
		if (ffmpeg_av_codec->format_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			ffmpeg_av_codec->codec_context = ffmpeg_av_codec->format_ctx->streams[i]->codec;
			break;
		}
	}

	if (!ffmpeg_av_codec->codec_context) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"couldn't find stream[%s] codec_context.",
			tmp_video_url);
		return -2;
	}

#if 0
	//查找最好的流
	tmp_ret_int = av_find_best_stream(ffmpeg_av_codec->format_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &ffmpeg_av_codec->codec, 0);
	if (tmp_ret_int < 0) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"av_find_best_stream() error. couldn't find stream[%s] media[%d] best stream. reason:[%s].",
			tmp_video_url,
			AVMEDIA_TYPE_VIDEO,
			ffmpeg_av_codec->error_text);
		return -2;
	}
	else {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"av_find_best_stream() successed.");
	}
#endif

	//查找decodec
	ffmpeg_av_codec->codec = avcodec_find_decoder(ffmpeg_av_codec->codec_context->codec_id);
	if (NULL == ffmpeg_av_codec->codec) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
		cp_ffmepg_av_codec_log(notice, ffmpeg_av_codec,
			"stream[%s] avcodec_find_decoder() error. not found codec.",
			tmp_video_url);
		return -3;
	}
	else {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"avcodec_find_decoder() successed. find decoder[%d] successed.",
			ffmpeg_av_codec->codec_context->codec_id);
	}

	//打开解码器
	if (avcodec_open2(ffmpeg_av_codec->codec_context, ffmpeg_av_codec->codec, NULL) < 0) {
		cp_ffmepg_av_codec_log(notice, ffmpeg_av_codec,
			"stream[%s] avcodec_open2() error.",
			tmp_video_url);
		return -4;
	}
	else {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"avcodec_open2() successed. find decoder[%d] successed.",
			ffmpeg_av_codec->codec_context->codec_id);
	}

	av_init_packet(&ffmpeg_av_codec->avpkt);
	ffmpeg_av_codec->css_av_type = md->encodec_type;

	cp_ffmepg_av_codec_log(notice, ffmpeg_av_codec, "open_ffmpeg_av_file_stream() successed.");

	open_test_file(ffmpeg_av_codec);

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: close_ffmpeg_av_file_stream
*
* 函数全名: close_ffmpeg_av_file_stream
*
* 函数访问: public
*
* 函数说明: 关闭url指定的媒体源信息
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-6 15:39:07
********************************************************************************/
cp_int32_t close_ffmpeg_av_file_stream(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{

	if (ffmpeg_av_codec->codec_context) {
		avcodec_close(ffmpeg_av_codec->codec_context);
		avcodec_free_context(&ffmpeg_av_codec->codec_context);
	}

	if (ffmpeg_av_codec->format_ctx) {
		avformat_close_input(&ffmpeg_av_codec->format_ctx);
		avformat_free_context(ffmpeg_av_codec->format_ctx);
		ffmpeg_av_codec->format_ctx = CP_NULL;
	}

	avformat_network_deinit();

	return 0;
}

//启动解码线程
cp_int32_t start_ffmpeg_av_decode_thread_process(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (!ffmpeg_av_codec || !ffmpeg_av_codec->file_info) {
		return -1;
	}

	//这里创建一个线程统一处理媒体
	ffmpeg_av_codec->file_info->decode_thread_status = cp_thread_status_start;
	ffmpeg_av_codec->file_info->decode_thread = cp_create_thread(
		ffmpeg_av_codec->manager->app,
		(cp_thread_cb)ffmpeg_av_decode_thread_cb_proc, ffmpeg_av_codec);
	if (!ffmpeg_av_codec->file_info->decode_thread) {
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"start_ffmpeg_av_decode_thread_process() error. cp_create_thread() failed");
		return -1;
	}

	return 0;
}

//停止解码线程
cp_int32_t stop_ffmpeg_av_decode_thread_process(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (ffmpeg_av_codec->file_info->decode_thread) {
		ffmpeg_av_codec->file_info->decode_thread_status = cp_thread_status_stop;
		cp_thread_join(ffmpeg_av_codec->file_info->decode_thread);
		cp_destroy_thread(ffmpeg_av_codec->file_info->decode_thread);
		ffmpeg_av_codec->file_info->decode_thread = CP_NULL;
	}

	return 0;
}

//解码线程处理
void ffmpeg_av_decode_thread_cb_proc(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	cp_int32_t						tmp_ret_int = 0;
	AVFrame							*tmp_av_frame = CP_NULL;
	AVFrame							*tmp_new_av_frame = CP_NULL;



	if (!ffmpeg_av_codec || !ffmpeg_av_codec->file_info || !ffmpeg_av_codec->format_ctx) {
		return;
	}

	tmp_av_frame = &ffmpeg_av_codec->decoded_frame;

	while (cp_thread_status_start == ffmpeg_av_codec->file_info->decode_thread_status) {

		if (cp_safe_queue_size(ffmpeg_av_codec->file_info->data_sq) >=
			ffmpeg_av_codec->file_info->min_cache_size) {
			cp_sleep_ns(0, CP_FFMPEG_AV_FILE_SQ_DEFAULT_SLEEP_INTERVAL);
			continue;
		}

		av_init_packet(&ffmpeg_av_codec->avpkt);

		//获取数据帧
		tmp_ret_int = av_read_frame(ffmpeg_av_codec->format_ctx, &ffmpeg_av_codec->avpkt);
		if (tmp_ret_int < 0) {
			set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"ffmpeg_av_decode_thread_cb_proc() error. av_read_frame() failed. reason:%s",
				ffmpeg_av_codec->error_text);
			break;
		}

		//开始解码数据
		tmp_ret_int = avcodec_send_packet(ffmpeg_av_codec->codec_context, &ffmpeg_av_codec->avpkt);
		if (tmp_ret_int < 0 && tmp_ret_int != AVERROR(EAGAIN) && tmp_ret_int != AVERROR_EOF) {
			set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);
			break;
		}

		while (cp_true) {

			//获取解码后数据
			tmp_ret_int = avcodec_receive_frame(ffmpeg_av_codec->codec_context, tmp_av_frame);
			if (tmp_ret_int < 0 && tmp_ret_int != AVERROR_EOF) {
				break;
			}

			//克隆数据
			tmp_new_av_frame = av_frame_clone(tmp_av_frame);
			if (!tmp_new_av_frame) {
				break;
			}

			//插入数据到队列中
			cp_safe_queue_push(ffmpeg_av_codec->file_info->data_sq, tmp_new_av_frame);
		}
	}
}


