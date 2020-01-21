/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_UV_SOCKET_INCLUDE_H_
#define _CP_UV_SOCKET_INCLUDE_H_

#include <stddef.h>
#include "uv.h"
#include "cp_uv_socket_core.h"



//typedef struct cp_uv_socket_s				cp_uv_socket_t;
#define			CP_UV_SOCKET_ADDRESS_BUFFER_LENGTH							128


#pragma pack(1)


#define CP_UV_SOCKET_FIELDS																\
		CP_SOCKET_FIELDS																\
		uv_handle_t				*handle;				/*uv socket处理句柄*/			\
		uv_req_t				*req;					/*描述请求信息结构体*/			\
		uv_connect_t			*connect_req;			/*描述连接信息结构体*/			\
		cp_uint64_t				read_timeout;			/*表示读超时时间,单位毫秒*/		\
		cp_uint64_t				write_timeout;			/*表示写超时时间,单位毫秒*/		\
		cp_uint64_t				read_time;				/*表示最近的读时间*/				\
		cp_uint64_t				write_time;				/*表示最近的写时间*/				\
		uv_timer_t				read_timer;				/*表示读定时器*/					\
		uv_timer_t				write_timer;			/*表示写定时器*/					\
		uv_os_sock_t			native_sock;			/*表示系统socket*/				\
		cp_mutex_t				free_mutex;				/*表示释放模块互斥量*/			\
		cp_char_t				si[CP_UV_SOCKET_ADDRESS_BUFFER_LENGTH];				/*表示socket info信息*/	\
		cp_int32_t				rw_flag;				/*表示socket 读写标识*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_uv_socket_s {
	CP_UV_SOCKET_FIELDS									/*表示时间模块信息*/
};


#pragma pack()


cp_uv_socket_t* create_uv_socket(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_uv_socket_info_t *info);
cp_int32_t destroy_uv_socket(cp_socket_manager_t *manager, cp_uv_socket_t* uv_socket);


#endif


