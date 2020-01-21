/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SOCKET_CORE_INCLUDE_H_
#define _CP_SOCKET_CORE_INCLUDE_H_


#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif




typedef struct cp_socket_info_s					cp_socket_info_t;
typedef	struct cp_socket_s						cp_socket_t;
typedef struct cp_socket_manager_info_s			cp_socket_manager_info_t;
typedef struct cp_socket_manager_s				cp_socket_manager_t;





#include "cp_rbtree.h"
#include "cp_typedef.h"
#include "cp_inet.h"


#include "cp_module_core.h"
#include "cp_socket_type.h"
#include "cp_socket_status.h"
#include "cp_socket_option.h"
#include "cp_socket_flag.h"
#include "cp_socket_info.h"
#include "cp_socket_manager_info.h"
#include "cp_socket.h"
#include "cp_socket_manager.h"



#endif


