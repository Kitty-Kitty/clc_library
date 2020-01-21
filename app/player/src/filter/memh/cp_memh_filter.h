/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_MEMH_FILTER_INCLUDE_H_
#define _CP_MEMH_FILTER_INCLUDE_H_

#include "cp_memh_filter_core.h"
#include "cp_socket.h"



//typedef struct cp_memh_filter_s					cp_memh_filter_t;




#pragma pack(1)


#define CP_MEMH_FILTER_FIELDS											\
		CP_FILTER_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_memh_filter_s {
	CP_MEMH_FILTER_FIELDS												/*表示时间模块信息*/
};


#pragma pack()



cp_memh_filter_t* create_memh_filter(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_memh_filter_info_t *info);
cp_int32_t destroy_memh_filter(cp_memh_filter_manager_t *manager, cp_memh_filter_t* memh_filter);


#endif


