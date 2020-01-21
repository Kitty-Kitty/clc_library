/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_hi3531_tde.h"
#include "cp_third_party.h"
#include "cp_include.h"


#ifndef PIX_FMT_YUV420P
#define PIX_FMT_YUV420P	AV_PIX_FMT_YUV420P
#endif


/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, const cp_hi3531_tde_info_t *hi3531_tde_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, const cp_hi3531_tde_info_t *hi3531_tde_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_hi3531_tde(cp_hi3531_tde_t *hi3531_tde);
/*退出模块*/
cp_int32_t exit_hi3531_tde(cp_hi3531_tde_t *hi3531_tde);
/*设置模块参数*/
cp_int32_t set_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, cp_void_t* optval);




/*创建一个模块*/
cp_hi3531_tde_t* create_hi3531_tde(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3531_tde_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_hi3531_tde_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_hi3531_tde_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, hi3531_tde);
	return tmp_module;
}

/*释放模块*/
cp_int32_t destroy_hi3531_tde(cp_codec_manager_t *manager, cp_hi3531_tde_t* hi3531_tde)
{
	if (!manager || !hi3531_tde) {
		return -1;
	}
	cp_free_module(hi3531_tde);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	const cp_hi3531_tde_info_t *hi3531_tde_info)
{
	cp_int32_t						tmp_ret_int = 0;



	//读取配置文件
	tmp_ret_int = hi3531_tde_parse_configure((cp_module_t*)hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_parse_configure() error.");
		return -1;
	}

	//初始化tde设备信息
	tmp_ret_int = hi3531_tde_init_dev(hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_init_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_tde, "hi3531_tde_init_dev() successed!");
	}

	cp_hi3531_dev_log(notice, hi3531_tde, "init() successed.");
	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	const cp_hi3531_tde_info_t *hi3531_tde_info)
{
	cp_int32_t					tmp_ret_int = 0;


	//初始化tde设备信息
	tmp_ret_int = hi3531_tde_start_dev(hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_start_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_tde, "hi3531_tde_start_dev() successed!");
	}

	cp_hi3531_dev_log(notice, hi3531_tde, "open() successed.");
	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_hi3531_tde(cp_hi3531_tde_t *hi3531_tde,
	const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if 0
	cp_int32_t						tmp_ret_int = 0;
	cp_video_frame_process_t		*tmp_vfproc = CP_NULL;



	if (!buf || !*buf || !len) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_vfproc = *((cp_video_frame_process_t**)buf);
	if (!tmp_vfproc || !tmp_vfproc->mpro || !tmp_vfproc->vfpp) {
		cp_module_log(error, hi3531_tde,
			"write video frame process is null error. ");
		return -2;
	}

	switch (tmp_vfproc->vfp_type)
	{
		case cp_video_frame_process_type_fill:
		{
			//填充图像内容
			return hi3531_tde_video_frame_fill(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_video_frame_process_type_copy:
		{
			//视频帧快速烤备图像
			return hi3531_tde_video_frame_copy(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_video_frame_process_type_resize:
		{
			//缩放图像内容
			return hi3531_tde_video_frame_resize(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_video_frame_process_type_copy_resize:
		{
			//缩放图像内容
			return hi3531_tde_video_frame_copy_resize(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		default:
		{
			cp_module_log(error, hi3531_tde,
				"write video frame process error. unknow video frame process type[%d]",
				tmp_vfproc->vfp_type);
			return -3;
		}
		break;
	}
#endif

	return 0;
}

/*关闭模块*/
cp_int32_t close_hi3531_tde(cp_hi3531_tde_t *hi3531_tde)
{
	cp_int32_t					tmp_ret_int = 0;

	//初始化tde设备信息
	tmp_ret_int = hi3531_tde_stop_dev(hi3531_tde, &hi3531_tde->hacc);
	if (tmp_ret_int) {
		cp_hi3531_dev_log(error, hi3531_tde, "hi3531_tde_stop_dev() failed!");
		return -1;
	}
	else {
		cp_hi3531_dev_log(notice, hi3531_tde, "hi3531_tde_stop_dev() successed!");
	}

	return 0;
}

/*退出模块*/
cp_int32_t exit_hi3531_tde(cp_hi3531_tde_t *hi3531_tde)
{
	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, const cp_void_t* optval)
{
	if (!hi3531_tde || !optval) {
		return -1;
	}

	cp_hi3531_dev_log(notice, hi3531_tde, "set_option_hi3531_tde() failed");

	return -2;
}

cp_int32_t get_option_hi3531_tde(cp_hi3531_tde_t *hi3531_tde, cp_int32_t optname, cp_void_t* optval)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_video_frame_process_t		*tmp_vfproc = CP_NULL;



	if (!hi3531_tde || !optval) {
		return -1;
	}

	//转换媒体数据，并校验数据合法性
	tmp_vfproc = *((cp_video_frame_process_t**)optval);
	if (!tmp_vfproc || !tmp_vfproc->mpro || !tmp_vfproc->vfpp) {
		cp_module_log(error, hi3531_tde,
			"process video frame process is null error. ");
		return -2;
	}

	switch (optname)
	{
		case cp_hi3531_tde_option_get_copy:
		{
			//视频帧快速烤备图像
			return hi3531_tde_video_frame_copy(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_hi3531_tde_option_get_fill:
		{
			//填充图像内容
			return hi3531_tde_video_frame_fill(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		case cp_hi3531_tde_option_get_resize:
		{
			//缩放图像内容
			return hi3531_tde_video_frame_resize(hi3531_tde, tmp_vfproc->mpro->ms, tmp_vfproc->mpro->mp, tmp_vfproc->vfpp);
		}
		break;
		default:
		{
			cp_module_log(error, hi3531_tde,
				"write video frame process error. unknow video frame process type[%d]",
				tmp_vfproc->vfp_type);
			return -3;
		}
		break;
	}

	return 0;
}
