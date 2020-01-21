/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-11-22

Description:

**************************************************************************/

#ifndef _CP_SEMH_MAKE_GMF_INCLUDE_H_
#define _CP_SEMH_MAKE_GMF_INCLUDE_H_


#include "cp_semh_hook_core.h"



/************************************************************************/
/* 前端请求接口                                                          */
/************************************************************************/
cp_int32_t make_semh_center_register(cp_player_t *player, cp_buf_t **gmf_data);
cp_int32_t make_semh_center_cancel_register(cp_player_t *player, cp_buf_t **gmf_data);
cp_int32_t make_device_semh_life_heart_data(cp_player_t *player, cp_int32_t command, cp_buf_t* out_buf);
cp_int32_t make_semh_center_exception(cp_player_t *player, cp_buf_t **gmf_data, cp_exception_info_t *exp_info);
cp_int32_t make_semh_request_data(cp_player_t *player, cp_int32_t command, gmp_gmf_t *src_gmf, cp_buf_t **gmf_data);
cp_int32_t make_semh_get_audio_channel_info(cp_player_t *player, cp_play_channel_info_t *cp_info, cp_buf_t **gmf_data);


#endif