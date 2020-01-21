/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_audio_func.h"
#include "cp_demo_codec_core.h"
#include "cp_demo_dev_core.h"




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
	
	return 0;
}

/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_audio_func(cp_audio_func_t *audio_func, const cp_audio_func_info_t *audio_func_info)
{
	
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
	return 0;
}

/*关闭模块*/
cp_int32_t close_audio_func(cp_audio_func_t *audio_func)
{

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
	return 0;
}

cp_int32_t get_option_audio_func(cp_audio_func_t *audio_func, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
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
