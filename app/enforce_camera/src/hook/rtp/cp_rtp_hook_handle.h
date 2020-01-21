/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SEMH_HOOK_HANDLE_INCLUDE_H_
#define _CP_SEMH_HOOK_HANDLE_INCLUDE_H_


#include "cp_rtp_hook_core.h"


/************************************************************************/
/* 系统基础函数                                                         */
/************************************************************************/
cp_int32_t func_global(cp_ecam_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg);
cp_int32_t func_global_destroy(cp_ecam_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg);
cp_int32_t func_check_rtp_command(cp_ecam_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg);
cp_int32_t func_get_rtp_hook(cp_ecam_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg);
cp_int32_t func_parse_gmf_data(cp_ecam_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg);
cp_int32_t func_gmf_error_data(cp_ecam_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg);
cp_int32_t func_error_response(cp_ecam_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg, cp_char_t *fmt, ...);


#endif

