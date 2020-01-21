/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SOCKET_INCLUDE_H_
#define _CP_SOCKET_INCLUDE_H_



#include "cp_socket_core.h"


/************************************************************************/
/* 表示默认的读写超时时间，默认为10秒钟                                   */
/************************************************************************/
#define CP_SOCKET_DEFAULT_READ_WRITE_TIMEOUT							10000



#pragma pack(1)


typedef int(*cp_socket_listen_handle)(cp_socket_t *s, cp_sockaddr_in *addr);										/*打开监听*/
typedef int(*cp_socket_connect_handle)(cp_socket_t *s, cp_sockaddr_in *addr);										/*开始连接*/
typedef int(*cp_socket_read_s_handle)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);		/*读数据*/
typedef int(*cp_socket_write_s_handle)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nwrite, 						/*写数据*/
	const cp_sockaddr_in *remote_addr, cp_int32_t flags);
typedef int(*cp_socket_close_s_handle)(cp_socket_t *s);																/*关闭连接*/
typedef int(*cp_socket_connect_cb_handle)(cp_socket_t *s, cp_int32_t status);										/*连接回调函数*/
typedef int(*cp_socket_close_cb_handle)(cp_socket_t *s, cp_int32_t status);											/*关闭回调函数*/
typedef int(*cp_socket_read_cb_handle)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/
typedef int(*cp_socket_write_cb_handle)(cp_socket_t *s, cp_int32_t status);											/*写回调函数*/
typedef int(*cp_socket_error_cb_handle)(cp_socket_t *s, cp_int32_t status);											/*错误回调函数*/
typedef int(*cp_socket_general_cb_handle)(cp_socket_t *s, cp_int32_t status);										/*常规回调函数*/


#if 0
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CP_SOCKET_HANDLER_FIELDS																							\
		int(*listen)(cp_socket_t *s, cp_sockaddr_in *addr);											/*打开监听*/				\
		int(*connect)(cp_socket_t *s, cp_sockaddr_in *addr);										/*开始连接*/				\
		int(*read_s)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);		/*读数据*/				\
		int(*write_s)(cp_socket_t *s, cp_int32_t nread, const cp_buf_t *buf,						/*写数据*/				\
					const cp_sockaddr_in *remote_addr, cp_int32_t flags);													\
		int(*close_s)(cp_socket_t *s);																/*关闭连接*/				\
		int(*connect_cb)(cp_socket_t *s, cp_int32_t status);										/*连接回调函数*/			\
		int(*close_cb)(cp_socket_t *s, cp_int32_t status);											/*关闭回调函数*/			\
		int(*read_cb)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*读回调函数*/			\
		int(*write_cb)(cp_socket_t *s, cp_int32_t status);											/*写回调函数*/			\
		int(*error_cb)(cp_socket_t *s, cp_int32_t status);											/*错误回调函数*/			\

#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CP_SOCKET_HANDLER_FIELDS																	\
		cp_socket_listen_handle listen;										/*打开监听*/				\
		cp_socket_connect_handle connect;									/*开始连接*/				\
		cp_socket_read_s_handle read_s;										/*读数据*/				\
		cp_socket_write_s_handle write_s;									/*写数据*/				\
		cp_socket_close_s_handle close_s;									/*关闭连接*/				\
		cp_socket_connect_cb_handle connect_cb;								/*连接回调函数*/			\
		cp_socket_close_cb_handle close_cb;									/*关闭回调函数*/			\
		cp_socket_read_cb_handle read_cb;									/*读回调函数*/			\
		cp_socket_write_cb_handle write_cb;									/*写回调函数*/			\
		cp_socket_error_cb_handle error_cb;									/*错误回调函数*/			\




#define CP_SOCKET_FIELDS																	\
		CP_MODULE_FIELDS																	\
		CP_SOCKET_HANDLER_FIELDS						/*网络接口句柄*/						\
		cp_buf_t						*buf;			/*缓存地址*/							\
		cp_buf_t						*cache_buf;		/*缓存*/								\
		cp_int32_t						nread;			/*表示读取的数据*/					\
		cp_int32_t						socket_status;	/*表示当前连接*/						\
		cp_socket_type_e				socket_type;	/*表示socket类型*/					\
		cp_sockaddr_in					remote_addr;	/*远程地址，在UDP通信时使用*/			\
		cp_sockaddr_in					local_addr;		/*本地地址，在UDP通信时使用*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_socket_s {
	CP_SOCKET_FIELDS
};


#pragma pack()



#if 0

/************************************************************************/
/* socket设置句柄                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_SET_HANDLERS(module, name)							\
	CP_MODULE_SET_HANDLERS(module, name)										\
	CP_MODULE_SET_SINGLE_HANDLER(module, listen, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, connect, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, read_s, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, write_s, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, close_s, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, connect_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, close_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, read_cb, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, write_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, error_cb, name)						\



/************************************************************************/
/* socket设置回调函数句柄                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(module, name)					\
	CP_MODULE_SET_SINGLE_HANDLER(module, connect_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, close_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, read_cb, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, write_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, error_cb, name)						\



/************************************************************************/
/* socket更新句柄                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_UPDATE_HANDLERS(src_module, dest_module)				\
	CP_MODULE_UPDATE_HANDLERS(src_module, dest_module)							\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, listen)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, connect)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, read_s)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, write_s)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, close_s)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, connect_cb)		\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, close_cb)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, read_cb)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, write_cb)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER(src_module, dest_module, error_cb)			\


#endif






/************************************************************************/
/* socket设置句柄                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_SET_HANDLERS(module, name)							\
	CP_MODULE_SET_HANDLERS(module, name)										\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, listen, name, cp_socket_listen_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, connect, name, cp_socket_connect_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, read_s, name, cp_socket_read_s_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, write_s, name, cp_socket_write_s_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, close_s, name, cp_socket_close_s_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, connect_cb, name, cp_socket_connect_cb_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, close_cb, name, cp_socket_close_cb_handle)						\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, read_cb, name, cp_socket_read_cb_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, write_cb, name, cp_socket_write_cb_handle)						\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, error_cb, name, cp_socket_error_cb_handle)						\



/************************************************************************/
/* socket设置回调函数句柄                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(module, name)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, connect_cb, name, cp_socket_connect_cb_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, close_cb, name, cp_socket_close_cb_handle)						\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, read_cb, name, cp_socket_read_cb_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, write_cb, name, cp_socket_write_cb_handle)						\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, error_cb, name, cp_socket_error_cb_handle)						\



/************************************************************************/
/* socket更新句柄                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_UPDATE_HANDLERS(src_module, dest_module)				\
	CP_MODULE_UPDATE_HANDLERS(src_module, dest_module)							\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, listen, cp_socket_listen_handle)				\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, connect, cp_socket_connect_handle)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, read_s, cp_socket_read_s_handle)				\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, write_s, cp_socket_write_s_handle)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, close_s, cp_socket_close_s_handle)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, connect_cb, cp_socket_connect_cb_handle)		\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, close_cb, cp_socket_close_cb_handle)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, read_cb, cp_socket_read_cb_handle)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, write_cb, cp_socket_write_cb_handle)			\
	CP_MODULE_UPDATE_SINGLE_HANDLER_AND_TYPE(src_module, dest_module, error_cb, cp_socket_error_cb_handle)			\






/************************************************************************/
/* socket 处理函数                                                       */
/************************************************************************/
cp_socket_t *cp_create_socket(const cp_app_t *app, cp_socket_type_e type);
cp_int32_t cp_listen_socket(cp_socket_t *socket, cp_sockaddr_in *addr);
cp_int32_t cp_connect_socket(cp_socket_t *socket, cp_sockaddr_in *addr);
cp_int32_t cp_read_socket(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);
cp_int32_t cp_write_socket(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nwrite, const cp_sockaddr_in *remote_addr, cp_int32_t flags);
cp_int32_t cp_close_socket(cp_socket_t *socket);
cp_int32_t cp_destroy_socket(cp_socket_t *socket);
cp_int32_t cp_set_callback_socket(cp_socket_t *socket, cp_socket_connect_cb_handle connect_cb, cp_socket_write_cb_handle write_cb);
const cp_char_t *cp_get_socket_type_name(cp_socket_type_e st);

/************************************************************************/
/* 初始化session信息                                                     */
/************************************************************************/
#define CP_SOCKET_SET_FIELDS(socket, in_buf, in_nread, in_status, in_remote_addr)	do {			\
			(socket)->buf = (cp_buf_t*)in_buf;		/*缓存地址*/					\
			(socket)->nread = in_nread;				/*表示读取的数据*/			\
			(socket)->socket_status = in_status;	/*表示当前连接*/				\
			(socket)->remote_addr = in_remote_addr;	/*表示远端连接*/				\
		} while (0);															\


/************************************************************************/
/* 判断socket类型信息，成功为TRUE                                       */
/************************************************************************/
#define CP_SOCKET_CHECK_TYPE(socket, type)			((socket)->socket_type == type)
#endif


