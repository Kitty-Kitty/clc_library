/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_HI3531_TDE_INFO_INCLUDE_H_
#define _CP_HI3531_TDE_INFO_INCLUDE_H_



#include "cp_hi3531_tde_core.h"




#define		CP_HI3531_TDE_NAME_MAX_LENGTH				32			//表示解码器最大的




//typedef	struct cp_hi3531_tde_info_s					cp_hi3531_tde_info_t;
typedef void(*cp_hi3531_tde_cb)(cp_hi3531_tde_t* th);



#pragma pack(1)


#define CP_HI3531_TDE_INFO_FIELDS																\
		CP_CODEC_INFO_FIELDS																	\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_tde_info_s {
	CP_HI3531_TDE_INFO_FIELDS
};

#pragma pack()




#endif





