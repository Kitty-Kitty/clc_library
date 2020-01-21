/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_THREAD_MANAGER_INFO_INCLUDE_H_
#define _CP_THREAD_MANAGER_INFO_INCLUDE_H_

#include "cp_core.h"





typedef	struct cp_thread_manager_info_s			cp_thread_manager_info_t;



#pragma pack(1)



#define CP_THREAD_MANAGER_INFO_FIELDS																				\
		CP_MODULE_MANAGER_INFO_FIELDS																				\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_thread_manager_info_s {
	CP_THREAD_MANAGER_INFO_FIELDS
};


#pragma pack()



#endif


