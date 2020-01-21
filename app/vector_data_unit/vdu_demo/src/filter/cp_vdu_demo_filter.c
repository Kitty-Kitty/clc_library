/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_demo_filter.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "css_status.h"



cp_vdu_demo_filter_t *cp_vdu_demo_filter_create();
/*模块创建接口，表示创建一个模块*/
cp_int32_t init_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, const cp_vdu_demo_filter_info_t *vdu_demo_filter_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, const cp_vdu_demo_filter_info_t *vdu_demo_filter_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter);
/*退出模块*/
cp_int32_t exit_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter);
/*设置模块参数*/
cp_int32_t set_option_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_vdu_demo_filter(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_vdu_demo_filter(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_vdu_demo_filter(cp_vdu_demo_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_vdu_demo_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_vdu_demo_filter(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_vdu_demo_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: vdu_demo_filter_tcp_data_integrity
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
cp_filter_status_e vdu_demo_filter_tcp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


cp_filter_status_e vdu_demo_filter_udp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: vdu_demo_filter_process_func
*
* 函数说明: 处理func部分内容
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
* 创建日期：2016-07-01 15:32:56
******************************************************************************************************/
cp_int32_t vdu_demo_filter_process_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);



cp_vdu_demo_filter_t* create_vdu_demo_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_vdu_demo_filter_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_vdu_demo_filter_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_vdu_demo_filter_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FILTER_MODULE_SET_HANDLERS(tmp_module, vdu_demo_filter);

	return tmp_module;
}

cp_int32_t destroy_vdu_demo_filter(cp_vdu_demo_filter_manager_t *manager, cp_vdu_demo_filter_t* vdu_demo_filter)
{
	if (!manager || !vdu_demo_filter) {
		return -1;
	}
	cp_free_module(vdu_demo_filter);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, const cp_vdu_demo_filter_info_t *vdu_demo_filter_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, const cp_vdu_demo_filter_info_t *vdu_demo_filter_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_vdu_demo_filter(cp_vdu_demo_filter_t *vdu_demo_filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_vdu_demo_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_vdu_demo_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_vdu_demo_filter(cp_vdu_demo_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_vdu_demo_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_vdu_demo_filter(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_vdu_demo_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;



	if (cp_socket_type_tcp == socket->socket_type) {
		//这里处理数据的完整性
		ret_int = vdu_demo_filter_tcp_data_integrity(socket, buf, nread, status);
	} else {
		ret_int = vdu_demo_filter_udp_data_integrity(socket, buf, nread, status);
	}
	
	if ((ret_int & cp_filter_status_match) && (ret_int & cp_filter_status_successorerror) 
		&& (ret_int & cp_filter_status_get_func)) {
		//数据处理成功处理func
		return vdu_demo_filter_process_func(socket, buf, cp_buf_get_length(buf), status);
	}
	return ret_int;
}

cp_int32_t write_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_vdu_demo_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e vdu_demo_filter_tcp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e vdu_demo_filter_udp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t vdu_demo_filter_process_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_queue_t								*modules;
	cp_queue_t								*current;
	cp_func_t								*func;
	cp_func_manager_t						*func_manager;
	cp_int32_t								ret_int = 0;
	cp_module_manager_info_t				tmp_module_manager_info;



	//处理func managet部分内容
	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_func);
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

