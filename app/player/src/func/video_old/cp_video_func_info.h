/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_VIDEO_FUNC_INFO_INCLUDE_H_
#define _CP_VIDEO_FUNC_INFO_INCLUDE_H_

#include "cp_video_func_core.h"





//typedef	struct cp_video_func_info_s			cp_video_func_info_t;
typedef void(*cp_video_func_cb)(cp_video_func_t* th);




#pragma pack(1)



#define CP_VIDEO_FUNC_INFO_FIELDS										\
		CP_FUNC_INFO_FIELDS												\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_video_func_info_s {
	CP_VIDEO_FUNC_INFO_FIELDS
};

#pragma pack()

#endif





