/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_SESSION_OPTION_INCLUDE_H_
#define _CP_SESSION_OPTION_INCLUDE_H_

#include "cp_session_core.h"





//typedef	enum cp_session_option_enum			cp_session_option_e;




/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef	enum cp_session_option_enum {
	CP_SESSION_OPTION_SET_HISTORY = CP_MODULE_OPTION_MAKE_SET_FLAG(B8(10000000)),
}cp_session_option_e;


#endif





