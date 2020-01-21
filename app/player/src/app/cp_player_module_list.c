/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

 
#include "cp_player_module_list.h"
#include "cp_player_module_type.h"





/************************************************************************/
/* 添加各个基础模块管理器的支持                                           */
/************************************************************************/
CP_ROOT_MODULE_MANAGER_DEPENDENT_BEGIN(player)

CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_pool, 1, "pool_manager", "pool manager", create_pool_manager, destroy_pool_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_thread, 1, "thread_manager", "thread manager", create_thread_manager, destroy_thread_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_timer, 1, "timer_manager", "timer manager", create_timer_manager, destroy_timer_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_hook, 1, "hook_manager", "hook manager", create_hook_manager, destroy_hook_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_session, 1, "session_manager", "session manager", create_session_manager, destroy_session_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_filter, 1, "filter_manager", "filter manager", create_filter_manager, destroy_filter_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_process, 1, "process_manager", "process manager", create_process_manager, destroy_process_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_func, 1, "func_manager", "func manager", create_func_manager, destroy_func_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_socket, 1, "socket_manager", "socket manager", create_socket_manager, destroy_socket_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_codec, 1, "codec_manager", "codec manager", create_codec_manager, destroy_codec_manager));
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_dev, 1, "dev_manager", "dev manager", create_dev_manager, destroy_dev_manager));
// CP_ADD_ROOT_MANAGER_DEPENDENT(
// 	cp_module_manager_register_t,
// 	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
// 	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_extend, 1, "extend_manager", "extend manager", create_extend_manager, destroy_extend_manager));


CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(player)

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_hook, 1, "hook_module_manager", "uv hook module manager", create_css_hook_manager, destroy_css_hook_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_session, 1, "session_module_manager", "uv session module manager", create_css_session_manager, destroy_css_session_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_filter, 1, "filter_module_manager", "uv filter module manager", create_player_filter_manager, destroy_player_filter_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_process, 1, "player_process_module_manager", "player process module manager", create_player_process_manager, destroy_player_process_manager));

/////////////////////////////基础管理器/////////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_func, 1, "player_func_module_manager", "player func module manager", create_player_func_manager, destroy_player_func_manager));

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_audio_func, 1, "audio_func_module_manager", "audio func module manager", create_audio_func_manager, destroy_audio_func_manager));

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_video_func, 1, "video_func_module_manager", "video func module manager", create_video_func_manager, destroy_video_func_manager));

///////////////////////////////解码器///////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_codec, 1, "player_codec_module_manager", "player codec module manager", create_player_codec_manager, destroy_player_codec_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_dev, 1, "player_dev_module_manager", "player dev module manager", create_player_dev_manager, destroy_player_dev_manager));
// CP_ADD_SUB_MANAGER_DEPENDENT(
// 	cp_module_manager_register_t,
// 	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
// 	CP_MODULE_MANAGER_REGISTER(cp_player_manager_type_extend, 1, "player_extend_module_manager", "player extend module manager", create_player_extend_manager, destroy_player_extend_manager));


CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(player)

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_session,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_session, 1, "session_module", "session module", create_semh_session, destroy_semh_session));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_filter,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_semh_filter, 1, "semh_filter_module", "semh filter module", create_semh_filter, destroy_semh_filter));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_filter,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_memh_filter, 1, "memh_filter_module", "memh filter module", create_memh_filter, destroy_memh_filter));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_filter,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_ptp_filter, 1, "ptp_filter_module", "ptp filter module", create_ptp_filter, destroy_ptp_filter));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_process,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_process, 1, "player_process_module", "player process module", create_player_process, destroy_player_process));

/////////////////////////////业务处理模块/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_func, 1, "player_func_module", "player func module", create_player_func, destroy_player_func));

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_audio_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_audio_func, 1, "audio_func_module", "audio func module", create_audio_func, destroy_audio_func));

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_video_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_video_func, 1, "video_func_module", "video func module", create_video_func, destroy_video_func));

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_ptp_func, 1, "ptp_func_module", "ptp func module", create_ptp_func, destroy_ptp_func));

/////////////////////////////注册解码器模块/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_player_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_player_module_type_codec, 1, "player_codec_module", "player codec module", create_player_codec, destroy_player_codec));


#if !defined(CP_HI3531_VDEC_MODE)

	CP_ADD_MODULE_DEPENDENT(
		cp_module_register_t,
		cp_player_manager_type_codec,
		CP_MODULE_DEPENDENT_CALLBACK_NULL,
		CP_MODULE_REGISTER(cp_player_module_type_ffmpeg_codec, 1, "ffmpeg_codec_module", "ffmpeg codec module", create_ffmpeg_av_codec, destroy_ffmpeg_av_codec));

	///////////////////////////播放设备模块///////////////////////////////////////////////
	CP_ADD_MODULE_DEPENDENT(
		cp_module_register_t,
		cp_player_manager_type_dev,
		CP_MODULE_DEPENDENT_CALLBACK_NULL,
		CP_MODULE_REGISTER(cp_player_module_type_sdl_dev, 1, "sdl_dev_module", "sdl codec module", create_sdl_av_dev, destroy_sdl_av_dev));

#endif

/////////////////////////////扩展处理模块/////////////////////////////////////////////
// CP_ADD_MODULE_DEPENDENT(
// 	cp_module_register_t,
// 	cp_player_manager_type_extend,
// 	CP_MODULE_DEPENDENT_CALLBACK_NULL,
// 	CP_MODULE_REGISTER(cp_player_module_type_web_goahead_extend, 1, "web_goahead_extend", "web goahead extend", create_web_goahead_extend, destroy_web_goahead_extend));



CP_MODULE_DEPENDENT_END()



