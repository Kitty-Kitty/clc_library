/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_FUSION_PLAYER_PROCESS_MANAGER_INCLUDE_H_
#define _CP_FUSION_PLAYER_PROCESS_MANAGER_INCLUDE_H_

#include "cp_fusion_player_process_core.h"




//typedef struct cp_fusion_player_process_manager_s						cp_fusion_player_process_manager_t;



#pragma pack(1)


#define CP_FUSION_PLAYER_PROCESS_MANAGER_FIELDS																		\
		CP_PROCESS_MANAGER_FIELDS																				\


struct cp_fusion_player_process_manager_s
{
	CP_FUSION_PLAYER_PROCESS_MANAGER_FIELDS
};


cp_fusion_player_process_manager_t* create_player_process_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_fusion_player_process_manager_info_t *info);
cp_int32_t destroy_player_process_manager(cp_app_t *app, cp_fusion_player_process_manager_t* manager);


#pragma pack()


#endif


