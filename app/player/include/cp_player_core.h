
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_player main include file 

**************************************************************************/


#ifndef _CP_PLAYER_CORE_INCLUDE_H_
#define _CP_PLAYER_CORE_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>


typedef	struct cp_player_info_s							cp_player_info_t;
typedef	struct cp_media_server_info_s					cp_media_server_info_t;
typedef struct cp_player_s								cp_player_t;




#include "cp_core.h"
#include "cp_include.h"
#include "cp_player_version.h"
#include "cp_player_default.h"
#include "css_core.h"
#include "cp_player_module_type.h"
#include "cp_player_socket_data.h"
#include "cp_player_conf_string.h"
#include "cp_player_heartbeat.h"
#include "cp_player_time.h"
#include "cp_media_play_manager.h"
#include "cp_media_play.h"
#include "cp_player_info.h"
#include "cp_media_server_info.h"
#include "cp_player.h"



#include "cp_player_proc.h"


#include "cp_format_media_play.h"


#endif