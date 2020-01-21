/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_ecam_session_module_list.h"


#if 0

cp_module_register_t  session_module_manager_list[] = {
	CP_MODULE_REGISTER(cp_ecam_session_manager_type_ecam_session,
	1, "session_module_manager", "uv session module manager", create_ecam_session_manager, destroy_ecam_session_manager)
};

cp_int32_t session_module_manager_list_size = cp_ary_size(session_module_manager_list);


 cp_module_register_t  session_module_list[] = {
	 CP_MODULE_REGISTER(cp_ecam_session_module_type_rtp_session, 1, "session_module", "session module", create_rtp_session, destroy_rtp_session)
 };
 
 cp_int32_t session_module_list_size = cp_ary_size(session_module_list);


#endif
