/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

 
#include "cp_ipc_module_list.h"
#include "cp_ipc_module_type.h"





/************************************************************************/
/* ��Ӹ�������ģ���������֧��                                           */
/************************************************************************/
CP_ROOT_MODULE_MANAGER_DEPENDENT_BEGIN(ipc)

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
/* ��Ӹ�����ģ���������֧��                                             */
/************************************************************************/
CP_SUB_MODULE_MANAGER_DEPENDENT_BEGIN(ipc)

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_hook, 1, "hook_module_manager", "uv hook module manager", create_ipc_hook_manager, destroy_ipc_hook_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_session, 1, "session_module_manager", "uv session module manager", create_ipc_session_manager, destroy_ipc_session_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_filter, 1, "filter_module_manager", "uv filter module manager", create_ipc_filter_manager, destroy_ipc_filter_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_process, 1, "ipc_process_module_manager", "ipc process module manager", create_ipc_process_manager, destroy_ipc_process_manager));

/////////////////////////////����������/////////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_func, 1, "ipc_func_module_manager", "ipc func module manager", create_ipc_func_manager, destroy_ipc_func_manager));

#if 0

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_audio_func, 1, "audio_func_module_manager", "audio func module manager", create_audio_func_manager, destroy_audio_func_manager));

CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_video_func, 1, "video_func_module_manager", "video func module manager", create_video_func_manager, destroy_video_func_manager));

#endif

///////////////////////////////������///////////////////////////////////////////
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_codec, 1, "ipc_codec_module_manager", "ipc codec module manager", create_ipc_codec_manager, destroy_ipc_codec_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_dev, 1, "ipc_dev_module_manager", "ipc dev module manager", create_ipc_dev_manager, destroy_ipc_dev_manager));
CP_ADD_SUB_MANAGER_DEPENDENT(
	cp_module_manager_register_t,
	CP_MANAGER_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_MANAGER_REGISTER(cp_ipc_manager_type_extend, 1, "ipc_extend_module_manager", "ipc extend module manager", create_ipc_extend_manager, destroy_ipc_extend_manager));

CP_MODULE_MANAGER_DEPENDENT_END()



/************************************************************************/
/* ���ģ���֧��                                                        */
/************************************************************************/
CP_MODULE_DEPENDENT_BEGIN(ipc)

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_session,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_session, 1, "session_module", "session module", create_rtp_session, destroy_rtp_session));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_filter,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_memh_filter, 1, "rtp_filter_module", "rtp filter module", create_rtp_filter, destroy_rtp_filter));
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_process,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_process, 1, "ipc_process_module", "ipc process module", create_ipc_process, destroy_ipc_process));

/////////////////////////////ҵ����ģ��/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_func, 1, "ipc_func_module", "ipc func module", create_ipc_func, destroy_ipc_func));

#if 0

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_audio_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_audio_func, 1, "audio_func_module", "audio func module", create_audio_func, destroy_audio_func));

CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_video_func,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_video_func, 1, "video_func_module", "video func module", create_video_func, destroy_video_func));

#endif


/////////////////////////////ע�������ģ��/////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_codec, 1, "ipc_codec_module", "ipc codec module", create_ipc_codec, destroy_ipc_codec));

#if defined(CP_HI3519_MODE)
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_hi3519_codec, 1, "hi3519_codec_module", "hi3519 codec module", create_hi3519_av_codec, destroy_hi3519_av_codec));
#endif
#if defined(CP_HI3559_MODE)
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_codec,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_hi3559_codec, 1, "hi3559_codec_module", "hi3559 codec module", create_hi3559_av_codec, destroy_hi3559_av_codec));
#endif


///////////////////////////�����豸ģ��///////////////////////////////////////////////
CP_ADD_MODULE_DEPENDENT(
	cp_module_register_t,
	cp_ipc_manager_type_dev,
	CP_MODULE_DEPENDENT_CALLBACK_NULL,
	CP_MODULE_REGISTER(cp_ipc_module_type_hi3519_dev, 1, "hi3519_module", "hi3519 codec module", create_hi3519_dev, destroy_hi3519_dev));


CP_MODULE_DEPENDENT_END()



