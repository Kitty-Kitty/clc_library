/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-24

Description:

**************************************************************************/

#ifndef _CP_PLAYER_MODULE_TYPE_INCLUDE_H_
#define _CP_PLAYER_MODULE_TYPE_INCLUDE_H_


#include "cp_include.h"


enum cp_player_manager_type_enum
{
	cp_player_manager_type_hook = CP_MODULE_MANAGER_TYPE_HOOK(1),
	cp_player_manager_type_session = CP_MODULE_MANAGER_TYPE_SESSION(1),
	cp_player_manager_type_filter = CP_MODULE_MANAGER_TYPE_FILTER(1),
	cp_player_manager_type_process = CP_MODULE_MANAGER_TYPE_PROCESS(1),
	/////////////////////////音视频处理相关内容////////////////////////////////
	cp_player_manager_type_func = CP_MODULE_MANAGER_TYPE_FUNC(1),
	cp_player_manager_type_audio_func = CP_MODULE_MANAGER_TYPE_FUNC(2),
	cp_player_manager_type_video_func = CP_MODULE_MANAGER_TYPE_FUNC(3),
	cp_player_manager_type_ptp_func = CP_MODULE_MANAGER_TYPE_FUNC(4),
	/////////////////////////解码器管理器//////////////////////////////////////
	cp_player_manager_type_codec = CP_MODULE_MANAGER_TYPE_CODEC(1),
	cp_player_manager_type_hi3531_codec = CP_MODULE_MANAGER_TYPE_CODEC(2),
	/////////////////////////设备管理器////////////////////////////////////////
	cp_player_manager_type_dev = CP_MODULE_MANAGER_TYPE_DEV(1),
	cp_player_manager_type_hi3531_dev = CP_MODULE_MANAGER_TYPE_DEV(2),
	//////////////////////////////////////////////////////////////////////////
	cp_player_manager_type_extend = CP_MODULE_MANAGER_TYPE_EXTEND(1),
};



enum cp_player_module_type_enum
{
	cp_player_module_type_session = CP_MODULE_TYPE_SESSION(1),
	cp_player_module_type_semh_filter = CP_MODULE_TYPE_FILTER(1),
	cp_player_module_type_memh_filter = CP_MODULE_TYPE_FILTER(2),
	cp_player_module_type_ptp_filter = CP_MODULE_TYPE_FILTER(3),
	cp_player_module_type_process = CP_MODULE_TYPE_PROCESS(1),
	////////////////////////音视频处理相关内容//////////////////////////////////////////////////
	cp_player_module_type_func = CP_MODULE_TYPE_FUNC(1),
	cp_player_module_type_audio_func = CP_MODULE_TYPE_FUNC(2),
	cp_player_module_type_video_func = CP_MODULE_TYPE_FUNC(3),
	cp_player_module_type_ptp_func = CP_MODULE_TYPE_FUNC(4),
	//////////////////////////////////////////////////////////////////////////////////////////
	cp_player_module_type_codec = CP_MODULE_TYPE_CODEC(1),
	cp_player_module_type_ffmpeg_codec = CP_MODULE_TYPE_CODEC(2),
	cp_player_module_type_hi3531_dec_codec = CP_MODULE_TYPE_CODEC(3),
	//////////////////////////////////////////////////////////////////////////////////////////
	cp_player_module_type_sdl_dev = CP_MODULE_TYPE_DEV(1),
	cp_player_module_type_hi3531_dev_vo = CP_MODULE_TYPE_DEV(2),
	cp_player_module_type_hi3531_dev_vpss = CP_MODULE_TYPE_DEV(3),
	cp_player_module_type_hi3531_dev_tde = CP_MODULE_TYPE_DEV(4),
	cp_player_module_type_hi3531_dev_sdl = CP_MODULE_TYPE_DEV(5),
	/////////////////////////////////////////////////////////////////////////////////////////
	cp_player_module_type_hi3531_dev = CP_MODULE_TYPE_DEV(2),
	cp_player_module_type_web_goahead_extend = CP_MODULE_TYPE_EXTEND(1),
};



#endif