/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_PLAYER_DEV_INCLUDE_H_
#define _CP_PLAYER_DEV_INCLUDE_H_

#include <stddef.h>
#include "uv.h"
#include "cp_player_dev_core.h"



//typedef struct cp_player_dev_s				cp_player_dev_t;





#pragma pack(1)


#define CP_PLAYER_DEV_FIELDS											\
		CP_DEV_FIELDS


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_player_dev_s {
	CP_PLAYER_DEV_FIELDS												/*表示时间模块信息*/
};

#pragma pack()




cp_player_dev_t* create_player_dev(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_player_dev_info_t *info);
cp_int32_t destroy_player_dev(cp_codec_manager_t *manager, cp_player_dev_t* player_dev);

#endif


