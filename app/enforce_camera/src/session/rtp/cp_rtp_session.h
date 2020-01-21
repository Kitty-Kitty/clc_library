/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_RTP_SESSION_INCLUDE_H_
#define _CP_RTP_SESSION_INCLUDE_H_


#include "cp_rtp_session_core.h"
#include "prot_core.h"



//typedef struct cp_rtp_session_s				cp_rtp_session_t;
#define			CP_RTP_SESSION_BUFFER_LENGTH							256


#pragma pack(1)


#define CP_RTP_SESSION_FIELDS																							\
 		CP_SESSION_FIELDS																								\
		cp_app_t				*app;													/*��ʾappָ��*/					\
		cp_app_info_t			*app_info;												/*��ʾapp��Ϣָ��*/				\
		cp_char_t				rtp_si[CP_RTP_SESSION_BUFFER_LENGTH];					/*��ʾrtp session info��Ϣ*/		\
		
 
 
 /************************************************************************/
 /*                                                                      */
 /************************************************************************/
 struct cp_rtp_session_s {
 	CP_RTP_SESSION_FIELDS												/*��ʾʱ��ģ����Ϣ*/
 };
 
 #pragma pack()



cp_rtp_session_t* create_rtp_session(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_rtp_session_info_t *info);
cp_int32_t destroy_rtp_session(cp_ecam_session_manager_t *manager, cp_rtp_session_t* rtp_session);


#endif


