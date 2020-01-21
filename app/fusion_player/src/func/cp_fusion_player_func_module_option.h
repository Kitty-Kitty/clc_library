/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-13

Description:

**************************************************************************/

#ifndef _CP_FUSION_PLAYER_FUNC_MODULE_OPTION_INCLUDE_H_
#define _CP_FUSION_PLAYER_FUNC_MODULE_OPTION_INCLUDE_H_




#include "cp_bit.h"
#include "cp_module_option.h"




typedef enum cp_fusion_player_func_option_enum		cp_fusion_player_func_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
enum cp_fusion_player_func_option_enum
{
	cp_fusion_player_func_set_option_stop_media_play	= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000000, 00000010)),			//停止一个播放，optval为cp_module_info_t
	cp_fusion_player_func_set_option_update_media_info = CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000000, 00000100)),			//更新一个播放信息

	cp_fusion_player_func_get_option_media_channel_info = CP_MODULE_OPTION_MAKE_GET_FLAG(B16(00000000, 00000100)),			//获取一个播放信息
};



#endif