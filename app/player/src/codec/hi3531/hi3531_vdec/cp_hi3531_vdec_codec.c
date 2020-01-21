/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_vdec_codec.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"




#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif




/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, const cp_hi3531_vdec_codec_info_t *hi3531_vdec_codec_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, const cp_hi3531_vdec_codec_info_t *hi3531_vdec_codec_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec);
/*退出模块*/
cp_int32_t exit_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec);
/*设置模块参数*/
cp_int32_t set_option_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_int32_t optname, cp_void_t* optval);




/*创建一个模块*/
cp_hi3531_vdec_codec_t* create_hi3531_vdec_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_vdec_codec_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3531_vdec_codec_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info || !info->md) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3531_vdec_codec_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3531_vdec_codec);

	//这里配置媒体信息
	ret_int = set_vdec_codec_media_description(tmp_module, info);
	if (ret_int) {
		cp_free_module(tmp_module);
		cp_manager_log(error, manager, "create_hi3531_vdec_codec() error. set_vdec_codec_media_description() error.");
		return CP_NULL;
	}

	return tmp_module;
}

/*释放模块*/
cp_int32_t destroy_hi3531_vdec_codec(cp_codec_manager_t *manager, cp_hi3531_vdec_codec_t* hi3531_vdec_codec)
{
	if (!manager || !hi3531_vdec_codec) {
		return -1;
	}

	destroy_hi3531_vdec_info(hi3531_vdec_codec);

	cp_free_module(hi3531_vdec_codec);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec,
	const cp_hi3531_vdec_codec_info_t *hi3531_vdec_codec_info)
{
	cp_int32_t								tmp_ret_int = 0;
	cp_hi3531_vdec_codec_info_t				tmp_vdec_codec_info = { 0, };



	//读取配置文件
	tmp_ret_int = hi3531_vdec_codec_parse_configure((cp_module_t*)hi3531_vdec_codec, &hi3531_vdec_codec->hacc);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec, "hi3531_vdec_codec_parse_configure() error.");
		return -1;
	}

	//创建vdec_info内容
	tmp_vdec_codec_info.md = &(hi3531_vdec_codec->vd);
	tmp_ret_int = create_hi3531_vdec_info((cp_module_t*)hi3531_vdec_codec, &tmp_vdec_codec_info);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec, "create_hi3531_vdec_info() error.");
		return -1;
	}

	//初始化hi3531 vdec内容
	tmp_ret_int = init_hi3531_vdec(hi3531_vdec_codec, hi3531_vdec_codec->vdec_info);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec, "init_hi3531_vdec() error.");
		return -1;
	}

	cp_module_log(notice, hi3531_vdec_codec, "init() successed.");
	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec,
	const cp_hi3531_vdec_codec_info_t *hi3531_vdec_codec_info)
{
	cp_int32_t					tmp_ret_int = 0;




	//启动hi3531 vdec内容
	tmp_ret_int = start_hi3531_vdec(hi3531_vdec_codec, hi3531_vdec_codec->vdec_info);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec, "start_hi3531_vdec() error.");
		return -1;
	}

#if defined(CP_HI3531_VDEC_CODEC_FILE_DEBUG)
	if (!hi3531_vdec_codec->file) {
		hi3531_vdec_codec->file = fopen(CP_HI3531_VDEC_CODEC_VIDEO_DEMO_FILE_PATH, "wb");
	}
#endif

#if defined(CP_HI3531_VDEC_CODEC_FILE_DEMO)
	cp_void_t				*tmp_data = CP_NULL;


	/*表示打开测试用的文件*/
	hi3531_vdec_codec->video_file = fopen(CP_HI3531_VDEC_CODEC_VIDEO_FILE_PATH, "rb");
	if (!hi3531_vdec_codec->video_file) {
		cp_module_log(error, hi3531_vdec_codec,
			"start_hi3531_vdec_get_stream() error. open file[%s] failed!",
			CP_HI3531_VDEC_CODEC_VIDEO_FILE_PATH);
		return -1;
	}
	tmp_data = cp_palloc(hi3531_vdec_codec->pool, CP_HI3531_VDEC_CODEC_VIDEO_BUFFER_LENGTH);
	if (!tmp_data) {
		cp_module_log(error, hi3531_vdec_codec,
			"start_hi3531_vdec_get_stream() error. create buffer failed!");
		return -1;
	}
	cp_buf_assemble(&hi3531_vdec_codec->data_buf, tmp_data, CP_HI3531_VDEC_CODEC_VIDEO_BUFFER_LENGTH);

	hi3531_vdec_codec->rtp_sd = create_rtp_socket_data(hi3531_vdec_codec->pool);
	if (!hi3531_vdec_codec->rtp_sd) {
		cp_module_log(error, hi3531_vdec_codec,
			"create_rtp_socket_data() socket_data[%d] failed!");
		return -1;
	}

#endif
	cp_module_log(notice, hi3531_vdec_codec, "open() successed.");
	return 0;
}

//测试通过文件读取数据的方式
int hi3519_test_read_video_file(cp_hi3531_vdec_codec_t * hi3531_vdec_codec)
{
	cp_int32_t				i = 0;
	cp_int32_t				tmp_index = 0;
	cp_int32_t				tmp_flag_len = 0;
	cp_bool_t				tmp_is_flag = cp_false;
	cp_int32_t				tmp_last_len = 0;
	cp_int32_t				tmp_packet_num = 4;
	cp_char_t				tmp_data_buf[1024] = { 0, };
	cp_int32_t				ret_int = 0;
	cp_buf_t				*tmp_buf = CP_NULL;



#if defined(CP_HI3531_VDEC_CODEC_FILE_DEMO)

	tmp_last_len = cp_buf_get_free_size(&hi3531_vdec_codec->data_buf);

	//ret_int = fread(tmp_data_buf, 1, 1024, hi3531_vdec_codec->video_file);
	ret_int = fread(hi3531_vdec_codec->data_buf.last, 1, tmp_last_len, hi3531_vdec_codec->video_file);
	if (ret_int > 0) {
		cp_buf_position(&hi3531_vdec_codec->data_buf, ret_int);
	}
	else {
		fseek(hi3531_vdec_codec->video_file, 0, SEEK_SET);
	}

	// 	tmp_buf = create_a_rtp_socket_buffer(hi3531_vdec_codec->pool, hi3531_vdec_codec->rtp_sd, (ret_int));
	// 	if (!tmp_buf) {
	// 		return 0;
	// 	}
	// 	cp_buf_strcat(tmp_buf, (void *)((hi3531_vdec_codec->data_buf.pos)),
	// 		ret_int);
	// 	push_a_rtp_socket_buffer(hi3531_vdec_codec->rtp_sd, tmp_buf);
	//#if 0
	if (cp_buf_get_length(&hi3531_vdec_codec->data_buf) > 0) {
		for (i = 0; i < cp_buf_get_length(&hi3531_vdec_codec->data_buf); i++) {
			if ((hi3531_vdec_codec->data_buf.pos[i] == 0x00 &&
				hi3531_vdec_codec->data_buf.pos[i + 1] == 0x00 &&
				hi3531_vdec_codec->data_buf.pos[i + 2] == 0x00 &&
				hi3531_vdec_codec->data_buf.pos[i + 3] == 0x01
				)) {
				tmp_is_flag = cp_true;
				if (tmp_flag_len <= 0) {
					tmp_flag_len = 4;
				}
			}
			else {
				if ((hi3531_vdec_codec->data_buf.pos[i] == 0x00 &&
					hi3531_vdec_codec->data_buf.pos[i + 1] == 0x00 &&
					hi3531_vdec_codec->data_buf.pos[i + 2] == 0x01)){
					tmp_is_flag = cp_true;
					if (tmp_flag_len <= 0) {
						tmp_flag_len = 3;
					}
				}
			}

			if (tmp_is_flag) {
				++tmp_index;
				tmp_is_flag = cp_false;
				if (tmp_packet_num != tmp_index) {
					//第一个标志位
					i += 2;
				}

				if (tmp_packet_num == tmp_index) {
					//第二个标志位
					tmp_flag_len = 0;

					tmp_buf = create_a_rtp_socket_buffer(hi3531_vdec_codec->pool, hi3531_vdec_codec->rtp_sd, (i - tmp_flag_len));
					if (!tmp_buf) {
						continue;
					}
					cp_buf_strcat(tmp_buf, (void *)((hi3531_vdec_codec->data_buf.pos + tmp_flag_len)),
						(i - tmp_flag_len));
					push_a_rtp_socket_buffer(hi3531_vdec_codec->rtp_sd, tmp_buf);


					tmp_last_len = cp_buf_get_length(&hi3531_vdec_codec->data_buf) - i;
					break;
				}
			}
		}
	}
	memmove(hi3531_vdec_codec->data_buf.start, hi3531_vdec_codec->data_buf.pos + i, tmp_last_len);
	cp_buf_clear(&hi3531_vdec_codec->data_buf);
	cp_buf_position(&hi3531_vdec_codec->data_buf, tmp_last_len);
#endif
	//#endif
	return ret_int;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return read_hi3531_vdec_data(hi3531_vdec_codec, buf, len, flag);
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return write_hi3531_vdec_data(hi3531_vdec_codec, buf, len, flag);
}

/*关闭模块*/
cp_int32_t close_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec)
{
	cp_int32_t					tmp_ret_int = 0;


	//停止hi3531 vdec内容
	tmp_ret_int = stop_hi3531_vdec(hi3531_vdec_codec, hi3531_vdec_codec->vdec_info);
	if (tmp_ret_int) {
		cp_module_log(error, hi3531_vdec_codec, "stop_hi3531_vdec() error.");
		return -1;
	}

#if defined(CP_HI3531_VDEC_CODEC_FILE_DEBUG)
	if (hi3531_vdec_codec->file) {
		fclose(hi3531_vdec_codec->file);
	}
#endif

#if defined(CP_HI3531_VDEC_CODEC_FILE_DEMO)
	if (hi3531_vdec_codec->video_file) {
		fclose(hi3531_vdec_codec->video_file);
	}
#endif

	return 0;
}

/*退出模块*/
cp_int32_t exit_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec)
{
	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_int32_t optname, const cp_void_t* optval)
{
	if (!hi3531_vdec_codec || !optval) {
		return -1;
	}

	cp_module_log(notice, hi3531_vdec_codec, "set_option_hi3531_vdec_codec() failed");

	return -2;
}

cp_int32_t get_option_hi3531_vdec_codec(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

//创建媒体描述信息
cp_int32_t set_vdec_codec_media_description(cp_hi3531_vdec_codec_t *hi3531_vdec_codec, cp_hi3531_vdec_codec_info_t *info)
{
	if (!hi3531_vdec_codec || !info || !info->md) {
		return -1;
	}

	switch (info->md->type)
	{
		case cp_media_description_type_general:
		{
			cp_memcpy(&hi3531_vdec_codec->vd, info->md, cp_sizeof(cp_media_description_t));
		}
		break;
		case cp_media_description_type_video:
		{
			cp_memcpy(&hi3531_vdec_codec->vd, info->md, cp_sizeof(cp_video_description_t));
		}
		break;
		default:
		{
			return -2;
		}
		break;
	}

	return 0;
}