/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

 
#include "cp_ecam_module_list.h"
#include "cp_ecam_module_type.h"





/************************************************************************/
/* 添加各个基础模块管理器的支持                                           */
/************************************************************************/
CP_ROOT_MODULE_MANAGER_DEPENDENT_BEGIN(ecam)

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
CP_ADD_ROOT_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_module_manager_type_extend, 1, "extend_manager", "extend manager", create_extend_manager, destroy_extend_manager));

CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加各个子模块管理器的支持                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(ecam)

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_hook, 1, "hook_module_manager", "uv hook module manager", create_ecam_hook_manager, destroy_ecam_hook_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_session, 1, "session_module_manager", "uv session module manager", create_ecam_session_manager, destroy_ecam_session_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_filter, 1, "filter_module_manager", "uv filter module manager", create_ecam_filter_manager, destroy_ecam_filter_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_process, 1, "ecam_process_module_manager", "ecam process module manager", create_ecam_process_manager, destroy_ecam_process_manager));

/////////////////////////////基础管理器/////////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_func, 1, "ecam_func_module_manager", "ecam func module manager", create_ecam_func_manager, destroy_ecam_func_manager));

#if 0

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_audio_func, 1, "audio_func_module_manager", "audio func module manager", create_audio_func_manager, destroy_audio_func_manager));

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_video_func, 1, "video_func_module_manager", "video func module manager", create_video_func_manager, destroy_video_func_manager));

#endif

///////////////////////////////解码器///////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_codec, 1, "ecam_codec_module_manager", "ecam codec module manager", create_ecam_codec_manager, destroy_ecam_codec_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_dev, 1, "ecam_dev_module_manager", "ecam dev module manager", create_ecam_dev_manager, destroy_ecam_dev_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ecam_manager_type_extend, 1, "ecam_extend_module_manager", "ecam extend module manager", create_ecam_extend_manager, destroy_ecam_extend_manager));

CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* 添加模块的支持                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(ecam)

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_session,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_session, 1, "session_module", "session module", create_rtp_session, destroy_rtp_session));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_filter,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_memh_filter, 1, "rtp_filter_module", "rtp filter module", create_rtp_filter, destroy_rtp_filter));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_process,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_process, 1, "ecam_process_module", "ecam process module", create_ecam_process, destroy_ecam_process));

/////////////////////////////业务处理模块/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_func, 1, "ecam_func_module", "ecam func module", create_ecam_func, destroy_ecam_func));

#if 0

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_audio_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_audio_func, 1, "audio_func_module", "audio func module", create_audio_func, destroy_audio_func));

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_video_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_video_func, 1, "video_func_module", "video func module", create_video_func, destroy_video_func));

#endif


/////////////////////////////注册解码器模块/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_codec, 1, "ecam_codec_module", "ecam codec module", create_ecam_codec, destroy_ecam_codec));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_hi3516c_codec, 1, "hi3516c_codec_module", "hi3516c codec module", create_hi3516c_av_codec, destroy_hi3516c_av_codec));

///////////////////////////播放设备模块///////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ecam_manager_type_dev,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ecam_module_type_hi3516c_dev, 1, "hi3516c_module", "hi3516c codec module", create_hi3516c_dev, destroy_hi3516c_dev));


CP_MODULE_DEPENDENT_END()



