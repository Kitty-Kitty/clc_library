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
		cp_app_t				*app;													/*表示app指针*/					\
		cp_app_info_t			*app_info;												/*表示app信息指针*/				\
		cp_char_t				rtp_si[CP_RTP_SESSION_BUFFER_LENGTH];					/*表示rtp session info信息*/		\
		
 
 
 /************************************************************************/
 /*                                                                      */
 /************************************************************************/
 struct cp_rtp_session_s {
 	CP_RTP_SESSION_FIELDS												/*表示时间模块信息*/
 };
 
 #pragma pack()



cp_rtp_session_t* create_rtp_session(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_rtp_session_info_t *info);
cp_int32_t destroy_rtp_session(cp_ecam_session_manager_t *manager, cp_rtp_session_t* rtp_session);


#endif


