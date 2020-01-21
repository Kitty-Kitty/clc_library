/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CSS_HOOK_TYPE_INCLUDE_H_
#define _CP_CSS_HOOK_TYPE_INCLUDE_H_

#include "cp_ipc_hook_core.h"




/************************************************************************/
/* 校验类型的合法性                                                      */
/************************************************************************/
#define CP_CHECK_CSS_HOOK_TYPE(type)						\
		((type >= 0 && type < cp_css_rtp_hook_type_end))




typedef enum cp_ipc_hook_manager_type_enum			cp_ipc_hook_manager_type_e;
typedef enum cp_css_rtp_hook_type_enum				cp_css_rtp_hook_type_e;



#pragma pack(1)

enum cp_ipc_hook_manager_type_enum
{
	cp_ipc_hook_manager_type_ipc_hook = CP_MODULE_MANAGER_TYPE_HOOK(1),
};



enum cp_css_rtp_hook_type_enum
{
	cp_css_rtp_hook_type_global = CP_MODULE_TYPE_HOOK(1),
	cp_css_rtp_hook_type_global_destroy,
	cp_css_rtp_hook_type_func_check_rtp_command,
	cp_css_rtp_hook_type_func_get_rtp_hook,
	cp_css_rtp_hook_type_func_parse_gmf_data,
	cp_css_rtp_hook_type_func_error_response,
	cp_css_rtp_hook_type_func_gmf_error_data,
	cp_css_rtp_hook_type_center_register_return,
	cp_css_rtp_hook_type_center_life_heart,
	cp_css_rtp_hook_type_ipc_life_heart_return,
	cp_css_rtp_hook_type_ipc_software_update,
	cp_css_rtp_hook_type_ipc_set_log,
	cp_css_rtp_hook_type_ipc_get_log,
	cp_css_rtp_hook_type_ipc_delete_log,
	cp_css_rtp_hook_type_ipc_query_log,
	cp_css_rtp_hook_type_ipc_get_dev_info,
	cp_css_rtp_hook_type_ipc_set_dev_info,
	cp_css_rtp_hook_type_ipc_start_dev,
	cp_css_rtp_hook_type_ipc_stop_dev,
	cp_css_rtp_hook_type_ipc_test_dev,
	cp_css_rtp_hook_type_ipc_set_network,
	cp_css_rtp_hook_type_ipc_set_focus,
	cp_css_rtp_hook_type_ipc_set_background,
	cp_css_rtp_hook_type_ipc_clear_background,
	cp_css_rtp_hook_type_ipc_reflesh_picture,
	cp_css_rtp_hook_type_ipc_media_play,
	cp_css_rtp_hook_type_ipc_media_play_update,
	cp_css_rtp_hook_type_ipc_media_layer_update,
	cp_css_rtp_hook_type_ipc_media_stop,
	cp_css_rtp_hook_type_ipc_media_close,
	cp_css_rtp_hook_type_ipc_media_get_channel_info,

	/////////////////////////////音频部分/////////////////////////////////////////////
	cp_css_rtp_hook_type_ipc_audio_play,
	cp_css_rtp_hook_type_ipc_audio_play_update,
	cp_css_rtp_hook_type_ipc_audio_layer_update,
	cp_css_rtp_hook_type_ipc_audio_stop,

	//////////////////////////////心跳部分内容////////////////////////////////////////////
	cp_css_rtp_hook_type_ipc_center_register,
	cp_css_rtp_hook_type_ipc_center_life_heart,
	cp_css_rtp_hook_type_ipc_media_life_heart,
	cp_css_rtp_hook_type_ipc_background_life_heart,
	cp_css_rtp_hook_type_ipc_client_life_heart,

	cp_css_rtp_hook_type_ipc_offline_get_passwd,
	cp_css_rtp_hook_type_ipc_offline_set_passwd,
	cp_css_rtp_hook_type_ipc_offline_update_passwd,
	cp_css_rtp_hook_type_ipc_offline_get_information,
	cp_css_rtp_hook_type_ipc_offline_set_information,

	cp_css_rtp_hook_type_end
};

#pragma pack()

#endif


