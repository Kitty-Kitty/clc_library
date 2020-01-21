/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_IPC_FUNC_INCLUDE_H_
#define _CP_IPC_FUNC_INCLUDE_H_

#include "cp_ipc_func_core.h"
#include "cp_socket.h"




//typedef struct cp_ipc_func_s					cp_ipc_func_t;
#if defined(CP_HI3559_MODE)
#define cp_ipc_module_type_hi_codec			cp_ipc_module_type_hi3519_codec
#else
#define cp_ipc_module_type_hi_codec			cp_ipc_module_type_hi3559_codec
#endif




#pragma pack(1)



#define CP_IPC_FUNC_FIELDS																\
		CP_FUNC_FIELDS																	\
		cp_ipc_func_thread_manager_t			*pftm;		/*线程管理器*/				\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ipc_func_s {
	CP_IPC_FUNC_FIELDS													/*表示时间模块信息*/
	cp_ipc_func_conf_t							ipc_conf;				//ipc的配置信息
	cp_module_t									*video_codec;			//表示一个编码器

#if defined(CP_IPC_FUNC_SAVE_FILE)
 	FILE										*file;
#endif
	cp_socket_t									*rtp_socket;			//表示用于RTP发送的socket
	cp_ipc_rtp_session_t						*ipc_rtp_session;		//表示ipc_rtp_session
	cp_thread_t									*rtp_video_thread;		//表示rtp处理线程
	cp_bool_t									is_process_video;		//表示是否处理视频
};

#pragma pack()


cp_ipc_func_t* create_ipc_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ipc_func_info_t *info);
cp_int32_t destroy_ipc_func(cp_ipc_func_manager_t *manager, cp_ipc_func_t* ipc_func);


#endif


