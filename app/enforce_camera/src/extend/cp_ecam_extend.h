/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_EXTEND_INCLUDE_H_
#define _CP_ECAM_EXTEND_INCLUDE_H_

#include "cp_ecam_extend_core.h"



//typedef struct cp_ecam_extend_s					cp_ecam_extend_t;




#pragma pack(1)


#define CP_ECAM_EXTEND_FIELDS											\
		CP_EXTEND_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ecam_extend_s {
	CP_ECAM_EXTEND_FIELDS												/*表示时间模块信息*/
};


#pragma pack()



cp_ecam_extend_t* create_ecam_extend(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_ecam_extend_info_t *info);
cp_int32_t destroy_ecam_extend(cp_ecam_extend_manager_t *manager, cp_ecam_extend_t* ecam_extend);


#endif


