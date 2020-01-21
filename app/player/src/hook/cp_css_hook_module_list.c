/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/
#include "cp_css_hook_module_list.h"
#include "css_core.h"



#define CP_SEMH_HOOK_REGISTER(type, version, name, description, command, hook_handle)				\
	CP_CSS_HOOK_REGISTER(type, version, name, description, create_semh_hook, destroy_semh_hook, command, hook_handle)	






/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(css_hook)

CP_ADD_SUB_MANAGER_DEPENDENT(
cp_module_manager_register_t,
CP_MANAGER_DEPENDENT_CALLBACK_NULL,
CP_MODULE_MANAGER_REGISTER(cp_css_hook_manager_type_css_hook,
1, "hook_module_manager", "uv hook module manager", create_css_hook_manager, destroy_css_hook_manager));

CP_MODULE_MANAGER_DEPENDENT_END()





/************************************************************************/
/* 添加内存模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(css_hook)

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_global,
	1, "func_global", "func global",
	0, func_global));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_global_destroy,
	1, "func_global_destroy", "func global destroy",
	0, func_global_destroy));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_func_check_semh_command,
	1, "func_check_semh_command", "func_check_semh_command",
	1, func_check_semh_command));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_func_get_semh_hook,
	1, "func_get_semh_hook", "get semh ",
	1, func_get_semh_hook));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_func_parse_gmf_data,
	1, "func_parse_gmf_data", "func_parse_gmf_data",
	1, func_parse_gmf_data));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_func_error_response,
	1, "func_error_response", "func_error_response",
	22000, func_error_response));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_func_gmf_error_data,
	1, "func_gmf_error_data", "func_gmf_error_data",
	3, func_gmf_error_data));

///////////////////////////中心部分实现///////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_center_register_return,
	1, "proc_semh_center_register_return", "proc_semh_center_register_return",
	GMP_SEMH_CENTER_CMD_REGISTER_RETURN, proc_semh_center_register_return));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_center_life_heart,
	1, "proc_semh_center_life_heart", "proc_semh_center_life_heart",
	GMP_SEMH_CENTER_CMD_LIFE_HEART, proc_semh_center_life_heart));

///////////////////////////播放前端实现///////////////////////////

// CP_ADD_MODULE_DEPENDENT(
// 	cp_css_hook_register_t,
// 	cp_css_hook_manager_type_css_hook,
// 	CP_MODULE_DEPENDENT_CALLBACK_NULL,
// 	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_life_heart_return,
// 	1, "proc_semh_player_heart_return", "proc_semh_player_heart_return",
// 	GMP_SEMH_PLAYER_CMD_LIFE_HEART_RETURN, proc_semh_player_heart_return));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_life_heart_return,
	1, "proc_semh_player_heart_return", "proc_semh_player_heart_return",
	GMP_SEMH_PLAYER_CMD_LIFE_HEART_RETURN, proc_semh_player_heart_return));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_software_update,
	1, "proc_semh_player_software_update", "proc_semh_player_software_update",
	GMP_SEMH_PLAYER_CMD_UPDATE_NOTIFY, proc_semh_player_software_update));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_set_log,
	1, "proc_semh_player_set_log", "proc_semh_player_set_log",
	GMP_SEMH_PLAYER_CMD_SET_LOG, proc_semh_player_set_log));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_get_log,
	1, "proc_semh_player_get_log", "proc_semh_player_get_log",
	GMP_SEMH_PLAYER_CMD_GET_LOG, proc_semh_player_get_log));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_delete_log,
	1, "proc_semh_player_delete_log", "proc_semh_player_delete_log",
	GMP_SEMH_PLAYER_CMD_DELETE_LOG, proc_semh_player_delete_log));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_query_log,
	1, "proc_semh_player_query_log", "proc_semh_player_query_log",
	GMP_SEMH_PLAYER_CMD_QUERY_LOG, proc_semh_player_query_log));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_get_dev_info,
	1, "proc_semh_player_get_dev_info", "proc_semh_player_get_dev_info",
	GMP_SEMH_PLAYER_CMD_GET_DEV_INFO, proc_semh_player_get_dev_info));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_set_dev_info,
	1, "proc_semh_player_set_dev_info", "proc_semh_player_set_dev_info",
	GMP_SEMH_PLAYER_CMD_SET_DEV_INFO, proc_semh_player_set_dev_info));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_start_dev,
	1, "proc_semh_player_start_dev", "proc_semh_player_start_dev",
	GMP_SEMH_PLAYER_CMD_START_DEV, proc_semh_player_start_dev));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_stop_dev,
	1, "proc_semh_player_stop_dev", "proc_semh_player_stop_dev",
	GMP_SEMH_PLAYER_CMD_STOP_DEV, proc_semh_player_stop_dev));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_test_dev,
	1, "proc_semh_player_test_dev", "proc_semh_player_test_dev",
	GMP_SEMH_PLAYER_CMD_TEST_DEV, proc_semh_player_test_dev));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_set_network,
	1, "proc_semh_player_set_network", "proc_semh_player_set_network",
	GMP_SEMH_PLAYER_CMD_SET_NETWORK, proc_semh_player_set_network));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_set_focus,
	1, "proc_semh_player_set_focus", "proc_semh_player_set_focus",
	GMP_SEMH_PLAYER_CMD_SET_FOCUS, proc_semh_player_set_focus));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_set_background,
	1, "proc_semh_player_set_background", "proc_semh_player_set_background",
	GMP_SEMH_PLAYER_CMD_SET_BACKGROUND, proc_semh_player_set_background));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_clear_background,
	1, "proc_semh_player_clear_background", "proc_semh_player_clear_background",
	GMP_SEMH_PLAYER_CMD_CLEAR_BACKGROUND, proc_semh_player_clear_background));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_reflesh_picture,
	1, "proc_semh_player_reflesh_picture", "proc_semh_player_reflesh_picture",
	GMP_SEMH_PLAYER_CMD_REFLESH_PICTURE, proc_semh_player_reflesh_picture));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_media_play,
	1, "proc_semh_player_media_play", "proc_semh_player_media_play",
	GMP_SEMH_PLAYER_CMD_MEDIA_PLAY, proc_semh_player_media_play));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_media_play_update,
	1, "proc_semh_player_media_play_update", "proc_semh_player_media_play_update",
	GMP_SEMH_PLAYER_CMD_MEDIA_PLAY_UPDATE, proc_semh_player_media_play_update));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_media_layer_update,
	1, "proc_semh_player_media_layer_update", "proc_semh_player_media_layer_update",
	GMP_SEMH_PLAYER_CMD_MEDIA_LAYER_UPDATE, proc_semh_player_media_layer_update));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_media_stop,
	1, "proc_semh_player_media_stop", "proc_semh_player_media_stop",
	GMP_SEMH_PLAYER_CMD_MEDIA_STOP, proc_semh_player_media_stop));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_media_close,
	1, "proc_semh_player_media_close", "proc_semh_player_media_close",
	GMP_SEMH_PLAYER_CMD_MEDIA_CLOSE_NOTIFY, proc_semh_player_media_close));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_media_get_channel_info,
	1, "proc_semh_player_media_get_channel_info", "proc_semh_player_media_get_channel_info",
	GMP_SEMH_PLAYER_CMD_MEDIA_GET_CHANNEL_INFO, proc_semh_player_media_get_channel_info));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_offline_get_passwd,
	1, "proc_semh_player_offline_get_passwd", "proc_semh_player_offline_get_passwd",
	GMP_SEMH_PLAYER_CMD_OFFLINE_GET_PASSWORD, proc_semh_player_offline_get_passwd));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_offline_set_passwd,
	1, "proc_semh_player_offline_set_passwd", "proc_semh_player_offline_set_passwd",
	GMP_SEMH_PLAYER_CMD_OFFLINE_SET_PASSWORD, proc_semh_player_offline_set_passwd));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_offline_update_passwd,
	1, "proc_semh_player_offline_update_passwd", "proc_semh_player_offline_update_passwd",
	GMP_SEMH_PLAYER_CMD_OFFLINE_UPDATE_PASSWORD, proc_semh_player_offline_update_passwd));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_offline_get_information,
	1, "proc_semh_player_offline_get_information", "proc_semh_player_offline_get_information",
	GMP_SEMH_PLAYER_CMD_OFFLINE_GET_INFORMATION, proc_semh_player_offline_get_information));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_offline_set_information,
	1, "proc_semh_player_offline_set_information", "proc_semh_player_offline_set_information",
	GMP_SEMH_PLAYER_CMD_OFFLINE_SET_INFORMATION, proc_semh_player_offline_set_information));


/////////////////////////////////音频部分内容/////////////////////////////////////////

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_set_audio_dev_info,
	1, "proc_semh_player_set_audio_dev_info", "proc_semh_player_set_audio_dev_info",
	GMP_SEMH_PLAYER_CMD_SET_AUDIO_DEV_INFO, proc_semh_player_set_dev_info));


CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_audio_play,
	1, "proc_semh_player_audio_play", "proc_semh_player_audio_play",
	GMP_SEMH_AUDIO_PLAYER_CMD_MEDIA_PLAY, proc_semh_player_audio_play));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_audio_play_update,
	1, "proc_semh_player_audio_play_update", "proc_semh_player_audio_play_update",
	GMP_SEMH_AUDIO_PLAYER_CMD_MEDIA_PLAY_UPDATE, proc_semh_player_audio_play_update));

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_audio_stop,
	1, "proc_semh_player_audio_stop", "proc_semh_player_audio_stop",
	GMP_SEMH_AUDIO_PLAYER_CMD_MEDIA_STOP, proc_semh_player_audio_stop));



////////////////////////////////媒体服务器部分实现//////////////////////////////////////////

CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_media_life_heart,
	1, "proc_semh_media_life_heart", "proc_semh_media_life_heart",
	GMP_SEMH_MEDIA_SERVER_CMD_LIFE_HEART, proc_semh_media_server_life_heart));


//////////////////////////////////背景服务器部分实现////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_background_life_heart,
	1, "proc_semh_background_life_heart", "proc_semh_background_life_heart",
	GMP_SEMH_PLAYER_BACKGROUND_CMD_LIFE_HEART, proc_semh_player_background_server_life_heart));


//////////////////////////////////回显服务器部分实现////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_css_hook_register_t,
	cp_css_hook_manager_type_css_hook,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_SEMH_HOOK_REGISTER(cp_css_semh_hook_type_player_client_life_heart,
	1, "proc_semh_client_life_heart", "proc_semh_client_life_heart",
	GMP_SEMH_CLIENT_BACKGROUND_CMD_LIFE_HEART, proc_semh_client_background_server_life_heart));


CP_MODULE_DEPENDENT_END()





 /************************************************************************/
 /* 添加入口函数的依赖关系                                                */
 /************************************************************************/
CP_CSS_HOOK_SET_ENTRY_DEPENDENT_BEGIN



//   	CP_CSS_ADD_ENTRY_DEPENDENT(cp_css_semh_hook_type_global, 
// 	cp_css_semh_hook_type_func_get_semh_hook, cp_css_semh_hook_type_player_media_close, cp_css_semh_hook_type_player_media_close, cp_css_semh_hook_type_end);
// 
// 	CP_CSS_ADD_ENTRY_DEPENDENT(cp_css_semh_hook_type_global,
// 		cp_css_semh_hook_type_func_parse_gmf_data, cp_css_semh_hook_type_end);




CP_CSS_HOOK_DEPENDENT_END






/************************************************************************/
/* 添加正确返回依赖关系                                                  */
/************************************************************************/
CP_CSS_HOOK_SET_RIGHT_DEPENDENT_BEGIN

CP_CSS_ADD_RIGHT_DEPENDENT(cp_css_semh_hook_type_global,
cp_css_semh_hook_type_func_check_semh_command, cp_css_semh_hook_type_global_destroy, cp_css_semh_hook_type_end);
 
CP_CSS_ADD_RIGHT_DEPENDENT(cp_css_semh_hook_type_func_check_semh_command,
	cp_css_semh_hook_type_func_parse_gmf_data, cp_css_semh_hook_type_end);
 
CP_CSS_ADD_RIGHT_DEPENDENT(cp_css_semh_hook_type_func_parse_gmf_data,
	cp_css_semh_hook_type_func_get_semh_hook, cp_css_semh_hook_type_end);


CP_CSS_HOOK_DEPENDENT_END

			 


/************************************************************************/
/* 添加错误返回依赖关系                                                  */
/************************************************************************/
CP_CSS_HOOK_SET_ERROR_DEPENDENT_BEGIN


CP_CSS_ADD_ERROR_DEPENDENT(cp_css_semh_hook_type_func_parse_gmf_data,
cp_css_semh_hook_type_func_gmf_error_data, cp_css_semh_hook_type_end);

// 	CP_CSS_ADD_ERROR_DEPENDENT(cp_css_semh_hook_type_player_media_close, 
// 	cp_css_semh_hook_type_func_parse_gmf_data, cp_css_semh_hook_type_end)



CP_CSS_HOOK_DEPENDENT_END