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
		cp_ecam_func_thread_manager_t			*pftm;		/*�̹߳�����*/				\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ecam_func_s {
	CP_ECAM_FUNC_FIELDS													/*��ʾʱ��ģ����Ϣ*/
	cp_ecam_func_conf_t							ecam_conf;				//ecam��������Ϣ
	cp_module_t									*video_codec;			//��ʾһ��������

#if defined(CP_ECAM_FUNC_SAVE_FILE)
 	FILE										*file;
#endif
	cp_socket_t									*rtp_socket;			//��ʾ����RTP���͵�socket
	cp_ecam_rtp_session_t					*ecam_rtp_session;		//��ʾecam_rtp_session
	cp_thread_t									*rtp_video_thread;		//��ʾrtp�����߳�
	cp_bool_t									is_process_video;		//��ʾ�Ƿ�����Ƶ
};

#pragma pack()


cp_ecam_func_t* create_ecam_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ecam_func_info_t *info);
cp_int32_t destroy_ecam_func(cp_ecam_func_manager_t *manager, cp_ecam_func_t* ecam_func);


#endif


