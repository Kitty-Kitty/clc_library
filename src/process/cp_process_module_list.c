/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/



#if 0




#include "cp_process_module_list.h"



cp_module_register_t  process_module_manager_list[] = {
	CP_MODULE_REGISTER(cp_process_manager_type_player,
	1, "player_process_module_manager", "player process module manager", create_player_process_manager, destroy_player_process_manager)
};

cp_int32_t process_module_manager_list_size = cp_ary_size(process_module_manager_list);




cp_module_register_t  process_module_list[] = {
	CP_MODULE_REGISTER(cp_process_module_type_player, 1, "player_process_module", "player process module", create_player_process, destroy_player_process)
};
 
cp_int32_t process_module_list_size = cp_ary_size(process_module_list);


#endif


