/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_HI3536_DEV_INCLUDE_H_
#define _CP_HI3536_DEV_INCLUDE_H_



#include "cp_lockfree_queue.h"
#include "cp_hi3536_dev_core.h"



//typedef struct cp_hi3536_dev_s					cp_hi3536_dev_t;




#pragma pack(1)

#define CP_HI3536_DEV_FIELDS																							\
		CP_VDU_DEV_FIELDS																							\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3536_dev_s {
	CP_HI3536_DEV_FIELDS								/*表示时间模块信息*/
};

#pragma pack()



cp_hi3536_dev_t* create_hi3536_dev(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_hi3536_dev_info_t *info);
cp_int32_t destroy_hi3536_dev(cp_codec_manager_t *manager, cp_hi3536_dev_t* hi3536_dev);

#endif


