/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_video_func.h"
#include "cp_player_codec_core.h"




cp_video_func_t *cp_video_func_create();
/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_video_func(cp_video_func_t *video_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_video_func(cp_video_func_t *video_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_video_func(cp_video_func_t *video_func);
/*退出模块*/
cp_int32_t exit_video_func(cp_video_func_t *video_func);
/*设置模块参数*/
cp_int32_t set_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_video_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_video_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_video_func(cp_video_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_video_func(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_video_func(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_video_func(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_video_func(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_video_func(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

cp_int32_t video_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t video_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

void video_func_thread_cb_proc(cp_video_func_t *video_func);

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
cp_int32_t set_video_multicast_data_filter(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//打开视频接 socket
cp_int32_t open_video_multicast_socket(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//关闭视频 socket
cp_int32_t close_video_multicast_socket(cp_video_func_t *video_func);

//设置memh的socket数据
cp_int32_t set_video_memh_socket_data(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len);

//消毁memh socket数据
cp_int32_t unset_video_memh_socket_data(cp_video_func_t *video_func);

//校验数据是否结
cp_inline cp_static cp_bool_t check_is_end(cp_buf_t *buf);

//打开测试文件
cp_inline cp_static cp_bool_t open_test_file(cp_video_func_t *video_func);

//关闭测试文件
cp_inline cp_static cp_bool_t close_test_file(cp_video_func_t *video_func);

//设置解码器信息
cp_inline cp_static cp_int32_t set_video_codec_info(cp_video_func_t *video_func, cp_array_t *ary);

//消毁视频解码器信息
cp_inline cp_static cp_int32_t unset_codec_info(cp_video_func_t *video_func);

//设置播放信息
cp_inline cp_static cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *vd);

//消毁视频显视信息
cp_inline cp_static cp_int32_t unset_video_dev_info(cp_video_func_t *video_func);

//解码媒体数据
cp_inline cp_static cp_media_packet_t* merge_media_data(cp_video_func_t *video_func, cp_array_t *ary);

//获取一帧数
cp_inline cp_static cp_int32_t get_a_frame_data(cp_video_func_t *video_func, cp_array_t *ary);

//解码媒体数据
cp_inline cp_static cp_int32_t decode_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//播媒体数据
cp_inline cp_static cp_int32_t play_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp);

//停止一个媒体播放
cp_inline cp_static cp_int32_t stop_video_func_media_play(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//添加媒体通道
cp_inline cp_static cp_int32_t insert_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//删除媒体通道
cp_inline cp_static cp_int32_t remove_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci);

//消毁所有数据
cp_inline cp_static cp_int32_t destroy_tmp_data(cp_video_func_t *video_func, cp_media_packet_t *mp, cp_array_t *ary);

//初始化媒体信息
cp_inline cp_static cp_int32_t init_media_description_info(cp_video_func_t *video_func);

//初始化解码信息
cp_inline cp_static cp_int32_t init_codec_callback_info(cp_video_func_t *video_func);

//停止处理线程
cp_inline cp_static cp_int32_t stop_thread_process(cp_video_func_t *video_func);

cp_video_func_t* create_video_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_video_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_video_func_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_video_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, video_func);

	return tmp_module;
}

cp_int32_t destroy_video_func(cp_video_func_manager_t *manager, cp_video_func_t* video_func)
{
	if (!manager || video_func) {
		return -1;
	}
	cp_free_module(video_func);
	return 0;
}

/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info)
{
	cp_int32_t									ret_int = 0;
	cp_void_t									*tmp_void_p = CP_NULL;
	cp_player_t									*tmp_player = (cp_player_t*)video_func->manager->app;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);


	if (!video_func || !video_func_info || !video_func_info->data) {
		return -1;
	}

	//这里判断是否已经初始化
	if (CP_MODULE_GET_STATUS(video_func, cp_module_status_init)) {
		return 0;
	}

	//设备media_channel 信息
	video_func->mci = *((cp_media_channel_info_t *)(video_func_info->data));

	//初始化解码数据内容
	video_func->decode_mp = create_media_packet(video_func->pool, 0, cp_media_packet_type_data_and_timestamp);
	if (!video_func->decode_mp) {
		cp_module_log(error, video_func, "init_video_func() error. create_media_packet() error.");
		return -2;
	}
	//设置
	video_func->decode_mp->orgin_module = (cp_module_t*)video_func;
	//初始化数据包描述信息
	ret_int = create_media_packet_description(video_func->pool, video_func->decode_mp, cp_media_description_type_video);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. create_media_packet_description() error.");
		return -2;
	}

	//初始媒体相关信息
	ret_int = init_media_description_info(video_func);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. init_media_description_info() error.");
		return -2;
	}

	//初始解码器相关信息
	ret_int = init_codec_callback_info(video_func);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. init_codec_callback_info() error.");
		return -2;
	}

	//初始化通道管理器
	ret_int = init_channel_manager(video_func->manager->app, &video_func->cm,
		tmp_player_info->device_info->hardware.limit_play_count);
	if (ret_int) {
		cp_module_log(error, video_func, "init_video_func() error. init_channel_manager() error.");
		return -2;
	}

	open_test_file(video_func);

	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_video_func(cp_video_func_t *video_func, const cp_video_func_info_t *video_func_info)
{
	cp_media_channel_info_t				*tmp_mci = CP_NULL;
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_channel_t						tmp_chl = { 0, };



	//这里判断是否已经初始化
	if (!CP_MODULE_GET_STATUS(video_func, cp_module_status_open)) {

		//启动通道管理器
		tmp_ret_int = start_channel_manager(&video_func->cm);
		if (tmp_ret_int) {
			cp_module_log(error, video_func, "open_video_func() error. start_channel_manager() error.");
			return -2;
		}

		//打开网络接
		tmp_ret_int = open_video_multicast_socket(video_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
		if (tmp_ret_int) {
			cp_module_log(error, video_func, "open_video_func() error. open_video_multicast_socket() error. reason:%s",
				tmp_buf);
			return -2;
		}

		//这里创建一个线程统一处理媒体
		video_func->thread_status = cp_video_func_thread_status_start;
		video_func->thread = cp_create_thread(video_func_thread_cb_proc, video_func);
		if (!video_func->thread) {
			cp_module_log(error, video_func, "open_video_func() error, make_player_func_thread_manager() failed");
			return -1;
		}
	}

	//添加通道信息
	tmp_ret_int = insert_media_channel_info(video_func, (cp_media_channel_info_t *)video_func_info->data);
	if (tmp_ret_int) {
		cp_module_log(error, video_func, "open_video_func() error. insert_media_channel_info() error.");
		return -1;
	}

	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_video_func(cp_video_func_t *video_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_video_func(cp_video_func_t *video_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if 0
	cp_int32_t							ret_int = 0;
	cp_int32_t							tmp_css_av_type = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_socket_t							*tmp_socket = CP_NULL;


	if (video_func->is_open_codec) {
		return 0;
	}

	if (cp_player_func_flag_socket_point != flag ||
		len != cp_sizeof(cp_socket_t*)) {
		return 0;
	}

	tmp_socket = (cp_socket_t *)(*buf);
	if (tmp_socket) {
		//取出semh包头，判断semh最小长度
		tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_socket->buf);

		if (gmp_gmph_emh_type_memh == tmp_bmh->emht) {
			tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
			//这里
			if (!video_func->is_open_codec && video_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				//
				tmp_css_av_type = tmp_memh->media_type;
				ret_int = cp_set_option_module(video_func->codec, cp_player_codec_set_option_codec_info, &tmp_css_av_type);
				if (ret_int) {
					cp_module_log(error, video_func, "module(video_func) set codec type[%d] error.", tmp_css_av_type);
				}
				else {
					video_func->is_open_codec = cp_true;
				}
			}
		}
	}
#endif
	return 0;
}
/*关闭模块*/
cp_int32_t close_video_func(cp_video_func_t *video_func)
{
	//关闭组播
	close_video_multicast_socket(video_func);

	//关闭线程
	stop_thread_process(video_func);

	//消毁视频解码器信息
	unset_codec_info(video_func);

	//消毁视频显视信息
	unset_video_dev_info(video_func);

	//关闭通道管理器
	stop_channel_manager(&video_func->cm);

	if (video_func->decode_mp) {
		//消毁媒体包描述信息
		destroy_media_packet_description(video_func->pool, video_func->decode_mp);

		//消毁媒体包
		destroy_media_packet(video_func->decode_mp);
		video_func->decode_mp = CP_NULL;
	}

	close_test_file(video_func);

	return 0;
}
/*退出模块*/
cp_int32_t exit_video_func(cp_video_func_t *video_func)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, const cp_void_t* optval)
{
	cp_module_info_t					*module_info;



	if (cp_player_func_set_option_stop_media_play & optname) {
		if (!optval) {
			return -1;
		}
		module_info = (cp_module_info_t *)optval;
		return stop_video_func_media_play(video_func, (cp_media_channel_info_t*)(module_info->data));
	}

	cp_module_log(error, video_func, "%s unsupport optname[%d]", __FUNCTION__, optname);
	return -1;
}

cp_int32_t get_option_video_func(cp_video_func_t *video_func, cp_int32_t optname, cp_void_t* optval)
{
	cp_media_channel_info_t					**tmp_mci = CP_NULL;



	if (cp_player_func_get_option_media_channel_info == optname) {
		if (!optval) {
			return -1;
		}
		tmp_mci = (cp_media_channel_info_t **)optval;

		*tmp_mci = &(video_func->mci);
		return 0;
	}

	cp_module_log(error, video_func, "%s unsupport optname[%d]", __FUNCTION__, optname);
	return -1;
}

#if 0
cp_int32_t listen_video_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_video_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_video_func(cp_video_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_video_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_video_func(cp_socket_t *socket, cp_int32_t status)
{
	cp_buf_t				*buf;
	cp_int32_t				tmp_read_length = 0;


	//只有tcp读头，其他的报文读一个报文
	if (CP_SOCKET_CHECK_TYPE(socket, cp_socket_type_tcp)) {
		tmp_read_length = CSS_GMP_GMPH_SEMH_LEN;
	}
	else {
		tmp_read_length = 1024;
	}
	//分配空间
	buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + tmp_read_length);
	if (!buf) {
		return -1;
	}
	cp_buf_assemble(buf, (cp_uchar_t*)buf + cp_sizeof(cp_buf_t), tmp_read_length);
	cp_buf_memzero(buf);

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, video_func);
	cp_read_socket(socket, buf, tmp_read_length, 0);
	return 0;
}

cp_int32_t close_cb_video_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_video_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;
	cp_video_func_t*			tmp_video_func = CP_NULL;


	//这里接 数据采用filter进行
	if (!socket->data || !((cp_video_func_t*)(socket->data))->filter ||
		!((cp_video_func_t*)(socket->data))->filter->read_cb) {
		return -1;
	}

	((cp_video_func_t*)(socket->data))->filter->read_cb(socket, buf, nread, status);

	return ret_int;
}

cp_int32_t write_cb_video_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_video_func(socket, status);
}

cp_int32_t error_cb_video_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

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
* 函数名称: open_video_multicast_socket
*
* 函数说明: 打开视频接 socket
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
* 创建日期：2016-11-25 15:18:29
******************************************************************************************************/
cp_int32_t open_video_multicast_socket(cp_video_func_t *video_func, cp_char_t *buf, cp_int32_t len)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_sockaddr_in						tmp_multicast_addr = { 0, };


	cp_memset(buf, 0, len);
	if (!video_func->mci.channel_info.multicast_info.port ||
		!cp_strlen(video_func->mci.channel_info.multicast_info.ip)) {
		cp_snprintf(buf, len, "url address [%s:%d] error.",
			video_func->mci.channel_info.multicast_info.ip,
			video_func->mci.channel_info.multicast_info.port);
		return -1;
	}
	//创
	video_func->socket = cp_create_socket(cp_socket_type_multicast);
	if (!video_func->socket) {
		cp_snprintf(buf, len, "cp_create_socket() error.");
		return -2;
	}

	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(video_func->socket, video_func);
	tmp_ret_int = set_video_multicast_data_filter(video_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "set_video_multicast_data_filter() error. %s", tmp_buf);
		return -2;
	}

	cp_ip4_addr(video_func->mci.channel_info.multicast_info.ip,
		video_func->mci.channel_info.multicast_info.port, &tmp_multicast_addr);

	//启动multicast监听
	tmp_ret_int = cp_listen_socket(video_func->socket, &tmp_multicast_addr);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "cp_listen_socket() [%s:%d] error.",
			video_func->mci.channel_info.multicast_info.ip,
			video_func->mci.channel_info.multicast_info.port);
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
		destroy_socket_data(video_func->socket->pool, video_func->socket->data);
		video_func->socket->data = CP_NULL;
	}
	return 0;
}

/*解码器读数据回调函数据*/
cp_int32_t video_func_codec_read_cb_handle(cp_video_func_t *video_func, cp_codec_callback_info_t *ccb_info_p, cp_media_packet_t *mp)
{
	if (!video_func) {
		return -1;
	}

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



	//初始化数组
	cp_array_init(&tmp_array, tmp_buf_array, cp_sizeof(cp_buf_t*), CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE);

	while (cp_true)
	{
		if (video_func->thread_status != cp_video_func_thread_status_start) {
			break;
		}

		//获取end标志的一帧数据
		ret_int = get_a_frame_data(video_func, &tmp_array);
		if (ret_int) {
			//cp_sleep_ns(0, 1000000);
			continue;
		}

		//处理指令
		set_video_codec_info(video_func, &tmp_array);
		tmp_mp = merge_media_data(video_func, &tmp_array);
		if (tmp_mp) {
#if defined(CP_VIDEO_FILE_DEBUG)
			if (video_func->file) {
				fwrite(cp_buf_get_pos(&tmp_mp->buf[0]), 1, cp_buf_get_length(&tmp_mp->buf[0]), video_func->file);
			}
#endif
			ret_int = decode_media_data(video_func, tmp_mp);
			if (!ret_int) {
				play_media_data(video_func, video_func->decode_mp);
			}
		}
		//消毁数据缓存
		//destroy_tmp_data(video_func, tmp_mp, &tmp_array);
		cp_array_clear(&tmp_array);
	}
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: check_is_end
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
cp_bool_t check_is_end(cp_buf_t *buf)
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
cp_bool_t open_test_file(cp_video_func_t *video_func)
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
* 函数名称: close_test_file
*
* 函数说明: 关闭测试文件
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
* 创建日期：2016-12-16 15:16:02
******************************************************************************************************/
cp_bool_t close_test_file(cp_video_func_t *video_func)
{
#if defined(CP_AUDIO_FILE_DEBUG)

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
	//获取音频处理管理器
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
	//获取音频处理管理器
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
	cp_uint32_t							i = 0;
	cp_buf_t							**tmp_buf = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_module_t							*tmp_codec_module = CP_NULL;



	if (!video_func || !ary) {
		return -1;
	}

	if (video_func->is_open_codec) {
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
			if (!video_func->is_open_codec && !video_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				//
				video_func->decode_md.md.encodec_type = tmp_memh->media_type;

				//初始化解码器
				tmp_codec_module = create_video_codec_module((cp_player_t*)(video_func->manager->app),
					(cp_media_description_t *)&video_func->decode_md,
					cp_player_manager_type_codec, cp_player_module_type_ffmpeg_codec);
				if (!tmp_codec_module) {
					cp_module_log(error, video_func, "set_video_codec_info() error. create_video_codec_module() error.");
					return -2;
				}
				video_func->codec = (cp_codec_t *)tmp_codec_module;
				video_func->is_open_codec = cp_true;
				return 0;
			}
		}

		if (check_is_end((*tmp_buf))) {
			break;
		}
	}

	return -2;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: unset_codec_info
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
cp_int32_t unset_codec_info(cp_video_func_t *video_func)
{
	if (video_func->is_open_codec && video_func->codec) {
		//关闭解码器
		cp_close_module(video_func->codec);
		//消毁解码器
		cp_destroy_module(video_func->codec->manager, video_func->codec);
		//设置解器状态
		video_func->is_open_codec = cp_true;
		video_func->codec = CP_NULL;
	}

	return 0;
}

//设置播放信息
cp_int32_t set_video_dev_info(cp_video_func_t *video_func, cp_video_description_t *vd)
{
	cp_module_t									*tmp_dev_module = CP_NULL;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(video_func->manager->app->app_info);
	cp_dev_video_description_t					tmp_vdd = { 0, };



	if (!video_func || !vd) {
		return -1;
	}

	if (video_func->dev) {
		return 0;
	}

	//初始化播放器
	tmp_vdd.dd.type = cp_dev_description_type_video;
	tmp_vdd.width = tmp_player_info->device_info->hardware.resolution_width;
	tmp_vdd.height = tmp_player_info->device_info->hardware.resolution_height;
	tmp_vdd.fps = vd->fps;
	tmp_dev_module = create_video_dev_module((cp_player_t*)(video_func->manager->app),
		(cp_dev_description_t *)&tmp_vdd,
		(cp_media_description_t *)vd,
		cp_player_manager_type_dev, cp_player_module_type_sdl_dev);
	if (!tmp_dev_module) {
		cp_module_log(error, video_func, "set_video_dev_info() error. create_video_codec_module() error.");
		return -2;
	}
	video_func->dev = (cp_dev_t *)tmp_dev_module;

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
* 参    数: cp_video_description_t * vd						[in]参数说明
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
* 函数名称: merge_media_data
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
cp_media_packet_t* merge_media_data(cp_video_func_t *video_func, cp_array_t *ary)
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

		if (check_is_end((*tmp_buf))) {
			break;
		}
	}

	if (tmp_total <= 0) {
		return CP_NULL;
	}

	//create media packet
	tmp_mp = create_media_packet(video_func->pool, tmp_total,
		cp_media_packet_type_data_and_timestamp);
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
			cp_buf_strcat(&tmp_mp->buf[0], cp_buf_get_pos((*tmp_buf)) + cp_sizeof(gmp_gmph_memh_t), tmp_memh->body_size);

			//这里获取时间
			if ((css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				tmp_ts.tv_sec = tmp_memh->time_stamp_s;
				tmp_ts.tv_nsec = tmp_memh->time_stamp_ns;
			}
		}

		if (check_is_end((*tmp_buf))) {
			break;
		}
	}

	tmp_mp->ts = tmp_ts;
	return tmp_mp;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_a_frame_data
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
cp_int32_t get_a_frame_data(cp_video_func_t *video_func, cp_array_t *ary)
{
	cp_buf_t				*tmp_buf = CP_NULL;


	while (cp_true)
	{
		//逐个获取数据句
		tmp_buf = pop_a_memh_socket_buffer(video_func->socket->data);
		if (!tmp_buf) {
			break;
		}

		cp_array_set_back(ary, &tmp_buf);
		if (check_is_end(tmp_buf)) {
			return 0;
		}
	}
	return -1;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: decode_media_data
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
cp_int32_t decode_media_data(cp_video_func_t *video_func, cp_media_packet_t	*mp)
{
	if (!video_func || !mp || !video_func->codec) {
		return -1;
	}

	return cp_write_module(video_func->codec, &mp, cp_sizeof(cp_media_packet_t**), 0);
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: play_media_data
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
cp_int32_t play_media_data(cp_video_func_t *video_func, cp_media_packet_t *mp)
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
	tmp_ret_int = remove_media_channel_info(video_func, mci);
	if (tmp_ret_int) {
		cp_module_log(error, video_func, "open_video_func() error. remove_media_channel_info() error.");
		return -1;
	}

	//如果还有通道再使用则返回
	if (video_func->cm.size > 0) {
		return 0;
	}

	//如果没有则停止
	close_video_func(video_func);

	//消毁模块
	cp_destroy_module(video_func->manager, video_func);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: insert_media_channel_info
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
cp_int32_t insert_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_channel_t						*tmp_find_chl = CP_NULL;
	cp_channel_t						tmp_chl = { 0, };



	if (!video_func || !mci) {
		return -1;
	}

	//查找是否已经存在
	tmp_find_chl = find_channel(&video_func->cm, mci->channel_info.index);
	if (tmp_find_chl) {
		cp_module_log(warn, video_func,
			"insert_media_channel_info() error, channel[%d] exist now!",
			mci->channel_info.index);
		return 0;
	}

	//创建媒体通道
	tmp_chl_info = cp_palloc(video_func->pool, cp_sizeof(cp_channel_info_t));
	if (!tmp_chl_info) {
		cp_module_log(error, video_func, "insert_media_channel_info() error, cp_palloc() make media channel information failed");
		return -1;
	}
	*tmp_chl_info = mci->channel_info;

	set_channel(&tmp_chl, mci->channel_info.index, mci->channel_info.play_session, (cp_module_t*)video_func, tmp_chl_info);
	insert_channel(&video_func->cm, &tmp_chl);

	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: remove_media_channel_info
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
cp_int32_t remove_media_channel_info(cp_video_func_t *video_func, cp_media_channel_info_t *mci)
{
	cp_channel_info_t					*tmp_chl_info = CP_NULL;
	cp_channel_t						*tmp_chl = { 0, };



	tmp_chl = find_channel(&video_func->cm, mci->channel_info.index);
	if (!tmp_chl) {
		cp_module_log(error, video_func,
			"remove_media_channel_info() error, not found channel[%d]",
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
* 函数名称: destroy_tmp_data
*
* 函数说明: 消毁所有数据
*
* 参    数: cp_video_func_t * video_func						[in]参数说明
* 参    数: cp_media_packet_t * mp						[in]参数说明
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
cp_int32_t destroy_tmp_data(cp_video_func_t *video_func, cp_media_packet_t	*mp, cp_array_t *ary)
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
		destroy_a_memh_socket_buffer(video_func->socket->pool, video_func->socket->data, (*tmp_buf));
	}

	destroy_media_packet(mp);
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_media_description_info
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
cp_int32_t init_media_description_info(cp_video_func_t *video_func)
{
	if (!video_func) {
		return -1;
	}
	video_func->decode_md.md.type = cp_media_description_type_video;
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: init_codec_callback_info
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
cp_int32_t init_codec_callback_info(cp_video_func_t *video_func)
{
	cp_memset(&video_func->cc_info.handle, 0, cp_sizeof(cp_codec_callback_handle_t));
	video_func->cc_info.handle.read_cb = (cp_codec_general_cb_handle)video_func_codec_read_cb_handle;
	video_func->decode_mp->ccb_info_p = &video_func->cc_info;
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: stop_thread_process
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
* 创建日期：2016-12-14 16:38:27
******************************************************************************************************/
cp_int32_t stop_thread_process(cp_video_func_t *video_func)
{
	if (video_func->thread) {
		video_func->thread_status = cp_video_func_thread_status_stop;
		cp_thread_join(video_func->thread);
		cp_destroy_thread(video_func->thread);
		video_func->thread = CP_NULL;
	}
	return 0;
}