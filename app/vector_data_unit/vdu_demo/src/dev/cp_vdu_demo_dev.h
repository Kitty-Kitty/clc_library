/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VDU_DEMO_DEV_INCLUDE_H_
#define _CP_VDU_DEMO_DEV_INCLUDE_H_

#include <stddef.h>
#include "uv.h"
#include "cp_vdu_demo_dev_core.h"



//typedef struct cp_vdu_demo_dev_s				cp_vdu_demo_dev_t;





#pragma pack(1)


#define CP_VDU_DEMO_DEV_FIELDS											\
		CP_DEV_FIELDS


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_vdu_demo_dev_s {
	CP_VDU_DEMO_DEV_FIELDS												/*表示时间模块信息*/
};

#pragma pack()




cp_vdu_demo_dev_t* create_vdu_demo_dev(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_vdu_demo_dev_info_t *info);
cp_int32_t destroy_vdu_demo_dev(cp_codec_manager_t *manager, cp_vdu_demo_dev_t* vdu_demo_dev);

#endif


