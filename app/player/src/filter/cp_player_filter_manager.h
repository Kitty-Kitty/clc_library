/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PLAYER_FILTER_MANAGER_INCLUDE_H_
#define _CP_PLAYER_FILTER_MANAGER_INCLUDE_H_

#include "cp_player_filter_core.h"




//typedef struct cp_player_filter_manager_s						cp_player_filter_manager_t;



#pragma pack(1)


#define CP_PLAYER_FILTER_MANAGER_FIELDS																		\
		CP_FILTER_MANAGER_FIELDS																			\


struct cp_player_filter_manager_s
{
	CP_PLAYER_FILTER_MANAGER_FIELDS
};

#pragma pack()




cp_player_filter_manager_t* create_player_filter_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_player_filter_manager_info_t *info);
cp_int32_t destroy_player_filter_manager(cp_app_t *app, cp_player_filter_manager_t* manager);



#endif


