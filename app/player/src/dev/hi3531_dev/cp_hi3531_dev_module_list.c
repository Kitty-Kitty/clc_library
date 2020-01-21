/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-09-18

Description:

**************************************************************************/

#include "cp_hi3531_dev_module_list.h"





cp_module_register_t  hi3531_dev_module_list[] = {
	CP_MODULE_REGISTER(cp_player_module_type_hi3531_dev_vo,
	1, "hi3531_dev_vo", "hi3531_dev_vo", create_hi3531_vo, destroy_hi3531_vo)
	CP_MODULE_REGISTER(cp_player_module_type_hi3531_dev_vpss,
	1, "hi3531_dev_vpss", "hi3531_dev_vpss", create_hi3531_vpss, destroy_hi3531_vpss)
	CP_MODULE_REGISTER(cp_player_module_type_hi3531_dev_tde,
	1, "hi3531_dev_tde", "hi3531_dev_tde", create_hi3531_tde, destroy_hi3531_tde)
	CP_MODULE_REGISTER(cp_player_module_type_hi3531_dev_sdl,
	1, "hi3531_dev_sdl", "hi3531_dev_sdl", create_hi3531_sdl, destroy_hi3531_sdl)
};


cp_int32_t hi3531_dev_module_list_size = cp_ary_size(hi3531_dev_module_list);








