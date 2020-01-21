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
		cp_socket_t			*socket;				/*��ʾ��ǰ����*/						\
		cp_hook_t			*global_hook;			/*�����ʾȫ��hook*/					\
		cp_int32_t			option;					/*��ʾ���sesion�Ĳ�����Ϣ*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_session_s {
	CP_SESSION_FIELDS							/*��ʾʱ��ģ����Ϣ*/
};

#pragma pack()


/************************************************************************/
/* ��ʼ��session��Ϣ                                                     */
/************************************************************************/
#define CP_SESSION_SET_SOCKET_INFO(session, in_socket, in_buf, in_nread, in_status)	do {	\
			(session)->socket = (cp_socket_t*)(in_socket);	/*��ʾ��ǰ����*/					\
			(session)->buf = (cp_buf_t*)(in_buf);			/*�����ַ*/						\
			(session)->nread = (in_nread);					/*��ʾ��ȡ������*/				\
			(session)->status = (in_status);				/*��ʾ��ǰ����*/					\
		} while (0);																		\



/************************************************************************/
/* ����session��һ����Ҫִ�е�hook�Ͳ���                                */
/************************************************************************/
#define CP_SESSION_SET_NEXT_HOOK_INFO(session, in_hook, in_arg)	do {						\
			(session)->current_hook = (in_hook);	/*���õ�ǰhook���*/						\
			(session)->arg = (in_arg);				/*���õ�ǰhook����*/						\
		} while (0);																		\




cp_session_t* cp_create_session(const cp_app_t *app, cp_session_info_t *info);
cp_int32_t cp_detory_session(cp_session_t *session);


#endif


