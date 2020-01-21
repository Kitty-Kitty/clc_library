/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_player_func.h"
#include "cp_third_party.h"
#include "cp_include.h"


CP_EXTERN_GLOBAL_APP()


cp_player_func_t *cp_player_func_create();
/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_player_func(cp_player_func_t *player_func, const cp_player_func_info_t *player_func_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_player_func(cp_player_func_t *player_func, const cp_player_func_info_t *player_func_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_player_func(cp_player_func_t *player_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_player_func(cp_player_func_t *player_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_player_func(cp_player_func_t *player_func);
/*退出模块*/
cp_int32_t exit_player_func(cp_player_func_t *player_func);
/*设置模块参数*/
cp_int32_t set_option_player_func(cp_player_func_t *player_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_player_func(cp_player_func_t *player_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_player_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_player_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_player_func(cp_player_func_t *cp_s, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_player_func(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_player_func(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_player_func(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_player_func(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_player_func(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_player_func(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_player_func(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

cp_int32_t player_func_data_integrity
(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t status);

cp_int32_t player_func_process_socket_data(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t status);

cp_player_func_t* create_player_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_player_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_player_func_t					*tmp_module = CP_NULL;


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}
	CP_MODULE_MALLOC(tmp_module, manager, cp_player_func_t);
	if (tmp_module) {
		tmp_module->pool = cp_create_pool();
		if (!tmp_module->pool) {
			CP_MODULE_FREE(tmp_module);
			return CP_NULL;
		}
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, player_func);
	return tmp_module;
}

cp_int32_t destory_player_func(cp_player_func_manager_t *manager, cp_player_func_t* player_func)
{
	if (!manager || player_func) {
		return -1;
	}
	if (player_func->pool) {
		cp_destroy_pool(player_func->pool);
		player_func->pool = CP_NULL;
	}
	CP_MODULE_FREE(player_func);
	return 0;
}

/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_player_func(cp_player_func_t *player_func, const cp_player_func_info_t *player_func_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_player_func(cp_player_func_t *player_func, const cp_player_func_info_t *player_func_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_player_func(cp_player_func_t *player_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_player_func(cp_player_func_t *player_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_player_func(cp_player_func_t *player_func)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_player_func(cp_player_func_t *player_func)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_player_func(cp_player_func_t *player_func, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_player_func(cp_player_func_t *player_func, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_player_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_player_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_player_func(cp_player_func_t *cp_s, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_player_func(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_player_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_player_func(cp_socket_t *socket, cp_int32_t status)
{
	cp_buf_t				*buf;
	cp_int32_t				tmp_read_length = 0;


	//只有tcp读头，其他的报文读一个报文
	if (CP_SOCKET_CHECK_TYPE(socket, CP_SOCKET_TCP)) {
		tmp_read_length = CSS_GMP_GMPH_SEMH_LEN;
	} else {
		tmp_read_length = 1024;
	}
	//分配空间
	buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + tmp_read_length);
	if (!buf) {
		return -1;
	}
	cp_assemble_buf_t(buf, (cp_uchar_t*)buf + cp_sizeof(cp_buf_t), tmp_read_length);
	pc_clear_buf_t(buf);

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, player_func);
	cp_read_socket(socket, tmp_read_length, buf, 0);
	return 0;
}

cp_int32_t close_cb_player_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_player_func(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;
	


	//判断数据是否接收完全
	ret_int = player_func_process_socket_data(socket, nread, buf, status);
	if (!(socket->flag & CP_SOCKET_FLAG_LISTEN)) {
		cp_close_socket(socket);
		cp_manager_destory_module(socket->manager, socket);
	}

	return ret_int;
}

cp_int32_t write_cb_player_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_player_func(socket, status);
}

cp_int32_t error_cb_player_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t player_func_data_integrity
(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t status)
{
	gmp_gmph_bmh_t						*tmp_bmh = CP_NULL;
	gmp_gmph_semh_t						*tmp_semh = CP_NULL;
	cp_session_t						*tmp_session = CP_NULL;
	cp_buf_t							*tmp_buf = (cp_buf_t*)buf;


	//协议头还没有收全
	if (cp_length_buf_t(tmp_buf) < CSS_GMP_GMPH_SEMH_LEN) {
		return CP_FUNC_STATUS_READ_AGAIN;
	}
	//数据内容没有收完
	tmp_bmh = (gmp_gmph_bmh_t*)cp_get_buf_t(tmp_buf);
	if (gmp_gmph_emh_type_semh == tmp_bmh->emht) {
		tmp_semh = (gmp_gmph_semh_t*)tmp_bmh;
		if (cp_length_buf_t(tmp_buf) < (cp_int32_t)(tmp_semh->length + CSS_GMP_GMPH_SEMH_LEN)) {
			return CP_FUNC_STATUS_MATCH | CP_FUNC_STATUS_READ_AGAIN;
		}
		//操作成功返回
		return CP_FUNC_STATUS_MATCH | CP_FUNC_STATUS_SUCCESSORERROR;
	}
	return 0;
}

cp_int32_t player_func_process_socket_data(cp_socket_t *socket, cp_int32_t nread, const cp_buf_t* buf, cp_int32_t status)
{
	cp_session_t				*tmp_session;
	cp_session_info_t			tmp_session_info;
	cp_int32_t					ret_int = 0;



	//判断数据是否接收完全
	ret_int = player_func_data_integrity(socket, nread, buf, status);
	if ((ret_int & CP_FUNC_STATUS_MATCH) && (ret_int & CP_FUNC_STATUS_SUCCESSORERROR)) {
		if (!cp_app->module_manager_array[cp_module_manager_type_session]) {
			return CP_FUNC_STATUS_MATCH;
		}
		cp_memset(&tmp_session_info, 0, cp_sizeof(cp_session_info_t));
		//tmp_session_info.type = 0;
		//创建一个session处理数据
		tmp_session = (cp_session_t*)cp_manager_create_module(cp_app->module_manager_array[cp_module_manager_type_session],
			&tmp_session_info);
		if (tmp_session) {
			ret_int = cp_init_module(tmp_session, &tmp_session_info);
			if (!ret_int) {
				CP_SESSION_SET_SOCKET_INFO(tmp_session, socket, buf, nread, status);
				//开始进行业务处理
				ret_int = cp_open_module(tmp_session, &tmp_session_info);
				if (!ret_int) {
					cp_manager_destory_module(tmp_session->manager, tmp_session);
					return CP_FUNC_STATUS_MATCH | CP_FUNC_STATUS_SUCCESSORERROR;
				}
			}
			cp_manager_destory_module(tmp_session->manager, tmp_session);
		}
	}
	return CP_FUNC_STATUS_MATCH;
}
