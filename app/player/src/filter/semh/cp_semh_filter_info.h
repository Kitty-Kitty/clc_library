/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_SEMH_FILTER_INFO_INCLUDE_H_
#define _CP_SEMH_FILTER_INFO_INCLUDE_H_

#include "cp_semh_filter_core.h"





//typedef	struct cp_semh_filter_info_s			cp_semh_filter_info_t;
typedef void(*cp_semh_filter_cb)(cp_semh_filter_t* th);




#pragma pack(1)


#define CP_SEMH_FILTER_INFO_FIELDS										\
		CP_FILTER_INFO_FIELDS											\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_semh_filter_info_s {
	CP_SEMH_FILTER_INFO_FIELDS
};

#pragma pack()




#endif





