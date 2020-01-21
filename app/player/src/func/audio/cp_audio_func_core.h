/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_AUDIO_FUNC_CORE_INCLUDE_H_
#define _CP_AUDIO_FUNC_CORE_INCLUDE_H_




#define CP_AUDIO_FUNC_USED_MULTI_THREAD							1					//使用多线程模式




typedef struct cp_audio_func_info_s								cp_audio_func_info_t;
typedef	struct cp_audio_func_manager_info_s						cp_audio_func_manager_info_t;
typedef	struct cp_audio_func_s									cp_audio_func_t;
typedef struct cp_audio_func_manager_s							cp_audio_func_manager_t;




#include "cp_core.h"
#include "cp_socket.h"
#include "cp_safe_queue.h"
#include "cp_func_core.h"
#include "cp_player_module_type.h"
#include "css_media_info.h"
#include "cp_player_func_manager_core.h"
#include "cp_audio_func_conf.h"
#include "cp_audio_func_info.h"
#include "cp_audio_func_manager_info.h"
#include "cp_audio_func.h"
#include "cp_audio_func_manager.h"





#endif


