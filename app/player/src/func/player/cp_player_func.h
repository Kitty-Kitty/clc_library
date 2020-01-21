/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PLAYER_FUNC_INCLUDE_H_
#define _CP_PLAYER_FUNC_INCLUDE_H_

#include "cp_player_func_core.h"
#include "cp_socket.h"



//typedef struct cp_player_func_s					cp_player_func_t;



#pragma pack(1)



#define CP_PLAYER_FUNC_FIELDS																\
		CP_FUNC_FIELDS																		\
		cp_player_func_thread_manager_t			*pftm;		/*线程管理器*/					\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_player_func_s {
	CP_PLAYER_FUNC_FIELDS									/*表示时间模块信息*/
};

#pragma pack()


cp_player_func_t* create_player_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_player_func_info_t *info);
cp_int32_t destroy_player_func(cp_player_func_manager_t *manager, cp_player_func_t* player_func);


#endif


