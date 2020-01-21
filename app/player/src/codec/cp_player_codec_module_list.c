/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#include "cp_player_codec_module_list.h"




#if (defined(CP_HI3531_VDEC_MODE) || defined(CP_HI3531_VDEC_MODE_DEBUG))
cp_module_register_t  player_codec_module_manager_list[] = {
	CP_MODULE_REGISTER(cp_player_manager_type_hi3531_codec,
	1, "hi3531_manager", "hi3531_manager", create_hi3531_manager, destroy_hi3531_manager)
};

cp_int32_t player_codec_module_manager_list_size = cp_ary_size(player_codec_module_manager_list);
#else
 cp_module_register_t  player_codec_module_manager_list[] = {
 	CP_MODULE_REGISTER(cp_player_manager_type_hi3531_codec,
 	1, "hi3531_manager", "hi3531_manager", CP_NULL, CP_NULL)
 };
 
 cp_int32_t player_codec_module_manager_list_size = 0;
#endif







