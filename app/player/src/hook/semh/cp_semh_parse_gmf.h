/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-21

Description:

**************************************************************************/

#ifndef _CP_SEMH_PARSE_GMF_INCLUDE_H_
#define _CP_SEMH_PARSE_GMF_INCLUDE_H_



#include "cp_semh_hook_core.h"



cp_play_channel_info_t* get_semh_play_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg, cp_char_t *buf, cp_int32_t len);
cp_play_channel_info_t* get_semh_play_information_play_info(cp_css_hook_t *hook, cp_semh_session_t *session, cp_void_t *arg, cp_char_t *buf, cp_int32_t len);
cp_int32_t destroy_play_info(cp_semh_session_t *session, cp_play_channel_info_t *pc_info);

#endif