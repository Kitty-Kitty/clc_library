/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_audio_func.h"
#include "cp_audio_func_proc.h"



cp_audio_func_t *cp_audio_func_create();
/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_audio_func(cp_audio_func_t *audio_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_audio_func(cp_audio_func_t *audio_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_audio_func(cp_audio_func_t *audio_func);
/*退出模块*/
cp_int32_t exit_audio_func(cp_audio_func_t *audio_func);
/*设置模块参数*/
cp_int32_t set_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_audio_func(cp_audio_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_audio_func(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_audio_func(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_audio_func(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_audio_func(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_audio_func(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

//打开视频接 socket
cp_int32_t open_audio_multicast_socket(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len);

cp_audio_func_t* create_audio_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_audio_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_audio_func_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_audio_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, audio_func);

	return tmp_module;
}

cp_int32_t destroy_audio_func(cp_audio_func_manager_t *manager, cp_audio_func_t* audio_func)
{
	if (!manager || !audio_func) {
		return -1;
	}
	cp_free_module(audio_func);
	return 0;
}

/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info)
{
	cp_int32_t									ret_int = 0;
	cp_void_t									*tmp_void_p = CP_NULL;
	cp_player_t									*tmp_player = (cp_player_t*)audio_func->manager->app;
	cp_player_info_t							*tmp_player_info = (cp_player_info_t *)(tmp_player->app_info);


	if (!audio_func || !audio_func_info || !audio_func_info->data) {
		return -1;
	}

	//这里判断是否已经初始化
	if (CP_MODULE_GET_STATUS(audio_func, cp_module_status_init)) {
		return 0;
	}

	//解析音频配置文件
	ret_int = audio_func_parse_configure((cp_module_t*)audio_func, &audio_func->afc);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. audio_func_parse_configure() error.");
		return -2;
	}

	//设备media_channel 信息
	audio_func->mci = *((cp_media_channel_info_t *)(audio_func_info->data));

	//初始化解码数据内容
	audio_func->mp_info.decode_mp = create_media_packet(audio_func->pool, 0, cp_media_packet_type_data_and_timestamp);
	if (!audio_func->mp_info.decode_mp) {
		cp_module_log(error, audio_func, "init_audio_func() error. create_media_packet() error.");
		return -2;
	}
	//设置
	audio_func->mp_info.decode_mp->orgin_module = (cp_module_t*)audio_func;
	//初始化数据包描述信息
	ret_int = create_media_packet_description(audio_func->pool, audio_func->mp_info.decode_mp, cp_media_description_type_audio);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. create_media_packet_description() error.");
		return -2;
	}

	//初始媒体相关信息
	ret_int = init_audio_media_description_info(audio_func);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. init_audio_media_description_info() error.");
		return -2;
	}

	//初始解码器相关信息
	ret_int = init_audio_codec_callback_info(audio_func);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. init_audio_codec_callback_info() error.");
		return -2;
	}

	//初始化merge
	ret_int = init_audio_merge_safe_queue(audio_func);
	if (ret_int) {
		cp_module_log(error, audio_func, "init_audio_func() error. init_audio_merge_safe_queue() error.");
		return -3;
	}

	open_audio_test_file(audio_func);

	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };



	//这里判断是否已经初始化
	if (!CP_MODULE_GET_STATUS(audio_func, cp_module_status_open)) {
		//打开网络接
		tmp_ret_int = open_audio_multicast_socket(audio_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
		if (tmp_ret_int) {
			cp_module_log(error, audio_func, "open_audio_func() error. open_audio_multicast_socket() error. reason:%s",
				tmp_buf);
			return -2;
		}

		start_audio_thread_process(audio_func);		
	}

	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_audio_func(cp_audio_func_t *audio_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_audio_func(cp_audio_func_t *audio_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
#if 0
	cp_int32_t							ret_int = 0;
	cp_int32_t							tmp_css_av_type = 0;
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_socket_t							*tmp_socket = CP_NULL;


	if (audio_func->is_open_codec) {
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
			if (!audio_func->is_open_codec && audio_func->codec &&
				(css_media_network_begin == tmp_memh->packet_type ||
				css_media_network_other == tmp_memh->packet_type ||
				css_media_network_end == tmp_memh->packet_type)) {
				//
				tmp_css_av_type = tmp_memh->media_type;
				ret_int = cp_set_option_module(audio_func->codec, cp_player_codec_set_option_codec_info, &tmp_css_av_type);
				if (ret_int) {
					cp_module_log(error, audio_func, "module(audio_func) set codec type[%d] error.", tmp_css_av_type);
				}
				else {
					audio_func->is_open_codec = cp_true;
				}
			}
		}
	}
#endif
	return 0;
}

/*关闭模块*/
cp_int32_t close_audio_func(cp_audio_func_t *audio_func)
{
	//关闭组播
	close_audio_multicast_socket(audio_func);

	//关闭音频解码器
	close_audio_codec_info(audio_func);

	//关闭线程
	stop_audio_thread_process(audio_func);

	//消毁视频解码器信息
	unset_audio_codec_info(audio_func);

	//消毁视频显视信息
	unset_audio_dev_info(audio_func);

	//消毁merge
	destory_audio_merge_safe_queue(audio_func);

	if (audio_func->mp_info.decode_mp) {
		//消毁媒体包描述信息
		destroy_media_packet_description(audio_func->pool, audio_func->mp_info.decode_mp);

		//消毁媒体包
		destroy_media_packet(audio_func->mp_info.decode_mp);
		audio_func->mp_info.decode_mp = CP_NULL;
	}

	close_audio_test_file(audio_func);

	return 0;
}

/*退出模块*/
cp_int32_t exit_audio_func(cp_audio_func_t *audio_func)
{
	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, const cp_void_t* optval)
{
	cp_module_info_t					*module_info;



	if (cp_player_func_set_option_stop_media_play & optname) {
		if (!optval) {
			return -1;
		}
		module_info = (cp_module_info_t *)optval;
		return stop_audio_func_media_play(audio_func, (cp_media_channel_info_t*)(module_info->data));
	}

	if (cp_player_func_set_option_update_media_info & optname) {
		if (!optval) {
			return -1;
		}
		module_info = (cp_module_info_t *)optval;
		return update_audio_func_media_play(audio_func, (cp_media_channel_info_t*)(module_info->data));
	}

	cp_module_log(error, audio_func,
		"set_option_audio_func() error. unsupport optname[%d]", optname);
	return -1;
}

cp_int32_t get_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, cp_void_t* optval)
{
	cp_media_channel_info_t					**tmp_mci = CP_NULL;



	if (cp_player_func_get_option_media_channel_info == optname) {
		if (!optval) {
			return -1;
		}
		tmp_mci = (cp_media_channel_info_t **)optval;

		*tmp_mci = &(audio_func->mci);
		return 0;
	}

	cp_module_log(error, audio_func,
		"set_option_audio_func() error. unsupport optname[%d]", optname);
	return -1;
}

#if 0
cp_int32_t listen_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_audio_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_audio_func(cp_audio_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_audio_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
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

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, audio_func);
	cp_read_socket(socket, buf, tmp_read_length, 0);
	return 0;
}

cp_int32_t close_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_audio_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;
	cp_audio_func_t*			tmp_audio_func = CP_NULL;


	//这里接 数据采用filter进行
	if (!socket->data || !((cp_audio_func_t*)(socket->data))->filter ||
		!((cp_audio_func_t*)(socket->data))->filter->read_cb) {
		return -1;
	}

	((cp_audio_func_t*)(socket->data))->filter->read_cb(socket, buf, nread, status);

	return ret_int;
}

cp_int32_t write_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_audio_func(socket, status);
}

cp_int32_t error_cb_audio_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: open_audio_multicast_socket
*
* 函数说明: 打开视频接 socket
*
* 参    数: cp_audio_func_t * audio_func						[in]参数说明
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
cp_int32_t open_audio_multicast_socket(cp_audio_func_t *audio_func, cp_char_t *buf, cp_int32_t len)
{
	cp_int32_t							tmp_ret_int = 0;
	cp_char_t							tmp_buf[CP_APP_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_sockaddr_in						tmp_multicast_addr = { 0, };


	cp_memset(buf, 0, len);
	if (!audio_func->mci.channel_info.multicast_info.port ||
		!cp_strlen(audio_func->mci.channel_info.multicast_info.ip)) {
		cp_snprintf(buf, len, "url address [%s:%d] error.",
			audio_func->mci.channel_info.multicast_info.ip,
			audio_func->mci.channel_info.multicast_info.port);
		return -1;
	}
	//创
	audio_func->socket = cp_create_socket(audio_func->manager->app, cp_socket_type_multicast);
	if (!audio_func->socket) {
		cp_snprintf(buf, len, "cp_create_socket() error.");
		return -2;
	}

	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(audio_func->socket, audio_func);
	tmp_ret_int = set_audio_multicast_data_filter(audio_func, tmp_buf, CP_APP_DEFAULT_BUFFER_LENGTH);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "set_audio_multicast_data_filter() error. %s", tmp_buf);
		return -2;
	}

	cp_ip4_addr(audio_func->mci.channel_info.multicast_info.ip,
		audio_func->mci.channel_info.multicast_info.port, &tmp_multicast_addr);

	//启动multicast监听
	tmp_ret_int = cp_listen_socket(audio_func->socket, &tmp_multicast_addr);
	if (tmp_ret_int) {
		cp_snprintf(buf, len, "cp_listen_socket() [%s:%d] error.",
			audio_func->mci.channel_info.multicast_info.ip,
			audio_func->mci.channel_info.multicast_info.port);
		return -2;
	}

	return 0;
}
