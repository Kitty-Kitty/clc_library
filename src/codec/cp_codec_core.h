/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_CODEC_CORE_INCLUDE_H_
#define _CP_CODEC_CORE_INCLUDE_H_





// #ifdef WIN32
// 
// typedef void *cp_codec_t;
// 
// #else
// 
// typedef pcodec_t cp_codec_t;
// 
// #endif
// 



typedef struct cp_codec_info_s							cp_codec_info_t;
typedef struct cp_codec_manager_info_s					cp_codec_manager_info_t;
typedef	struct cp_codec_s								cp_codec_t;
typedef	struct cp_codec_status_info_s					cp_codec_status_info_t;
typedef	struct cp_codec_callback_info_s					cp_codec_callback_info_t;
typedef struct cp_codec_manager_s						cp_codec_manager_t;
typedef	struct cp_codec_handles_s						cp_codec_handles_t;
typedef	struct cp_codec_manager_handles_s				cp_codec_manager_handles_t;







#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_media_core.h"
#include "cp_codec_option.h"
#include "cp_codec_info.h"
#include "cp_codec_manager_info.h"
#include "cp_codec.h"
#include "cp_codec_manager.h"




#endif


