/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_ECAM_FILTER_MANAGER_INFO_INCLUDE_H_
#define _CP_ECAM_FILTER_MANAGER_INFO_INCLUDE_H_

#include "cp_filter_core.h"





//typedef	struct cp_ecam_filter_manager_info_s			cp_ecam_filter_manager_info_t;



#pragma pack(1)


/************************************************************************/
/*                                                                      */
/************************************************************************/

#define CP_ECAM_FILTER_MANAGER_INFO_FIELDS							\
		CP_FILTER_MANAGER_INFO_FIELDS									\


struct cp_ecam_filter_manager_info_s {
	CP_ECAM_FILTER_MANAGER_INFO_FIELDS
};

#pragma pack()



#endif


