/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_memh_filter.h"
#include "cp_player_func_manager_core.h"



cp_memh_filter_t *cp_memh_filter_create();
/*模块创建接口，表示创建一个模块*/
cp_int32_t init_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_memh_filter(cp_memh_filter_t *memh_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_memh_filter(cp_memh_filter_t *memh_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_memh_filter(cp_memh_filter_t *memh_filter);
/*退出模块*/
cp_int32_t exit_memh_filter(cp_memh_filter_t *memh_filter);
/*设置模块参数*/
cp_int32_t set_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_memh_filter(cp_memh_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_memh_filter(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_memh_filter(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: memh_filter_tcp_data_integrity
*
* 函数说明: 校验接收数据的完整性，判断是否已经接收完全
*
* 参    数: cp_socket_t * socket						[in]参数说明
* 参    数: cp_int32_t nread							[in]参数说明
* 参    数: const cp_buf_t * buf						[in]参数说明
* 参    数: cp_int32_t status						[in]参数说明
*
* 返 回 值: cp_filter_status_e
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-06-30 20:32:52
******************************************************************************************************/
cp_filter_status_e memh_filter_tcp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: memh_filter_udp_data_integrity
*
* 函数说明: 处理udp数据
*
* 参    数: cp_socket_t * socket						[in]参数说明
* 参    数: cp_int32_t nread						[in]参数说明
* 参    数: const cp_buf_t * buf						[in]参数说明
* 参    数: cp_int32_t status						[in]参数说明
*
* 返 回 值: cp_filter_status_e
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-05 15:24:40
******************************************************************************************************/
cp_filter_status_e memh_filter_udp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: memh_filter_process_media_func
*
* 函数说明: 处理媒体数据
*
* 参    数: cp_socket_t * socket						[in]参数说明
* 参    数: cp_int32_t nread						[in]参数说明
* 参    数: const cp_buf_t * buf						[in]参数说明
* 参    数: cp_int32_t status						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-05 15:25:21
******************************************************************************************************/
cp_int32_t memh_filter_process_media_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: memh_filter_process_player_func
*
* 函数说明: 过滤处理memh 数据
*
* 参    数: cp_socket_t * socket						[in]参数说明
* 参    数: cp_int32_t nread						[in]参数说明
* 参    数: const cp_buf_t * buf						[in]参数说明
* 参    数: cp_int32_t status						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-05 11:25:16
******************************************************************************************************/
cp_int32_t memh_filter_process_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);




cp_memh_filter_t* create_memh_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_memh_filter_info_t *info)
{
	cp_memh_filter_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_memh_filter_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FILTER_MODULE_SET_HANDLERS(tmp_module, memh_filter);

	return tmp_module;
}

cp_int32_t destroy_memh_filter(cp_memh_filter_manager_t *manager, cp_memh_filter_t* memh_filter)
{
	if (!manager || !memh_filter) {
		return -1;
	}

	cp_free_module(memh_filter);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_memh_filter(cp_memh_filter_t *memh_filter, const cp_memh_filter_info_t *memh_filter_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_memh_filter(cp_memh_filter_t *memh_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_memh_filter(cp_memh_filter_t *memh_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_memh_filter(cp_memh_filter_t *memh_filter)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_memh_filter(cp_memh_filter_t *memh_filter)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_memh_filter(cp_memh_filter_t *memh_filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_memh_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_memh_filter(cp_memh_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_memh_filter(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_memh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;



	if (cp_socket_type_udp == socket->socket_type || 
		cp_socket_type_multicast == socket->socket_type) {
		ret_int = memh_filter_udp_data_integrity(socket, buf, nread, status);
	}
	
	return ret_int;
}

cp_int32_t write_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_memh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e memh_filter_tcp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e memh_filter_udp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_memh_t						*tmp_memh = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t*)buf;
	cp_device_info_t					*tmp_pdi = ((cp_player_info_t*)(socket->manager->app->app_info))->device_info;
	cp_int64_t							tmp_length = 0;
	cp_int32_t							tmp_ret_int = cp_filter_status_successorerror;



	//取出semh包头，判断semh最小长度
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	if (gmp_gmph_emh_type_memh != tmp_bmh->emht) {
		return cp_filter_status_successorerror;
	}

	//将数据
	if (push_a_memh_socket_buffer(socket->data, buf)) {
		cp_buf_clear(tmp_buf);
		return tmp_ret_int;
	}
	tmp_memh = (gmp_gmph_memh_t*)tmp_bmh;
	tmp_length = get_memh_socket_buffer_length(socket->data);
	if (css_media_network_metadata == tmp_memh->packet_type || 
		css_media_network_end == tmp_memh->packet_type) {
		//这里使用相关 func进行处理
		if (cp_media_type_video_h264 == tmp_memh->media_type || 
			(cp_media_type_audio_begin < tmp_memh->media_type &&
			tmp_memh->media_type < cp_media_type_audio_end)) {
			memh_filter_process_media_func(socket, buf, nread, status);
		}
		else {
			cp_module_log(error, socket, "unsupport memh type[%d].", tmp_memh->media_type);
		}
	}
	tmp_buf = create_a_memh_socket_buffer(socket->pool, socket->data, (cp_int32_t)tmp_pdi->network.packet_length);
	if (!tmp_buf) {
		return tmp_ret_int;
	}

	//更新操作句柄
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, memh_filter);
	//cp_read_socket(socket, tmp_buf, cp_buf_get_free_size(tmp_buf), 0);
	socket->buf = tmp_buf;
	return cp_filter_status_match | cp_filter_status_read_again;

	return 0;
}

cp_int32_t memh_filter_process_media_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_func_t						*tmp_player_func = CP_NULL;
	cp_int32_t						ret_int = 0;



	if (!socket || !socket->data) {
		return -1;
	}
	tmp_player_func = get_memh_socket_buffer_func(socket->data);
	if (!tmp_player_func) {
		cp_module_log(error, socket, "memh_filter_process_media_func() error. not found video func.");
		return -1;
	}
	//初始化模块
	ret_int = cp_write_module(tmp_player_func, &socket, cp_sizeof(cp_socket_t *), cp_player_func_flag_socket_point);
	if (ret_int) {
		cp_module_log(error, socket, "memh_filter_process_media_func() error. write video func module error.");
		return -1;
	}

	return 0;
}
