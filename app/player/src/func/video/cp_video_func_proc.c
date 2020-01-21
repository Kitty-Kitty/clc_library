/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-12

Description:

**************************************************************************/
#include "cp_video_func_proc.h"
#include "cp_player_codec_core.h"
#include "cp_player_dev_core.h"





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

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_video_multicast_data_filter
*
* 函数说明: 设置multicast socket
*
* 参    数: cp_video_func_t * video_func			[in]参数说明
* 参    数: cp_char_t * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-11-25 15:31:55
******************************************************************************************************/
cp_int32_t set_video_multicast_data_filter(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len)
{
	cp_module_t								*tmp_module = CP_NULL;
	cp_int32_t								ret_int = 0;
	cp_char_t								tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_memset(buf, 0, len);

	tmp_module = cp_manager_get_sub_module(video_func->manager->app,
		cp_player_manager_type_filter, cp_player_module_type_memh_filter);
	if (!tmp_module) {
		cp_snprintf(buf, len, "not found filter[memh]");
		return -1;
	}
	video_func->filter = (cp_filter_t *)tmp_module;
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(video_func->filter, video_func->socket, read_cb, cp_socket_read_cb_handle);

	ret_int = set_video_memh_socket_data(video_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (ret_int) {
		cp_snprintf(buf, len, "%s", tmp_buf);
		return -2;
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: close_video_multicast_socket
*
* 函数说明: 关闭组播
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
* 创建日期：2016-12-14 16:26:50
******************************************************************************************************/
cp_int32_t close_video_multicast_socket(cp_video_func_t *video_func)
{
	if (video_func->socket) {
		cp_close_socket(video_func->socket);
		unset_video_memh_socket_data(video_func);
		cp_destroy_module(video_func->socket->manager, video_func->socket);
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_video_memh_socket_data
*
* 函数说明: 设置memh socket数据
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_char_t * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-14 16:34:00
******************************************************************************************************/
cp_int32_t set_video_memh_socket_data(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len)
{
	cp_memh_socket_data_t				*tmp_memh_socket_data = CP_NULL;



	if (!video_func || !video_func->socket) {
		cp_module_log(error, video_func, "set_video_memh_socket_data() error. video_func[%p] socket is null.",
			video_func);
		return -1;
	}
	//创 memh socket 数据
	tmp_memh_socket_data = create_memh_socket_data(video_func->socket->pool);
	if (!tmp_memh_socket_data) {
		cp_module_log(error, video_func, "set_video_memh_socket_data() error. create_memh_socket_data() error.");
		return -2;
	}
	set_memh_socket_buffer_func(tmp_memh_socket_data, (cp_func_t*)video_func);
	//设置memh socket data
	video_func->msd = tmp_memh_socket_data;
	video_func->socket->data = tmp_memh_socket_data;

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: unset_video_memh_socket_data
*
* 函数说明: 消毁memh socket数据
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_char_t * buf						[in]参数说明
* 参    数: cp_int32_t len						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-14 16:33:54
******************************************************************************************************/
cp_int32_t unset_video_memh_socket_data(cp_video_func_t *video_func)
{
	if (video_func->socket->data) {
		destroy_socket_data(video_func->socket->pool, video_func->msd);
		video_func->socket->data = CP_NULL;
		video_func->msd = CP_NULL;
	}
	return 0;
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
		cp_write_module(video_func->dev, &mp, cp_sizeof(cp_media_packet_t**), 0);
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: video_func_thread_cb_proc
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
void video_func_thread_cb_proc(cp_video_func_t *video_func)
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
		if (video_func->mp_info.thread_status != cp_video_func_thread_status_start) {
			break;
		}

		//获取end标志的一帧数据
		ret_int = get_a_video_frame_data(video_func, &tmp_array);
		if (ret_int) {
			cp_sleep_ns(0, CP_VIDEO_FUNC_PROC_MERGE_SLEEP_INTERVAL);
			continue;
		}

		//处理指令
		set_video_codec_info(video_func, &tmp_array);
		tmp_mp = merge_video_media_data(video_func, &tmp_array);
		if (tmp_mp) {
#if defined(CP_VIDEO_FILE_DEBUG)
			if (video_func->file) {
				fwrite(cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]), 1, cp_buf_get_length(&tmp_mp->mp_buf.buf[0]), video_func->file);
			}
#endif
			//cp_module_log(warn, video_func, "merge_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
			ret_int = decode_video_media_data(video_func, tmp_mp);
			if (!ret_int) {
				//cp_module_log(warn, video_func, "decode_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
#if defined CP_HI3531_VDEC_MODE
				video_func->mp_info.decode_mp->mp_buf.buf_type = cp_media_packet_buf_type_hi;
#else
				video_func->mp_info.decode_mp->mp_buf.buf_type = cp_media_packet_buf_type_ffmpeg;
#endif
				video_func->mp_info.decode_mp->ts = tmp_mp->ts;
				play_video_media_data(video_func, video_func->mp_info.decode_mp);
				//cp_module_log(warn, video_func, "play_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
			}
		}
		//消毁数据缓存
		destroy_video_tmp_data(video_func, &tmp_array);
		cp_array_clear(&tmp_array);
	}
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: video_func_decode_thread_cb_proc
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
void video_func_decode_thread_cb_proc(cp_video_func_t *video_func)
{
	cp_int32_t							ret_int = 0;
	cp_array_t							tmp_array = { 0, };
	cp_media_packet_t					*tmp_mp = CP_NULL;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	while (cp_true)
	{
		if (video_func->mp_info.thread_status != cp_video_func_thread_status_start) {
			break;
		}

		tmp_mp = cp_safe_queue_pop(video_func->mp_info.merge_sq);
		if (!tmp_mp) {
			cp_sleep_ns(0, CP_VIDEO_FUNC_PROC_MERGE_SLEEP_INTERVAL);
			continue;
		}

#if defined(CP_VIDEO_FILE_DEBUG)
		if (video_func->file) {
			fwrite(cp_buf_get_pos(&tmp_mp->mp_buf.buf[0]), 1, cp_buf_get_length(&tmp_mp->mp_buf.buf[0]), video_func->file);
		}
#endif

		ret_int = decode_video_media_data(video_func, tmp_mp);
		if (!ret_int) {
			//cp_module_log(warn, video_func, "decode_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
#if defined CP_HI3531_DEV_MODE
			video_func->mp_info.decode_mp->mp_buf.buf_type = cp_media_packet_buf_type_hi;
#else
			video_func->mp_info.decode_mp->mp_buf.buf_type = cp_media_packet_buf_type_ffmpeg;
#endif
			video_func->mp_info.decode_mp->ts = tmp_mp->ts;
			play_video_media_data(video_func, video_func->mp_info.decode_mp);
			//cp_module_log(warn, video_func, "play_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
		}

#if 0
		while (cp_true)
		{
			//cp_module_log(warn, video_func, "merge_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
			ret_int = decode_video_media_data(video_func, tmp_mp);
			if (!ret_int) {
				//cp_module_log(warn, video_func, "decode_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
#if defined CP_HI3531_DEV_MODE
				video_func->mp_info.decode_mp->mp_buf.buf_type = cp_media_packet_buf_type_hi;
#else
				video_func->mp_info.decode_mp->mp_buf.buf_type = cp_media_packet_buf_type_ffmpeg;
#endif
				video_func->mp_info.decode_mp->ts = tmp_mp->ts;
				play_video_media_data(video_func, video_func->mp_info.decode_mp);
				//cp_module_log(warn, video_func, "play_video %s", format_video_frame_timestamp(tmp_buf, cp_sizeof(tmp_buf)));
				continue;
			}
			break;
		}
#endif

		//消毁media packet
		destroy_a_video_media_packet(video_func, tmp_mp);
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
		if (video_func->mp_info.thread_status != cp_video_func_thread_status_start) {
			break;
		}

		//获取end标志的一帧数据
		ret_int = get_a_video_frame_data(video_func, &tmp_array);
		if (ret_int) {
			cp_sleep_ns(0, CP_VIDEO_FUNC_PROC_MERGE_SLEEP_INTERVAL);
			continue;
		}

		//处理指令
		ret_int = set_video_codec_info(video_func, &tmp_array);
		if (ret_int) {

		}

 		tmp_mp = merge_video_media_data(video_func, &tmp_array);
 		if (tmp_mp) {
 			cp_safe_queue_push(video_func->mp_info.merge_sq, tmp_mp);
 		}

		//消毁数据缓存
		destroy_video_tmp_data(video_func, &tmp_array);
		cp_array_clear(&tmp_array);
	}
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: check_video_is_end
*
* 函数说明: 校验数据是否结束
*
* 参    数: cp_buf_t * buf						[in]参数说明
*
* 返 回 值: cp_bool_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-06 10:26:11
******************************************************************************************************/
cp_bool_t check_video_is_end(cp_buf_t *buf)
{
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;


	//取出semh包头，判断semh最小长度
	tmp_memh = (gmp_gmph_memh_t*)cp_buf_get_pos(buf);
	if (gmp_gmph_emh_type_memh == tmp_memh->bmh.emht &&
		css_media_network_end == tmp_memh->packet_type) {
		return cp_true;
	}

	return cp_false;
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
cp_module_t* create_video_codec_module(cp_player_t *player, cp_media_description_t *md, cp_int32_t manager_type, cp_int32_t module_type)
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
cp_module_t* create_video_dev_module(cp_player_t *player, cp_dev_description_t *dd,
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

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_video_codec_info
*
* 函数说明: 设置解码器信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_array_t * ary						[in]参数说明
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
cp_int32_t set_video_codec_info(cp_video_func_t *video_func, cp_array_t *ary)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_uint32_t							i = 0;
	cp_buf_t							**tmp_buf = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_module_t							*tmp_codec_module = CP_NULL;



	if (!video_func || !ary) {
		return -1;
	}

	if (video_func->mp_info.is_open_codec) {
		return 0;
	}

	//count size
	for (i = 0; i < cp_array_max_size(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos((*tmp_buf));
		tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			if (!video_func->mp_info.is_open_codec && !video_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {

				//核验媒体信息
				if (!check_video_media_type(video_func, tmp_memh->media_type)) {
					cp_module_log(error, video_func,
						"set_video_codec_info() error. unsupport media_type[%d] error.",
						tmp_memh->media_type);
					break;
				}

				video_func->decode_md.encodec_type = tmp_memh->media_type;

				//初始化解码器
				tmp_codec_module = create_video_codec_module((cp_player_t*)(video_func->manager->app),
					(cp_media_description_t *)&video_func->decode_md,
					cp_player_manager_type_codec, cp_video_func_video_codec);
				if (!tmp_codec_module) {
					cp_module_log(error, video_func,
						"set_video_codec_info() error. create_video_codec_module() error.");
					return -2;
				}

				video_func->codec = (cp_codec_t *)tmp_codec_module;
				video_func->mp_info.is_open_codec = cp_true;

				return 0;
			}
		}

		if (check_video_is_end((*tmp_buf))) {
			break;
		}
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_video_codec_convert_info
*
* 函数说明: 设置视频重采样信息
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
* 创建日期：2016-12-20 16:06:41
******************************************************************************************************/
cp_int32_t set_video_codec_convert_info(cp_video_func_t *video_func)
{
	cp_int32_t										tmp_ret_int = 0;
	cp_video_description_t							tmp_ad = { 0, };


#if 0
	if (video_func->afc.convert_flag) {
		tmp_ad.md.type = cp_media_description_type_video;
		tmp_ad.channel_layout = video_func->afc.channel_layout;
		tmp_ad.sample_rate = video_func->afc.sample_rate;
		tmp_ad.sample_format = video_func->afc.sample_format;
		tmp_ad.samples = video_func->afc.samples;

		tmp_ret_int = cp_set_option_module(video_func->codec, cp_player_codec_set_option_video_convert_info, &tmp_ad);
		if (tmp_ret_int) {
			cp_module_log(error, video_func, "set_video_codec_convert_info() error.");
		}
		return tmp_ret_int;
	}
#endif

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: check_video_media_type
*
* 函数说明: 核实媒体信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_int32_t type						[in]参数说明
*
* 返 回 值: cp_bool_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-16 10:53:22
******************************************************************************************************/
cp_bool_t check_video_media_type(cp_video_func_t *video_func, cp_int32_t type)
{
	if (cp_media_type_video_begin < type &&
		type < cp_media_type_video_end) {
		return cp_true;
	}
	return cp_false;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: unset_video_codec_info
*
* 函数说明: 关闭视频解码器信息
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
cp_int32_t close_video_codec_info(cp_video_func_t *video_func)
{
	if (video_func->mp_info.is_open_codec && video_func->codec) {
		//关闭解码器
		cp_close_module(video_func->codec);
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: unset_video_codec_info
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
cp_int32_t unset_video_codec_info(cp_video_func_t *video_func)
{
	if (video_func->mp_info.is_open_codec && video_func->codec) {
		//关闭解码器
		cp_exit_module(video_func->codec);
		//消毁解码器
		cp_destroy_module(video_func->codec->manager, video_func->codec);
		//设置解器状态
		video_func->mp_info.is_open_codec = cp_true;
		video_func->codec = CP_NULL;
	}

	return 0;
}

//设置播放信息
cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *ad)
{
	cp_int32_t									tmp_ret_int = 0;
	cp_module_t									*tmp_dev_module = CP_NULL;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(video_func->manager->app->app_info);
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
	tmp_dev_module = create_video_dev_module((cp_player_t*)(video_func->manager->app),
		(cp_dev_description_t *)&tmp_vdd,
		(cp_media_description_t *)ad,
		cp_player_manager_type_dev, cp_video_func_video_dev);
	if (!tmp_dev_module) {
		cp_module_log(error, video_func, "set_video_dev_info() error. create_video_codec_module() error.");
		return -2;
	}
	video_func->dev = (cp_dev_t *)tmp_dev_module;

	//配置缓存数量
	if (video_func->afc.buffer_size > 0) {
		tmp_ret_int = cp_set_option_module(tmp_dev_module,
			cp_player_dev_set_option_video_buffer_size,
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
* 函数名称: merge_video_media_data
*
* 函数说明: 解码媒体数据
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_array_t * ary						[in]参数说明
*
* 返 回 值: cp_media_packet_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 10:52:45
******************************************************************************************************/
cp_media_packet_t* merge_video_media_data(cp_video_func_t *video_func, cp_array_t *ary)
{
	cp_uint32_t							i = 0;
	cp_int32_t							tmp_total = 0;
	cp_buf_t							**tmp_buf = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_media_packet_t					*tmp_mp = CP_NULL;
	cp_timespec_t						tmp_ts = { 0, };



	//count size
	for (i = 0; i < cp_array_max_size(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos((*tmp_buf));
		tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			tmp_total += tmp_memh->body_size;
		}

		if (check_video_is_end((*tmp_buf))) {
			break;
		}
	}

	if (tmp_total <= 0) {
		return CP_NULL;
	}

	//根据业务需求创建media packet
	tmp_mp = create_a_video_media_packet(video_func, tmp_total);
	if (!tmp_mp) {
		return CP_NULL;
	}

	//copy data
	for (i = 0; i < cp_array_max_size(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos((*tmp_buf));
		tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			cp_buf_strcat(&tmp_mp->mp_buf.buf[0], cp_buf_get_pos((*tmp_buf)) + cp_sizeof(gmp_gmph_memh_t), (cp_int32_t)tmp_memh->body_size);

			//这里获取时间
			if ((css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				tmp_ts.tv_sec = tmp_memh->time_stamp_s;
				tmp_ts.tv_nsec = tmp_memh->time_stamp_ns;
			}
		}

		if (check_video_is_end((*tmp_buf))) {
			break;
		}
	}

	tmp_mp->ts = tmp_ts;
	return tmp_mp;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_a_video_frame_data
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_array_t * ary						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 10:28:37
******************************************************************************************************/
cp_int32_t get_a_video_frame_data(cp_video_func_t *video_func, cp_array_t *ary)
{
	cp_buf_t				*tmp_buf = CP_NULL;


	while (cp_true)
	{
		//逐个获取数据句
		tmp_buf = pop_a_memh_socket_buffer(video_func->msd);
		if (!tmp_buf) {
			break;
		}

		cp_array_set_back(ary, &tmp_buf);
		if (check_video_is_end(tmp_buf)) {
			return 0;
		}
	}
	return -1;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: decode_video_media_data
*
* 函数说明: 解码媒体数据
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_media_packet_t * mp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-06 10:14:20
******************************************************************************************************/
cp_int32_t decode_video_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp)
{
	if (!video_func || !mp || !video_func->codec) {
		return -1;
	}

	return cp_write_module(video_func->codec, &mp, cp_sizeof(cp_media_packet_t**), 0);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: play_video_media_data
*
* 函数说明: 播放媒体
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_media_packet_t * mp						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 10:13:34
******************************************************************************************************/
cp_int32_t play_video_media_data(cp_video_func_t *video_func, cp_media_packet_t *mp)
{
	cp_int32_t								tmp_ret_int = 0;



	if (!video_func || !mp) {
		return -1;
	}

	//读取解码后的数据
	mp->md_p = (cp_media_description_t *)&video_func->decode_md;
	mp->type = cp_media_packet_type_data_and_timestamp;
	tmp_ret_int = cp_read_module(video_func->codec, &mp, cp_sizeof(cp_media_packet_t**), 0);
	if (!tmp_ret_int) {
		return -2;
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

	//删除通道信息
	tmp_ret_int = remove_video_media_channel_info(video_func, mci);
	if (tmp_ret_int) {
		cp_module_log(error, video_func, "open_video_func() error. remove_video_media_channel_info() error.");
		return -1;
	}

	//如果还有通道再使用则返回
	if (video_func->cm.size > 0) {
		return 0;
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
* 函数名称: insert_video_media_channel_info
*
* 函数说明: 添加媒体通道
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
* 创建日期：2016-12-14 11:24:52
******************************************************************************************************/
cp_int32_t insert_video_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_video_func_frame_process_t		*tmp_vffp = CP_NULL;
	cp_channel_t						*tmp_find_chl = CP_NULL;
	cp_channel_t						tmp_chl = { 0, };



	if (!video_func || !mci) {
		return -1;
	}

	//查找是否已经存在
	tmp_find_chl = find_channel(&video_func->cm, mci->channel_info.index);
	if (tmp_find_chl) {
		cp_module_log(warn, video_func,
			"insert_video_media_channel_info() error, channel[%d] exist now!",
			mci->channel_info.index);
		return 0;
	}

	//创建媒体通道
	tmp_vffp = cp_palloc(video_func->pool, cp_sizeof(cp_video_func_frame_process_t));
	if (!tmp_vffp) {
		cp_module_log(error, video_func, "insert_video_media_channel_info() error, cp_palloc() make media channel information failed");
		return -1;
	}
	else {
		cp_memset(tmp_vffp, 0, cp_sizeof(cp_video_func_frame_process_t));
	}

	set_video_frame_by_media_channel_info(tmp_vffp, mci);
	//tmp_vffp->chann_info = mci->channel_info;

	set_channel(&tmp_chl, mci->channel_info.index, mci->channel_info.play_session, (cp_module_t*)video_func, tmp_vffp);
	insert_channel(&video_func->cm, &tmp_chl);

	return 0;
}

/*******************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: set_video_frame_by_channel_info
*
* 函数全名: set_video_frame_by_channel_info
*
* 函数访问: public 
*
* 函数说明: 设置帧处理信息
*
* 参    数: cp_video_func_frame_process_t * vffp						[in/out]参数说明
* 参    数: cp_media_channel_info_t *mci						[in/out]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非0  : 失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-8-20 18:52:30
********************************************************************************/
cp_int32_t set_video_frame_by_media_channel_info(cp_video_func_frame_process_t *vffp, cp_media_channel_info_t *mci)
{
	if (!vffp || !mci) {
		return -1;
	}

	vffp->chann_info = mci->channel_info;
	//mci->channel_info.position.
	//vffp->vfpp.fpp.source.margin.top

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
* 函数名称: remove_video_media_channel_info
*
* 函数说明: 删除媒体通道
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
* 创建日期：2016-12-14 11:31:00
******************************************************************************************************/
cp_int32_t remove_video_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_channel_t						*tmp_chl = { 0, };



	tmp_chl = find_channel(&video_func->cm, mci->channel_info.index);
	if (!tmp_chl) {
		cp_module_log(error, video_func,
			"remove_video_media_channel_info() error, not found channel[%d]",
			mci->channel_info.index);
		return -1;
	}
	if (tmp_chl->data) {
		cp_pfree(video_func->pool, tmp_chl->data);
	}

	remove_channel(&video_func->cm, mci->channel_info.index);
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destroy_video_tmp_data
*
* 函数说明: 消毁所有数据
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_array_t * ary						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-13 11:27:54
******************************************************************************************************/
cp_int32_t destroy_video_tmp_data(cp_video_func_t *video_func, cp_array_t *ary)
{
	cp_uint32_t							i = 0;
	cp_uint32_t							tmp_number = 0;
	cp_buf_t							**tmp_buf = 0;


	//count size
	for (i = 0; i < cp_array_max_size(ary) &&
		tmp_number < cp_array_length(ary); i++) {
		tmp_buf = (cp_buf_t**)cp_array_get(ary, i);
		if (!(*tmp_buf)) {
			break;
		}
		++tmp_number;
		//消毁指令
		destroy_a_memh_socket_buffer(video_func->socket->pool, video_func->msd, (*tmp_buf));
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
	if (!video_func) {
		return -1;
	}

	video_func->decode_md.type = cp_media_description_type_video;
	video_func->decode_md.encodec_type = video_func->mci.media_info.video_source.encodec_type;
	video_func->decode_md.width = video_func->mci.media_info.video_source.width;
	video_func->decode_md.height = video_func->mci.media_info.video_source.height;
	video_func->decode_md.fps = video_func->mci.media_info.video_source.fps;

	init_video_description((cp_media_description_t *)&video_func->decode_md);

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
	cp_memset(&video_func->cc_info.handle, 0, cp_sizeof(cp_codec_callback_handle_t));
	video_func->cc_info.handle.read_cb = (cp_codec_general_cb_handle)video_func_codec_read_cb_handle;
	video_func->mp_info.decode_mp->ccb_info_p = &video_func->cc_info;
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_video_merge_safe_queue
*
* 函数说明: 初始化merge
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
* 创建日期：2017-01-13 17:03:18
******************************************************************************************************/
cp_int32_t init_video_merge_safe_queue(cp_video_func_t *video_func)
{
	cp_void_t						*tmp_buf = CP_NULL;
	cp_int32_t						tmp_ret_int = 0;
	cp_int32_t						i = 0;
	cp_media_packet_t				*tmp_mp = CP_NULL;



	//计算内存大小
	tmp_ret_int = cp_safe_queue_get_memory_size(cp_safe_queue_mode_qbss, video_func->afc.buffer_size);
	if (!tmp_ret_int) {
		cp_module_log(error, video_func,
			"init_video_merge_safe_queue() error. cp_safe_queue_get_memory_size() error. size[%d]",
			video_func->afc.buffer_size);
		return tmp_ret_int;
	}

	//创建内存
	tmp_buf = cp_palloc(video_func->pool, tmp_ret_int);
	if (!tmp_buf) {
		cp_module_log(error, video_func,
			"init_video_merge_safe_queue() error. cp_palloc() error. size[%d]",
			tmp_ret_int);
		return -1;
	}

	//创建safe queue
	video_func->mp_info.merge_sq = cp_create_memory_safe_queue(tmp_buf, tmp_ret_int, cp_safe_queue_mode_qbss, video_func->afc.buffer_size);
	if (!video_func->mp_info.merge_sq) {
		cp_module_log(error, video_func,
			"init_video_merge_safe_queue() error. cp_create_memory_safe_queue() error. ");
		return -2;
	}

	//创建内存
	tmp_buf = cp_palloc(video_func->pool, tmp_ret_int);
	if (!tmp_buf) {
		cp_module_log(error, video_func,
			"init_video_merge_safe_queue() error. cp_palloc() error. size[%d]",
			tmp_ret_int);
		return -3;
	}

	//创建safe queue
	video_func->mp_info.merge_cache_sq = cp_create_memory_safe_queue(tmp_buf, tmp_ret_int, cp_safe_queue_mode_qbss, video_func->afc.buffer_size);
	if (!video_func->mp_info.merge_cache_sq) {
		cp_module_log(error, video_func,
			"init_video_merge_safe_queue() error. cp_create_memory_safe_queue() error. ");
		return -4;
	}

	//创建缓存数组
	tmp_mp = create_number_media_packet(video_func->pool,
		video_func->afc.each_buffer_length, video_func->afc.buffer_size, cp_media_packet_type_data_and_timestamp);
	if (!tmp_mp) {
		cp_module_log(error, video_func,
			"init_video_merge_safe_queue() error. create_number_media_packet() size[%d] number[%d] error. ",
			video_func->afc.buffer_size,
			video_func->afc.each_buffer_length);
		return -5;
	}
	video_func->mp_info.merge_cache_mp = tmp_mp;

	//初始化缓存
	for (i = 0; i < video_func->afc.buffer_size; i++, tmp_mp++) {
		cp_safe_queue_push(video_func->mp_info.merge_cache_sq, tmp_mp);
	}

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: destory_video_merge_safe_queue
*
* 函数说明: 消毁merge
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
* 创建日期：2017-01-13 17:03:31
******************************************************************************************************/
cp_int32_t destory_video_merge_safe_queue(cp_video_func_t *video_func)
{
	if (video_func->mp_info.merge_sq) {
		cp_destroy_safe_queue(video_func->mp_info.merge_sq);
		cp_pfree(video_func->pool, video_func->mp_info.merge_sq);
	}

	if (video_func->mp_info.merge_cache_sq) {
		cp_destroy_safe_queue(video_func->mp_info.merge_cache_sq);
		cp_pfree(video_func->pool, video_func->mp_info.merge_cache_sq);
	}

	if (video_func->mp_info.merge_cache_mp) {
		cp_pfree(video_func->pool, video_func->mp_info.merge_cache_mp);
	}

	return 0;
}

//创建一个media_packet
cp_media_packet_t *create_a_video_media_packet(cp_video_func_t *video_func, cp_int32_t len)
{
	cp_media_packet_t					*tmp_mp = CP_NULL;



#if defined(CP_VIDEO_FUNC_USED_MULTI_THREAD)
	//先从空闲队列中获得
	if (len < video_func->afc.each_buffer_length) {
		tmp_mp = cp_safe_queue_pop(video_func->mp_info.merge_cache_sq);
	}
	if (!tmp_mp) {
		//create media packet
		tmp_mp = cp_malloc(cp_sizeof(cp_media_packet_t) + len);
		if (!tmp_mp) {
			return CP_NULL;
		}
		cp_memset(tmp_mp, 0, cp_sizeof(cp_media_packet_t) + len);
		tmp_mp->type = cp_media_packet_type_data_and_timestamp;
		tmp_mp->pool = CP_NULL;
		cp_buf_assemble(&tmp_mp->mp_buf.buf[0], (cp_uchar_t*)tmp_mp + cp_sizeof(cp_media_packet_t), len);
	}
#else
	tmp_mp = create_media_packet(video_func->pool, len, cp_media_packet_type_data_and_timestamp);
#endif

	return tmp_mp;
}

//消毁一个media_packet
cp_int32_t destroy_a_video_media_packet(cp_video_func_t *video_func, cp_media_packet_t *mp)
{
#if defined(CP_VIDEO_FUNC_USED_MULTI_THREAD)
	if (get_media_packet_data_length(mp) > video_func->afc.each_buffer_length) {
		cp_free(mp);
	}
	else {
		clear_media_packet(mp);
		cp_safe_queue_push(video_func->mp_info.merge_cache_sq, mp);
	}
#else
	destroy_media_packet(mp);
#endif
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
	video_func->mp_info.thread_status = cp_video_func_thread_status_start;
	video_func->mp_info.merge_thread = cp_create_thread(video_func->manager->app, video_func_thread_cb_proc, video_func);
	if (!video_func->mp_info.merge_thread) {
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
	tmp_ret_int = start_video_decode_thread_process(video_func);
	if (tmp_ret_int) {
		return tmp_ret_int;
	}
	return 0;
}

//启动播放线程
cp_int32_t start_video_merge_thread_process(cp_video_func_t *video_func)
{
	//这里创建一个线程统一处理媒体
	video_func->mp_info.thread_status = cp_video_func_thread_status_start;
	video_func->mp_info.merge_thread = cp_create_thread(video_func->manager->app, video_func_merge_thread_cb_proc, video_func);
	if (!video_func->mp_info.merge_thread) {
		cp_module_log(error, video_func, "open_video_func() error, make_player_func_thread_manager() failed");
		return -1;
	}

	return 0;
}

//启动处理线程
cp_int32_t start_video_decode_thread_process(cp_video_func_t *video_func)
{
	//这里创建一个线程统一处理媒体
	video_func->mp_info.thread_status = cp_video_func_thread_status_start;
	video_func->play_flag = 0;
	video_func->mp_info.decode_thread = cp_create_thread(video_func->manager->app, video_func_decode_thread_cb_proc, video_func);
	if (!video_func->mp_info.decode_thread) {
		cp_module_log(error, video_func, "open_video_func() error, make_player_func_thread_manager() failed");
		return -1;
	}

	return 0;
}

//停止播放线程
cp_int32_t stop_video_merge_thread_process(cp_video_func_t *video_func)
{
	if (video_func->mp_info.merge_thread) {
		video_func->mp_info.thread_status = cp_video_func_thread_status_stop;
		cp_thread_join(video_func->mp_info.merge_thread);
		cp_destroy_thread(video_func->mp_info.merge_thread);
		video_func->mp_info.merge_thread = CP_NULL;
	}
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_video_decode_thread_process
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
cp_int32_t stop_video_decode_thread_process(cp_video_func_t *video_func)
{
	if (video_func->mp_info.decode_thread) {
		video_func->mp_info.thread_status = cp_video_func_thread_status_stop;
		cp_thread_join(video_func->mp_info.decode_thread);
		cp_destroy_thread(video_func->mp_info.decode_thread);
		video_func->mp_info.decode_thread = CP_NULL;
	}
	return 0;
}

//停止处理线程
cp_int32_t stop_video_thread_process(cp_video_func_t *video_func)
{
	stop_video_merge_thread_process(video_func);
	stop_video_decode_thread_process(video_func);
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