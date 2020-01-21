/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SESSION_INCLUDE_H_
#define _CP_SESSION_INCLUDE_H_

#include "cp_session_core.h"
#include "cp_hook_handle.h"
#include "cp_socket.h"



//typedef struct cp_session_s				cp_session_t;



#pragma pack(1)






#define CP_SESSION_FIELDS																\
		CP_SOCKET_FIELDS																\
		CP_HANDLE_SLAB_FIELDS															\
		cp_socket_t			*socket;				/*表示当前连接*/						\
		cp_hook_t			*global_hook;			/*这个表示全局hook*/					\
		cp_int32_t			option;					/*表示这个sesion的部分信息*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_session_s {
	CP_SESSION_FIELDS							/*表示时间模块信息*/
};

#pragma pack()


/************************************************************************/
/* 初始化session信息                                                     */
/************************************************************************/
#define CP_SESSION_SET_SOCKET_INFO(session, in_socket, in_buf, in_nread, in_status)	do {	\
			(session)->socket = (cp_socket_t*)(in_socket);	/*表示当前连接*/					\
			(session)->buf = (cp_buf_t*)(in_buf);			/*缓存地址*/						\
			(session)->nread = (in_nread);					/*表示读取的数据*/				\
			(session)->status = (in_status);				/*表示当前连接*/					\
		} while (0);																		\



/************************************************************************/
/* 设置session下一个需要执行的hook和参数                                */
/************************************************************************/
#define CP_SESSION_SET_NEXT_HOOK_INFO(session, in_hook, in_arg)	do {						\
			(session)->current_hook = (in_hook);	/*设置当前hook句柄*/						\
			(session)->arg = (in_arg);				/*设置当前hook参数*/						\
		} while (0);																		\




cp_session_t* cp_create_session(const cp_app_t *app, cp_session_info_t *info);
cp_int32_t cp_detory_session(cp_session_t *session);


#endif


