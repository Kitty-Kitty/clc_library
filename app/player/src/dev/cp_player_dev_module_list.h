/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#ifndef _CP_PLAYER_DEV_MODULE_LIST_INCLUDE_H_
#define _CP_PLAYER_DEV_MODULE_LIST_INCLUDE_H_


#include "cp_player_dev_core.h"




#include "sdl/cp_sdl_av_dev_core.h"
#include "hi3531_dev/cp_hi3531_dev_core.h"
#include "hi3531_dev/cp_hi3531_dev_include.h"



#if 0

enum cp_player_dev_manager_type_enum
{
	cp_player_manager_type_hi3531_dev = CP_MODULE_MANAGER_TYPE_DEV(4),
};


enum cp_player_codec_module_type_enum
{
	cp_hi3531_dec_av_codec = CP_MODULE_TYPE_CODEC(4),
};

#endif


#endif


