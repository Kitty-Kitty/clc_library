/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ffmpeg_av_codec.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"







/*模块创建接口，表示创建一个模块*/
cp_int32_t init_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, const cp_ffmpeg_av_codec_info_t *ffmpeg_av_codec_info);

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, const cp_ffmpeg_av_codec_info_t *ffmpeg_av_codec_info);

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);

/*关闭模块*/
cp_int32_t close_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/*退出模块*/
cp_int32_t exit_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

/*设置模块参数*/
cp_int32_t set_option_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t optname, cp_void_t* optval);

/*设置解码器信息*/
cp_inline cp_static cp_int32_t set_ffmpeg_av_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md);

//打开测试文件
cp_inline cp_static cp_bool_t open_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);

//关闭测试文件
cp_inline cp_static cp_bool_t close_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec);




/*创建一个模块*/
cp_ffmpeg_av_codec_t* create_ffmpeg_av_codec(cp_module_register_t *register_info,
	cp_codec_manager_t *manager, cp_ffmpeg_av_codec_info_t *info)
{
	cp_ffmpeg_av_codec_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_ffmpeg_av_codec_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, ffmpeg_av_codec);

	return tmp_module;
}

/*释放模块*/
cp_int32_t destroy_ffmpeg_av_codec(cp_codec_manager_t *manager, cp_ffmpeg_av_codec_t* ffmpeg_av_codec)
{
	if (!manager || !ffmpeg_av_codec) {
		return -1;
	}
	cp_free_module(ffmpeg_av_codec);
	return 0;
}




/*模块创建接口，表示创建一个模块*/
cp_int32_t init_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_ffmpeg_av_codec_info_t *ffmpeg_av_codec_info)
{
	ffmpeg_av_codec->is_used_probe = cp_true;
	cp_mutex_init(&ffmpeg_av_codec->process_probe_mutex);

	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_ffmpeg_av_codec_info_t *ffmpeg_av_codec_info)
{
	if (!ffmpeg_av_codec) {
		return -1;
	}

	if (!ffmpeg_av_codec_info || !ffmpeg_av_codec_info->md) {
		cp_module_log(error, ffmpeg_av_codec,
			"open_ffmpeg_av_codec() error. dev info is null, or media description is null");
		return -2;
	}

	switch (ffmpeg_av_codec_info->md->type)
	{
		case cp_media_description_type_general:
		case cp_media_description_type_video:
		case cp_media_description_type_audio:
		{
			return set_ffmpeg_av_codec_info(ffmpeg_av_codec, ffmpeg_av_codec_info->md);
		}
		break;
		default:
		{
			return -3;
		}
		break;
	}
	return -4;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;
	AVFrame							*tmp_av_frame = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		cp_module_log(error, ffmpeg_av_codec, "unsupport media packet type[%d].", tmp_mp->type);
		return -2;
	}
	tmp_av_frame = &ffmpeg_av_codec->decoded_frame;


#if 0

	ret_int = avcodec_receive_frame(ffmpeg_av_codec->codec_context, tmp_av_frame);
	if (ret_int < 0 && ret_int != AVERROR_EOF) {
		//set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, ret_int);
		//cp_module_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);
		ret_int = -1;
		return ret_int;
	}
	else {
		ffmpeg_av_codec->error_no = 0;
	}

	switch (tmp_mp->md_p->type) 
	{
		case cp_media_description_type_general:
		{
			cp_module_log(error, ffmpeg_av_codec, "unsupport media description type[%d].", tmp_mp->md_p->type);
			return -1;
		}
		break;
		case cp_media_description_type_video:
		{
			//视频处理
			ret_int = read_ffmpeg_video_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
				tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
			return ret_int;
		}
		break;
		case cp_media_description_type_audio:
		{
			//音频处理
			ret_int = read_ffmpeg_audio_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
				tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
		}
		break;
		default:
		{
			cp_module_log(error, ffmpeg_av_codec, "unsupport media description type[%d].", tmp_mp->md_p->type);
			ret_int = -3;
		}
		break;
}
#endif

	while (cp_true) {
		ret_int = avcodec_receive_frame(ffmpeg_av_codec->codec_context, tmp_av_frame);
		if (ret_int < 0 && ret_int != AVERROR_EOF) {
			//set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, ret_int);
			//cp_module_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);
			ret_int = -1;
			break;
		}
		else {
			ffmpeg_av_codec->error_no = 0;
		}

		switch (tmp_mp->md_p->type)
		{
			case cp_media_description_type_general:
			{
				cp_module_log(error, ffmpeg_av_codec, "unsupport media description type[%d].", tmp_mp->md_p->type);
				return -1;
			}
			break;
			case cp_media_description_type_video:
			{
				//视频处理
				ret_int = read_ffmpeg_video_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
					tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
				break;
			}
			break;
			case cp_media_description_type_audio:
			{
				//音频处理
				ret_int = read_ffmpeg_audio_data(ffmpeg_av_codec, ffmpeg_av_codec->codec_context,
					tmp_av_frame/*&ffmpeg_av_codec->decoded_frame*/, tmp_mp, len, flag);
			}
			break;
			default:
			{
				cp_module_log(error, ffmpeg_av_codec, "unsupport media description type[%d].", tmp_mp->md_p->type);
				ret_int = -3;
			}
			break;
		}
	}

	return ret_int;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;
	AVPacket						tmp_pkt = { 0, };



	if (!buf || !*buf || !len) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_mp = *((cp_media_packet_t**)buf);
	if (cp_media_packet_type_data_and_timestamp != tmp_mp->type) {
		return -2;
	}

	av_init_packet(&ffmpeg_av_codec->avpkt);
	if (cp_media_description_type_audio == ffmpeg_av_codec->md.type) {
		//这里加入probe处理的原因是：mp3处理时总是head missing,
		//但是采用test中的av_read_frame()都是成功的
		if (ffmpeg_av_codec->audio_info->probe &&
			(ffmpeg_av_codec->audio_info->probe->status >= cp_ffmepg_av_probe_status_unprobe &&
			ffmpeg_av_codec->audio_info->probe->status <= cp_ffmepg_av_probe_status_start)) {
			ret_int = read_frame_by_probe_info(&ffmpeg_av_codec->avpkt, ffmpeg_av_codec, buf, len, flag);
			if (ret_int) {
				cp_module_log(error, ffmpeg_av_codec, "read_frame_by_probe_info() error.");
			}
		}
		else {
			//设置音频数据
			ffmpeg_av_codec->avpkt.data = cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]);
			ffmpeg_av_codec->avpkt.size = cp_buf_get_length(&tmp_mp->mp_buf.buf[0]);
		}
	}
	else {
		//设置视频数据
		ffmpeg_av_codec->avpkt.data = cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]);
		ffmpeg_av_codec->avpkt.size = cp_buf_get_length(&tmp_mp->mp_buf.buf[0]);
	}

	ret_int = avcodec_send_packet(ffmpeg_av_codec->codec_context, &ffmpeg_av_codec->avpkt);
	if (ret_int < 0 && ret_int != AVERROR(EAGAIN) && ret_int != AVERROR_EOF) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, ret_int);
		cp_module_log(error, ffmpeg_av_codec, "%s", ffmpeg_av_codec->error_text);

		if (cp_media_description_type_audio == ffmpeg_av_codec->md.type &&
			ffmpeg_av_codec->is_used_probe) {
			proc_decode_failed_data(ffmpeg_av_codec, buf, len, flag);
		}

		return -1;
	}
	else {
		proc_decode_successed_data(ffmpeg_av_codec, buf, len, flag);
	}

	return 0;
}

/*关闭模块*/
cp_int32_t close_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	close_test_file(ffmpeg_av_codec);

	if (ffmpeg_av_codec->codec_context) {
		avcodec_close(ffmpeg_av_codec->codec_context);
	}

	return 0;
}

/*退出模块*/
cp_int32_t exit_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	int								ret_int = 0;


	if (ffmpeg_av_codec->audio_info) {
		unset_ffmpeg_av_audio_convert_context_info(ffmpeg_av_codec);
	}

	destroy_ffmpeg_buf_info(ffmpeg_av_codec);

	if (ffmpeg_av_codec->codec_context) {
		avcodec_free_context(&ffmpeg_av_codec->codec_context);
	}

	//退出media probe
	ret_int = cp_ffmpeg_av_codec_exit_media_probe(ffmpeg_av_codec);
	if (ret_int) {
		cp_module_log(error, ffmpeg_av_codec,
			"cp_ffmpeg_av_codec_exit_media_probe() error.");
		return -1;
	}

	cp_mutex_destroy(&ffmpeg_av_codec->process_probe_mutex);

	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t optname, const cp_void_t* optval)
{
	if (!ffmpeg_av_codec || !optval) {
		return -1;
	}

	if (cp_player_codec_set_option_audio_convert_info == optname) {
		switch (((cp_media_description_t *)optval)->type)
		{
			case cp_media_description_type_audio:
			{
				ffmpeg_av_codec->audio_info->cp_convert_ad = *((cp_audio_description_t *)optval);
				ffmpeg_av_codec->audio_info->audio_convert = cp_true;
				return 0;
			}
			break;
			default:
			{
				cp_module_log(error, ffmpeg_av_codec,
					"set audio convert info error. unsupport media description[%d]",
					((cp_media_description_t *)optval)->type);
				return -1;
			}
			break;
		}
	}

	if (cp_player_codec_set_option_codec_is_used_probe == optname) {
		ffmpeg_av_codec->is_used_probe = *((cp_bool_t*)optval);
		return 0;
	}
	return -2;
}

cp_int32_t get_option_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: open_test_file
*
* 函数说明: 打开测试文件
*
* 参    数: cp_audio_func_t * audio_func						[in]参数说明
*
* 返 回 值: cp_bool_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-16 14:05:17
******************************************************************************************************/
cp_bool_t open_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
#if defined(CP_FFMPEG_AV_CODEC_FILE_DEBUG)
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_snprintf(tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH, "%s_%d",
		ffmpeg_av_codec->register_info.name,
		ffmpeg_av_codec->codec->type);

	ffmpeg_av_codec->file = fopen(tmp_buf, "wb");
#endif

	return cp_true;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: close_test_file
*
* 函数说明: 关闭测试文件
*
* 参    数: cp_audio_func_t * ffmpeg_av_codec						[in]参数说明
*
* 返 回 值: cp_bool_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-16 15:16:02
******************************************************************************************************/
cp_bool_t close_test_file(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
#if defined(CP_FFMPEG_AV_CODEC_FILE_DEBUG)

	if (ffmpeg_av_codec->file) {
		fclose(ffmpeg_av_codec->file);
		ffmpeg_av_codec->file = CP_NULL;
	}
#endif
	return cp_true;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_ffmpeg_av_codec_info
*
* 函数说明: 配置ffmepg av部分内容
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
cp_int32_t set_ffmpeg_av_codec_info(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_media_description_t *md)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_ffmpeg_av_codec_conf_t					*tmp_codec_conf = CP_NULL;
	cp_ffmpeg_av_codec_audio_channel_layout_t	*tmp_ffmpeg_channel_layout = CP_NULL;
	cp_audio_description_t						*tmp_ad = CP_NULL;



	if (!ffmpeg_av_codec) {
		return -1;
	}

	if (ffmpeg_av_codec->codec) {
		cp_module_log(error, ffmpeg_av_codec,
			"set_ffmpeg_av_codec_info() warning. repeat operation. ");
		return 0;
	}

	tmp_ret_int = init_media_codec_info(ffmpeg_av_codec, md);
	if (tmp_ret_int) {
		cp_module_log(error, ffmpeg_av_codec,
			"init_media_codec_info() error.");
		return -1;
	}

	tmp_codec_conf = get_codec_info(md->encodec_type);
	//tmp_codec_conf = get_codec_info(cp_media_type_audio_mp3);
	if (!tmp_codec_conf) {
		cp_module_log(error, ffmpeg_av_codec,
			"set_ffmpeg_av_codec_info() error. not found ffmpeg av codec information for css type[%d]",
			md->encodec_type);
		return -1;
	}

	//avcodec register
	//avcodec_register_all();
	av_register_all();

	ffmpeg_av_codec->codec = avcodec_find_decoder(tmp_codec_conf->ffmpeg_codec_type);
	if (!ffmpeg_av_codec->codec) {
		cp_module_log(error, ffmpeg_av_codec, "set_ffmpeg_av_codec_info() error. codec not found");
		return -2;
	}
	ffmpeg_av_codec->codec_context = avcodec_alloc_context3(ffmpeg_av_codec->codec);
	if (!ffmpeg_av_codec->codec_context) {
		cp_module_log(error, ffmpeg_av_codec, "set_ffmpeg_av_codec_info() error. could not allocate audio codec context");
		return -3;
	}
	switch (md->type)
	{
		case cp_media_description_type_audio:
		{
			tmp_ad = (cp_audio_description_t*)md;

			tmp_ffmpeg_channel_layout = get_ffmpeg_audio_channel_layout_info(tmp_ad->channel_layout);
			if (!tmp_ffmpeg_channel_layout) {
				cp_module_log(error, ffmpeg_av_codec,
					"set_ffmpeg_av_codec_info() error. get_ffmpeg_audio_channel_layout_info() error. unsupport cp_audio_channel_layout[%d]",
					tmp_ad->channel_layout);
				//return -4;
				ffmpeg_av_codec->codec_context->channels = CP_FFMPEG_AV_CODEC_DEFAULT_CHANNELS;
			}
			else {
				ffmpeg_av_codec->codec_context->channels = av_get_channel_layout_nb_channels(tmp_ffmpeg_channel_layout->ffmpeg_audio_channel_layout_type);
			}

			ffmpeg_av_codec->codec_context->sample_rate = tmp_ad->sample_rate;
			ffmpeg_av_codec->codec_context->bit_rate = tmp_ad->bit_rate;
			ffmpeg_av_codec->codec_context->sample_fmt = AV_SAMPLE_FMT_S16;
		}
		break;
		case cp_media_description_type_video:
			break;
		default:
			break;
	}

	/* open it */
	tmp_ret_int = avcodec_open2(ffmpeg_av_codec->codec_context, ffmpeg_av_codec->codec, NULL);
	if (tmp_ret_int < 0) {
		set_ffmpeg_av_codec_error_info(ffmpeg_av_codec, tmp_ret_int);
		cp_module_log(error, ffmpeg_av_codec,
			"set_ffmpeg_av_codec_info() error. could not open codec! %s",
			ffmpeg_av_codec->error_text);
		return -4;
	}

	av_init_packet(&ffmpeg_av_codec->avpkt);
	ffmpeg_av_codec->css_av_type = md->encodec_type;

	cp_module_log(notice, ffmpeg_av_codec, "init ffmpeg library version[%d] successed. ", avformat_version());

	open_test_file(ffmpeg_av_codec);

	return 0;
}