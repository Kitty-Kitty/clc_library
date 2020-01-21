/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_POOL_MANAGER_INCLUDE_H_
#define _CP_POOL_MANAGER_INCLUDE_H_

#include "cp_module_manager.h"




typedef struct cp_pool_manager_s					cp_pool_manager_t;



#pragma pack(1)


struct cp_pool_manager_s
{
	CP_MODULE_MANAGER_FIELDS
};


#pragma pack()


cp_pool_manager_t* create_pool_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_pool_manager_info_t *info);
cp_int32_t destroy_pool_manager(cp_app_t *app, cp_pool_manager_t* manager);



#endif


