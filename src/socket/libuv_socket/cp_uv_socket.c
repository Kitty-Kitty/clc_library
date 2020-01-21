/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#include <assert.h>
#include "cp_uv_socket.h"
#include "cp_uv_socket_printf.h"


//set current local address
#define CP_UV_SOCKET_LOCAL_ADDRESS											"0.0.0.0"
#define CP_UV_SOCKET_DEFAULT_MULTICAST_TTL									64
//get socket handle type
#define CP_GET_UV_SOCKET_TYPE(uv_socket)									(uv_socket->handle->type)
//check handle type is UV_UDP/UV_TCP
#define	CP_CHECK_UV_SOCKET_TYPE(uv_socket, handle_type)						(handle_type == CP_GET_UV_SOCKET_TYPE(uv_socket))



/*模块创建接口，表示创建一个模块*/
cp_int32_t init_uv_socket(cp_uv_socket_t *uv_socket, const cp_uv_socket_info_t *info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_uv_socket(cp_uv_socket_t *uv_socket, const cp_uv_socket_info_t *info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_uv_socket(cp_uv_socket_t *uv_socket, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_uv_socket(cp_uv_socket_t *uv_socket, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_uv_socket(cp_uv_socket_t *uv_socket);
/*退出模块*/
cp_int32_t exit_uv_socket(cp_uv_socket_t *uv_socket);
/*设置模块参数*/
cp_int32_t set_option_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t optname, cp_void_t* optval);

cp_int32_t listen_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_uv_socket(cp_uv_socket_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_uv_socket(cp_uv_socket_t *uv_socket);																/*关闭连接*/
cp_int32_t connect_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status);											/*错误回调函数*/



cp_inline cp_int32_t uv_socket_set_handle(cp_uv_socket_t *uv_socket, uv_loop_t *loop, uv_stream_t *handle, cp_socket_type_e st);
cp_inline cp_uv_socket_t* uv_socket_malloc_new(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_uv_socket_info_t *info);
cp_inline cp_uv_socket_t *uv_socket_create_new(cp_uv_socket_t *uv_socket, uv_stream_t *handle, cp_socket_type_e st);
cp_static void uv_socket_accept_connect_cb(uv_stream_t* server, cp_int32_t status);
cp_static void uv_socket_read_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
cp_static void uv_socket_after_tcp_read(uv_stream_t *handle, ssize_t nread, const uv_buf_t* buf);
cp_static void uv_socket_after_udp_read(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf,
	const struct sockaddr* addr,
	unsigned flags);
cp_static void uv_socket_read_timer_cb(uv_timer_t* handle);
cp_static void uv_socket_write_timer_cb(uv_timer_t* handle);
cp_inline cp_int32_t uv_socket_init_timer(cp_uv_socket_t *uv_socket, uv_loop_t *loop);
cp_inline cp_int32_t uv_socket_start_timer(cp_uv_socket_t *uv_socket, uv_loop_t *loop);
cp_inline cp_int32_t listen_tcp_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr);
cp_inline cp_int32_t listen_udp_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr);
cp_inline cp_int32_t listen_udp_multicast_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr);
cp_static cp_int32_t read_s_tcp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread);
cp_static cp_int32_t read_s_udp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread);
cp_static cp_int32_t write_s_tcp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread);
cp_static cp_int32_t write_s_udp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr);
cp_static cp_void_t uv_socket_connect_cb(uv_connect_t *conn, cp_int32_t status);
cp_static cp_void_t uv_socket_write_cb(uv_write_t* req, cp_int32_t status);
cp_static cp_void_t uv_socket_close_cb(uv_handle_t* handle);
cp_static cp_void_t uv_socket_timer_close_cb(uv_handle_t* handle);
cp_static void uv_socket_error_cb(cp_uv_socket_t *uv_socket, cp_int32_t status, const cp_char_t* msg);
//设置uv_socket的详细信息
cp_int32_t option_uv_socket_set_print_information(cp_uv_socket_t *uv_socket, cp_int32_t optname, const cp_void_t* optval);
cp_inline cp_int32_t uv_socket_set_native_socket(cp_uv_socket_t *uv_socket);


cp_uv_socket_t* create_uv_socket(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_uv_socket_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_uv_socket_t						*tmp_module = CP_NULL;
	cp_uv_socket_manager_t				*tmp_manager = (cp_uv_socket_manager_t*)manager;



	tmp_module = uv_socket_malloc_new(register_info, manager, info);
	if (!tmp_module) {
		return CP_NULL;
	}
	tmp_module->socket_type = info->socket_type;
	ret_int = uv_socket_set_handle(tmp_module, &(tmp_manager->loop), CP_NULL, info->socket_type);
	if (ret_int) {
		return CP_NULL;
	}

	return tmp_module;
}

cp_int32_t destroy_uv_socket(cp_socket_manager_t *manager, cp_uv_socket_t* uv_socket)
{
	if (!manager || !uv_socket) {
		return -1;
	}
	//close socket
	CP_MODULE_UNSET_STATUS(uv_socket, cp_module_status_create);
	close_uv_socket(uv_socket);
	return 0;
}


/*模块创建接口，表示创建一个模块*/
cp_int32_t init_uv_socket(cp_uv_socket_t *uv_socket, const cp_uv_socket_info_t *info)
{
	cp_mutex_init(&uv_socket->free_mutex);

	cp_module_log(info, uv_socket,
		"init uv_socket [libuv-v%s] success!",
		uv_version_string());

	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_uv_socket(cp_uv_socket_t *uv_socket, const cp_uv_socket_info_t *info)
{
	return 0;
}

/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_uv_socket(cp_uv_socket_t *uv_socket, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_uv_socket(cp_uv_socket_t *uv_socket, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}

/*关闭模块*/
cp_int32_t close_uv_socket(cp_uv_socket_t *uv_socket)
{
	if (!uv_socket) {
		return -1;
	}

	if (uv_is_active((uv_handle_t *)&uv_socket->read_timer)) {
		//uv_close((uv_handle_t *)&uv_socket->read_timer, uv_socket_timer_close_cb);
		uv_close((uv_handle_t *)&uv_socket->read_timer, CP_NULL);
	}

	if (uv_is_active((uv_handle_t *)&uv_socket->write_timer)) {
		//uv_close((uv_handle_t *)&uv_socket->write_timer, uv_socket_timer_close_cb);
		uv_close((uv_handle_t *)&uv_socket->write_timer, CP_NULL);
	}
	if (uv_is_active((uv_handle_t*)uv_socket->handle)) {
		if (CP_CHECK_UV_SOCKET_TYPE(uv_socket, UV_UDP)) {
			uv_udp_recv_stop((uv_udp_t*)uv_socket->handle);
		}
		else if (CP_CHECK_UV_SOCKET_TYPE(uv_socket, UV_TCP)) {
			uv_read_stop((uv_stream_t*)uv_socket->handle);
		}
		uv_close((uv_handle_t*)uv_socket->handle, uv_socket_close_cb);
	}

	return 0;
}

/*退出模块*/
cp_int32_t exit_uv_socket(cp_uv_socket_t *uv_socket)
{
	return 0;
}

/*设置模块参数*/
cp_int32_t set_option_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t optname, const cp_void_t* optval)
{
	int							ret_int = 0;
	int							tmp_optval = 0;


	if (optname & cp_module_option_set_print_information) {
		return option_uv_socket_set_print_information(uv_socket, optname, optval);
	}

	if (optname & cp_socket_set_option_membership) {
		if (cp_socket_type_multicast == uv_socket->socket_type) {
			/* join the multicast channel */
			ret_int = uv_udp_set_membership((uv_udp_t *)(uv_socket->handle), (cp_char_t*)optval, NULL, UV_JOIN_GROUP);
			if (ret_int == UV_ENODEV) {
				cp_uv_socket_log(error, uv_socket,
					"set member ship option error. no multicast support, addr[%s]",
					(cp_char_t*)optval);
			}
			else {
				return 0;
			}
		}
	}

	if (optname & cp_socket_set_option_write_sync) {
		if (*((cp_int32_t*)optval)) {
			uv_socket->rw_flag |= optname;
#if 0
			if (uv_socket->native_sock) {
				ret_int = uv__nonblock(uv_socket->native_sock, 0);
				if (ret_int) {
					cp_module_log(error, uv_socket,
						"uv__nonblock() socket[%d] failed.",
						uv_socket->native_sock);
				}
			}
#endif
		}
		else {
			uv_socket->rw_flag &= (~optname);
		}

		return 0;
	}

	return 0;
}

/*获取模块参数*/
cp_int32_t get_option_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t optname, cp_void_t* optval)
{
	int							ret_int = 0;


	switch (optname)
	{
		case cp_module_option_get_print_information:
		{
			*((cp_char_t**)optval) = uv_socket->si;
		}
		break;
		default:
		{
			if (optname & cp_socket_get_option_is_writable) {
				if (cp_socket_type_multicast == uv_socket->socket_type) {
					/* join the multicast channel */
					ret_int = uv_udp_set_membership((uv_udp_t *)(uv_socket->handle), (cp_char_t*)optval, NULL, UV_JOIN_GROUP);
					if (ret_int == UV_ENODEV) {
						cp_uv_socket_log(error, uv_socket,
							"set member ship option error. no multicast support, addr[%s]",
							(cp_char_t*)optval);
					}
					else {
						return 0;
					}
				}
			}
			else if (optname & cp_socket_get_option_is_writable) {
			}

			return -1;
		}
		break;
	}

	return 0;
}

/*打开监听*/
cp_int32_t listen_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr)
{
	cp_int32_t				ret_int = 1;



	if (uv_socket && addr) {
		uv_socket->local_addr = *addr;
	}

	switch (uv_socket->socket_type) {
		case cp_socket_type_tcp: {
			ret_int = listen_tcp_uv_socket(uv_socket, addr);
		}
								 break;
		case cp_socket_type_udp: {
			ret_int = listen_udp_uv_socket(uv_socket, addr);
		}
								 break;
		case cp_socket_type_multicast: {
			ret_int = listen_udp_multicast_uv_socket(uv_socket, addr);
		}
									   break;
		case UV_FILE:
		default: {
			//abort();
			return -1;
		}
	}

	if (!ret_int) {
		uv_socket->flag |= CP_SOCKET_FLAG_LISTEN;
	}

	option_uv_socket_set_print_information(uv_socket, cp_module_option_set_print_information, CP_NULL);
	return ret_int;
}

/*开始连接*/
cp_int32_t connect_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr)
{
	cp_int32_t						ret_int = -1;
	cp_uv_socket_manager_t			*tmp_manager = (cp_uv_socket_manager_t*)uv_socket->manager;


	if (!CP_CHECK_UV_SOCKET_TYPE(uv_socket, UV_TCP)) {
		cp_uv_socket_log(warn, uv_socket, "connect error. socket type not [tcp]");
		return -1;
	}

	if (!uv_socket->connect_req)	{
		uv_socket->connect_req = (uv_connect_t*)cp_palloc(uv_socket->pool, cp_sizeof(uv_connect_t));
		if (!uv_socket->connect_req) {
			cp_uv_socket_log(warn, uv_socket, "malloc uv_connect_t error");
			return -1;
		}
		uv_socket->connect_req->data = uv_socket;
	}

	ret_int = uv_tcp_init(&(tmp_manager->loop), (uv_tcp_t*)(uv_socket->handle));
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"uv_tcp_init() error. [%s:%s]",
			uv_err_name(ret_int),
			uv_strerror(ret_int));
		return ret_int;
	}

	ret_int = uv_tcp_connect(uv_socket->connect_req, (uv_tcp_t *)(uv_socket->handle), (const struct sockaddr *) addr, uv_socket_connect_cb);
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"uv_tcp_init() error. [%s:%s]",
			uv_err_name(ret_int),
			uv_strerror(ret_int));
		return ret_int;
	}

	uv_socket_set_native_socket(uv_socket);

	return 0;
}

/*读数据*/
cp_int32_t read_s_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	switch (uv_socket->socket_type) {
		case cp_socket_type_tcp:
		{
			return read_s_tcp_uv_socket(uv_socket, buf, nread);
		}
		break;
		case cp_socket_type_udp:
		case cp_socket_type_multicast:
		{
			return read_s_udp_uv_socket(uv_socket, buf, nread);
		}
		break;
		case UV_FILE:
		default:
			//ASSERT(0 && "Bad serverType");
			abort();
	}

	return 0;
}

/*写数据*/
cp_int32_t write_s_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	switch (CP_GET_UV_SOCKET_TYPE(uv_socket)) {
		case UV_TCP:
		{
			return write_s_tcp_uv_socket(uv_socket, buf, nread);
		}
		break;
		case UV_UDP:
		{
			return write_s_udp_uv_socket(uv_socket, buf, nread, remote_addr);
		}
		break;
		case UV_FILE:
		default:
			//ASSERT(0 && "Bad serverType");
			//abort();
			return -1;
	}

	return 0;
}

/*关闭连接*/
cp_int32_t close_s_uv_socket(cp_uv_socket_t *uv_socket)
{
	return close_uv_socket(uv_socket);
}

/*连接回调函数*/
cp_int32_t connect_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status)
{
	option_uv_socket_set_print_information(uv_socket, cp_module_option_set_print_information, CP_NULL);
	return cp_process_connect_cb((cp_socket_t *)uv_socket, status);
}

/*关闭回调函数*/
cp_int32_t close_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status)
{
	return cp_process_close_cb((cp_socket_t *)uv_socket, status);
}

/*读回调函数*/
cp_int32_t read_cb_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return cp_process_read_cb((cp_socket_t *)uv_socket, buf, nread, status);
}

/*写回调函数*/
cp_int32_t write_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status)
{
	return cp_process_write_cb((cp_socket_t *)uv_socket, status);
}

/*错误回调函数*/
cp_int32_t error_cb_uv_socket(cp_uv_socket_t *uv_socket, cp_int32_t status)
{
	return cp_process_error_cb((cp_socket_t *)uv_socket, status);
}

//设置handle
cp_int32_t uv_socket_set_handle(cp_uv_socket_t *uv_socket, uv_loop_t *loop, uv_stream_t *handle, cp_socket_type_e st)
{
	cp_int32_t							ret_int;

	if (!uv_socket) {
		return -1;
	}

	switch (st)
	{
		case cp_socket_type_udp:
		case cp_socket_type_multicast:
		{
			if (!uv_socket->handle) {
				uv_socket->handle = (uv_handle_t*)cp_palloc(uv_socket->pool, sizeof(uv_udp_t));
			}

			if (handle) {
				uv_socket->handle = (uv_handle_t *)handle;
			}

			uv_socket->req = (uv_req_t *)cp_palloc(uv_socket->pool, sizeof(uv_udp_send_t));
			if (uv_socket->req) {
				uv_socket->req->data = uv_socket;
			}

			uv_socket->handle->type = UV_UDP;

			ret_int = uv_udp_init(loop, (uv_udp_t*)(uv_socket->handle));
			if (ret_int) {
				/* TODO: Error codes */
				cp_uv_socket_log(error, uv_socket,
					"socket creation error. [%s:%s]",
					uv_err_name(ret_int),
					uv_strerror(ret_int));
				return -1;
			}
		}
		break;
		case cp_socket_type_tcp:
		{
			if (!uv_socket->handle) {
				uv_socket->handle = (uv_handle_t*)cp_palloc(uv_socket->pool, sizeof(uv_tcp_t));
			}
			if (handle) {
				uv_socket->handle = (uv_handle_t *)handle;
			}

			uv_socket->req = (uv_req_t*)cp_palloc(uv_socket->pool, sizeof(uv_write_t));
			if (uv_socket->req) {
				uv_socket->req->data = uv_socket;
			}
			uv_socket->handle->type = UV_TCP;

			ret_int = uv_tcp_init(loop, (uv_tcp_t*)(uv_socket->handle));
			if (ret_int) {
				/* TODO: Error codes */
				cp_uv_socket_log(error, uv_socket,
					"socket creation error. [%s:%s]",
					uv_err_name(ret_int),
					uv_strerror(ret_int));
				return -2;
			}
		}
		break;
		default:
		{
			return -3;
		}
		break;
	}
	//check handle
	if (!uv_socket->handle) {
		return -4;
	}
	//init timer
	ret_int = uv_socket_init_timer(uv_socket, loop);
	if (ret_int) {
		return ret_int;
	}
	//create cp_uv_socket_t
	if (uv_socket->handle) {
		uv_socket->handle->data = uv_socket;
	}
	return 0;
}

//释放handle
cp_int32_t uv_socket_unset_handle(cp_uv_socket_t *uv_socket)
{
	cp_int32_t							ret_int;

	if (!uv_socket) {
		return -1;
	}

	if (uv_socket->req) {
		ret_int = cp_pfree(uv_socket->pool, uv_socket->req);
		if (!ret_int) {
			uv_socket->req = CP_NULL;
		}

	}

	if (!uv_socket->handle) {
		ret_int = cp_pfree(uv_socket->pool, uv_socket->handle);
		if (!ret_int) {
			uv_socket->handle = CP_NULL;
		}
	}

	return 0;
}

cp_uv_socket_t* uv_socket_malloc_new(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_uv_socket_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_uv_socket_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}
	tmp_module = cp_malloc_module(manager, cp_uv_socket_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_SOCKET_MODULE_SET_HANDLERS(tmp_module, uv_socket);
	return tmp_module;
}

cp_int32_t uv_socket_free(cp_socket_manager_t *manager, cp_uv_socket_t* uv_socket)
{
	cp_int32_t						tmp_ret_int = -1;



	if (!manager || !uv_socket) {
		return tmp_ret_int;
	}

	cp_mutex_lock(&uv_socket->free_mutex);

#if 0
	if (!CP_MODULE_GET_STATUS(uv_socket, cp_module_status_create)) {
		if (!uv_is_active((uv_handle_t *)&uv_socket->read_timer) &&
			!uv_is_active((uv_handle_t *)&uv_socket->write_timer) &&
			!uv_is_active((uv_handle_t*)uv_socket->handle)) {
			//释放handle数据
			uv_socket_unset_handle(uv_socket);
			//cp_free_module(uv_socket);
			tmp_ret_int = 0;
		}
	}
#endif

	if (!CP_MODULE_GET_STATUS(uv_socket, cp_module_status_create)) {
		if (!uv_is_active((uv_handle_t*)uv_socket->handle)) {
			//释放handle数据
			uv_socket_unset_handle(uv_socket);
			//cp_free_module(uv_socket);
			tmp_ret_int = 0;
		}
	}

	cp_mutex_unlock(&uv_socket->free_mutex);

	if (!tmp_ret_int) {
		cp_free_module(uv_socket);
	}

	return tmp_ret_int;
}

cp_uv_socket_t *uv_socket_create_new(cp_uv_socket_t *uv_socket, uv_stream_t *handle, cp_socket_type_e st)
{
	cp_int32_t									ret_int = 0;
	cp_uv_socket_info_t							tmp_info = { 0, };
	cp_uv_socket_t								*tmp_uv_socket = CP_NULL;
	cp_uv_socket_manager_t						*tmp_manager = (cp_uv_socket_manager_t*)uv_socket->manager;


	//创建socket
	tmp_info.socket_type = st;
	tmp_uv_socket = (cp_uv_socket_t*)cp_create_module(&uv_socket->register_info, tmp_manager, &tmp_info);
	if (!tmp_uv_socket) {
		return tmp_uv_socket;
	}

	//初始化socket
	ret_int = cp_init_module(tmp_uv_socket, &tmp_info);
	if (ret_int) {
		cp_destroy_module(tmp_manager, tmp_uv_socket);
		return CP_NULL;
	}

	//设置socket
	ret_int = uv_socket_set_handle(tmp_uv_socket, &(tmp_manager->loop), handle, st);
	if (ret_int) {
		return CP_NULL;
	}

	return tmp_uv_socket;
}

cp_static void uv_socket_accept_connect_cb(uv_stream_t* server, cp_int32_t status) {
	cp_int32_t						ret_int;
	cp_uv_socket_t					*tmp_new_uv_socket = NULL;
	cp_uv_socket_t					*tmp_uv_socket = server->data;



	if (status != 0) {
		cp_uv_socket_log(error, tmp_uv_socket,
			"accept callback error. [%s:%s]",
			uv_err_name(status),
			uv_strerror(status));
		return;
	}

	switch (server->type) {
		case UV_TCP:
		{
			tmp_new_uv_socket = uv_socket_create_new(tmp_uv_socket, NULL, cp_socket_type_tcp);
		}
		break;
		case UV_UDP:
		{
			tmp_new_uv_socket = uv_socket_create_new(tmp_uv_socket, NULL, cp_socket_type_udp);
		}
		break;
		default:
			tmp_new_uv_socket = NULL;
	}
	if (!tmp_new_uv_socket)	{
		cp_uv_socket_log(error, tmp_uv_socket,
			"accept callback uv_socket_create_new() error. unknow handle type.");
		return;
	}
	//这里更新了操作句柄
	CP_SOCKET_MODULE_UPDATE_HANDLERS(tmp_uv_socket, tmp_new_uv_socket);

	uv_socket_start_timer(tmp_new_uv_socket, server->loop);

	ret_int = uv_accept(server, (uv_stream_t *)(tmp_new_uv_socket->handle));
	if (tmp_new_uv_socket->connect_cb)	{
		tmp_new_uv_socket->connect_cb((cp_socket_t *)tmp_new_uv_socket, 0);
	}
}

cp_static void uv_socket_read_alloc(uv_handle_t* handle,
	size_t suggested_size,
	uv_buf_t* buf) {

	cp_uv_socket_t *tmp_uv_socket = (cp_uv_socket_t *)handle->data;



	if (!tmp_uv_socket->buf) {
		//cp_buf_create(tmp_uv_socket->buf, suggested_size);
		cp_uv_socket_log(error, tmp_uv_socket,
			"uv_socket_read_alloc() socket type[%d] buf is null error.",
			handle->type);
		return;
	}

	buf->base = cp_buf_get_last(tmp_uv_socket->buf);
	buf->len = cp_buf_get_free_size(tmp_uv_socket->buf);

	if (!buf->len) {
		cp_uv_socket_log(error, tmp_uv_socket,
			"buf_len[%d] error.", buf->len);

		//默认的处理方法是清空缓存中的数据
		cp_buf_clear(tmp_uv_socket->buf);
		buf->len = cp_buf_get_free_size(tmp_uv_socket->buf);
	}
}

cp_static void uv_socket_after_tcp_read(uv_stream_t *handle,
	ssize_t nread,
	const uv_buf_t* buf) {

	cp_uv_socket_t *tmp_uv_socket = (cp_uv_socket_t *)handle->data;


	if (buf->len <= 0) {
		cp_uv_socket_log(error, tmp_uv_socket,
			"buf_len[%d] nread[%d] error.",
			buf->len, nread);

		uv_socket_error_cb(tmp_uv_socket, ENOMEM, "[tcp] read [0] Byte error.");
		return;
	}

	cp_buf_position(tmp_uv_socket->buf, nread);
	tmp_uv_socket->read_time = uv_now(handle->loop);
	if (tmp_uv_socket->read_cb) {
		tmp_uv_socket->read_cb((cp_socket_t *)tmp_uv_socket, tmp_uv_socket->buf, nread, 0);
	}
	else {
		cp_uv_socket_log(error, tmp_uv_socket,
			"close now! handle[read_cb] is null.");

		close_s_uv_socket(tmp_uv_socket);
	}
}

cp_static void uv_socket_after_udp_read(uv_udp_t* handle,
	ssize_t nread,
	const uv_buf_t* buf,
	const struct sockaddr* addr,
	unsigned flags) {

	cp_uv_socket_t *tmp_uv_socket = (cp_uv_socket_t *)handle->data;


	if (nread < 0) {
		cp_uv_socket_log(error, tmp_uv_socket,
			"buf_len[%d] nread[%d] addr[0x%x] error.",
			buf->len,
			nread,
			addr);

		//如果udp出现上述错误，则直接停止接收
		uv_udp_recv_stop(handle);
		uv_socket_error_cb(tmp_uv_socket, ENOMEM, "[udp] nread[0] bytes error.");
		close_uv_socket(tmp_uv_socket);

		return;
	}

	if (!nread) {
		if (!addr) {
			return;
		}

		cp_uv_socket_log(warn, tmp_uv_socket,
			"buf_len[%d] nread[%d] warning. remote address[%s].",
			buf->len,
			nread,
			(cp_char_t*)inet_ntoa(((cp_sockaddr_in*)addr)->sin_addr));

		return;
	}

	// 	if (cp_socket_type_multicast == tmp_uv_socket->socket_type) {
	// 		// 		cp_uv_socket_log(notice, tmp_uv_socket,
	// 		// 			"buf_len[%d] nread[%d].",
	// 		// 			buf->len,
	// 		// 			nread);
	// 
	// 		cp_log_printf("--> buf_len[%d] nread[%d].", buf->len, nread);
	// 	}

	cp_buf_position(tmp_uv_socket->buf, nread);
	tmp_uv_socket->read_time = uv_now(handle->loop);
	tmp_uv_socket->remote_addr = *(cp_sockaddr_in *)addr;
	if (tmp_uv_socket->read_cb) {
		tmp_uv_socket->read_cb((cp_socket_t *)tmp_uv_socket, tmp_uv_socket->buf, nread, 0);
	}
}

cp_static void uv_socket_read_timer_cb(uv_timer_t* handle)
{
	cp_uv_socket_t *tmp_uv_socket = CP_NULL;
	cp_uint64_t		tmp_now_time = uv_now(handle->loop);



	tmp_uv_socket = (cp_uv_socket_t *)handle->data;
	if (tmp_now_time - tmp_uv_socket->read_time > tmp_uv_socket->read_timeout) {
		//print error information
#if defined(CP_UV_SOCKET_PRINT_DEBUG_INFO)
		cp_uv_socket_log(info, uv_socket,
			"read time out[%d].",
			tmp_now_time);
#endif

		if (tmp_uv_socket->error_cb) {
			tmp_uv_socket->error_cb((cp_socket_t *)tmp_uv_socket, CP_SOCKET_STATUS_DATA_READ_TIMEOUT);
		}
		else {

		}
	}

}

cp_static void uv_socket_write_timer_cb(uv_timer_t* handle)
{
	cp_uv_socket_t *tmp_uv_socket = CP_NULL;
	cp_uint64_t		tmp_now_time = uv_now(handle->loop);



	tmp_uv_socket = (cp_uv_socket_t *)handle->data;
	if (tmp_now_time - tmp_uv_socket->write_time > tmp_uv_socket->write_timeout) {
		//print error information
#if defined(CP_UV_SOCKET_PRINT_DEBUG_INFO)
		cp_uv_socket_log(info, uv_socket,
			"write time out[%d].",
			tmp_now_time);
#endif

		if (tmp_uv_socket->error_cb) {
			tmp_uv_socket->error_cb((cp_socket_t *)tmp_uv_socket, CP_SOCKET_STATUS_DATA_WRITE_TIMEOUT);
		}
		else {

		}
	}
}

cp_int32_t uv_socket_init_timer(cp_uv_socket_t *uv_socket, uv_loop_t *loop)
{
	cp_int32_t					ret_int = 0;



	uv_socket->read_timeout = CP_SOCKET_DEFAULT_READ_WRITE_TIMEOUT;
	uv_socket->write_timeout = CP_SOCKET_DEFAULT_READ_WRITE_TIMEOUT;
	//init read timer
	ret_int = uv_timer_init(loop, &uv_socket->read_timer);
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"init read_timer error. [%s:%s]",
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		return ret_int;
	}
	uv_socket->read_timer.data = uv_socket;
	//init write timer
	ret_int = uv_timer_init(loop, &uv_socket->write_timer);
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"init write_timer error. [%s:%s]",
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		return ret_int;
	}
	uv_socket->write_timer.data = uv_socket;
	return 0;
}

cp_int32_t uv_socket_start_timer(cp_uv_socket_t *uv_socket, uv_loop_t *loop)
{
	int ret_int;


	//start timer
	ret_int = uv_timer_start(&uv_socket->read_timer,
		uv_socket_read_timer_cb, uv_socket->read_timeout, uv_socket->read_timeout);
	if (ret_int) {
		cp_log_error(uv_socket->logger, "start read timer error. %s",
			uv_err_name(ret_int));
		return ret_int;
	}
	uv_socket->read_time = uv_now(loop);

	ret_int = uv_timer_start(&uv_socket->write_timer,
		uv_socket_write_timer_cb, uv_socket->write_timeout, uv_socket->write_timeout);
	if (ret_int) {
		cp_log_error(uv_socket->logger, "start write timer error. %s",
			uv_err_name(ret_int));
		return ret_int;
	}
	uv_socket->write_time = uv_socket->read_time;
	return 0;
}

cp_int32_t listen_tcp_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr)
{
	cp_int32_t ret_int;


	ret_int = uv_tcp_bind((uv_tcp_t*)(uv_socket->handle), (const struct sockaddr*) addr, 0);
	if (ret_int) {
		/* TODO: Error codes */
		cp_uv_socket_log(error, uv_socket,
			"bind tcp[%s:%d] error. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		return ret_int;
	}
	uv_socket_set_native_socket(uv_socket);

	ret_int = uv_listen((uv_stream_t*)(uv_socket->handle), SOMAXCONN, uv_socket_accept_connect_cb);
	if (ret_int) {
		/* TODO: Error codes */
		cp_uv_socket_log(error, uv_socket,
			"listen tcp[%s:%d] error. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		return ret_int;
	}

	cp_uv_socket_log(notice, uv_socket,
		"listen_tcp[%s:%d] success.",
		(cp_char_t*)inet_ntoa(addr->sin_addr),
		ntohs(addr->sin_port));

	return 0;
}

cp_int32_t listen_udp_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr)
{
	cp_int32_t							ret_int;
	cp_uv_socket_manager_t				*tmp_manager = (cp_uv_socket_manager_t *)uv_socket->manager;

	//init udp listen
	// 	ret_int = uv_udp_init(tmp_manager->loop, (uv_udp_t*)(uv_socket->handle));
	// 	if (ret_int) {
	// 		cp_log_error(uv_socket->logger, "socket udp creation %s", uv_err_name(ret_int));
	// 		return ret_int;
	// 	}
	//	r = uv_udp_open((uv_udp_t*)(uv_socket->handle), sock);

	//bind udp listen
	ret_int = uv_udp_bind((uv_udp_t*)(uv_socket->handle), (const struct sockaddr*) addr, 0);
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"bind udp[%s:%d] error. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		return ret_int;
	}

	cp_uv_socket_log(notice, uv_socket,
		"listen_udp[%s:%d] success.",
		(cp_char_t*)inet_ntoa(addr->sin_addr),
		ntohs(addr->sin_port));

	uv_socket_set_native_socket(uv_socket);
	uv_socket_start_timer(uv_socket, uv_socket->handle->loop);

	//connect callback
	if (uv_socket->connect_cb)	{
		uv_socket->connect_cb((cp_socket_t *)uv_socket, 0);
	}

	return 0;
}

cp_int32_t listen_udp_multicast_uv_socket(cp_uv_socket_t *uv_socket, cp_sockaddr_in *addr)
{
	cp_int32_t							ret_int = 0;
	cp_sockaddr_in						tmp_local_addr = { 0, };


	ret_int = uv_ip4_addr(CP_UV_SOCKET_LOCAL_ADDRESS, ntohs(addr->sin_port), &tmp_local_addr);
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"uv_ip4_addr() error. [%s:%d]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port));

		return ret_int;
	}

	//It is necessary to set the broadcast flag, otherwise you will get an EACCES error
	ret_int = uv_udp_set_broadcast((uv_udp_t*)(uv_socket->handle), 1);
	if (ret_int) {
		cp_uv_socket_log(warn, uv_socket,
			"uv_udp_set_broadcast() warning. no multicast support, addr[%s:%d]. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		//return ret_int;
	}

	//bind udp listen
	ret_int = uv_udp_bind((uv_udp_t*)(uv_socket->handle), (const struct sockaddr*) &tmp_local_addr, 0);
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"bind udp[%s:%d] multicast[%s:%d] error. [%s:%s]",
			(cp_char_t*)inet_ntoa(tmp_local_addr.sin_addr),
			ntohs(addr->sin_port),
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		close_uv_socket(uv_socket);

		return ret_int;
	}

	//set interface
	ret_int = uv_udp_set_multicast_interface((uv_udp_t *)(uv_socket->handle), CP_UV_SOCKET_LOCAL_ADDRESS);
	if (ret_int) {
		cp_uv_socket_log(warn, uv_socket,
			"uv_udp_set_multicast_interface() warning. no multicast support addr[%s:%d]. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		//return ret_int;
	}

	//set ttl
	ret_int = uv_udp_set_multicast_ttl((uv_udp_t *)(uv_socket->handle), CP_UV_SOCKET_DEFAULT_MULTICAST_TTL);
	if (ret_int) {
		cp_uv_socket_log(warn, uv_socket,
			"set ttl option warning. no multicast support addr[%s:%d]. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		//return ret_int;
	}

	//set loop
	ret_int = uv_udp_set_multicast_loop((uv_udp_t *)(uv_socket->handle), 1);
	if (ret_int) {
		cp_uv_socket_log(warn, uv_socket,
			"set loop option warning. no multicast support addr[%s:%d]. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		//return ret_int;
	}

	//join group
	ret_int = uv_udp_set_membership((uv_udp_t *)(uv_socket->handle),
		inet_ntoa(addr->sin_addr), NULL, UV_JOIN_GROUP);
	if (ret_int) {
		cp_uv_socket_log(error, uv_socket,
			"set member ship option error. no multicast support addr[%s:%d]. [%s:%s]",
			(cp_char_t*)inet_ntoa(addr->sin_addr),
			ntohs(addr->sin_port),
			uv_err_name(ret_int),
			uv_strerror(ret_int));

		return ret_int;
	}

	cp_uv_socket_log(notice, uv_socket,
		"listen_udp_multicast[%s:%d] success.",
		(cp_char_t*)inet_ntoa(addr->sin_addr),
		ntohs(addr->sin_port));

	uv_socket_set_native_socket(uv_socket);
	uv_socket_start_timer(uv_socket, uv_socket->handle->loop);

	//connect callback
	if (uv_socket->connect_cb)	{
		uv_socket->connect_cb((cp_socket_t *)uv_socket, 0);
	}

	return 0;
}

cp_int32_t read_s_tcp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread)
{
	cp_int32_t ret_int;


	uv_socket->buf = (cp_buf_t*)buf;
	if (uv_is_readable((uv_stream_t*)(uv_socket->handle))) {
		ret_int = uv_read_start((uv_stream_t*)(uv_socket->handle), uv_socket_read_alloc, uv_socket_after_tcp_read);
		if (ret_int) {
			cp_uv_socket_log(error, uv_socket,
				"uv_read_start() error. [%s:%s]",
				uv_err_name(ret_int),
				uv_strerror(ret_int));

			return ret_int;
		}
	}
	else {
		cp_uv_socket_log(warn, uv_socket,
			"read error. disreadable");
	}

	cp_uv_socket_log(info, uv_socket, "socket read info. read_s_tcp_uv_socket() info.");

	return 0;
}

cp_int32_t read_s_udp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread)
{
	cp_int32_t ret_int;


	uv_socket->buf = (cp_buf_t*)buf;
	ret_int = uv_udp_recv_start((uv_udp_t *)(uv_socket->handle), uv_socket_read_alloc, uv_socket_after_udp_read);
	if (ret_int) {
#if defined(CP_UV_SOCKET_PRINT_DEBUG_INFO)
		cp_uv_socket_log(error, uv_socket,
			"uv_udp_recv_start() error. [%s:%s]",
			uv_err_name(ret_int),
			uv_strerror(ret_int));
#endif
		return ret_int;
	}

	cp_uv_socket_log(info, uv_socket, "socket read info. uv_udp_recv_start() info.");

	return 0;
}

cp_int32_t write_s_tcp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread)
{
	cp_int32_t				ret_int;
	uv_buf_t				tmp_send_bufer = uv_buf_init(cp_buf_get_pos(buf), cp_buf_get_length(buf));



	if (!uv_socket || !buf || !nread) {
		cp_uv_socket_log(error, uv_socket,
			"socket write error. write_s_tcp_uv_socket() error. null point error.");

		return -1;
	}

	if (nread > cp_buf_get_length(buf)) {
		cp_uv_socket_log(error, uv_socket,
			"socket write error. write_s_tcp_uv_socket() error. data length error. nread[%d] more than buffer[%d]",
			nread,
			cp_buf_get_length(buf));

		return -1;
	}

	uv_socket->write_time = uv_now(uv_socket->handle->loop);

	if (uv_socket->rw_flag & cp_socket_set_option_write_sync) {
		//这里使用native socket通信
		ret_int = send(uv_socket->native_sock,
			cp_buf_get_pos(buf),
			nread,
			0);
		if (ret_int != nread) {
			cp_uv_socket_log(error, uv_socket,
				"socket write error. write_s_tcp_uv_socket() error. send() error.");

			return ret_int;
		}
	}
	else {
		ret_int = uv_write((uv_write_t *)uv_socket->req,
			(uv_stream_t *)(uv_socket->handle), &tmp_send_bufer, 1, uv_socket_write_cb);
		if (ret_int) {
			cp_uv_socket_log(error, uv_socket,
				"socket write error. write_s_tcp_uv_socket() error. [%s:%s]",
				uv_err_name(ret_int),
				uv_strerror(ret_int));

			return ret_int;
		}
	}

	return 0;
}

cp_int32_t write_s_udp_uv_socket(cp_uv_socket_t *uv_socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr)
{
	cp_int32_t				ret_int;
	uv_udp_send_t			*tmp_udp_send_p = CP_NULL;
	uv_buf_t				tmp_send_bufer = uv_buf_init(cp_buf_get_pos(buf), cp_buf_get_length(buf));


	if (!uv_socket || !buf || !remote_addr) {
		cp_uv_socket_log(error, uv_socket,
			"socket write error. write_s_udp_uv_socket() error. null point error.");

		return -1;
	}

	if (nread > cp_buf_get_length(buf)) {
		cp_uv_socket_log(error, uv_socket,
			"socket write error. write_s_udp_uv_socket() error. data length error. nread[%d] more than buffer[%d]",
			nread,
			cp_buf_get_length(buf));
		return -1;
	}

	uv_socket->write_time = uv_now(uv_socket->handle->loop);

	if (uv_socket->rw_flag & cp_socket_set_option_write_sync) {
		//这里使用native socket通信
		ret_int = sendto(uv_socket->native_sock,
			cp_buf_get_pos(buf),
			nread,
			0,
			(const struct sockaddr*) remote_addr,
			cp_sizeof(struct sockaddr));
		if (ret_int != nread) {
			cp_uv_socket_log(error, uv_socket,
				"socket write error. write_s_udp_uv_socket() error. sendto() error.");
			return ret_int;
		}
	}
	else {
		//这里UDP每发送一个数据都需要一个uv_udp_send_t数据，如果使用uv_socket->req可能会出错
		tmp_udp_send_p = (uv_udp_send_t *)cp_malloc(sizeof(uv_udp_send_t));
		if (!tmp_udp_send_p) {
			cp_uv_socket_log(error, uv_socket,
				"socket write error. malloc() uv_udp_send_t error. ");
			return -1;
		}

		tmp_udp_send_p->data = uv_socket;
		// 	ret_int = uv_udp_send((uv_udp_send_t *)(uv_socket->req),
		// 		(uv_udp_t *)(uv_socket->handle), &tmp_send_bufer, 1,
		// 		(const struct sockaddr*) remote_addr, (uv_udp_send_cb)uv_socket_write_cb);
		ret_int = uv_udp_send(tmp_udp_send_p,
			(uv_udp_t *)(uv_socket->handle), &tmp_send_bufer, 1,
			(const struct sockaddr*) remote_addr, (uv_udp_send_cb)uv_socket_write_cb);
		if (ret_int) {
			cp_uv_socket_log(error, uv_socket,
				"socket write error. write_s_udp_uv_socket() error. [%s:%s]",
				uv_err_name(ret_int),
				uv_strerror(ret_int));
			return ret_int;
		}
	}

	return 0;
}

cp_void_t uv_socket_connect_cb(uv_connect_t *conn, cp_int32_t status)
{
	cp_uv_socket_t	*tmp_uv_socket = ((cp_uv_socket_t*)(conn->data));
	uv_stream_t		*tcp = conn->handle;


	if (status)	{
		cp_uv_socket_log(error, tmp_uv_socket,
			"socket connect error. uv_socket_connect_cb() error. [%s:%s]",
			uv_err_name(status),
			uv_strerror(status));
		//return status;
	}
	else {
		uv_socket_set_native_socket(tmp_uv_socket);
	}

	if (tmp_uv_socket->connect_cb){
		tmp_uv_socket->connect_cb((cp_socket_t *)tmp_uv_socket, status);
	}
	else {
		cp_uv_socket_log(warn, tmp_uv_socket,
			"uv_socket_connect_cb() connect_cb is null.");
	}

	//return 0;
}

cp_void_t uv_socket_write_cb(uv_write_t* req, cp_int32_t status)
{
	cp_uv_socket_t			*tmp_uv_socket = (cp_uv_socket_t*)(req->data);


	if (status) {
		cp_uv_socket_log(error, tmp_uv_socket,
			"uv_socket_write_cb() error. [%s:%s]",
			uv_err_name(status),
			uv_strerror(status));
	}

	if (CP_CHECK_UV_SOCKET_TYPE(tmp_uv_socket, UV_UDP)) {
		cp_free(req);
	}
	if (tmp_uv_socket->write_cb) {
		//return tmp_uv_socket->write_cb((cp_socket_t *)tmp_uv_socket, status);
		tmp_uv_socket->write_cb((cp_socket_t *)tmp_uv_socket, status);
	}
	//return 0;
}

cp_void_t uv_socket_close_cb(uv_handle_t* handle)
{
	cp_uv_socket_t			*tmp_uv_socket = ((cp_uv_socket_t*)(handle->data));


	if (!uv_socket_free((cp_socket_manager_t*)tmp_uv_socket->manager, tmp_uv_socket)) {
		return;
	}

	if (tmp_uv_socket->close_cb) {
		tmp_uv_socket->close_cb((cp_socket_t *)tmp_uv_socket, 0);
	}
	else {
		cp_uv_socket_log(warn, tmp_uv_socket,
			"uv_socket_close_cb() close_cb is null.");
	}
}

cp_static cp_void_t uv_socket_timer_close_cb(uv_handle_t* handle)
{
	cp_uv_socket_t			*tmp_uv_socket = ((cp_uv_socket_t*)(handle->data));


	uv_socket_free((cp_socket_manager_t*)tmp_uv_socket->manager, tmp_uv_socket);
}

cp_static void uv_socket_error_cb(cp_uv_socket_t *uv_socket, cp_int32_t status, const cp_char_t* msg)
{
	if (uv_socket->error_cb) {
		uv_socket->error_cb((cp_socket_t *)uv_socket, status);
	}
	else {
		cp_log_warn(uv_socket->logger, "%s", msg);
	}
}

cp_int32_t option_uv_socket_set_print_information(cp_uv_socket_t *uv_socket, cp_int32_t optname, const cp_void_t* optval)
{
	cp_int32_t						tmp_name_len = 0;
	struct sockaddr_in				tmp_src_name = { 0, };
	struct sockaddr_in				tmp_dst_name = { 0, };
	cp_char_t						tmp_name_flag[CP_UV_SOCKET_ADDRESS_BUFFER_LENGTH] = { 0, };
	cp_char_t						tmp_src_name_buf[CP_UV_SOCKET_ADDRESS_BUFFER_LENGTH] = { 0, };
	cp_char_t						tmp_dst_name_buf[CP_UV_SOCKET_ADDRESS_BUFFER_LENGTH] = { 0, };



	if (!uv_socket) {
		return -1;
	}

	tmp_name_len = cp_sizeof(struct sockaddr);
	if (CP_CHECK_UV_SOCKET_TYPE(uv_socket, UV_UDP)) {
		uv_udp_getsockname((uv_udp_t*)(uv_socket->handle), (struct sockaddr *)&tmp_src_name, &tmp_name_len);
		tmp_dst_name = uv_socket->remote_addr;
		cp_snprintf(tmp_name_flag, cp_sizeof(tmp_name_flag), "%s", cp_get_socket_type_name(cp_socket_type_udp));
	}
	else if (CP_CHECK_UV_SOCKET_TYPE(uv_socket, UV_TCP)) {
		uv_tcp_getsockname((uv_tcp_t*)(uv_socket->handle), (struct sockaddr *)&tmp_src_name, &tmp_name_len);
		uv_tcp_getpeername((uv_tcp_t*)(uv_socket->handle), (struct sockaddr *)&tmp_dst_name, &tmp_name_len);
		cp_snprintf(tmp_name_flag, cp_sizeof(tmp_name_flag), "%s", cp_get_socket_type_name(cp_socket_type_tcp));
	}
	else {
		return -1;
	}

	cp_snprintf(tmp_src_name_buf, cp_sizeof(tmp_src_name_buf),
		"%s:%d",
		inet_ntoa(tmp_src_name.sin_addr),
		ntohs(tmp_src_name.sin_port)
		);
	cp_snprintf(tmp_dst_name_buf, cp_sizeof(tmp_dst_name_buf),
		"%s:%d",
		inet_ntoa(tmp_dst_name.sin_addr),
		ntohs(tmp_dst_name.sin_port)
		);
	cp_snprintf(uv_socket->si, cp_sizeof(uv_socket->si),
		"socket[p:0x%x t:%s src:%s dst:%s]",
		uv_socket,
		tmp_name_flag,
		tmp_src_name_buf,
		tmp_dst_name_buf
		);

	return 0;
}

cp_int32_t uv_socket_set_native_socket(cp_uv_socket_t *uv_socket)
{
	if (CP_CHECK_UV_SOCKET_TYPE(uv_socket, UV_TCP)) {
#ifdef WIN32
		uv_socket->native_sock = ((uv_tcp_t *)(uv_socket->handle))->socket;
#else
		uv_socket->native_sock = ((uv_tcp_t *)(uv_socket->handle))->io_watcher.fd;
#endif // WIN32
	}
	else {
#ifdef WIN32
		uv_socket->native_sock = ((uv_udp_t *)(uv_socket->handle))->socket;
#else
		uv_socket->native_sock = ((uv_udp_t *)(uv_socket->handle))->io_watcher.fd;
#endif // WIN32
	}

	return 0;
}