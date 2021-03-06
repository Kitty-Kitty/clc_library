/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-05

Description:

**************************************************************************/

#ifndef _CP_FUSION_PLAYER_CODEC_MODULE_OPTION_INCLUDE_H_
#define _CP_FUSION_PLAYER_CODEC_MODULE_OPTION_INCLUDE_H_


#include "cp_module_option.h"
#include "cp_bit.h"




typedef enum cp_fusion_player_codec_option_enum		cp_fusion_player_codec_option_e;



/************************************************************************/
/* 定义module的设置属性                                                  */
/************************************************************************/
enum cp_fusion_player_codec_option_enum
{
	cp_fusion_player_codec_set_option_codec_info			= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000001, 00000000)),
	cp_fusion_player_codec_set_option_codec_async			= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000000, 00000100)),

	cp_fusion_player_codec_set_option_audio_convert_info	= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000000, 00000010)),
	cp_fusion_player_codec_set_option_open_media_file		= CP_MODULE_OPTION_MAKE_SET_FLAG(B16(00000000, 00001000)),

	cp_fusion_player_codec_get_option_codec_info			= CP_MODULE_OPTION_MAKE_GET_FLAG(B16(00000001, 00000000)),
};



#endif