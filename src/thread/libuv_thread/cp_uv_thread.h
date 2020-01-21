/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_UV_THREAD_INCLUDE_H_
#define _CP_UV_THREAD_INCLUDE_H_

#include <stddef.h>
#include "uv.h"
#include "cp_uv_thread_core.h"



//typedef struct cp_uv_thread_s				cp_uv_thread_t;




#pragma pack(1)


#define CP_UV_THREAD_FIELDS												\
		CP_THREAD_FIELDS


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_uv_thread_s {
	CP_UV_THREAD_FIELDS												/*表示时间模块信息*/
	uv_thread_t							thread;						/*描述uv线程信息*/
};



#pragma pack()



cp_uv_thread_t* create_uv_thread(cp_module_register_t *register_info, cp_thread_manager_t *manager, cp_uv_thread_info_t *info);
cp_int32_t destroy_uv_thread(cp_thread_manager_t *manager, cp_uv_thread_t* uv_thread);

#endif


