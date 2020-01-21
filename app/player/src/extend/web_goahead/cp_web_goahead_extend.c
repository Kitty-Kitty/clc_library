/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_web_goahead_extend.h"
#include "cp_player_func_manager_core.h"


/*模块创建接口，表示创建一个模块*/
cp_int32_t init_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, const cp_web_goahead_extend_info_t *web_goahead_extend_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, const cp_web_goahead_extend_info_t *web_goahead_extend_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend);
/*退出模块*/
cp_int32_t exit_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend);
/*设置模块参数*/
cp_int32_t set_option_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_web_goahead_extend(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_web_goahead_extend(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_web_goahead_extend(cp_web_goahead_extend_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_web_goahead_extend(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_web_goahead_extend(cp_socket_t *socket);																/*关闭连接*/
#endif



cp_web_goahead_extend_t* create_web_goahead_extend(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_web_goahead_extend_info_t *info)
{
	cp_web_goahead_extend_t					*tmp_module = CP_NULL;
	cp_pool_info_t							tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_web_goahead_extend_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_MODULE_SET_HANDLERS(tmp_module, web_goahead_extend);
	return tmp_module;
}

cp_int32_t destroy_web_goahead_extend(cp_extend_manager_t *manager, cp_web_goahead_extend_t* web_goahead_extend)
{
	if (!manager || !web_goahead_extend) {
		return -1;
	}

	cp_free_module(web_goahead_extend);
	return 0;
}



/*模块创建接口，表示创建一个模块*/
cp_int32_t init_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, const cp_web_goahead_extend_info_t *web_goahead_extend_info)
{

	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, const cp_web_goahead_extend_info_t *web_goahead_extend_info)
{

	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend)
{
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_web_goahead_extend(cp_web_goahead_extend_t *web_goahead_extend, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_web_goahead_extend(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_web_goahead_extend(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_web_goahead_extend(cp_web_goahead_extend_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_web_goahead_extend(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_web_goahead_extend(cp_socket_t *socket)
{
	return 0;
}
#endif


