/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ipc_func.h"
#include "cp_third_party.h"
#include "cp_include.h"
#include "cp_ipc_codec_module_option.h"


//#define CP_IPC_FUNC_DEBUG_MEMORY					1


#if defined(CP_IPC_FUNC_DEBUG_MEMORY)
#include <crtdbg.h>
#endif


CP_EXTERN_GLOBAL_APP()


cp_ipc_func_t *cp_ipc_func_create();
/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_ipc_func(cp_ipc_func_t *ipc_func, const cp_ipc_func_info_t *ipc_func_info);
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_ipc_func(cp_ipc_func_t *ipc_func, const cp_ipc_func_info_t *ipc_func_info);
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ipc_func(cp_ipc_func_t *ipc_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_ipc_func(cp_ipc_func_t *ipc_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag);
/*关闭模块*/
cp_int32_t close_ipc_func(cp_ipc_func_t *ipc_func);
/*退出模块*/
cp_int32_t exit_ipc_func(cp_ipc_func_t *ipc_func);
/*设置模块参数*/
cp_int32_t set_option_ipc_func(cp_ipc_func_t *ipc_func, cp_int32_t optname, const cp_void_t* optval);
cp_int32_t get_option_ipc_func(cp_ipc_func_t *ipc_func, cp_int32_t optname, cp_void_t* optval);


#if 0
cp_int32_t listen_ipc_func(cp_socket_t *socket, cp_sockaddr_in *addr);											/*打开监听*/
cp_int32_t connect_ipc_func(cp_socket_t *socket, cp_sockaddr_in *addr);										/*开始连接*/
cp_int32_t read_s_ipc_func(cp_ipc_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);	/*读数据*/
cp_int32_t write_s_ipc_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t close_s_ipc_func(cp_socket_t *socket);																/*关闭连接*/
#endif

cp_int32_t connect_cb_ipc_func(cp_socket_t *socket, cp_int32_t status);										/*连接回调函数*/
cp_int32_t close_cb_ipc_func(cp_socket_t *socket, cp_int32_t status);											/*关闭回调函数*/
cp_int32_t read_cb_ipc_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
cp_int32_t write_cb_ipc_func(cp_socket_t *socket, cp_int32_t status);											/*写回调函数*/
cp_int32_t error_cb_ipc_func(cp_socket_t *socket, cp_int32_t status);											/*错误回调函数*/

cp_int32_t ipc_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_int32_t ipc_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);

cp_ipc_func_t* create_ipc_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ipc_func_info_t *info)
{
	cp_int32_t							ret_int = 0;
	cp_ipc_func_t						*tmp_module = CP_NULL;
	cp_pool_info_t						tmp_pool_info = { 0, };


	if (!register_info || !manager || !info) {
		return CP_NULL;
	}

	tmp_module = cp_malloc_module(manager, cp_ipc_func_t, &tmp_pool_info);
	if (!tmp_module) {
		return CP_NULL;
	}
	CP_FUNC_MODULE_SET_HANDLERS(tmp_module, ipc_func);

	return tmp_module;
}

cp_int32_t destroy_ipc_func(cp_ipc_func_manager_t *manager, cp_ipc_func_t* ipc_func)
{
	if (!manager || !ipc_func) {
		return -1;
	}
	cp_free_module(ipc_func);
	return 0;
}

/*模块初始化接口，在模块create之后，会被调用*/
cp_int32_t init_ipc_func(cp_ipc_func_t *ipc_func, const cp_ipc_func_info_t *ipc_func_info)
{
	cp_int32_t					tmp_ret_int = 0;


	//初始化配置文件
	tmp_ret_int = init_ipc_func_conf((cp_module_t*)ipc_func, &ipc_func->ipc_conf);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, "init_ipc_func_conf() error.");
		return -1;
	}

	//读取配置文件
	tmp_ret_int = set_ipc_func_conf((cp_module_t*)ipc_func, &ipc_func->ipc_conf);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, "init_ipc_func_conf() error.");
		return -1;
	}

	//表示创建一个视频编码器
	ipc_func->video_codec = create_video_codec_module(ipc_func, cp_ipc_module_type_hi_codec);
	if (!ipc_func->video_codec) {
		cp_module_log(error, ipc_func, "create_video_codec_module() error.");
		return -1;
	}

	//初始化video codec
	tmp_ret_int = init_video_codec_module(ipc_func, ipc_func->video_codec);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, "init_video_codec_module() error.");
		return -1;
	}

	cp_module_log(notice, ipc_func, "init() successed.");

	return 0;
}
/*模块打开运行接口，在模块init之后，会被调用*/
cp_int32_t open_ipc_func(cp_ipc_func_t *ipc_func, const cp_ipc_func_info_t *ipc_func_info)
{
	cp_int32_t					tmp_ret_int = 0;
	cp_sockaddr_in				tmp_rtp_addr = { 0, };
	cp_ipc_info_t				*tmp_ipc_info = (cp_ipc_info_t *)ipc_func->manager->app->app_info;


#if defined(CP_IPC_FUNC_SAVE_FILE)

	ipc_func->file = fopen("send_data_file.h264", "wb");
	if (!ipc_func->file) {
		cp_module_log(error, ipc_func, "fopen() error.");
		return -1;
	}
#endif

	ipc_func->rtp_socket = cp_create_socket(ipc_func->manager->app, cp_socket_type_udp);
	if (!ipc_func->rtp_socket) {
		cp_module_log(error, ipc_func, "cp_create_socket() error.");
		return -1;
	}
	cp_ip4_addr(tmp_ipc_info->device_info->network.ip,
		tmp_ipc_info->heartbeat_manager.local_heartbeat_udp_port, &tmp_rtp_addr);
	tmp_ret_int = cp_listen_socket(ipc_func->rtp_socket, &tmp_rtp_addr);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, 
			"join media multicast error. cp_listen_socket(multicast) error.[%s:%d]", 
			tmp_ipc_info->device_info->network.ip, 
			tmp_ipc_info->heartbeat_manager.local_heartbeat_udp_port);
		return -1;
	}
	ipc_func->rtp_socket->read_cb = CP_NULL;

	ipc_func->ipc_rtp_session = create_ipc_rtp_send_session(ipc_func);
	if (!ipc_func->ipc_rtp_session) {
		cp_module_log(error, ipc_func, "create_ipc_rtp_session() error.");
		return -1;
	}

	cp_module_log(notice, ipc_func, "create_rtp_send_session() successed.");

	tmp_ret_int = cp_set_option_module(ipc_func->video_codec, 
		cp_ipc_codec_set_option_rtp_session, ipc_func->ipc_rtp_session);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, "set rtp session error.");
		return -1;
	}

	//启动video codec
	tmp_ret_int = start_video_codec_module(ipc_func, ipc_func->video_codec);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, "start_video_codec_module() error.");
		return -1;
	}

#ifndef CP_IPC_CODEC_SEND_RTP
	//启动线程
	ipc_func->rtp_video_thread = create_video_process_thread(ipc_func);
	if (!ipc_func->rtp_video_thread) {
		stop_video_codec_module(ipc_func, ipc_func->video_codec);
		cp_module_log(error, ipc_func, "create_video_process_thread() error.");
		return -1;
	}
#endif // !CP_IPC_CODEC_SEND_RTP

	return 0;
}
/*读取模块数据，flag为读取模式的扩展标志。默认为0，其他为预留*/
cp_int32_t read_ipc_func(cp_ipc_func_t *ipc_func, cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*写模块数据，flag为写模式的扩展标志。默认为0，其他为预留*/
cp_int32_t write_ipc_func(cp_ipc_func_t *ipc_func, const cp_uchar_t **buf, cp_int32_t len, cp_int32_t flag)
{
	return 0;
}
/*关闭模块*/
cp_int32_t close_ipc_func(cp_ipc_func_t *ipc_func)
{
	cp_int32_t					tmp_ret_int = 0;



	//停止video codec
	tmp_ret_int = stop_video_codec_module(ipc_func, ipc_func->video_codec);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, "stop_video_codec_module() error.");
		return -1;
	}
	return 0;
}
/*退出模块*/
cp_int32_t exit_ipc_func(cp_ipc_func_t *ipc_func)
{
	cp_int32_t					tmp_ret_int = 0;



	//消毁video codec
	tmp_ret_int = destroy_video_codec_module(ipc_func, ipc_func->video_codec);
	if (tmp_ret_int) {
		cp_module_log(error, ipc_func, "destroy_video_codec_module() error.");
		return -1;
	}
	
	return 0;
}
/*设置模块参数*/
cp_int32_t set_option_ipc_func(cp_ipc_func_t *ipc_func, cp_int32_t optname, const cp_void_t* optval)
{
	return 0;
}

cp_int32_t get_option_ipc_func(cp_ipc_func_t *ipc_func, cp_int32_t optname, cp_void_t* optval)
{
	return 0;
}

#if 0
cp_int32_t listen_ipc_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t connect_ipc_func(cp_socket_t *socket, cp_sockaddr_in *addr)
{
	return 0;
}

cp_int32_t read_s_ipc_func(cp_ipc_func_t *cp_s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags)
{
	return 0;
}

cp_int32_t write_s_ipc_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, const cp_sockaddr_in *remote_addr, cp_int32_t flags)
{
	return 0;
}

cp_int32_t close_s_ipc_func(cp_socket_t *socket)
{
	return 0;
}
#endif

cp_int32_t connect_cb_ipc_func(cp_socket_t *socket, cp_int32_t status)
{
	cp_buf_t				*buf = socket->buf;
	cp_int32_t				tmp_read_length = 0;
	cp_ipc_info_t			*tmp_ipc_info = (cp_ipc_info_t *)(socket->manager->app->app_info);


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

	//CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(socket, ipc_func);
	//cp_read_socket(socket, buf, tmp_read_length, 0);
	return 0;
}

cp_int32_t close_cb_ipc_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t read_cb_ipc_func(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	cp_int32_t					ret_int = 0;


	//判断数据是否接收完全
	ret_int = ipc_func_process_socket_data(socket, buf, nread, status);
	if (!(socket->flag & CP_SOCKET_FLAG_LISTEN)) {
		cp_close_socket(socket);
		cp_manager_destroy_module(socket->manager, socket);
	}

 	if (CP_SOCKET_CHECK_TYPE(socket, cp_socket_type_udp) && socket->buf) {
 		cp_buf_clear(socket->buf);
 	}
	return ret_int;
}

cp_int32_t write_cb_ipc_func(cp_socket_t *socket, cp_int32_t status)
{
	return connect_cb_ipc_func(socket, status);
}

cp_int32_t error_cb_ipc_func(cp_socket_t *socket, cp_int32_t status)
{
	return 0;
}

cp_int32_t ipc_func_data_integrity
(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
	return 0;
}

cp_int32_t ipc_func_process_socket_data(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status)
{
#if 0
	cp_session_t				*tmp_session;
	cp_session_manager_t		*tmp_sm = CP_NULL;
	cp_session_info_t			tmp_session_info = { 0, };
	cp_module_manager_info_t	tmp_mm_info = { 0, };
	cp_int32_t					ret_int = 0;
#if defined(CP_IPC_FUNC_DEBUG_MEMORY)
	_CrtMemState				s1, s2, s3;
#endif


	//判断数据是否接收完全
	ret_int = ipc_func_data_integrity(socket, buf, nread, status);
	if ((ret_int & cp_func_status_match) && (ret_int & cp_func_status_successorerror)) {
		//先获取session manager 管理器
		tmp_mm_info.type = CP_MODULE_MANAGER_TYPE_SESSION(1);
		tmp_sm = (cp_session_manager_t*)cp_get_manager(socket->manager->app, &tmp_mm_info);
		if (!tmp_sm) {
			return cp_func_status_match;
		}

#if defined(CP_IPC_FUNC_DEBUG_MEMORY)
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

#if defined(CP_IPC_FUNC_DEBUG_MEMORY)
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
#endif
	return cp_func_status_match;
}
