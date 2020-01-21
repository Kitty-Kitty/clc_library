/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_EXTEND_MANAGER_INCLUDE_H_
#define _CP_ECAM_EXTEND_MANAGER_INCLUDE_H_

#include "cp_ecam_extend_core.h"




//typedef struct cp_ecam_extend_manager_s						cp_ecam_extend_manager_t;



#pragma pack(1)


#define CP_ECAM_EXTEND_MANAGER_FIELDS																		\
		CP_FILTER_MANAGER_FIELDS																			\
		cp_int32_t						number;								/*表示当前已经播放的数量*/		\
		cp_int32_t						max_number;							/*表示当前能够播放的总数量*/		\


struct cp_ecam_extend_manager_s
{
	CP_ECAM_EXTEND_MANAGER_FIELDS
};

#pragma pack()




cp_ecam_extend_manager_t* create_ecam_extend_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_ecam_extend_manager_info_t *info);
cp_int32_t destroy_ecam_extend_manager(cp_app_t *app, cp_ecam_extend_manager_t* manager);



#endif


