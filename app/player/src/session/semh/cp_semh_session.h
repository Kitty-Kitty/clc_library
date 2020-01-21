/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SEMH_SESSION_INCLUDE_H_
#define _CP_SEMH_SESSION_INCLUDE_H_


#include "cp_semh_session_core.h"
#include "prot_core.h"



//typedef struct cp_semh_session_s				cp_semh_session_t;
#define			CP_SEMH_SESSION_BUFFER_LENGTH							256


#pragma pack(1)


#define CP_SEMH_SESSION_FIELDS																							\
 		CP_SESSION_FIELDS																								\
 		gmp_gmph_semh_t			*semh_p;												/*semh头信息*/					\
 		gmp_gmf_t				*gmf;													/*gmf信息*/						\
		cp_app_t				*app;													/*表示app指针*/					\
		cp_app_info_t			*app_info;												/*表示app信息指针*/				\
		cp_char_t				semh_si[CP_SEMH_SESSION_BUFFER_LENGTH];					/*表示semh session info信息*/	\
		
 
 
 /************************************************************************/
 /*                                                                      */
 /************************************************************************/
 struct cp_semh_session_s {
 	CP_SEMH_SESSION_FIELDS												/*表示时间模块信息*/
 };
 
 #pragma pack()



cp_semh_session_t* create_semh_session(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_semh_session_info_t *info);
cp_int32_t destroy_semh_session(cp_css_session_manager_t *manager, cp_semh_session_t* semh_session);


#endif


