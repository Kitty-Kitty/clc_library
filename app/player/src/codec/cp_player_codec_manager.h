/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PLAYER_CODEC_MANAGER_INCLUDE_H_
#define _CP_PLAYER_CODEC_MANAGER_INCLUDE_H_



#include "cp_player_codec_core.h"
#include "cp_player_codec_module_list.h"



typedef struct cp_player_codec_manager_s					cp_player_codec_manager_t;



#pragma pack(1)


/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CP_PLAYER_CODEC_MANAGER_FIELDS																				\
		CP_CODEC_MANAGER_FIELDS																						\
		cp_module_manager_t							*hi3531_manager;		/*表示连接操作使用的定时器*/				\


struct cp_player_codec_manager_s
{
	CP_PLAYER_CODEC_MANAGER_FIELDS
};

#pragma pack()




cp_player_codec_manager_t* create_player_codec_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_player_codec_manager_info_t *info);
cp_int32_t destroy_player_codec_manager(cp_app_t *app, cp_player_codec_manager_t* manager);

#endif


