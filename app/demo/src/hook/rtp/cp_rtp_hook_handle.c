/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-07

Description:

**************************************************************************/
#include "cp_rtp_hook_handle.h"

cp_int32_t func_global(cp_demo_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_global_destroy(cp_demo_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_check_rtp_command(cp_demo_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_get_rtp_hook(cp_demo_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_parse_gmf_data(cp_demo_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_gmf_error_data(cp_demo_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg)
{
	return 0;
}

cp_int32_t func_error_response(cp_demo_hook_t *hook, cp_rtp_session_t *session, cp_void_t *arg, cp_char_t *fmt, ...)
{
	return 0;
}

