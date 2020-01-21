/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CSS_HOOK_TYPE_INCLUDE_H_
#define _CP_CSS_HOOK_TYPE_INCLUDE_H_

#include "cp_ecam_hook_core.h"




/************************************************************************/
/* 校验类型的合法性                                                      */
/************************************************************************/
#define CP_CHECK_CSS_HOOK_TYPE(type)						\
		((type >= 0 && type < cp_css_rtp_hook_type_end))




typedef enum cp_ecam_hook_manager_type_enum			cp_ecam_hook_manager_type_e;
typedef enum cp_css_rtp_hook_type_enum				cp_css_rtp_hook_type_e;



#pragma pack(1)

enum cp_ecam_hook_manager_type_enum
{
	cp_ecam_hook_manager_type_ecam_hook = CP_MODULE_MANAGER_TYPE_HOOK(1),
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
	cp_css_rtp_hook_type_ecam_life_heart_return,
	cp_css_rtp_hook_type_ecam_software_update,
	cp_css_rtp_hook_type_ecam_set_log,
	cp_css_rtp_hook_type_ecam_get_log,
	cp_css_rtp_hook_type_ecam_delete_log,
	cp_css_rtp_hook_type_ecam_query_log,
	cp_css_rtp_hook_type_ecam_get_dev_info,
	cp_css_rtp_hook_type_ecam_set_dev_info,
	cp_css_rtp_hook_type_ecam_start_dev,
	cp_css_rtp_hook_type_ecam_stop_dev,
	cp_css_rtp_hook_type_ecam_test_dev,
	cp_css_rtp_hook_type_ecam_set_network,
	cp_css_rtp_hook_type_ecam_set_focus,
	cp_css_rtp_hook_type_ecam_set_background,
	cp_css_rtp_hook_type_ecam_clear_background,
	cp_css_rtp_hook_type_ecam_reflesh_picture,
	cp_css_rtp_hook_type_ecam_media_play,
	cp_css_rtp_hook_type_ecam_media_play_update,
	cp_css_rtp_hook_type_ecam_media_layer_update,
	cp_css_rtp_hook_type_ecam_media_stop,
	cp_css_rtp_hook_type_ecam_media_close,
	cp_css_rtp_hook_type_ecam_media_get_channel_info,

	/////////////////////////////音频部分/////////////////////////////////////////////
	cp_css_rtp_hook_type_ecam_audio_play,
	cp_css_rtp_hook_type_ecam_audio_play_update,
	cp_css_rtp_hook_type_ecam_audio_layer_update,
	cp_css_rtp_hook_type_ecam_audio_stop,

	//////////////////////////////心跳部分内容////////////////////////////////////////////
	cp_css_rtp_hook_type_ecam_center_register,
	cp_css_rtp_hook_type_ecam_center_life_heart,
	cp_css_rtp_hook_type_ecam_media_life_heart,
	cp_css_rtp_hook_type_ecam_background_life_heart,
	cp_css_rtp_hook_type_ecam_client_life_heart,

	cp_css_rtp_hook_type_ecam_offline_get_passwd,
	cp_css_rtp_hook_type_ecam_offline_set_passwd,
	cp_css_rtp_hook_type_ecam_offline_update_passwd,
	cp_css_rtp_hook_type_ecam_offline_get_information,
	cp_css_rtp_hook_type_ecam_offline_set_information,

	cp_css_rtp_hook_type_end
};

#pragma pack()

#endif


