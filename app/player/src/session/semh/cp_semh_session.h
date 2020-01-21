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
 		gmp_gmph_semh_t			*semh_p;												/*semhͷ��Ϣ*/					\
 		gmp_gmf_t				*gmf;													/*gmf��Ϣ*/						\
		cp_app_t				*app;													/*��ʾappָ��*/					\
		cp_app_info_t			*app_info;												/*��ʾapp��Ϣָ��*/				\
		cp_char_t				semh_si[CP_SEMH_SESSION_BUFFER_LENGTH];					/*��ʾsemh session info��Ϣ*/	\
		
 
 
 /************************************************************************/
 /*                                                                      */
 /************************************************************************/
 struct cp_semh_session_s {
 	CP_SEMH_SESSION_FIELDS												/*��ʾʱ��ģ����Ϣ*/
 };
 
 #pragma pack()



cp_semh_session_t* create_semh_session(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_semh_session_info_t *info);
cp_int32_t destroy_semh_session(cp_css_session_manager_t *manager, cp_semh_session_t* semh_session);


#endif


