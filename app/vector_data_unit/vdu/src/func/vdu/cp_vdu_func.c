/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_vdu_func.h"
#include "cp_third_party.h"
#include "cp_include.h"




cp_vdu_func_t *cp_vdu_func_create();
/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_vdu_func(cp_vdu_func_t *vdu_func, const cp_vdu_func_info_t *vdu_func_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_func(cp_vdu_func_t *vdu_func, const cp_vdu_func_info_t *vdu_func_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_func(cp_vdu_func_t *vdu_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_func(cp_vdu_func_t *vdu_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_vdu_func(cp_vdu_func_t *vdu_func);
/*退出模块*/
cp_int32_t exit_vdu_func(cp_vdu_func_t *vdu_func);
/*设置模块参数*/
cp_int32_t set_option_vdu_func(cp_vdu_func_t *vdu_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_vdu_func(cp_vdu_func_t *vdu_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_vdu_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_vdu_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_vdu_func(cp_vdu_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_vdu_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_vdu_func(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_vdu_func(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_vdu_func(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_vdu_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_vdu_func(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_vdu_func(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/


cp_vdu_func_t* create_vdu_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_vdu_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_vdu_func_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_vdu_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, vdu_func);
	return tmp_module;
}

cp_int32_t destroy_vdu_func(cp_vdu_func_manager_t *manager, cp_vdu_func_t* vdu_func)
{
	if (!manager || !vdu_func) {
		return -1;
	}

	//退出func
	exit_vdu_func(vdu_func);

	cp_free_module(vdu_func);
	return 0;
}

/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_vdu_func(cp_vdu_func_t *vdu_func, const cp_vdu_func_info_t *vdu_func_info)
{
	cp_int32_t								tmp_int_ret = 0;
	cp_module_info_t						tmp_module_info = { 0, };


	//创建一个qt_svg解码器
	vdu_func->codec = (cp_codec_t *)cp_app_create_module_by_type(vdu_func->manager->app,
		cp_vdu_manager_type_codec,
		cp_vdu_module_type_qt_svg_codec,
		&tmp_module_info);
	if (!vdu_func->codec) {
		cp_module_log(error, vdu_func, 
			"create module[cp_vdu_module_type_qt_svg_codec] error.");
		return -1;
	}

	//初始化这个解码器
	tmp_int_ret = cp_init_module(vdu_func->codec, &tmp_module_info);
	if (tmp_int_ret) {
		cp_module_log(error, vdu_func, "init[codec] error.");
		return -1;
	}

	//打开这个解码器
	tmp_int_ret = cp_open_module(vdu_func->codec, &tmp_module_info);
	if (tmp_int_ret) {
		cp_module_log(error, vdu_func, "open[codec] error.");
		return -1;
	}

	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_vdu_func(cp_vdu_func_t *vdu_func, const cp_vdu_func_info_t *vdu_func_info)
{
	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_vdu_func(cp_vdu_func_t *vdu_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_vdu_func(cp_vdu_func_t *vdu_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_vdu_func(cp_vdu_func_t *vdu_func)
{
	return 0;
}
/*退出模块*/
cp_int32_t exit_vdu_func(cp_vdu_func_t *vdu_func)
{
	cp_int32_t								tmp_int_ret = 0;
	cp_module_info_t						tmp_module_info = { 0, };


	//判断codec是否一个qt_svg解码器
	if (!vdu_func->codec) {
		cp_module_log(error, vdu_func, "codec is null error.");
		return -1;
	}

	//关闭这个解码器
	tmp_int_ret = cp_close_module(vdu_func->codec);
	if (tmp_int_ret) {
		//return -1;
	}

	//退出这个解码器
	tmp_int_ret = cp_exit_module(vdu_func->codec);
	if (tmp_int_ret) {
		//return -1;
	}

 	//销毁这个解码器
 	tmp_int_ret = cp_destroy_module(vdu_func->codec->manager, vdu_func->codec);
 	if (tmp_int_ret) {
 		//return -1;
 	}

	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_vdu_func(cp_vdu_func_t *vdu_func, cp_int32_t optname, const cp_void_t* optval)
{
	if (!vdu_func || !vdu_func->codec) {
		return -1;
	}

	return cp_set_option_module(vdu_func->codec, optname, optval);
}

/*获取模块参数*/
cp_int32_t get_option_vdu_func(cp_vdu_func_t *vdu_func, cp_int32_t optname, cp_void_t* optval)
{
	if (!vdu_func || !vdu_func->codec) {
		return -1;
	}

	return cp_get_option_module(vdu_func->codec, optname, optval);
}

#if 0
cp_int32_t listen_vdu_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_vdu_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_vdu_func(cp_vdu_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_vdu_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_vdu_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_vdu_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t close_cb_vdu_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_vdu_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t write_cb_vdu_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t error_cb_vdu_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}
