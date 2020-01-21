/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_PROC_INCLUDE_H_
#define _CP_ECAM_PROC_INCLUDE_H_


#include "cp_ecam_core.h"



cp_int32_t init_ecam_other(cp_ecam_t *ecam, cp_app_info_t *app_info);
cp_int32_t start_ecam_other(cp_ecam_t *ecam, cp_app_info_t *app_info);
cp_int32_t stop_ecam_other(cp_ecam_t *ecam, cp_app_info_t *app_info);


#endif


