/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_AUDIO_FUNC_INFO_INCLUDE_H_
#define _CP_AUDIO_FUNC_INFO_INCLUDE_H_

#include "cp_audio_func_core.h"





//typedef	struct cp_audio_func_info_s			cp_audio_func_info_t;
typedef void(*cp_audio_func_cb)(cp_audio_func_t* th);




#pragma pack(1)



#define CP_AUDIO_FUNC_INFO_FIELDS										\
		CP_FUNC_INFO_FIELDS												\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_audio_func_info_s {
	CP_AUDIO_FUNC_INFO_FIELDS
};

#pragma pack()

#endif





