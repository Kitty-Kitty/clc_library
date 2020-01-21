/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-20

Description:

**************************************************************************/
#include "cp_ffmpeg_av_codec_core.h"


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_init_media_probe
*
* 函数说明: 初始化media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 14:35:49
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_init_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	cp_ffmepg_av_probe_info_t						*tmp_probe = CP_NULL;


	if (ffmpeg_av_codec->audio_info->probe) {
		return 0;
	}

	tmp_probe = cp_palloc(ffmpeg_av_codec->pool, cp_sizeof(cp_ffmepg_av_probe_info_t));
	if (!tmp_probe) {
		cp_module_log(error, ffmpeg_av_codec,
			"cp_ffmpeg_av_codec_init_media_probe() error.");

		return -1;
	}
	cp_memset(tmp_probe, 0, cp_sizeof(cp_ffmepg_av_probe_info_t));

	tmp_probe->sq = cp_create_general_safe_queue(cp_safe_queue_mode_qbss,
		CP_FFMPEG_AV_CODEC_SAFE_QUEUE_BUFFER_SIZE);
	if (!tmp_probe->sq) {
		cp_module_log(error, ffmpeg_av_codec,
			"cp_create_general_safe_queue() error.");

		return -2;
	}

	tmp_probe->buf = (uint8_t*)av_malloc(sizeof(uint8_t) * CP_FFMPEG_AV_CODEC_PROBE_BUFFER_SIZE);
	if (!tmp_probe->buf) {
		cp_module_log(error, ffmpeg_av_codec,
			"cp_ffmpeg_av_codec_init_media_probe() error. create buffer[%d].",
			CP_FFMPEG_AV_CODEC_PROBE_BUFFER_SIZE);
		return -3;
	}

	//初始化
	tmp_probe->format_ctx = avformat_alloc_context();
	if (!tmp_probe->format_ctx) {
		cp_module_log(error, ffmpeg_av_codec,
			"cp_ffmpeg_av_codec_init_media_probe() error. avformat_alloc_context() error.");
		return -5;
	}

	tmp_probe->pb = avio_alloc_context(tmp_probe->buf,
		CP_FFMPEG_AV_CODEC_PROBE_BUFFER_SIZE, 0,
		ffmpeg_av_codec, cp_ffmpeg_av_codec_probe_read_meida_packet, NULL, NULL);
	if (!tmp_probe->pb) {
		cp_module_log(error, ffmpeg_av_codec,
			"cp_ffmpeg_av_codec_init_media_probe() error. avio_alloc_context() error.");
		return -4;
	}

	tmp_probe->format_ctx->pb = tmp_probe->pb;
	tmp_probe->codec = ffmpeg_av_codec;
	tmp_probe->status = cp_ffmepg_av_probe_status_init;

	ffmpeg_av_codec->audio_info->probe = tmp_probe;

	cp_ffmpeg_av_codec_probe_open_debug_file(ffmpeg_av_codec);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_start_media_probe
*
* 函数说明: 启动media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 16:33:54
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_start_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (ffmpeg_av_codec->audio_info->probe->thread) {
		return 0;
	}

	ffmpeg_av_codec->audio_info->probe->status = cp_ffmepg_av_probe_status_probe;
	ffmpeg_av_codec->audio_info->probe->thread = cp_create_thread(
		ffmpeg_av_codec->manager->app,
		(cp_thread_cb)cp_ffmpeg_av_codec_probe_thread_cb,
		ffmpeg_av_codec);
	if (!ffmpeg_av_codec->audio_info->probe->thread) {
		cp_module_log(error, ffmpeg_av_codec,
			"cp_ffmpeg_av_codec_start_media_probe() error. create thread failed.");
		return -1;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_stop_media_probe
*
* 函数说明: 停止media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 16:34:10
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_stop_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	ffmpeg_av_codec->audio_info->probe->status = cp_ffmepg_av_probe_status_unprobe;


	if (ffmpeg_av_codec->audio_info->probe->media_codec_context) {
		avcodec_close(ffmpeg_av_codec->audio_info->probe->media_codec_context);
	}

	// 	if (ffmpeg_av_codec->audio_info->probe->format_ctx) {
	// 		av_read_pause(ffmpeg_av_codec->audio_info->probe->format_ctx);
	// 	}

	if (ffmpeg_av_codec->audio_info->probe->thread) {
		cp_thread_join(ffmpeg_av_codec->audio_info->probe->thread);
		cp_destroy_thread(ffmpeg_av_codec->audio_info->probe->thread);
		ffmpeg_av_codec->audio_info->probe->thread = CP_NULL;
	}

	cp_ffmpeg_av_codec_probe_close_debug_file(ffmpeg_av_codec);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_exit_media_probe
*
* 函数说明: 退出media probe
*
* 参    数: cp_ffmpeg_av_codec_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 14:36:46
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_exit_media_probe(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	if (!ffmpeg_av_codec || !ffmpeg_av_codec->audio_info->probe) {
		return -1;
	}

	cp_ffmpeg_av_codec_stop_media_probe(ffmpeg_av_codec);

	if (ffmpeg_av_codec->audio_info->probe->pb) {
		av_freep(ffmpeg_av_codec->audio_info->probe->pb);
		ffmpeg_av_codec->audio_info->probe->pb = CP_NULL;
		ffmpeg_av_codec->audio_info->probe->format_ctx->pb = CP_NULL;
	}


	if (ffmpeg_av_codec->audio_info->probe->format_ctx) {
		//avformat_free_context(ffmpeg_av_codec->audio_info->probe->format_ctx);
		//ffmpeg_av_codec->audio_info->probe->format_ctx = CP_NULL;
		avformat_close_input(&ffmpeg_av_codec->audio_info->probe->format_ctx);
	}

	//***这里释放内存，存在程序错误，需要后期查看资料
	//不需要释放buf
//  	if (ffmpeg_av_codec->audio_info->probe->buf) {
//  		av_free(ffmpeg_av_codec->audio_info->probe->buf);
//  		ffmpeg_av_codec->audio_info->probe->buf = CP_NULL;
//  	}

	if (ffmpeg_av_codec->audio_info->probe->sq) {
		cp_destroy_safe_queue(ffmpeg_av_codec->audio_info->probe->sq);
		ffmpeg_av_codec->audio_info->probe->sq = CP_NULL;
	}

	//消毁probe资源
	if (ffmpeg_av_codec->audio_info->probe) {
		cp_pfree(ffmpeg_av_codec->pool, ffmpeg_av_codec->audio_info->probe);
		ffmpeg_av_codec->audio_info->probe = CP_NULL;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_media_data
*
* 函数说明: 测试媒体的编码方式
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
* 备    注:当不确定媒体的编码方式时，可以使用这个方法测试媒体源的编码类型
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-20 14:27:25
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_media_data(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_media_packet_t				*tmp_mp = CP_NULL;
	cp_buf_t						*tmp_buf = CP_NULL;


	if (!buf || !*buf || !len) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_buf_get_length(&tmp_mp->mp_buf.buf[0]) <= 0) {
		return -2;
	}

	//主要malloc
	tmp_buf = cp_malloc(cp_sizeof(cp_buf_t) + cp_buf_get_length(&tmp_mp->mp_buf.buf[0]));
	if (!tmp_buf) {
		return -3;
	}

	//配置buf内存
	cp_buf_assemble(tmp_buf, (cp_uchar_t*)tmp_buf + cp_sizeof(cp_buf_t), cp_buf_get_length(&tmp_mp->mp_buf.buf[0]));
	cp_buf_strcat(tmp_buf, cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]), cp_buf_get_length(&tmp_mp->mp_buf.buf[0]));

	cp_safe_queue_push(ffmpeg_av_codec->audio_info->probe->sq, tmp_buf);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_read_frame
*
* 函数说明: 读取一帧数据
*
* 参    数: AVPacket * pkt						[out]参数说明
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
* 创建日期：2017-02-10 15:55:08
******************************************************************************************************/
cp_int32_t cp_ffmpeg_av_codec_probe_read_frame(AVPacket *pkt, cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_int32_t								tmp_ret_int = 0;


	tmp_ret_int = cp_ffmpeg_av_codec_probe_media_data(ffmpeg_av_codec, buf, len, flag);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	av_init_packet(pkt);
	tmp_ret_int = av_read_frame(ffmpeg_av_codec->audio_info->probe->format_ctx, pkt);
	if (tmp_ret_int >= 0) {
		return 0;
	}

	return -1;
}

int cp_ffmpeg_av_codec_probe_read_meida_packet(void *opaque, uint8_t *buf, int buf_size)
{
	cp_int32_t								tmp_read_len = 0;
	cp_int32_t								tmp_last_len = buf_size;
	cp_int32_t								tmp_ret_int = 0;
	uint8_t									*tmp_dest_buf = buf;
	cp_ffmpeg_av_codec_t					*tmp_codec = (cp_ffmpeg_av_codec_t*)opaque;
	cp_buf_t								*tmp_buf = CP_NULL;
	cp_char_t								tmp_data_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	while (cp_ffmepg_av_probe_status_probe == tmp_codec->audio_info->probe->status)
	{
		tmp_buf = cp_safe_queue_pop(tmp_codec->audio_info->probe->sq);
		if (!tmp_buf) {
			cp_sleep_ns(0, CP_FFMPEG_AV_CODEC_PROBE_INTERVAL_NS);
			continue;
		}

		tmp_read_len = cp_small(cp_buf_get_length(tmp_buf), tmp_last_len);
		if (tmp_read_len <= 0) {
			continue;
		}
		cp_memcpy(tmp_dest_buf, cp_buf_get_pos(tmp_buf), tmp_read_len);
		tmp_dest_buf += tmp_read_len;
		tmp_last_len -= tmp_read_len;
		tmp_ret_int = (buf_size - tmp_last_len);

		cp_free(tmp_buf);

		if (tmp_ret_int > 0) {
			break;
		}
	}

	cp_ffmpeg_av_codec_probe_write_debug_file(tmp_codec, buf, tmp_ret_int);
	//cp_snprintf(tmp_data_buf, cp_sizeof(tmp_data_buf), "%d\r\n", tmp_ret_int);
	//cp_ffmpeg_av_codec_probe_write_debug_file(tmp_codec, tmp_data_buf, cp_strlen(tmp_data_buf));

	return tmp_ret_int;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: cp_ffmpeg_av_codec_probe_thread_cb
*
* 函数说明: 媒体探测处理线程
*
* 参    数: cp_ffmpeg_av_codec_t *ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: void
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-21 09:53:03
******************************************************************************************************/
void cp_ffmpeg_av_codec_probe_thread_cb(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	cp_int32_t										i = 0;
	cp_int32_t										tmp_ret_int = 0;
	cp_int32_t										tmp_audio_stream = 0;
	cp_ffmepg_av_probe_info_t						*tmp_probe = CP_NULL;
	AVInputFormat									*tmp_pi_fmt = NULL;
	cp_char_t										tmp_error_buf[CP_APP_DEFAULT_ERROR_TEXT_BUFFER_LEN] = { 0, };


	tmp_probe = ffmpeg_av_codec->audio_info->probe;

	while (cp_ffmepg_av_probe_status_probe == tmp_probe->status)
	{
		//探测从内存中获取到的媒体流的格式
		if (av_probe_input_buffer(tmp_probe->pb, &tmp_pi_fmt, "", NULL, 0, 0) < 0) {
			cp_memset(tmp_error_buf, 0, cp_sizeof(tmp_error_buf));
			av_strerror(tmp_ret_int, tmp_error_buf, cp_sizeof(tmp_error_buf));
			cp_module_log(error, ffmpeg_av_codec,
				"av_probe_input_buffer() error. probe format failed. reason[%s]",
				tmp_error_buf);
			continue;
		}
		else {
			ffmpeg_av_codec->audio_info->probe->status = cp_ffmepg_av_probe_status_unprobe;
		}

		cp_module_log(notice, ffmpeg_av_codec,
			"av_probe_input_buffer() successed. format:%s[%s]",
			tmp_pi_fmt->name, tmp_pi_fmt->long_name);

		//已经获取媒体源信息则不再获取
		cp_mutex_lock(&ffmpeg_av_codec->process_probe_mutex);

		//打开
		tmp_ret_int = avformat_open_input(&tmp_probe->format_ctx, "", tmp_pi_fmt, NULL);
		if (tmp_ret_int != 0) {
			cp_memset(tmp_error_buf, 0, cp_sizeof(tmp_error_buf));
			av_strerror(tmp_ret_int, tmp_error_buf, cp_sizeof(tmp_error_buf));
			cp_module_log(notice, ffmpeg_av_codec,
				"avformat_open_input() failed. reason[%s]",
				tmp_error_buf);
			break;
		}

		// Retrieve stream information
		if (avformat_find_stream_info(tmp_probe->format_ctx, NULL) < 0) {
			cp_memset(tmp_error_buf, 0, cp_sizeof(tmp_error_buf));
			av_strerror(tmp_ret_int, tmp_error_buf, cp_sizeof(tmp_error_buf));
			cp_module_log(notice, ffmpeg_av_codec,
				"avformat_find_stream_info() failed. couldn't find stream information. reason[%s]",
				tmp_error_buf);
			break;
		}

		// Find the first audio stream
		tmp_audio_stream = -1;
		for (i = 0; i < tmp_probe->format_ctx->nb_streams; i++) {
			if (tmp_probe->format_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)	{
				tmp_audio_stream = i;
				break;
			}
		}

		if (tmp_audio_stream == -1) {
			cp_module_log(notice, ffmpeg_av_codec,
				"cp_ffmpeg_av_codec_probe_thread_cb() failed. didn't find a audio stream.");
			break;
		}
		// Get a pointer to the codec context for the audio stream
		tmp_probe->media_codec_context = tmp_probe->format_ctx->streams[tmp_audio_stream]->codec;
		// Find the decoder for the audio stream
		tmp_probe->media_codec = avcodec_find_decoder(tmp_probe->media_codec_context->codec_id);
		if (tmp_probe->media_codec == NULL) {
			cp_module_log(notice, ffmpeg_av_codec,
				"cp_ffmpeg_av_codec_probe_thread_cb() failed. avcodec_find_decoder() failed. codec not found.");
			break;
		}

		// Open codec
		if (avcodec_open2(tmp_probe->media_codec_context, tmp_probe->media_codec, NULL) < 0) {
			cp_module_log(notice, ffmpeg_av_codec,
				"cp_ffmpeg_av_codec_probe_thread_cb() failed. avcodec_open2() failed. codec not open codec.");
			break;
		}

		ffmpeg_av_codec->audio_info->probe->status = cp_ffmepg_av_probe_status_start;

		//cp_ffmpeg_av_codec_probe_successed_test(ffmpeg_av_codec);

		break;
	}

	//已经获取媒体源信息则不再获取
	cp_mutex_unlock(&ffmpeg_av_codec->process_probe_mutex);
}

cp_int32_t cp_ffmpeg_av_codec_probe_open_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
#if defined CP_FFMPEG_AV_PROBE_FILE_DEBUG
	cp_char_t									file_name[CP_FFMPEG_AV_PROBE_FILE_NAME_LENGTH] = {0, };



	cp_sprintf(file_name, "%s_probe_media.data", ffmpeg_av_codec->register_info.name);

	ffmpeg_av_codec->audio_info->probe->file = fopen(file_name, "wb");								/*表示debug文件*/
	if (!ffmpeg_av_codec->audio_info->probe->file) {
		cp_module_log(error, ffmpeg_av_codec, "cp_ffmpeg_av_codec_probe_open_debug_file() fopen() %s error!reason[%d:%s].",
			errno,
			strerror(errno));
		return -1;
}
#endif
	return 0;
}

cp_int32_t cp_ffmpeg_av_codec_probe_write_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_uchar_t *buf, cp_int32_t len)
{
#if defined CP_FFMPEG_AV_PROBE_FILE_DEBUG
	cp_int32_t						tmp_ret_int = 0;



	if (ffmpeg_av_codec->audio_info->probe->file) {
		tmp_ret_int = fwrite(buf, 1, len, ffmpeg_av_codec->audio_info->probe->file);
		if (tmp_ret_int != len) {
			cp_module_log(error, ffmpeg_av_codec,
				"cp_ffmpeg_av_codec_probe_write_debug_file() fwrite() length[%d] error. reason[%d:%s].",
				len,
				errno,
				strerror(errno));
		}
		fflush(ffmpeg_av_codec->audio_info->probe->file);
	}
#endif
	return 0;
}

cp_int32_t cp_ffmpeg_av_codec_probe_close_debug_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
#if defined CP_FFMPEG_AV_PROBE_FILE_DEBUG
	if (ffmpeg_av_codec->audio_info->probe->file) {
		fclose(ffmpeg_av_codec->audio_info->probe->file);
		ffmpeg_av_codec->audio_info->probe->file = CP_NULL;
	}
#endif
	return 0;
}

//测试probe是否成功
cp_int32_t cp_ffmpeg_av_codec_probe_successed_test(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	AVFormatContext				*pFormatCtx;
	int							i, audioStream;
	int							ret_int = 0;
	int							samples = 0;
	AVCodecContext				*pCodecCtx;
	AVCodec						*pCodec;
	char						*url = "E:\\project_work\\project\\css_player_fix_org\\platform\\win32\\css_player\\cp_player\\audio_func_module_23879_064-00-01-01-00-000000000000000-99e6806539b6cd88b8ea0013141516c0";
	char						error_text[1024] = { 0, };

	//支持网络流输入
	avformat_network_init();
	//初始化
	pFormatCtx = avformat_alloc_context();
	//打开
	ret_int = avformat_open_input(&pFormatCtx, url, NULL, NULL);
	if (ret_int != 0){
		printf("Couldn't open input stream.\n");
		av_strerror(ret_int, error_text, sizeof(error_text));
		return -1;
	}
	// Retrieve stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		printf("Couldn't find stream information.\n");
		return -1;
	}
	// Dump valid information onto standard error
	av_dump_format(pFormatCtx, 0, url, 0);

	// Find the first audio stream
	audioStream = -1;
	for (i = 0; i < pFormatCtx->nb_streams; i++)
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			break;
		}

	if (audioStream == -1)
	{
		printf("Didn't find a audio stream.\n");
		return -1;
	}

	// Get a pointer to the codec context for the audio stream
	pCodecCtx = pFormatCtx->streams[audioStream]->codec;

	// Find the decoder for the audio stream
	pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL)
	{
		printf("Codec not found.\n");
		return -1;
	}

	// Open codec
	if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		printf("Could not open codec.\n");
		return -1;
	}

	AVPacket *packet = (AVPacket *)malloc(sizeof(AVPacket));
	AVFrame		decoded_frame;
	av_init_packet(packet);

	AVFrame	*pFrame;
	pFrame = av_frame_alloc();
	uint32_t ret, len = 0;
	int got_picture;
	int index = 0;

	int out_buffer_size = 0;
	uint8_t *out_buffer = 0;
	uint8_t *extended_out_buffer = 0;

	while (av_read_frame(pFormatCtx, packet) >= 0)
	{
		if (packet->stream_index == audioStream)
		{
			ret = avcodec_send_packet(ffmpeg_av_codec->audio_info->probe->media_codec_context, packet);
			if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF) {
				printf("Error in decoding audio frame.\n");
				exit(0);
				return -1;
			}
			ret = avcodec_receive_frame(ffmpeg_av_codec->audio_info->probe->media_codec_context, pFrame);
			if (ret < 0 && ret != AVERROR_EOF) {
				ret_int = -1;
				return -1;
			}
		}
		//av_free_packet(packet);
	}
	// Close the codec
	avcodec_close(pCodecCtx);
	// Close the video file
	//av_close_input_file(pFormatCtx);
	return 0;
}
