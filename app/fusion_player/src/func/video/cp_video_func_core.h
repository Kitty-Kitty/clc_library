/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VIDEO_FUNC_CORE_INCLUDE_H_
#define _CP_VIDEO_FUNC_CORE_INCLUDE_H_




//#define CP_HI3531_MODE											1
#define CP_VIDEO_FUNC_USED_MULTI_THREAD								1					//使用多线程模式




 #define		cp_video_func_video_codec							cp_fusion_player_module_type_ffmpeg_codec
 #define		cp_video_func_video_dev								cp_fusion_player_module_type_sdl_dev




typedef struct cp_video_func_info_s								cp_video_func_info_t;
typedef	struct cp_video_func_manager_info_s						cp_video_func_manager_info_t;
typedef	struct cp_video_func_s									cp_video_func_t;
typedef struct cp_video_func_manager_s							cp_video_func_manager_t;
typedef	struct cp_video_func_handles_s							cp_video_func_handles_t;
typedef	struct cp_video_func_manager_handles_s					cp_video_func_manager_handles_t;




#include "cp_core.h"
#include "cp_socket.h"
#include "cp_safe_queue.h"
#include "cp_func_core.h"
#include "cp_fusion_player_module_type.h"
#include "css_media_info.h"
#include "cp_fusion_player_func_manager_core.h"
#include "cp_video_func_conf.h"
#include "cp_video_func_info.h"
#include "cp_video_func_manager_info.h"
#include "cp_video_func_struct.h"
#include "cp_video_func.h"
#include "cp_video_func_manager.h"





#endif


