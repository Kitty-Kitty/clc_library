/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_FILTER_INFO_INCLUDE_H_
#define _CP_FILTER_INFO_INCLUDE_H_

#include "cp_filter_core.h"





//typedef	struct cp_filter_info_s			cp_filter_info_t;




#pragma pack(1)


#define CP_FILTER_INFO_FIELDS																							\
		CP_MODULE_INFO_FIELDS																						\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_filter_info_s {
	CP_FILTER_INFO_FIELDS
};


#pragma pack()



#endif





