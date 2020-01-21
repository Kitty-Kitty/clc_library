/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_SESSION_INFO_INCLUDE_H_
#define _CP_SESSION_INFO_INCLUDE_H_

#include "cp_css_session_core.h"





typedef	struct cp_memh_session_info_s			cp_memh_session_info_t;




#pragma pack(1)


#define CP_SESSION_INFO_FIELDS																						\
		CP_MODULE_INFO_FIELDS																						\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_memh_session_info_s {
	CP_SESSION_INFO_FIELDS
};


#pragma pack()



#endif





