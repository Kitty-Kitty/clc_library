/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ptp_filter.h"
#include "cp_ptp_header.h"
#include "cp_player_func_manager_core.h"



cp_ptp_filter_t *cp_ptp_filter_create();
/*模块创建接口，表示创建一个模块*/
cp_int32_t init_ptp_filter(cp_ptp_filter_t *ptp_filter, const cp_ptp_filter_info_t *ptp_filter_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_ptp_filter(cp_ptp_filter_t *ptp_filter, const cp_ptp_filter_info_t *ptp_filter_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ptp_filter(cp_ptp_filter_t *ptp_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_ptp_filter(cp_ptp_filter_t *ptp_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_ptp_filter(cp_ptp_filter_t *ptp_filter);
/*退出模块*/
cp_int32_t exit_ptp_filter(cp_ptp_filter_t *ptp_filter);
/*设置模块参数*/
cp_int32_t set_option_ptp_filter(cp_ptp_filter_t *ptp_filter, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_ptp_filter(cp_ptp_filter_t *ptp_filter, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_ptp_filter(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_ptp_filter(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_ptp_filter(cp_ptp_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_ptp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_ptp_filter(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_ptp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ptp_filter_udp_data_integrity
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
cp_filter_status_e ptp_filter_udp_data_integrity(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ptp_filter_process_ptp_func
*
* 函数说明: 处理ptp数据
*
* 参    数: cp_socket_t * socket						[in]参数说明
* 参    数: cp_group_timestamp_t * group_ts						[in]参数说明
*
* 返 回 值: cp_int32_t
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2017-01-09 15:25:33
******************************************************************************************************/
cp_int32_t ptp_filter_process_ptp_func(cp_socket_t *socket, cp_group_timestamp_t *group_ts);

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: ptp_filter_process_player_func
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
cp_int32_t ptp_filter_process_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);




cp_ptp_filter_t* create_ptp_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ptp_filter_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_ptp_filter_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_ptp_filter_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FILTER_MODULE_SET_HANDLERS(tmp_module, ptp_filter);

	return tmp_module;
}

cp_int32_t destroy_ptp_filter(cp_filter_manager_t *manager, cp_ptp_filter_t* ptp_filter)
{
	if (!manager || !ptp_filter) {
		return -1;
	}
	cp_free_module(ptp_filter);
	return 0;
}

/*模块创建接口，表示创建一个模块*/
cp_int32_t init_ptp_filter(cp_ptp_filter_t *ptp_filter, const cp_ptp_filter_info_t *ptp_filter_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_ptp_filter(cp_ptp_filter_t *ptp_filter, const cp_ptp_filter_info_t *ptp_filter_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ptp_filter(cp_ptp_filter_t *ptp_filter, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_ptp_filter(cp_ptp_filter_t *ptp_filter, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_ptp_filter(cp_ptp_filter_t *ptp_filter)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_ptp_filter(cp_ptp_filter_t *ptp_filter)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_ptp_filter(cp_ptp_filter_t *ptp_filter, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_ptp_filter(cp_ptp_filter_t *ptp_filter, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_ptp_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_ptp_filter(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_ptp_filter(cp_ptp_filter_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_ptp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_ptp_filter(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_ptp_filter(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;



	if (cp_socket_type_udp == socket->socket_type || 
		cp_socket_type_multicast == socket->socket_type) {
		ret_int = ptp_filter_udp_data_integrity(socket, buf, nread, status);
	}
	else {
		if (buf) {
			cp_buf_clear((cp_buf_t*)buf);
		}
	}
	
	return ret_int;
}

cp_int32_t write_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_ptp_filter(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e ptp_filter_tcp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_filter_status_e ptp_filter_udp_data_integrity
	(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t							tmp_type;
	cp_ptp_message_t					*tmp_ptp_msg = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t*)buf;
	cp_int32_t							tmp_ret_int = cp_filter_status_successorerror;
	uint32_t							tmp_lsb = 0;
	uint16_t							tmp_msb = 0;
	cp_group_timestamp_t				tmp_group_ts = { 0, };



	//取出ptp包头，判断ptp最小长度
	if (nread < cp_sizeof(cp_ptp_header_t)) {
		return cp_filter_status_successorerror;
	}

	//获得ptp头
	tmp_ptp_msg = (cp_ptp_message_t*)cp_buf_get_pos(tmp_buf);
	if (!tmp_ptp_msg) {
		return cp_filter_status_successorerror;
	}
	
	//校验版本号
	if ((tmp_ptp_msg->header.ver & CP_PTP_VERSION_MASK) != CP_PTP_VERSION) {
		cp_buf_clear(tmp_buf);
		return cp_filter_status_successorerror;
	}

	//校验头类型是否为CP_FOLLOW_UP
	tmp_type = tmp_ptp_msg->header.tsmt & 0x0f;
	if (CP_FOLLOW_UP != tmp_type) {
		cp_buf_clear(tmp_buf);
		return cp_filter_status_successorerror;
	}
	else {
		tmp_lsb = ntohl(tmp_ptp_msg->follow_up.preciseOriginTimestamp.seconds_lsb);
		tmp_msb = ntohs(tmp_ptp_msg->follow_up.preciseOriginTimestamp.seconds_msb);

		tmp_group_ts.id = tmp_ptp_msg->header.domainNumber;
		tmp_group_ts.time.tv_sec = ((uint64_t)tmp_lsb) | (((uint64_t)tmp_msb) << 32);
		tmp_group_ts.time.tv_nsec = ntohl(tmp_ptp_msg->follow_up.preciseOriginTimestamp.nanoseconds);
	}

	//处理ptp数据
	ptp_filter_process_ptp_func(socket, &tmp_group_ts);

	//更新操作句柄
	CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, ptp_filter);
	//cp_read_socket(socket, tmp_buf, cp_buf_get_free_size(tmp_buf), 0);
	cp_buf_clear(tmp_buf);
	socket->buf = tmp_buf;
	return cp_filter_status_match | cp_filter_status_read_again;

	return 0;
}

cp_int32_t ptp_filter_process_ptp_func(cp_socket_t *socket, cp_group_timestamp_t *group_ts)
{
	cp_func_t							*tmp_ptp_func = CP_NULL;
	cp_int32_t							ret_int = 0;




	tmp_ptp_func = (cp_func_t *)cp_manager_get_sub_module(socket->manager->app, cp_player_manager_type_func, cp_player_module_type_ptp_func);
	if (!tmp_ptp_func) {
		cp_module_log(error, socket, "ptp_filter_process_ptp_func() error. not found ptp func.");
		return -1;
	}

	//写模块
	ret_int = cp_write_module(tmp_ptp_func, &group_ts, cp_sizeof(cp_group_timestamp_t *), cp_player_func_flag_group_timestamp);
	if (ret_int) {
		cp_module_log(error, socket, "ptp_filter_process_ptp_func() error. write ptp func module error.");
		return -1;
	}

	return 0;
}
