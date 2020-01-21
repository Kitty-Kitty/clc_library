/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3519_av_codec.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"


#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif


/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, const cp_hi3519_av_codec_info_t *hi3519_av_codec_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, const cp_hi3519_av_codec_info_t *hi3519_av_codec_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec);
/*退出模块*/
cp_int32_t exit_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec);
/*设置模块参数*/
cp_int32_t set_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, cp_void_t* optval);

/*创建一个模块*/
cp_hi3519_av_codec_t* create_hi3519_av_codec(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3519_av_codec_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3519_av_codec_t				*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3519_av_codec_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3519_av_codec);
	return tmp_module;
}
/*释放模块*/
cp_int32_t destroy_hi3519_av_codec(cp_codec_manager_t *manager, cp_hi3519_av_codec_t* hi3519_av_codec)
{
	if (!manager || !hi3519_av_codec) {
		return -1;
	}
	cp_free_module(hi3519_av_codec);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	const cp_hi3519_av_codec_info_t *hi3519_av_codec_info)
{
	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	const cp_hi3519_av_codec_info_t *hi3519_av_codec_info)
{
	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*关闭模块*/
cp_int32_t close_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec)
{
	return 0;
}

/*退出模块*/
cp_int32_t exit_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec)
{
	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, const cp_void_t* optval)
{
	if (!hi3519_av_codec || !optval) {
		return -1;
	}

	return 0;
}

cp_int32_t get_option_hi3519_av_codec(cp_hi3519_av_codec_t *hi3519_av_codec, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}
