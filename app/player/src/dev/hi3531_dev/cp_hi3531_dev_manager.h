/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3531_DEV_MANAGER_INCLUDE_H_
#define _CP_HI3531_DEV_MANAGER_INCLUDE_H_



#include "cp_hi3531_dev_core.h"
#include "cp_hi3531_dev_manager_conf.h"

//typedef struct cp_hi3531_dev_manager_s								cp_hi3531_dev_manager_t;



#pragma pack(1)


/************************************************************************/
/*                                                                      */
/************************************************************************/
#define CP_HI3531_DEV_MANAGER_FIELDS																					\
		CP_DEV_MANAGER_FIELDS																							\
		cp_hi3531_dev_configure_t									conf_info;		/*表示hi3531配置信息*/				\


struct cp_hi3531_dev_manager_s
{
	CP_HI3531_DEV_MANAGER_FIELDS
};

#pragma pack()




cp_hi3531_dev_manager_t* create_hi3531_dev_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_hi3531_dev_manager_info_t *info);
cp_int32_t destroy_hi3531_dev_manager(cp_app_t *app, cp_hi3531_dev_manager_t* manager);

#endif


