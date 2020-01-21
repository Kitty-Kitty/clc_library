/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FUSION_PLAYER_PROC_INCLUDE_H_
#define _CP_FUSION_PLAYER_PROC_INCLUDE_H_


#include "cp_fusion_player_core.h"



cp_int32_t init_player_other(cp_fusion_player_t *player, cp_app_info_t *app_info);
cp_int32_t start_player_other(cp_fusion_player_t *player, cp_app_info_t *app_info);
cp_int32_t stop_player_other(cp_fusion_player_t *player, cp_app_info_t *app_info);


cp_int32_t init_video_player(cp_fusion_player_t *player, cp_app_info_t *app_info);
cp_int32_t start_video_player(cp_fusion_player_t *player, cp_app_info_t *app_info);
cp_int32_t stop_video_player(cp_fusion_player_t *player, cp_app_info_t *app_info);



#endif


