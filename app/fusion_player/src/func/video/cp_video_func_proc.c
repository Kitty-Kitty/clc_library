/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-12

Description:

**************************************************************************/
#include "cp_video_func_proc.h"
#include "cp_fusion_player_codec_core.h"
#include "cp_fusion_player_dev_core.h"





cp_int32_t video_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_session_t						*tmp_session = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t*)buf;


	//协议头还没有收全
	if (cp_buf_get_length(tmp_buf) < CSS_GMP_GMPH_SEMH_LEN) {
		return cp_func_status_read_again;
	}
	//数据内容没有收完
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	if (gmp_gmph_emh_type_semh == tmp_bmh->emht) {
		tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
		if (cp_buf_get_length(tmp_buf) < (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			return cp_func_status_match | cp_func_status_read_again;
		}
		//操作成功返回
		return cp_func_status_match | cp_func_status_successorerror;
	}
	return 0;
}

cp_int32_t video_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_session_t				*tmp_session;
	cp_session_manager_t		*tmp_sm = CP_NULL;
	cp_session_info_t			tmp_session_info = { 0, };
	cp_module_manager_info_t	tmp_mm_info = { 0, };
	cp_int32_t					ret_int = 0;



	//判断数据是否接收完全
	ret_int = video_func_data_integrity(socket, buf, nread, status);
	if ((ret_int & cp_func_status_match) && (ret_int & cp_func_status_successorerror)) {
		//先获取session manager 管理器
		tmp_mm_info.type = CP_MODULE_MANAGER_TYPE_SESSION(1);
		tmp_sm = (cp_session_manager_t*)cp_get_manager(socket->manager->app, &tmp_mm_info);
		if (!tmp_sm) {
			return cp_func_status_match;
		}

		//创建一个session处理数据
		CP_MODULE_INFO_SET_TYPE(&tmp_session_info, CP_MODULE_TYPE_SESSION(1));
		tmp_session = (cp_session_t*)cp_manager_create_module(tmp_sm, &tmp_session_info);
		if (tmp_session) {
			ret_int = cp_init_module(tmp_session, &tmp_session_info);
			if (!ret_int) {
				CP_SESSION_SET_SOCKET_INFO(tmp_session, socket, buf, nread, status);
				//开始进行业务处理
				ret_int = cp_open_module(tmp_session, &tmp_session_info);
				if (!ret_int) {
					cp_manager_destroy_module(tmp_session->manager, tmp_session);
					return cp_func_status_match | cp_func_status_successorerror;
				}
			}
			cp_manager_destroy_module(tmp_session->manager, tmp_session);
		}
	}
	return cp_func_status_match;
}

/*解码器读数据回调函数据*/
cp_int32_t video_func_codec_read_cb_handle(cp_video_func_t *video_func, cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp)
{
	cp_char_t				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	if (!video_func) {
		return -1;
	}

	//cp_module_log(warn, video_func, "decode_video_end %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));

	//初始化播放器
	if (!set_video_dev_info(video_func, (cp_video_description_t *)mp->md_p)) {
		//播放视频数据
#if 0
		((cp_video_description_t *)mp->md_p)->volume = video_func->mci.media_info.video_source.volume;
#endif
		cp_write_module(video_func->dev, &mp, cp_sizeof(cp_media_packet_t**), 0);
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: video_func_merge_process_thread_cb_proc
*
* 函数说明: 媒体处理线程
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
*
* 返 回 值: void
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 10:49:17
******************************************************************************************************/
void video_func_merge_process_thread_cb_proc(cp_video_func_t *video_func)
{
	cp_int32_t				ret_int = 0;
	cp_buf_t				*tmp_buf_array[CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE] = { 0, };
	cp_array_t				tmp_array = { 0, };
	cp_media_packet_t		*tmp_mp = CP_NULL;
	cp_char_t				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//初始化数组
	cp_array_init(&tmp_array, tmp_buf_array, cp_sizeof(cp_buf_t*), CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE);

	while (cp_true)
	{
		if (video_func->merge_process_info.mp_info.thread_status != cp_video_func_thread_status_start) {
			break;
		}

		cp_array_clear(&tmp_array);
	}
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: video_func_check_thread_cb_proc
*
* 函数说明: 解码线程
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
*
* 返 回 值: void
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-12 15:41:26
******************************************************************************************************/
void video_func_check_thread_cb_proc(cp_video_func_t *video_func)
{
	cp_int32_t							ret_int = 0;
	cp_array_t							tmp_array = { 0, };
	cp_media_packet_t					*tmp_mp = CP_NULL;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	while (cp_true)
	{
		if (video_func->check_process_info.mp_info.thread_status != cp_video_func_thread_status_start) {
			break;
		}

		tmp_mp = cp_safe_queue_pop(video_func->check_process_info.mp_info.media_sq);
		if (!tmp_mp) {
			cp_sleep_ns(0, CP_VIDEO_FUNC_PROC_MERGE_SLEEP_INTERVAL);
			continue;
		}

#if defined(CP_VIDEO_FILE_DEBUG)
		if (video_func->file) {
			fwrite(cp_buf_get_pos(&tmp_mp->buf[0]), 1, cp_buf_get_length(&tmp_mp->buf[0]), video_func->file);
		}
#endif

	}
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: video_func_merge_thread_cb_proc
*
* 函数说明: 播放线程
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
*
* 返 回 值: void
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-12 15:38:47
******************************************************************************************************/
void video_func_merge_thread_cb_proc(cp_video_func_t *video_func)
{
	cp_int32_t				ret_int = 0;
	cp_int32_t				tmp_process_count = 0;
	cp_buf_t				*tmp_buf_array[CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE] = { 0, };
	cp_array_t				tmp_array = { 0, };
	cp_media_packet_t		*tmp_mp = CP_NULL;
	cp_char_t				tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//初始化数组
	cp_array_init(&tmp_array, tmp_buf_array, cp_sizeof(cp_buf_t*), CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE);

	while (cp_true)
	{
		if (video_func->merge_process_info.mp_info.thread_status != cp_video_func_thread_status_start) {
			break;
		}

		cp_array_clear(&tmp_array);
	}
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: open_video_test_file
*
* 函数说明: 打开测试文件
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
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
cp_bool_t open_video_test_file(cp_video_func_t *video_func)
{
#if defined(CP_VIDEO_FILE_DEBUG)
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_snprintf(tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH, "%s_%d_%s",
		video_func->register_info.name,
		video_func->mci.channel_info.index,
		video_func->mci.media_info.id);

	video_func->file = fopen(tmp_buf, "wb");
#endif



	return cp_true;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: close_video_test_file
*
* 函数说明: 关闭测试文件
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
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
cp_bool_t close_video_test_file(cp_video_func_t *video_func)
{
#if defined(CP_VIDEO_FILE_DEBUG)

	if (video_func->file) {
		fclose(video_func->file);
		video_func->file = CP_NULL;
	}
#endif
	return cp_true;
}

//创建需要的音视频解码模块
cp_module_t* create_video_codec_module(cp_fusion_player_t *player, 
	cp_media_description_t *md, cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_codec_info_t								tmp_codec_info = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);
	//获取视频处理管理器
	tmp_manager = cp_get_manager(player, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, player, "create_video_codec_module() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}
	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_codec_info, module_type);
	CP_CODEC_INFO_SET_MEDIA_DESCRIPTION(&tmp_codec_info, md);
	//先查找一个模块是否存在
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_codec_info);
	if (tmp_module) {
		cp_app_log(warn, player, "create_video_codec_module() warning. create module_type[%d] existed.",
			module_type);
		return CP_NULL;
	}
	//不存在则开始创建
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_codec_info);
	if (!tmp_module) {
		cp_app_log(error, player, "create_video_codec_module() error. create module_type[%d] error.",
			module_type);
		return CP_NULL;
	}
	//初始化模块失败
	ret_int = cp_init_module(tmp_module, &tmp_codec_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_codec_module() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	//设置模块属性
	ret_int = cp_set_option_module(tmp_module, cp_fusion_player_codec_set_option_open_media_file, &tmp_codec_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_codec_module() error. set option %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	//启动模块失败
	ret_int = cp_open_module(tmp_module, &tmp_codec_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_codec_module() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	return tmp_module;
}

//创建需要的音视频解码模块
cp_module_t* create_video_dev_module(cp_fusion_player_t *player, cp_dev_description_t *dd,
	cp_media_description_t *md, cp_int32_t manager_type, cp_int32_t module_type)
{
	cp_module_t									*tmp_module = CP_NULL;
	cp_module_manager_t							*tmp_manager = CP_NULL;
	cp_module_manager_info_t					tmp_manager_info = { 0, };
	cp_dev_info_t								tmp_dev_info = { 0, };
	cp_int32_t									ret_int = 0;
	cp_char_t									tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_manager_info, manager_type);
	//获取视频处理管理器
	tmp_manager = cp_get_manager(player, &tmp_manager_info);
	if (!tmp_manager) {
		cp_app_log(error, player, "create_video_dev_module() error. not found manager_type[%d] error.",
			manager_type);
		return CP_NULL;
	}
	//创建一个处理模块
	CP_MODULE_INFO_SET_TYPE(&tmp_dev_info, module_type);
	CP_DEV_INFO_SET_MEDIA_DESCRIPTION(&tmp_dev_info, dd);
	CP_CODEC_INFO_SET_MEDIA_DESCRIPTION(&tmp_dev_info, md);
	//先查找一个模块是否存在
	tmp_module = cp_manager_get_module(tmp_manager, &tmp_dev_info);
	if (tmp_module) {
		cp_app_log(warn, player, "create_video_dev_module() warning. create module_type[%d] existed.",
			module_type);
		return CP_NULL;
	}
	//不存在则开始创建
	tmp_module = cp_manager_create_module(tmp_manager, &tmp_dev_info);
	if (!tmp_module) {
		cp_app_log(error, player, "create_video_dev_module() error. create module_type[%d] error.",
			module_type);
		return CP_NULL;
	}
	//初始化模块失败
	ret_int = cp_init_module(tmp_module, &tmp_dev_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_dev_module() error. init %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}
	//启动模块失败
	ret_int = cp_open_module(tmp_module, &tmp_dev_info);
	if (ret_int) {
		//初始化失败，则销毁模块内容
		cp_manager_destroy_module(tmp_manager, tmp_module);
		cp_app_log(error, player, "create_video_dev_module() error. open %s error.",
			print_module_register_info(&tmp_module->register_info, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH));
		return CP_NULL;
	}

	return tmp_module;
}

//设置播放信息
cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *ad)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_module_t									*tmp_dev_module = CP_NULL;
	cp_fusion_player_info_t						*tmp_fusion_player_info = (cp_fusion_player_info_t *)(video_func->manager->app->app_info);
	cp_dev_video_description_t					tmp_vdd = { 0, };



	if (!video_func || !ad) {
		return -1;
	}

	if (video_func->dev) {
		return 0;
	}

	//初始化播放器
	tmp_vdd.dd.type = cp_dev_description_type_video;
	tmp_vdd.width = ad->width;
	tmp_vdd.height = ad->height;
	tmp_vdd.fps = ad->fps;
	tmp_vdd.bps = ad->bps;
	tmp_dev_module = create_video_dev_module((cp_fusion_player_t*)(video_func->manager->app),
		(cp_dev_description_t *)&tmp_vdd,
		(cp_media_description_t *)ad,
		cp_fusion_player_manager_type_dev, cp_video_func_video_dev);
	if (!tmp_dev_module) {
		cp_module_log(error, video_func, "set_video_dev_info() error. create_video_codec_module() error.");
		return -2;
	}
	video_func->dev = (cp_dev_t *)tmp_dev_module;

	//配置缓存数量
	if (video_func->afc.buffer_size > 0) {
		tmp_ret_int = cp_set_option_module(tmp_dev_module,
			cp_fusion_player_dev_set_option_video_buffer_size,
			&(video_func->afc.buffer_size));
		if (tmp_ret_int) {
			cp_module_log(error, video_func,
				"set_video_dev_info() error. set option buffer_size[%d].",
				video_func->afc.buffer_size);
			return tmp_ret_int;
		}
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: unset_video_dev_info
*
* 函数说明: 消毁视频显视信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_video_description_t * ad						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-14 16:08:24
******************************************************************************************************/
cp_int32_t unset_video_dev_info(cp_video_func_t *video_func)
{
	if (video_func->dev) {
		//关闭播放器
		cp_close_module(video_func->dev);
		//消毁播放器
		cp_destroy_module(video_func->dev->manager, video_func->dev);
		//设置播放状态
		video_func->dev = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: create_video_codecs
*
* 函数说明: 设置解码器信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数:  cp_video_func_configure_t *afc					[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 11:19:33
******************************************************************************************************/
cp_int32_t create_video_codecs(cp_video_func_t *video_func, cp_video_func_configure_t *afc)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_uint32_t							i = 0;
	cp_buf_t							**tmp_buf = 0;
	cp_module_t							*tmp_codec_module = CP_NULL;



	if (!video_func) {
		return -1;
	}

	//count size
	for (i = 0; i < cp_ary_size(afc->video_sources); i++) {

		if (!afc->video_sources[i].is_used) {
			continue;
		}

		if (cp_strlen(afc->video_sources[i].url) <= 0 || 
			cp_strlen(afc->video_sources[i].url) > cp_sizeof(video_func->codec_process_info[i].decode_md.url)) {
			cp_module_log(error, video_func,
				"create_video_codecs() error. video_sources url[%s] is null or more than [%d] character error.",
				afc->video_sources[i].url,
				cp_strlen(afc->video_sources[i].url)
				);
			continue;
		}

		video_func->codec_process_info[i].video_func = video_func;
		video_func->codec_process_info[i].decode_md.type = cp_media_description_type_video;
		video_func->codec_process_info[i].decode_md.encodec_type = cp_media_type_video_end;
		cp_strcpy(video_func->codec_process_info[i].decode_md.url, afc->video_sources[i].url);

		//初始化解码器
		tmp_codec_module = create_video_codec_module((cp_fusion_player_t*)(video_func->manager->app),
			(cp_media_description_t *)&video_func->codec_process_info[i].decode_md,
			cp_fusion_player_manager_type_codec, cp_video_func_video_codec);
		if (!tmp_codec_module) {
			cp_module_log(error, video_func,
				"create_video_codecs() error. create_video_codec_module() error.");
			return -2;
		}

		video_func->codec_process_info[i].codecs = (cp_codec_t *)tmp_codec_module;
		video_func->codec_process_info[i].is_open_codec = cp_true;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_video_codecs
*
* 函数说明: 消毁视频解码器信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-14 15:14:08
******************************************************************************************************/
cp_int32_t destroy_video_codecs(cp_video_func_t *video_func)
{
	cp_uint32_t							i = 0;


	for (i = 0; i < cp_ary_size(video_func->codec_process_info); i++) {
		if (video_func->codec_process_info[i].is_open_codec && video_func->codec_process_info[i].codecs) {
			//关闭解码器
			cp_close_module(video_func->codec_process_info[i].codecs);
			//消毁解码器
			cp_destroy_module(video_func->codec_process_info[i].codecs->manager, video_func->codec_process_info[i].codecs);
			//设置解器状态
			video_func->codec_process_info[i].is_open_codec = cp_true;
			video_func->codec_process_info[i].video_func = CP_NULL;
		}

		if (video_func->codec_process_info[i].mp_info.decode_mp) {
			//消毁媒体包描述信息
			destroy_media_packet_description(video_func->pool, video_func->codec_process_info[i].mp_info.decode_mp);

			//消毁媒体包
			destroy_media_packet(video_func->codec_process_info[i].mp_info.decode_mp);
			video_func->codec_process_info[i].mp_info.decode_mp = CP_NULL;
		}
	}	

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_video_func_media_play
*
* 函数说明: 停止一个媒体播放
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 15:01:08
******************************************************************************************************/
cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_int32_t							tmp_ret_int = 0;



	if (!video_func || !mci) {
		return -1;
	}

	//如果没有则停止
	cp_close_module(video_func);

	//消毁模块
	cp_destroy_module(video_func->manager, video_func);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: update_video_func_media_play
*
* 函数说明: 更新一个媒体播放
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_media_channel_info_t * mci						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-03-06 17:45:54
******************************************************************************************************/
cp_int32_t update_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	if (!video_func || !mci) {
		return -1;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_video_media_description_info
*
* 函数说明: 初始化媒体信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-08 15:42:41
******************************************************************************************************/
cp_int32_t init_video_media_description_info(cp_video_func_t *video_func)
{
	cp_int32_t							i = 0;



	if (!video_func) {
		return -1;
	}

	for (i = 0; i < cp_ary_size(video_func->codec_process_info); i++) {
	}
	video_func->codec_process_info[i].decode_md.type = cp_media_description_type_video;
	video_func->codec_process_info[i].decode_md.encodec_type = video_func->mci.media_info.video_source.encodec_type;

	init_video_description((cp_media_description_t *)&video_func->codec_process_info[i].decode_md);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_video_codec_callback_info
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-08 15:42:52
******************************************************************************************************/
cp_int32_t init_video_codec_callback_info(cp_video_func_t *video_func)
{
	cp_int32_t							i = 0;


	for (i = 0; i < cp_ary_size(video_func->codec_process_info); i++) {
		cp_memset(&video_func->codec_process_info[i].cc_info.handle, 0, cp_sizeof(cp_codec_callback_handle_t));
		video_func->codec_process_info[i].cc_info.handle.read_cb = (cp_codec_general_cb_handle)video_func_codec_read_cb_handle;
		video_func->codec_process_info[i].mp_info.decode_mp->ccb_info_p = &video_func->codec_process_info[i].cc_info;
	}
	
	return 0;
}

//启动处理线程
cp_int32_t start_video_thread_process(cp_video_func_t *video_func)
{
#if defined(CP_VIDEO_FUNC_USED_MULTI_THREAD)
	return start_video_multi_thread_process(video_func);
#else 
	//这里创建一个线程统一处理媒体
	return start_video_single_thread_process(video_func);
#endif

	return 0;
}

//启动处理线程
cp_int32_t start_video_single_thread_process(cp_video_func_t *video_func)
{
	//这里创建一个线程统一处理媒体
	video_func->merge_process_info.mp_info.thread_status = cp_video_func_thread_status_start;
	video_func->merge_process_info.mp_info.thread = cp_create_thread(
		video_func->manager->app, 
		video_func_merge_process_thread_cb_proc, 
		video_func);
	if (!video_func->merge_process_info.mp_info.thread) {
		cp_module_log(error, video_func, "open_video_func() error, make_player_func_thread_manager() failed");
		return -1;
	}
	return 0;
}

//启动处理线程
cp_int32_t start_video_multi_thread_process(cp_video_func_t *video_func)
{
	cp_int32_t					tmp_ret_int = 0;


	tmp_ret_int = start_video_merge_thread_process(video_func);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	tmp_ret_int = start_video_check_thread_process(video_func);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	return 0;
}

//启动播放线程
cp_int32_t start_video_merge_thread_process(cp_video_func_t *video_func)
{
	//这里创建一个线程统一处理媒体
	video_func->merge_process_info.mp_info.thread_status = cp_video_func_thread_status_start;
	video_func->merge_process_info.mp_info.thread = cp_create_thread(
		video_func->manager->app,
		video_func_merge_thread_cb_proc, &(video_func->merge_process_info));
	if (!video_func->merge_process_info.mp_info.thread) {
		cp_module_log(error, video_func, "open_video_func() error, make_player_func_thread_manager() failed");
		return -1;
	}

	return 0;
}

//启动处理线程
cp_int32_t start_video_check_thread_process(cp_video_func_t *video_func)
{
	//这里创建一个线程统一处理媒体
	video_func->check_process_info.mp_info.thread_status = cp_video_func_thread_status_start;
	video_func->play_flag = 0;
	video_func->check_process_info.mp_info.thread = cp_create_thread(
		video_func->manager->app,
		video_func_check_thread_cb_proc, &(video_func->check_process_info));
	if (!video_func->check_process_info.mp_info.thread) {
		cp_module_log(error, video_func, "open_video_func() error, make_player_func_thread_manager() failed");
		return -1;
	}

	return 0;
}

//停止播放线程
cp_int32_t stop_video_merge_thread_process(cp_video_func_t *video_func)
{
	if (video_func->merge_process_info.mp_info.thread) {
		video_func->merge_process_info.mp_info.thread_status = cp_video_func_thread_status_stop;
		cp_thread_join(video_func->merge_process_info.mp_info.thread);
		cp_destroy_thread(video_func->merge_process_info.mp_info.thread);
		video_func->merge_process_info.mp_info.thread = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_video_check_thread_process
*
* 函数说明: 停止处理线程
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-12 15:56:22
******************************************************************************************************/
cp_int32_t stop_video_check_thread_process(cp_video_func_t *video_func)
{
	if (video_func->check_process_info.mp_info.thread) {
		video_func->check_process_info.mp_info.thread_status = cp_video_func_thread_status_stop;
		cp_thread_join(video_func->check_process_info.mp_info.thread);
		cp_destroy_thread(video_func->check_process_info.mp_info.thread);
		video_func->check_process_info.mp_info.thread = CP_NULL;
	}
	return 0;
}

//停止处理线程
cp_int32_t stop_video_thread_process(cp_video_func_t *video_func)
{
	stop_video_merge_thread_process(video_func);
	stop_video_check_thread_process(video_func);
	return 0;
}

//停止处理线程
cp_int32_t stop_video_single_thread_process(cp_video_func_t *video_func)
{
	return stop_video_thread_process(video_func);
}

//停止处理线程
cp_int32_t stop_video_multi_thread_process(cp_video_func_t *video_func)
{
	return stop_video_thread_process(video_func);
}

//打印时间戳数据
cp_char_t* format_video_frame_timestamp(cp_char_t *buf, cp_int32_t len)
{
	cp_timeval							tmp_tv = { 0, };
	cp_int64_t							tmp_us = 0;



	if (!buf || !len) {
		return CP_NULL;
	}

	cp_gettimeofday(&tmp_tv, CP_NULL);
	cp_memset(buf, 0, len);
	tmp_us = tmp_tv.tv_sec * CP_TIME_SEC_TO_USEC + tmp_tv.tv_usec;
	cp_snprintf(buf, len, "timestamp:\t%d:%d\t%lld\t", tmp_tv.tv_sec, tmp_tv.tv_usec, tmp_us);
	return buf;
}