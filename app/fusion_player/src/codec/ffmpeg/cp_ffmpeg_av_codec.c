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
#include "cp_ffmpeg_av_file_proc.h"






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
	ffmpeg_av_codec->opera_type = cp_ffmpeg_operation_type_decode_stream;
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
		cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
			"open_ffmpeg_av_codec() error. dev info is null, or media description is null");
		return -2;
	}

	if (cp_ffmpeg_operation_type_open_stream == ffmpeg_av_codec->opera_type) {
		return open_ffmpeg_av_file_info(ffmpeg_av_codec, ffmpeg_av_codec_info->md);
	} 
	else {
		switch (ffmpeg_av_codec_info->md->type) {
			case cp_media_description_type_general:
			case cp_media_description_type_video:
			case cp_media_description_type_audio:
			{
				return open_ffmpeg_av_data_proc(ffmpeg_av_codec, ffmpeg_av_codec_info->md);
			}
			break;
			default:
			{
				return -3;
			}
			break;
		}
	}
	
	return -4;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;



	if (cp_ffmpeg_operation_type_open_stream == ffmpeg_av_codec->opera_type) {
		ret_int = read_ffmpeg_av_file_data(ffmpeg_av_codec, buf, len, flag);
	}
	else {
		ret_int = read_ffmpeg_av_data_stream(ffmpeg_av_codec, buf, len, flag);
	}

	return ret_int;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	int								ret_int = 0;



	if (cp_ffmpeg_operation_type_open_stream == ffmpeg_av_codec->opera_type) {
		ret_int = write_ffmpeg_av_file_data(ffmpeg_av_codec, buf, len, flag);
	}
	else {
		ret_int = write_ffmpeg_av_data_stream(ffmpeg_av_codec, buf, len, flag);
	}

	return ret_int;
}

/*关闭模块*/
cp_int32_t close_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	int								ret_int = 0;



	if (cp_ffmpeg_operation_type_open_stream == ffmpeg_av_codec->opera_type) {
		ret_int = close_ffmpeg_av_file_info(ffmpeg_av_codec);
	}
	else {
		ret_int = close_ffmpeg_av_data_proc(ffmpeg_av_codec);
	}

	return ret_int;
}

/*退出模块*/
cp_int32_t exit_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec)
{
	int								ret_int = 0;



	if (cp_ffmpeg_operation_type_open_stream == ffmpeg_av_codec->opera_type) {
		ret_int = exit_ffmpeg_av_file_info(ffmpeg_av_codec);
	}
	else {
		ret_int = exit_ffmpeg_av_data_proc(ffmpeg_av_codec);
	}

	cp_mutex_destroy(&ffmpeg_av_codec->process_probe_mutex);

	return ret_int;
}

/*设置模块参数*/
cp_int32_t set_option_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t						tmp_ret_int = 0;



	if (!ffmpeg_av_codec || !optval) {
		return -1;
	}

	if (cp_fusion_player_codec_set_option_audio_convert_info == optname) {
		switch (((cp_media_description_t *)optval)->type) {
			case cp_media_description_type_audio:
			{
				ffmpeg_av_codec->audio_info->cp_convert_ad = *((cp_audio_description_t *)optval);
				ffmpeg_av_codec->audio_info->audio_convert = cp_true;
				return 0;
			}
			break;
			default:
			{
				cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
					"set audio convert info error. unsupport media description[%d]",
					((cp_media_description_t *)optval)->type);
				return -1;
			}
			break;
		}
	}

	if (cp_fusion_player_codec_set_option_open_media_file == optname) {
		ffmpeg_av_codec->opera_type = cp_ffmpeg_operation_type_open_stream;

		tmp_ret_int = create_ffmpeg_av_file_info(ffmpeg_av_codec);
		if (tmp_ret_int) {
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"set open media file error. create_ffmpeg_av_file_info() error.");
			return -1;
		}

		tmp_ret_int = init_ffmpeg_av_file_info(ffmpeg_av_codec);
		if (tmp_ret_int) {
			cp_ffmepg_av_codec_log(error, ffmpeg_av_codec,
				"set open media file error. init_ffmpeg_av_file_info() error.");
			return -2;
		}
	}

	return 0;
}

cp_int32_t get_option_ffmpeg_av_codec(cp_ffmpeg_av_codec_t *ffmpeg_av_codec, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}



