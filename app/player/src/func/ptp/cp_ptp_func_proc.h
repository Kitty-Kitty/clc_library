/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-01-04

Description:

**************************************************************************/

#ifndef _CP_PTP_FUNC_PROC_INCLUDE_H_
#define _CP_PTP_FUNC_PROC_INCLUDE_H_


#include "cp_ptp_func_core.h"


//打开debug 文件
cp_int32_t open_ptp_debug_file(cp_ptp_func_t *ptp_func, cp_int32_t group_id);

//关闭debug 文件
cp_int32_t close_ptp_debug_file(cp_ptp_func_t *ptp_func);

//打印ptp  debug信息
cp_int32_t print_ptp_debug_info(cp_ptp_func_t *ptp_func, cp_player_timestamp_t *pt);

#endif