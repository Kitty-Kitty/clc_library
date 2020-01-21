/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_HI3519_DEV_INFO_INCLUDE_H_
#define _CP_HI3519_DEV_INFO_INCLUDE_H_



#include "cp_lockfree_queue.h"
#include "cp_hi3516c_dev_core.h"





//typedef	struct cp_hi3516c_dev_info_s			cp_hi3516c_dev_info_t;


typedef void(*cp_hi3516c_dev_cb)(cp_hi3516c_dev_t* th);




#pragma pack(1)


#define CP_HI3519_DEV_INFO_FIELDS																						\
		CP_DEV_INFO_FIELDS																								\



/************************************************************************/
/* sdl…Ë÷√–≈œ¢                                                           */
/************************************************************************/
struct cp_hi3516c_dev_info_s {
	CP_HI3519_DEV_INFO_FIELDS
};

#pragma pack()




#endif





