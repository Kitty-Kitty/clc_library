/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_TIMER_INFO_INCLUDE_H_
#define _CP_TIMER_INFO_INCLUDE_H_

#include "cp_timer_core.h"





//typedef	struct cp_timer_info_s			cp_timer_info_t;




#pragma pack(1)


#define CP_TIMER_INFO_FIELDS																						\
		CP_MODULE_INFO_FIELDS																						\
		cp_uint64_t		timeout;										/*��ʾ��ʱʱ�䣬��λ�����룩*/				\
		cp_uint64_t		repeat;											/*��ʾ�Ƿ�����*/								\
		cp_timer_cb		timer_cb;										/*��ʾʱ��ص�����*/							\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_timer_info_s {
	CP_TIMER_INFO_FIELDS
};


#pragma pack()



#endif





