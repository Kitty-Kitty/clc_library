/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_VDU_DEMO_SESSION_INFO_INCLUDE_H_
#define _CP_VDU_DEMO_SESSION_INFO_INCLUDE_H_

#include "cp_session_core.h"





//typedef	struct cp_vdu_demo_session_info_s			cp_vdu_demo_session_info_t;
//typedef void(*cp_session_cb)(cp_session_t* th);




#pragma pack(1)


#define CP_VDU_DEMO_SESSION_INFO_FIELDS																					\
		CP_SESSION_INFO_FIELDS																						\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_vdu_demo_session_info_s {
	CP_VDU_DEMO_SESSION_INFO_FIELDS
};


#pragma pack()



#endif




