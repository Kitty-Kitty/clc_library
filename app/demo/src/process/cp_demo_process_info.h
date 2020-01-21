/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_DEMO_PROCESS_INFO_INCLUDE_H_
#define _CP_DEMO_PROCESS_INFO_INCLUDE_H_

#include "cp_demo_process_core.h"





//typedef	struct cp_demo_process_info_s			cp_demo_process_info_t;
typedef void(*cp_demo_process_cb)(cp_demo_process_t* th);



#pragma pack(1)


#define CP_DEMO_PROCESS_INFO_FIELDS										\
		CP_PROCESS_INFO_FIELDS												\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_demo_process_info_s {
	CP_DEMO_PROCESS_INFO_FIELDS
};



#pragma pack()


#endif





