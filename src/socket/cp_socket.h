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
/* ��ʾĬ�ϵĶ�д��ʱʱ�䣬Ĭ��Ϊ10����                                   */
/************************************************************************/
#define CP_SOCKET_DEFAULT_READ_WRITE_TIMEOUT							10000



#pragma pack(1)


typedef int(*cp_socket_listen_handle)(cp_socket_t *s, cp_sockaddr_in *addr);										/*�򿪼���*/
typedef int(*cp_socket_connect_handle)(cp_socket_t *s, cp_sockaddr_in *addr);										/*��ʼ����*/
typedef int(*cp_socket_read_s_handle)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);		/*������*/
typedef int(*cp_socket_write_s_handle)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nwrite, 						/*д����*/
	const cp_sockaddr_in *remote_addr, cp_int32_t flags);
typedef int(*cp_socket_close_s_handle)(cp_socket_t *s);																/*�ر�����*/
typedef int(*cp_socket_connect_cb_handle)(cp_socket_t *s, cp_int32_t status);										/*���ӻص�����*/
typedef int(*cp_socket_close_cb_handle)(cp_socket_t *s, cp_int32_t status);											/*�رջص�����*/
typedef int(*cp_socket_read_cb_handle)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/
typedef int(*cp_socket_write_cb_handle)(cp_socket_t *s, cp_int32_t status);											/*д�ص�����*/
typedef int(*cp_socket_error_cb_handle)(cp_socket_t *s, cp_int32_t status);											/*����ص�����*/
typedef int(*cp_socket_general_cb_handle)(cp_socket_t *s, cp_int32_t status);										/*����ص�����*/


#if 0
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CP_SOCKET_HANDLER_FIELDS																							\
		int(*listen)(cp_socket_t *s, cp_sockaddr_in *addr);											/*�򿪼���*/				\
		int(*connect)(cp_socket_t *s, cp_sockaddr_in *addr);										/*��ʼ����*/				\
		int(*read_s)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t flags);		/*������*/				\
		int(*write_s)(cp_socket_t *s, cp_int32_t nread, const cp_buf_t *buf,						/*д����*/				\
					const cp_sockaddr_in *remote_addr, cp_int32_t flags);													\
		int(*close_s)(cp_socket_t *s);																/*�ر�����*/				\
		int(*connect_cb)(cp_socket_t *s, cp_int32_t status);										/*���ӻص�����*/			\
		int(*close_cb)(cp_socket_t *s, cp_int32_t status);											/*�رջص�����*/			\
		int(*read_cb)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);	/*���ص�����*/			\
		int(*write_cb)(cp_socket_t *s, cp_int32_t status);											/*д�ص�����*/			\
		int(*error_cb)(cp_socket_t *s, cp_int32_t status);											/*����ص�����*/			\

#endif

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CP_SOCKET_HANDLER_FIELDS																	\
		cp_socket_listen_handle listen;										/*�򿪼���*/				\
		cp_socket_connect_handle connect;									/*��ʼ����*/				\
		cp_socket_read_s_handle read_s;										/*������*/				\
		cp_socket_write_s_handle write_s;									/*д����*/				\
		cp_socket_close_s_handle close_s;									/*�ر�����*/				\
		cp_socket_connect_cb_handle connect_cb;								/*���ӻص�����*/			\
		cp_socket_close_cb_handle close_cb;									/*�رջص�����*/			\
		cp_socket_read_cb_handle read_cb;									/*���ص�����*/			\
		cp_socket_write_cb_handle write_cb;									/*д�ص�����*/			\
		cp_socket_error_cb_handle error_cb;									/*����ص�����*/			\




#define CP_SOCKET_FIELDS																	\
		CP_MODULE_FIELDS																	\
		CP_SOCKET_HANDLER_FIELDS						/*����ӿھ��*/						\
		cp_buf_t						*buf;			/*�����ַ*/							\
		cp_buf_t						*cache_buf;		/*����*/								\
		cp_int32_t						nread;			/*��ʾ��ȡ������*/					\
		cp_int32_t						socket_status;	/*��ʾ��ǰ����*/						\
		cp_socket_type_e				socket_type;	/*��ʾsocket����*/					\
		cp_sockaddr_in					remote_addr;	/*Զ�̵�ַ����UDPͨ��ʱʹ��*/			\
		cp_sockaddr_in					local_addr;		/*���ص�ַ����UDPͨ��ʱʹ��*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_socket_s {
	CP_SOCKET_FIELDS
};


#pragma pack()



#if 0

/************************************************************************/
/* socket���þ��                                                        */
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
/* socket���ûص��������                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(module, name)					\
	CP_MODULE_SET_SINGLE_HANDLER(module, connect_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, close_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, read_cb, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, write_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, error_cb, name)						\



/************************************************************************/
/* socket���¾��                                                        */
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
/* socket���þ��                                                        */
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
/* socket���ûص��������                                                        */
/************************************************************************/
#define  CP_SOCKET_MODULE_SET_CALLBACK_HANDLERS(module, name)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, connect_cb, name, cp_socket_connect_cb_handle)					\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, close_cb, name, cp_socket_close_cb_handle)						\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, read_cb, name, cp_socket_read_cb_handle)							\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, write_cb, name, cp_socket_write_cb_handle)						\
	CP_MODULE_SET_SINGLE_HANDLER_AND_TYPE(module, error_cb, name, cp_socket_error_cb_handle)						\



/************************************************************************/
/* socket���¾��                                                        */
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
/* socket ������                                                       */
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
/* ��ʼ��session��Ϣ                                                     */
/************************************************************************/
#define CP_SOCKET_SET_FIELDS(socket, in_buf, in_nread, in_status, in_remote_addr)	do {			\
			(socket)->buf = (cp_buf_t*)in_buf;		/*�����ַ*/					\
			(socket)->nread = in_nread;				/*��ʾ��ȡ������*/			\
			(socket)->socket_status = in_status;	/*��ʾ��ǰ����*/				\
			(socket)->remote_addr = in_remote_addr;	/*��ʾԶ������*/				\
		} while (0);															\


/************************************************************************/
/* �ж�socket������Ϣ���ɹ�ΪTRUE                                       */
/************************************************************************/
#define CP_SOCKET_CHECK_TYPE(socket, type)			((socket)->socket_type == type)
#endif


