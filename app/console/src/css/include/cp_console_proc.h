/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PLAYER_PROC_INCLUDE_H_
#define _CP_PLAYER_PROC_INCLUDE_H_


#include "cp_player_core.h"



cp_int32_t init_player_other(cp_player_t *player, cp_app_info_t *app_info);
cp_int32_t start_player_other(cp_player_t *player, cp_app_info_t *app_info);


cp_int32_t send_semh_connect_callback(cp_socket_t *s, cp_int32_t status);
cp_int32_t send_semh_write_callback(cp_socket_t *s, cp_int32_t status);

cp_int32_t send_semh_center_register(cp_player_t *player);

cp_int32_t send_semh_center_life_heart(cp_player_t *player, cp_socket_t *s);
cp_int32_t send_semh_media_life_heart(cp_player_t *player, cp_socket_t *s);
cp_int32_t send_semh_player_background_life_heart(cp_player_t *player, cp_socket_t *s);
cp_int32_t send_semh_client_background_life_heart(cp_player_t *player, cp_socket_t *s);


#endif


