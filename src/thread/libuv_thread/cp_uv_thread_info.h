/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_UV_THREAD_INFO_INCLUDE_H_
#define _CP_UV_THREAD_INFO_INCLUDE_H_

#include "cp_uv_thread_core.h"






//typedef	struct cp_uv_thread_info_s			cp_uv_thread_info_t;





#pragma pack(1)


#define CP_UV_THREAD_INFO_FIELDS																					\
		CP_THREAD_INFO_FIELDS																						\

/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_uv_thread_info_s {
	CP_UV_THREAD_INFO_FIELDS
};

#pragma pack()






#endif





