/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_TDE_CORE_INCLUDE_H_
#define _CP_HI3531_TDE_CORE_INCLUDE_H_





typedef struct cp_hi3531_tde_info_s						cp_hi3531_tde_info_t;
typedef	struct cp_hi3531_tde_s							cp_hi3531_tde_t;




#if defined(CP_HI3531_DEV_MODE)
#include "hi_tde_api.h"
#endif


#include "cp_core.h"
#include "cp_dev_core.h"
#include "cp_hi3531_dev_core.h"
#include "cp_hi3531_tde_info.h"
#include "cp_hi3531_tde_conf.h"
#include "cp_hi3531_tde_option.h"
#include "cp_video_frame_process.h"
#include "cp_hi3531_tde.h"
#include "cp_hi3531_tde_proc.h"



#endif


