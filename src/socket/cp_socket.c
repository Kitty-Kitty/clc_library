/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_socket.h"
#include "cp_include.h"




cp_socket_t *cp_create_socket(const cp_app_t *app, cp_socket_type_e type)
{
	cp_int32_t						tmp_ret_int = 0;
	cp_socket_manager_t				*tmp_manager = CP_NULL;
	cp_module_register_t			*tmp_module_register = CP_NULL;
	cp_socket_info_t				tmp_socket_info = { 0, };
	cp_socket_t						*tmp_socket = CP_NULL;
	cp_module_manager_info_t		tmp_module_manager_info = { 0, };
	


	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, CP_MODULE_MANAGER_TYPE_SOCKET(1));
	tmp_manager = (cp_socket_manager_t*)cp_get_manager(app, &tmp_module_manager_info);
	if (!tmp_manager) {
		return CP_NULL;
	}
	tmp_socket_info.socket_type = type;

	//这里先获取模块的注册器
	tmp_module_register = cp_manager_get_module_register(tmp_manager, CP_MODULE_TYPE_SOCKET(1));
	if (!tmp_module_register) {
		return CP_NULL;
	}
	//通过模块的注册器，来创建一个模块
	tmp_socket = (cp_socket_t *)cp_create_module(tmp_module_register, tmp_manager, &tmp_socket_info);
	if (!tmp_socket) {
		return tmp_socket;
	}

	//初始化socket
	tmp_ret_int = cp_init_module(tmp_socket, &tmp_socket_info);
	if (tmp_ret_int) {
		cp_destroy_module(tmp_manager, tmp_socket);
		return CP_NULL;
	}

	return tmp_socket;
}

cp_int32_t cp_listen_socket(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return socket->listen(socket, addr);
}
cp_int32_t cp_connect_socket(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return socket->connect(socket, addr);
}
cp_int32_t cp_read_socket(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return socket->read_s(socket, buf, nread, flags);
}
cp_int32_t cp_write_socket(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nwrite, 
	const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return socket->write_s(socket, buf, nwrite, remote_addr, flags);
}
cp_int32_t cp_close_socket(cp_socket_t *socket)
{
	return socket->close_s(socket);
}

cp_int32_t cp_destroy_socket(cp_socket_t *socket)
{
	cp_socket_manager_t				*tmp_manager = CP_NULL;
	cp_module_manager_info_t		tmp_module_manager_info;



	CP_MODULE_MANAGER_INFO_SET_TYPE(&tmp_module_manager_info, cp_module_manager_type_socket);
	tmp_manager = (cp_socket_manager_t*)cp_get_manager(socket->manager->app, &tmp_module_manager_info);

	return cp_destroy_module(tmp_manager, socket);
}

cp_int32_t cp_set_callback_socket(cp_socket_t *socket, cp_socket_connect_cb_handle connect_cb, cp_socket_write_cb_handle write_cb)
{
	if (connect_cb)
		socket->connect_cb = connect_cb;

	if (write_cb)
		socket->write_cb = write_cb;

	return 0;
}

//获取socket type 值
#define CP_SOCKET_TYPE_NAME_GEN(type, type_name) case cp_socket_type_ ## type: return type_name;
const cp_char_t *cp_get_socket_type_name(cp_socket_type_e st)
{
	switch (st)
	{
		CP_SOCKET_TYPE_NAME_MAP(CP_SOCKET_TYPE_NAME_GEN);
	}

	return "unknown socket type";
}
#undef CP_SOCKET_TYPE_NAME_GEN
