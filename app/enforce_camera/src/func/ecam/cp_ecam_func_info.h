/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_ECAM_FUNC_INFO_INCLUDE_H_
#define _CP_ECAM_FUNC_INFO_INCLUDE_H_

#include "cp_ecam_func_core.h"





//typedef	struct cp_ecam_func_info_s			cp_ecam_func_info_t;
typedef void(*cp_ecam_func_cb)(cp_ecam_func_t* th);




#pragma pack(1)



#define CP_ECAM_FUNC_INFO_FIELDS										\
		CP_FUNC_INFO_FIELDS												\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ecam_func_info_s {
	CP_ECAM_FUNC_INFO_FIELDS
};

#pragma pack()

#endif





