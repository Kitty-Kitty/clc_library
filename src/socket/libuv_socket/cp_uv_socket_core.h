/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_UV_SOCKET_CORE_INCLUDE_H_
#define _CP_UV_SOCKET_CORE_INCLUDE_H_



//#define CP_UV_SOCKET_PRINT_DEBUG_INFO				1


typedef struct cp_uv_socket_info_s					cp_uv_socket_info_t;
typedef	struct cp_uv_socket_s						cp_uv_socket_t;
typedef	struct cp_uv_socket_manager_info_s			cp_uv_socket_manager_info_t;
typedef struct cp_uv_socket_manager_s				cp_uv_socket_manager_t;
typedef	struct cp_uv_socket_handles_s				cp_uv_socket_handles_t;
typedef	struct cp_uv_socket_manager_handles_s		cp_uv_socket_manager_handles_t;



#include "uv.h"
#include "cp_socket_core.h"
#include "cp_uv_socket_info.h"
#include "cp_uv_socket_manager_info.h"
#include "cp_uv_socket.h"
#include "cp_uv_socket_manager.h"




#endif


