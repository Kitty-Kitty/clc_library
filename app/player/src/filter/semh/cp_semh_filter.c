/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_semh_filter.h"
#include "cp_player_func_manager_core.h"



cp_semh_filter_t *cp_semh_filter_create();
/*模块创建接口，表示创建一个模块*/
cp_int32_t init_semh_filter(cp_semh_filter_t *semh_filter, const cp_semh_filter_info_t *semh_filter_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_semh_filter(cp_semh_filter_t *semh_filter, const cp_semh_filter_info_t *semh_filter_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_semh_filter(cp_semh_filter_t *semh_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_semh_filter(cp_semh_filter_t *semh_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_semh_filter(cp_semh_filter_t *semh_filter);
/*退出模块*/
cp_int32_t exit_semh_filter(cp_semh_filter_t *semh_filter);
/*设置模块参数*/
cp_int32_t set_option_semh_filter(cp_semh_filter_t *semh_filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_semh_filter(cp_semh_filter_t *semh_filter, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_semh_filter(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_semh_filter(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_semh_filter(cp_semh_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_semh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_semh_filter(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_semh_filter(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_semh_filter(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_semh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_semh_filter(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_semh_filter(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: semh_filter_tcp_data_integrity
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
cp_filter_status_e semh_filter_tcp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: semh_filter_udp_data_integrity
*
* 函数说明: udp数据的过滤处理
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
* 创建日期：2016-11-19 17:09:03
******************************************************************************************************/
cp_filter_status_e semh_filter_udp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: semh_filter_process_func
*
* 函数说明: 处理func部分内容
*
* 参    数: cp_socket_t * socket					[in]参数说明
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
* 创建日期：2016-07-01 15:32:56
******************************************************************************************************/
cp_int32_t semh_filter_process_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t semh_filter_process_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_semh_filter_t* create_semh_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_semh_filter_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_semh_filter_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_semh_filter_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FILTER_MODULE_SET_HANDLERS(tmp_module, semh_filter);

	return tmp_module;
}

cp_int32_t destroy_semh_filter(cp_semh_filter_manager_t *manager, cp_semh_filter_t* semh_filter)
{
	if (!manager || !semh_filter) {
		return -1;
	}
	cp_free_module(semh_filter);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_semh_filter(cp_semh_filter_t *semh_filter, const cp_semh_filter_info_t *semh_filter_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_semh_filter(cp_semh_filter_t *semh_filter, const cp_semh_filter_info_t *semh_filter_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_semh_filter(cp_semh_filter_t *semh_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_semh_filter(cp_semh_filter_t *semh_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_semh_filter(cp_semh_filter_t *semh_filter)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_semh_filter(cp_semh_filter_t *semh_filter)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_semh_filter(cp_semh_filter_t *semh_filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_semh_filter(cp_semh_filter_t *semh_filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_semh_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_semh_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_semh_filter(cp_semh_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_semh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_semh_filter(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_semh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_semh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_semh_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;



	if (cp_socket_type_tcp == socket->socket_type) {
		//这里处理数据的完整性
		ret_int = semh_filter_tcp_data_integrity(socket, buf, nread, status);
	} else {
		ret_int = semh_filter_udp_data_integrity(socket, buf, nread, status);
	}
	
	if ((ret_int & cp_filter_status_match) && (ret_int & cp_filter_status_successorerror) 
		&& (ret_int & cp_filter_status_get_func)) {
		//数据处理成功处理func
		return semh_filter_process_func(socket, buf, cp_buf_get_length(buf), status);
	}
	return ret_int;
}

cp_int32_t write_cb_semh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_semh_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e semh_filter_tcp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t *)buf;
	cp_int32_t							tmp_len = 0;


	//协议头还没有收全
	if (cp_buf_get_length(tmp_buf) < CSS_GMP_GMPH_SEMH_LEN) {
#if 0
		if (cp_buf_get_size(tmp_buf) < CSS_GMP_GMPH_SEMH_LEN) {
			tmp_buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + CSS_GMP_GMPH_SEMH_LEN);
			if (!tmp_buf) {
				return 0;
			}
			cp_buf_assemble(tmp_buf, (cp_uchar_t*)tmp_buf + CSS_GMP_GMPH_SEMH_LEN, CSS_GMP_GMPH_SEMH_LEN);
		}
		//更新操作句柄
		CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, semh_filter);
		cp_read_socket(socket, CSS_GMP_GMPH_SEMH_LEN, tmp_buf, 0);
		return cp_filter_status_match | cp_filter_status_read_again;
#endif
		return 0;
	}

	//数据内容没有收完
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	if (gmp_gmph_emh_type_semh == tmp_bmh->emht) {
		tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
		tmp_len = cp_buf_get_length(tmp_buf);
		//如果接收成功则返回
		if (tmp_len >= (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			//如果数据已经接收完，则返回成功
			return cp_filter_status_match | cp_filter_status_successorerror | cp_filter_status_get_func;
		}
		//判断buf空间大小，如果不够则重新创建一个
		if (cp_buf_get_size(tmp_buf) < (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			tmp_buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + CSS_GMP_GMPH_SEMH_LEN + tmp_semh->length);
			if (!tmp_buf) {
				return 0;
			}
			cp_buf_assemble(tmp_buf, (cp_uchar_t*)tmp_buf + cp_sizeof(cp_buf_t), 
				CSS_GMP_GMPH_SEMH_LEN + tmp_semh->length);
			cp_buf_strcat(tmp_buf, cp_buf_get_pos(buf), cp_buf_get_length(buf));
		}
		//更新操作句柄
		CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, semh_filter);
		cp_read_socket(socket, tmp_buf, cp_buf_get_free_size(tmp_buf), 0);
		return cp_filter_status_match | cp_filter_status_read_again;
	}
	return 0;
}

cp_filter_status_e semh_filter_udp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t*)buf;
	cp_device_info_t					*tmp_pdi = ((cp_player_info_t*)(socket->manager->app->app_info))->device_info;
	cp_int64_t							tmp_length = 0;


	
	//取出semh包头，判断semh最小长度
	tmp_bmh = (gmp_gmph_bmh_t*)cp_buf_get_pos(tmp_buf);
	if (gmp_gmph_emh_type_semh != tmp_bmh->emht) {
		return cp_filter_status_successorerror;
	}

	//将数据
	if (push_a_semh_socket_buffer(socket->data, buf)) {
		cp_buf_clear(tmp_buf);
		return cp_filter_status_successorerror;
	}
	tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
	tmp_length = get_semh_socket_buffer_length(socket->data);
	if (tmp_semh->status == CSS_NETWORK_STATUS_602 || 
		tmp_length >= (CSS_GMP_GMPH_SEMH_LEN + tmp_semh->length)) {
		//这里使用player func进行处理
		semh_filter_process_player_func(socket, buf, nread, status);
	}
	tmp_buf = create_a_semh_socket_buffer(socket->pool, socket->data, (cp_int32_t)tmp_pdi->network.packet_length);
	if (!tmp_buf) {
		return cp_filter_status_successorerror;
	}
	
	//更新操作句柄
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, semh_filter);

	socket->buf = tmp_buf;
	//cp_read_socket(socket, tmp_buf, cp_buf_get_free_size(tmp_buf), 0);

	return cp_filter_status_match | cp_filter_status_read_again;
}

cp_int32_t semh_filter_process_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//处理func managet部分内容
	//CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_FUNC(1));
	func_manager = (cp_func_manager_t*)cp_get_manager(CP_NULL, &tmp_module_manager_info);
	if (func_manager) {
		modules = &func_manager->modules;
		for (current = cp_queue_next(modules); current != modules;
			current = cp_queue_next(current)) {
			func = cp_queue_data(current, cp_func_t, queue);
			if (func->read_cb) {
				ret_int = func->read_cb(socket, buf, nread, status);
				if (!(ret_int & cp_func_status_match)) {
					continue;
				}
				if ((ret_int & cp_func_status_successorerror) ||
					(ret_int & cp_func_status_read_again)) {
					return 0;
				}
				break;
			}
		}
	}
	return 0;
}

cp_int32_t semh_filter_process_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_func_t						*tmp_player_func = CP_NULL;
	cp_int32_t						ret_int = 0;



	tmp_player_func = (cp_func_t *)cp_manager_get_sub_module(socket->manager->app, cp_player_manager_type_func, cp_player_module_type_func);
	if (!tmp_player_func) {
		cp_module_log(error, socket, "semh_filter_process_player_func() error. not found player func.");
		return -1;
	}
	//初始化模块
	ret_int = cp_write_module(tmp_player_func, &socket, cp_sizeof(cp_socket_t *), cp_player_func_flag_socket_point);
	if (ret_int) {
		cp_module_log(error, socket, "semh_filter_process_player_func() error. write player func module error.");
		return -1;
	}

	return 0;
}
