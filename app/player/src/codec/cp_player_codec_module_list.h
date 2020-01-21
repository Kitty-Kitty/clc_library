/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#ifndef _CP_PLAYER_CODEC_MODULE_LIST_INCLUDE_H_
#define _CP_PLAYER_CODEC_MODULE_LIST_INCLUDE_H_


#include "cp_player_codec_core.h"
#include "hi3531/cp_hi3531_include.h"

#ifdef  WIN32
#include "hi3531/cp_hi3531_manager.h"
#include "ffmpeg/cp_ffmpeg_av_codec_core.h"
#else

#if (defined(CP_HI3531_VDEC_MODE) || defined(CP_HI3531_VDEC_MODE_DEBUG))
#include "hi3531/cp_hi3531_manager.h"
#else 
#include "ffmpeg/cp_ffmpeg_av_codec_core.h"
#endif

#endif //  WIN32




#if 0

enum cp_player_codec_manager_type_enum
{
	cp_player_manager_type_hi3531_codec = CP_MODULE_MANAGER_TYPE_CODEC(4),
};




enum cp_player_codec_module_type_enum
{
	cp_hi3531_dec_av_codec = CP_MODULE_TYPE_CODEC(4),
};

#endif


#endif


