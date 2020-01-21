/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_DEV_STATUS_INCLUDE_H_
#define _CP_DEV_STATUS_INCLUDE_H_

#include "cp_dev_core.h"





//typedef	enum cp_dev_status_enum			cp_dev_status_e;




/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef	enum cp_dev_status_enum {
	cp_dev_status_match				=	B8(10000000),
	cp_dev_status_successorerror	=	B8(00000001),
	cp_dev_status_read_again		=	B8(00000010),
	cp_dev_status_get_func			=	B8(00000100),
}cp_dev_status_e;




#endif





