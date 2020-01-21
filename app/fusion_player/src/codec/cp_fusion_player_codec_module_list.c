/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#include "cp_fusion_player_codec_module_list.h"




 cp_module_register_t  player_codec_module_manager_list[] = {
 	CP_MODULE_REGISTER(cp_hi3531_codec_manager,
 	1, "hi3531_manager", "hi3531_manager", CP_NULL, CP_NULL)
 };
 
 cp_int32_t player_codec_module_manager_list_size = 0;







