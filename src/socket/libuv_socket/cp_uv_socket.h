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
		uv_handle_t				*handle;				/*uv socket������*/			\
		uv_req_t				*req;					/*����������Ϣ�ṹ��*/			\
		uv_connect_t			*connect_req;			/*����������Ϣ�ṹ��*/			\
		cp_uint64_t				read_timeout;			/*��ʾ����ʱʱ��,��λ����*/		\
		cp_uint64_t				write_timeout;			/*��ʾд��ʱʱ��,��λ����*/		\
		cp_uint64_t				read_time;				/*��ʾ����Ķ�ʱ��*/				\
		cp_uint64_t				write_time;				/*��ʾ�����дʱ��*/				\
		uv_timer_t				read_timer;				/*��ʾ����ʱ��*/					\
		uv_timer_t				write_timer;			/*��ʾд��ʱ��*/					\
		uv_os_sock_t			native_sock;			/*��ʾϵͳsocket*/				\
		cp_mutex_t				free_mutex;				/*��ʾ�ͷ�ģ�黥����*/			\
		cp_char_t				si[CP_UV_SOCKET_ADDRESS_BUFFER_LENGTH];				/*��ʾsocket info��Ϣ*/	\
		cp_int32_t				rw_flag;				/*��ʾsocket ��д��ʶ*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_uv_socket_s {
	CP_UV_SOCKET_FIELDS									/*��ʾʱ��ģ����Ϣ*/
};


#pragma pack()


cp_uv_socket_t* create_uv_socket(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_uv_socket_info_t *info);
cp_int32_t destroy_uv_socket(cp_socket_manager_t *manager, cp_uv_socket_t* uv_socket);


#endif


