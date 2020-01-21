/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_demo_hook_module_list.h"
#include "css_core.h"



#define CP_SEMH_HOOK_REGISTER(type, version, name, description, command, hook_handle)				\
	CP_CSS_HOOK_REGISTER(type, version, name, description, create_rtp_hook, destroy_rtp_hook, command, hook_handle)	






/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(demo_hook)

CP_ADD_SUB_MANAGER_DEPENDENT(
cp_module_manager_register_t,
CP_MANAGER_DEPENDENT_CALLBACK_NULL,
CP_MODULE_MANAGER_REGISTER(cp_demo_hook_manager_type_demo_hook,
1, "hook_module_manager", "uv hook module manager", create_demo_hook_manager, destroy_demo_hook_manager));

CP_MODULE_MANAGER_DEPENDENT_END()





/************************************************************************/
/* 添加内存模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(demo_hook)

CP_ADD_MODULE_DEPENDENT(
	cp_demo_hook_register_t,
	cp_demo_hook_manager_type_demo_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_rtp_hook_type_global,
	1, "func_global", "func global",
	0, func_global));

CP_ADD_MODULE_DEPENDENT(
	cp_demo_hook_register_t,
	cp_demo_hook_manager_type_demo_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_rtp_hook_type_global_destroy,
	1, "func_global_destroy", "func global destroy",
	0, func_global_destroy));

CP_ADD_MODULE_DEPENDENT(
	cp_demo_hook_register_t,
	cp_demo_hook_manager_type_demo_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_rtp_hook_type_func_check_rtp_command,
	1, "func_check_rtp_command", "func_check_rtp_command",
	1, func_check_rtp_command));

CP_ADD_MODULE_DEPENDENT(
	cp_demo_hook_register_t,
	cp_demo_hook_manager_type_demo_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_rtp_hook_type_func_get_rtp_hook,
	1, "func_get_rtp_hook", "get rtp ",
	1, func_get_rtp_hook));

CP_ADD_MODULE_DEPENDENT(
	cp_demo_hook_register_t,
	cp_demo_hook_manager_type_demo_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_rtp_hook_type_func_parse_gmf_data,
	1, "func_parse_gmf_data", "func_parse_gmf_data",
	1, func_parse_gmf_data));

CP_ADD_MODULE_DEPENDENT(
	cp_demo_hook_register_t,
	cp_demo_hook_manager_type_demo_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_rtp_hook_type_func_error_response,
	1, "func_error_response", "func_error_response",
	22000, func_error_response));

CP_ADD_MODULE_DEPENDENT(
	cp_demo_hook_register_t,
	cp_demo_hook_manager_type_demo_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_rtp_hook_type_func_gmf_error_data,
	1, "func_gmf_error_data", "func_gmf_error_data",
	3, func_gmf_error_data));


CP_MODULE_DEPENDENT_END()





 /************************************************************************/
 /* 添加入口函数的依赖关系                                                */
 /************************************************************************/
CP_CSS_HOOK_SET_ENTRY_DEPENDENT_BEGIN



//   	CP_CSS_ADD_ENTRY_DEPENDENT(cp_css_rtp_hook_type_global, 
// 	cp_css_rtp_hook_type_func_get_rtp_hook, cp_css_rtp_hook_type_demo_media_close, cp_css_rtp_hook_type_demo_media_close, cp_css_rtp_hook_type_end);
// 
// 	CP_CSS_ADD_ENTRY_DEPENDENT(cp_css_rtp_hook_type_global,
// 		cp_css_rtp_hook_type_func_parse_gmf_data, cp_css_rtp_hook_type_end);




CP_CSS_HOOK_DEPENDENT_END






/************************************************************************/
/* 添加正确返回依赖关系                                                  */
/************************************************************************/
CP_CSS_HOOK_SET_RIGHT_DEPENDENT_BEGIN

CP_CSS_ADD_RIGHT_DEPENDENT(cp_css_rtp_hook_type_global,
cp_css_rtp_hook_type_func_check_rtp_command, cp_css_rtp_hook_type_global_destroy, cp_css_rtp_hook_type_end);
 
CP_CSS_ADD_RIGHT_DEPENDENT(cp_css_rtp_hook_type_func_check_rtp_command,
	cp_css_rtp_hook_type_func_parse_gmf_data, cp_css_rtp_hook_type_end);
 
CP_CSS_ADD_RIGHT_DEPENDENT(cp_css_rtp_hook_type_func_parse_gmf_data,
	cp_css_rtp_hook_type_func_get_rtp_hook, cp_css_rtp_hook_type_end);


CP_CSS_HOOK_DEPENDENT_END

			 


/************************************************************************/
/* 添加错误返回依赖关系                                                  */
/************************************************************************/
CP_CSS_HOOK_SET_ERROR_DEPENDENT_BEGIN


CP_CSS_ADD_ERROR_DEPENDENT(cp_css_rtp_hook_type_func_parse_gmf_data,
cp_css_rtp_hook_type_func_gmf_error_data, cp_css_rtp_hook_type_end);

// 	CP_CSS_ADD_ERROR_DEPENDENT(cp_css_rtp_hook_type_demo_media_close, 
// 	cp_css_rtp_hook_type_func_parse_gmf_data, cp_css_rtp_hook_type_end)



CP_CSS_HOOK_DEPENDENT_END