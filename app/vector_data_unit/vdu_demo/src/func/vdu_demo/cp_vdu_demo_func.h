/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VDU_DEMO_FUNC_INCLUDE_H_
#define _CP_VDU_DEMO_FUNC_INCLUDE_H_

#include "cp_vdu_demo_func_core.h"
#include "cp_socket.h"



//typedef struct cp_vdu_demo_func_s					cp_vdu_demo_func_t;



#pragma pack(1)



#define CP_VDU_DEMO_FUNC_FIELDS																	\
		CP_FUNC_FIELDS																			\
		cp_vdu_demo_func_thread_manager_t			*dftm;		/*线程管理器*/					\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_vdu_demo_func_s {
	CP_VDU_DEMO_FUNC_FIELDS									/*表示时间模块信息*/
};

#pragma pack()


cp_vdu_demo_func_t* create_vdu_demo_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_vdu_demo_func_info_t *info);
cp_int32_t destroy_vdu_demo_func(cp_vdu_demo_func_manager_t *manager, cp_vdu_demo_func_t* vdu_demo_func);


#endif


