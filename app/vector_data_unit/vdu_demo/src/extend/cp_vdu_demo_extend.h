/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VDU_DEMO_EXTEND_INCLUDE_H_
#define _CP_VDU_DEMO_EXTEND_INCLUDE_H_

#include "cp_vdu_demo_extend_core.h"



//typedef struct cp_vdu_demo_extend_s					cp_vdu_demo_extend_t;




#pragma pack(1)


#define CP_VDU_DEMO_EXTEND_FIELDS											\
		CP_EXTEND_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_vdu_demo_extend_s {
	CP_VDU_DEMO_EXTEND_FIELDS												/*表示时间模块信息*/
};


#pragma pack()



cp_vdu_demo_extend_t* create_vdu_demo_extend(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_vdu_demo_extend_info_t *info);
cp_int32_t destroy_vdu_demo_extend(cp_vdu_demo_extend_manager_t *manager, cp_vdu_demo_extend_t* vdu_demo_extend);


#endif


