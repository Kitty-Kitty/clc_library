/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_THREAD_MANAGER_INCLUDE_H_
#define _CP_THREAD_MANAGER_INCLUDE_H_



#include "cp_thread_core.h"




typedef struct cp_thread_manager_s					cp_thread_manager_t;




#pragma pack(1)


#define CP_THREAD_MANAGER_FIELDS																					\
		CP_MODULE_MANAGER_FIELDS																					\

struct cp_thread_manager_s
{
	CP_THREAD_MANAGER_FIELDS
};


#pragma pack()



cp_thread_manager_t* create_thread_manager(cp_module_manager_register_t *register_info, cp_app_t *app, cp_thread_manager_info_t *info);
cp_int32_t destroy_thread_manager(cp_app_t *app, cp_thread_manager_t* manager);



#endif


