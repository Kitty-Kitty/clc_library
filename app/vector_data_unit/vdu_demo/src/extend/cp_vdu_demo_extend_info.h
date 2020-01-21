/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_VDU_DEMO_EXTEND_INFO_INCLUDE_H_
#define _CP_VDU_DEMO_EXTEND_INFO_INCLUDE_H_

#include "cp_vdu_demo_extend_core.h"





//typedef	struct cp_vdu_demo_extend_info_s			cp_vdu_demo_extend_info_t;
typedef void(*cp_vdu_demo_extend_cb)(cp_vdu_demo_extend_t* th);




#pragma pack(1)


#define CP_VDU_DEMO_EXTEND_INFO_FIELDS										\
		CP_EXTEND_INFO_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_vdu_demo_extend_info_s {
	CP_VDU_DEMO_EXTEND_INFO_FIELDS
};

#pragma pack()




#endif





