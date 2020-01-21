/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_TIMER_MANAGER_INCLUDE_H_
#define _CP_TIMER_MANAGER_INCLUDE_H_

#include "cp_timer_core.h"




typedef struct cp_timer_manager_s					cp_timer_manager_t;



#pragma pack(1)


#define CP_TIMER_MANAGER_FIELDS						\
	CP_MODULE_MANAGER_FIELDS						\


struct cp_timer_manager_s
{
	CP_TIMER_MANAGER_FIELDS
};


#pragma pack()

cp_timer_manager_t* create_timer_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_timer_manager_info_t *info);
cp_int32_t destroy_timer_manager(cp_app_t *app, cp_timer_manager_t* manager);



#endif


