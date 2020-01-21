/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FUNC_INCLUDE_H_
#define _CP_FUNC_INCLUDE_H_

#include "cp_func_core.h"
#include "cp_socket.h"



//typedef struct cp_func_s				cp_func_t;
//typedef cp_bool_t (*func_entry_handle)(cp_socket_t *s, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);



#pragma pack(1)



#define CP_FUNC_FIELDS															\
		CP_SOCKET_FIELDS														\
		cp_socket_t					*socket;				/*表示当前连接*/		\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_func_s {
	CP_FUNC_FIELDS									/*表示时间模块信息*/
};

#pragma pack()




#define  CP_FUNC_MODULE_SET_HANDLERS(module, name)								\
	CP_MODULE_SET_HANDLERS(module, name)										\
	CP_MODULE_SET_SINGLE_HANDLER(module, connect_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, close_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, read_cb, name)							\
	CP_MODULE_SET_SINGLE_HANDLER(module, write_cb, name)						\
	CP_MODULE_SET_SINGLE_HANDLER(module, error_cb, name)						\


/*CP_MODULE_SET_SINGLE_HANDLER(module, listen, name)							\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, connect, name)							\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, read_s, name)							\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, write_s, name)							\*/
/*CP_MODULE_SET_SINGLE_HANDLER(module, close_s, name)							\*/


// #define CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, func, name)			\
// 	((cp_socket_t*)socket)->name = ((cp_func_t*)func)->name	\
// 
// 
// #define CP_UPDATE_SOCKET_MODULE_HANDLERS(socket, func)						\
// 	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, func, connect_cb)			\
// 	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, func, close_cb)				\
// 	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, func, read_cb)				\
// 	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, func, write_cb)				\
// 	CP_UPDATE_SOCKET_MODULE_SINGLE_HANDLERS(socket, func, error_cb)				\


#endif


