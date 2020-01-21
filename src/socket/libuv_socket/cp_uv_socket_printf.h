/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-03-03

Description:

**************************************************************************/

#ifndef _CP_UV_SOCKET_PRINTF_INCLUDE_H_
#define _CP_UV_SOCKET_PRINTF_INCLUDE_H_

#include "cp_uv_socket_core.h"




//这里重新包装了打印信息的格式
#define	 cp_uv_socket_log(level, uv_socket, format, ...)											\
	do {																							\
			cp_module_log(level, (uv_socket), "uv_socket[%s] [%s] " format,							\
				cp_get_socket_type_name((uv_socket)->socket_type),									\
				(uv_socket)->si,																	\
				##__VA_ARGS__)																		\
	;} while (0)																					\


#endif