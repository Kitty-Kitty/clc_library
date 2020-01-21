/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-07

Description:

**************************************************************************/
#include "cp_semh_session_printf.h"


cp_char_t *print_session_information(cp_semh_session_t *session)
{
	cp_char_t				*tmp_print_buf = CP_APP_STR_NULL_FLAG;

	//cp_get_option_module(session, cp_module_option_get_print_information, &tmp_print_buf);
	tmp_print_buf = session->semh_si;
	return tmp_print_buf;
}

