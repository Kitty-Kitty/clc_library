/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VDU_PROC_INCLUDE_H_
#define _CP_VDU_PROC_INCLUDE_H_


#include "cp_vdu_core.h"



cp_int32_t init_vdu_other(cp_vdu_app_t *vdu, cp_app_info_t *app_info);
cp_int32_t start_vdu_other(cp_vdu_app_t *vdu, cp_app_info_t *app_info);
cp_int32_t stop_vdu_other(cp_vdu_app_t *vdu, cp_app_info_t *app_info);


#endif


