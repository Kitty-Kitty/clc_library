/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-08-21

Description:

**************************************************************************/

#ifndef _CP_SEMH_REQUEST_INCLUDE_H_
#define _CP_SEMH_REQUEST_INCLUDE_H_


#include "cp_core.h"
#include "cp_include.h"
#include "cp_player_core.h"



cp_int32_t send_semh_connect_callback(cp_socket_t *s, cp_int32_t status);

cp_int32_t send_semh_write_heartbeat_callback(cp_socket_t *s, cp_int32_t status);

cp_int32_t send_semh_write_register_callback(cp_socket_t *s, cp_int32_t status);

cp_int32_t send_heartbeat_data_cycle(cp_heartbeat_manager_t *hm, cp_socket_t *s);

cp_int32_t send_device_heartbeat_data(cp_device_heartbeat_t *dhb, cp_socket_t *s);

cp_int32_t send_semh_center_register(cp_app_t *app);

//使用异步方式发送心跳
cp_int32_t send_semh_life_heart_async(cp_player_t *player);

//使用同步方式发送心跳
cp_int32_t send_semh_life_heart_sync(cp_player_t *player);

cp_int32_t send_semh_get_audio_channel_info(cp_player_t *player, cp_play_channel_info_t *cp_info);

void cp_semh_timer_task(cp_timer_t* timer);

cp_bool_t check_is_registe_now(cp_player_t *player);

#endif