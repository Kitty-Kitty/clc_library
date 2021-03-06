/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_fusion_player_func.h"
#include "cp_third_party.h"
#include "cp_include.h"


//#define CP_FUSION_PLAYER_FUNC_DEBUG_MEMORY					1


#if defined(CP_FUSION_PLAYER_FUNC_DEBUG_MEMORY)
#include <crtdbg.h>
#endif


CP_EXTERN_GLOBAL_APP()


cp_fusion_player_func_t *cp_fusion_player_func_create();
/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_fusion_player_func(cp_fusion_player_func_t *player_func, const cp_fusion_player_func_info_t *player_func_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_fusion_player_func(cp_fusion_player_func_t *player_func, const cp_fusion_player_func_info_t *player_func_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_fusion_player_func(cp_fusion_player_func_t *player_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_fusion_player_func(cp_fusion_player_func_t *player_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_fusion_player_func(cp_fusion_player_func_t *player_func);
/*退出模块*/
cp_int32_t exit_fusion_player_func(cp_fusion_player_func_t *player_func);
/*设置模块参数*/
cp_int32_t set_option_fusion_player_func(cp_fusion_player_func_t *player_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_fusion_player_func(cp_fusion_player_func_t *player_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_fusion_player_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_fusion_player_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_fusion_player_func(cp_fusion_player_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_fusion_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_fusion_player_func(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_fusion_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

cp_int32_t player_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t player_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_fusion_player_func_t* create_fusion_player_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_fusion_player_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_fusion_player_func_t					*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_fusion_player_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, fusion_player_func);

	return tmp_module;
}

cp_int32_t destroy_fusion_player_func(cp_fusion_player_func_manager_t *manager, cp_fusion_player_func_t* player_func)
{
	if (!manager || !player_func) {
		return -1;
	}
	cp_free_module(player_func);
	return 0;
}

/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_fusion_player_func(cp_fusion_player_func_t *player_func, const cp_fusion_player_func_info_t *player_func_info)
{
	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_fusion_player_func(cp_fusion_player_func_t *player_func, const cp_fusion_player_func_info_t *player_func_info)
{
	player_func->pftm = make_fusion_player_func_thread_manager((cp_func_t*)player_func);
	if (!player_func->pftm) {
		cp_module_log(error, player_func, "open_fusion_player_func() error, make_fusion_player_func_thread_manager() failed");
		return -1;
	}
	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_fusion_player_func(cp_fusion_player_func_t *player_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_fusion_player_func(cp_fusion_player_func_t *player_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	cp_socket_t								*tmp_socket = CP_NULL;
	cp_fusion_player_func_chunk_t						*tmp_pfc = CP_NULL;



	if (cp_fusion_player_func_flag_socket_point == flag &&
		len == cp_sizeof(cp_socket_t*)) {
		tmp_socket = (cp_socket_t *)(*buf);
		if (tmp_socket) {
			push_semh_fusion_player_func_chunk(player_func->pftm, tmp_socket, (gmp_gmph_semh_t*)(cp_buf_get_pos(tmp_socket->buf)));
		}
	}
	return 0;
}
/*关闭模块*/
cp_int32_t close_fusion_player_func(cp_fusion_player_func_t *player_func)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_fusion_player_func(cp_fusion_player_func_t *player_func)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_fusion_player_func(cp_fusion_player_func_t *player_func, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_fusion_player_func(cp_fusion_player_func_t *player_func, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_fusion_player_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_fusion_player_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_fusion_player_func(cp_fusion_player_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_fusion_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_fusion_player_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status)
{
	cp_buf_t				*buf;
	cp_int32_t				tmp_read_length = 0;
	cp_fusion_player_info_t		*tmp_player_info = (cp_fusion_player_info_t *)(socket->manager->app->app_info);


	//只有tcp读头，其他的报文读一个报文
	if (CP_SOCKET_CHECK_TYPE(socket, cp_socket_type_tcp)) {
		tmp_read_length = CSS_GMP_GMPH_SEMH_LEN;
		//分配空间
		buf = cp_palloc(socket->pool, cp_sizeof(cp_buf_t) + CSS_GMP_GMPH_SEMH_LEN);
		if (!buf) {
			return -1;
		}
		cp_buf_assemble(buf, (cp_uchar_t*)buf + cp_sizeof(cp_buf_t), tmp_read_length);
		cp_buf_memzero(buf);
	}
	else {
		tmp_read_length = (cp_int32_t)tmp_player_info->device_info->network.packet_length;
		buf = create_a_semh_socket_buffer(socket->pool, socket->data, tmp_read_length);
		if (!buf) {
			return -1;
		}
	}

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, player_func);
	cp_read_socket(socket, buf, tmp_read_length, 0);
	return 0;
}

cp_int32_t close_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_fusion_player_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;


	//判断数据是否接收完全
	ret_int = player_func_process_socket_data(socket, buf, nread, status);
	if (!(socket->flag & CP_SOCKET_FLAG_LISTEN)) {
		cp_close_socket(socket);
		cp_manager_destroy_module(socket->manager, socket);
	}

 	if (CP_SOCKET_CHECK_TYPE(socket, cp_socket_type_udp) && socket->buf) {
 		cp_buf_clear(socket->buf);
 	}
	return ret_int;
}

cp_int32_t write_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_fusion_player_func(socket, status);
}

cp_int32_t error_cb_fusion_player_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t player_func_data_integrity
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

cp_int32_t player_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_session_t				*tmp_session;
	cp_session_manager_t		*tmp_sm = CP_NULL;
	cp_session_info_t			tmp_session_info = { 0, };
	cp_module_manager_info_t	tmp_mm_info = { 0, };
	cp_int32_t					ret_int = 0;
#if defined(CP_FUSION_PLAYER_FUNC_DEBUG_MEMORY)
	_CrtMemState				s1, s2, s3;
#endif


	//判断数据是否接收完全
	ret_int = player_func_data_integrity(socket, buf, nread, status);
	if ((ret_int & cp_func_status_match) && (ret_int & cp_func_status_successorerror)) {
		//先获取session manager 管理器
		tmp_mm_info.type = CP_MODULE_MANAGER_TYPE_SESSION(1);
		tmp_sm = (cp_session_manager_t*)cp_get_manager(socket->manager->app, &tmp_mm_info);
		if (!tmp_sm) {
			return cp_func_status_match;
		}

#if defined(CP_FUSION_PLAYER_FUNC_DEBUG_MEMORY)
		_CrtMemCheckpoint(&s1);
		//_CrtDumpMemoryLeaks();
#endif
		
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

#if defined(CP_FUSION_PLAYER_FUNC_DEBUG_MEMORY)
					//_CrtDumpMemoryLeaks();
					_CrtMemCheckpoint(&s2);
					if (_CrtMemDifference(&s3, &s1, &s2))
						_CrtMemDumpStatistics(&s3);
#endif

					return cp_func_status_match | cp_func_status_successorerror;
				}
			}
			cp_manager_destroy_module(tmp_session->manager, tmp_session);
		}
		//_CrtDumpMemoryLeaks();
	}
	return cp_func_status_match;
}
