
/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-23

Description:css_ecam main include file 

**************************************************************************/


#ifndef _CP_ECAM_CORE_INCLUDE_H_
#define _CP_ECAM_CORE_INCLUDE_H_

#include <stdio.h>
#include <stdlib.h>


typedef	struct cp_ecam_info_s							cp_ecam_info_t;
typedef	struct cp_media_server_info_s					cp_media_server_info_t;
typedef struct cp_media_play_manager_s					cp_media_play_manager_t;
typedef struct cp_ecam_s								cp_ecam_t;




#include "cp_core.h"
#include "cp_include.h"
#include "cp_ecam_version.h"
#include "cp_ecam_default.h"
#include "css_core.h"
#include "cp_ecam_module_type.h"
#include "cp_ecam_socket_data.h"
#include "cp_ecam_conf_string.h"
#include "cp_ecam_heartbeat.h"
#include "cp_channel_manager.h"
#include "cp_media_play.h"
#include "cp_ecam_info.h"
#include "cp_media_server_info.h"
#include "cp_ecam.h"



#include "cp_ecam_proc.h"



#endif