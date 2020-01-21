/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PROCESS_INCLUDE_H_
#define _CP_PROCESS_INCLUDE_H_

#include "cp_process_core.h"
#include "cp_socket.h"



//typedef struct cp_process_s				cp_process_t;



#pragma pack(1)



#define CP_PROCESS_FIELDS													\
		CP_SOCKET_FIELDS													\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_process_s {
	CP_PROCESS_FIELDS												/*表示时间模块信息*/
};

#pragma pack()


cp_int32_t cp_process_connect_cb(cp_socket_t *socket, cp_int32_t status);
cp_int32_t cp_process_close_cb(cp_socket_t *socket, cp_int32_t status);
cp_int32_t cp_process_read_cb(cp_socket_t *socket, const cp_buf_t *buf, cp_int32_t nread, cp_int32_t status);
cp_int32_t cp_process_write_cb(cp_socket_t *socket, cp_int32_t status);
cp_int32_t cp_process_error_cb(cp_socket_t *socket, cp_int32_t status);


#endif


