/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FILTER_INCLUDE_H_
#define _CP_FILTER_INCLUDE_H_

#include "cp_filter_core.h"
#include "cp_socket.h"



//typedef struct cp_filter_s				cp_filter_t;



#pragma pack(1)


#define CP_FILTER_FIELDS												\
		CP_SOCKET_FIELDS												\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_filter_s {
	CP_FILTER_FIELDS												/*表示时间模块信息*/
};

#pragma pack()



#define  CP_FILTER_MODULE_SET_HANDLERS(module, name)								\
	CP_MODULE_SET_HANDLERS(module, name)											\
	CP_MODULE_SET_SINGLE_HANDLER(module, connect_cb, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, close_cb, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, read_cb, name)								\
	CP_MODULE_SET_SINGLE_HANDLER(module, write_cb, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, error_cb, name)							\


/*CP_MODULE_SET_SINGLE_HANDLER(module, listen, name)								\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, connect, name)								\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, read_s, name)								\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, write_s, name)								\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, close_s, name)								\*/


#define CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, filter, name)				\
	((cp_socket_t*)socket)->name = ((cp_filter_t*)filter)->name	\


#define CP_UPDATE_SOCKET_MODULE_HANDLERS(socket, filter)							\
	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, filter, connect_cb)				\
	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, filter, close_cb)				\
	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, filter, read_cb)				\
	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, filter, write_cb)				\
	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, filter, error_cb)				\



#endif


