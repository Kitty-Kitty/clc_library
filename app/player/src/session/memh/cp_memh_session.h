/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SESSION_INCLUDE_H_
#define _CP_SESSION_INCLUDE_H_

#include "cp_css_session_core.h"
#include "cp_socket.h"



typedef struct cp_memh_session_s				cp_memh_session_t;



#pragma pack(1)


#define CP_SESSION_FIELDS												\
		CP_SOCKET_FIELDS												\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_memh_session_s {
	CP_SESSION_FIELDS												/*表示时间模块信息*/
};

#pragma pack()




#endif


