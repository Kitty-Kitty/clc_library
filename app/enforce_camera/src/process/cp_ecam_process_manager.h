/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_PROCESS_MANAGER_INCLUDE_H_
#define _CP_ECAM_PROCESS_MANAGER_INCLUDE_H_

#include "cp_ecam_process_core.h"




//typedef struct cp_ecam_process_manager_s						cp_ecam_process_manager_t;



#pragma pack(1)


#define CP_ECAM_PROCESS_MANAGER_FIELDS																		\
		CP_PROCESS_MANAGER_FIELDS																				\


struct cp_ecam_process_manager_s
{
	CP_ECAM_PROCESS_MANAGER_FIELDS
};


cp_ecam_process_manager_t* create_ecam_process_manager
	(cp_module_manager_register_t *register_info, cp_app_t *app, cp_ecam_process_manager_info_t *info);
cp_int32_t destroy_ecam_process_manager(cp_app_t *app, cp_ecam_process_manager_t* manager);


#pragma pack()


#endif


