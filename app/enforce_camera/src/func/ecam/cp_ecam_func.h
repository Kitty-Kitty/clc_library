/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_FUNC_INCLUDE_H_
#define _CP_ECAM_FUNC_INCLUDE_H_

#include "cp_ecam_func_core.h"
#include "cp_socket.h"




//typedef struct cp_ecam_func_s					cp_ecam_func_t;




#pragma pack(1)



#define CP_ECAM_FUNC_FIELDS																\
		CP_FUNC_FIELDS																	\
		cp_ecam_func_thread_manager_t			*pftm;		/*线程管理器*/				\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ecam_func_s {
	CP_ECAM_FUNC_FIELDS													/*表示时间模块信息*/
	cp_ecam_func_conf_t							ecam_conf;				//ecam的配置信息
	cp_module_t									*video_codec;			//表示一个编码器

#if defined(CP_ECAM_FUNC_SAVE_FILE)
 	FILE										*file;
#endif
	cp_socket_t									*rtp_socket;			//表示用于RTP发送的socket
	cp_ecam_rtp_session_t					*ecam_rtp_session;		//表示ecam_rtp_session
	cp_thread_t									*rtp_video_thread;		//表示rtp处理线程
	cp_bool_t									is_process_video;		//表示是否处理视频
};

#pragma pack()


cp_ecam_func_t* create_ecam_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ecam_func_info_t *info);
cp_int32_t destroy_ecam_func(cp_ecam_func_manager_t *manager, cp_ecam_func_t* ecam_func);


#endif


