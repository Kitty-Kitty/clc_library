/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_FUNC_STATUS_INCLUDE_H_
#define _CP_FUNC_STATUS_INCLUDE_H_

#include "cp_func_core.h"





//typedef	enum cp_func_status_enum			cp_func_status_e;




/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef	enum cp_func_status_enum {
	cp_func_status_match			=	B8(10000000),
	cp_func_status_successorerror	=	B8(00000001),
	cp_func_status_read_again		=	B8(00000010),
	cp_func_status_get_func			=	B8(00000100),
}cp_func_status_e;




#endif





