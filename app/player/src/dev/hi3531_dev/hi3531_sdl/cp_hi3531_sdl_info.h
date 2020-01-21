/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_HI3531_SDL_INFO_INCLUDE_H_
#define _CP_HI3531_SDL_INFO_INCLUDE_H_



#include "cp_hi3531_sdl_core.h"




#define		CP_HI3531_SDL_NAME_MAX_LENGTH				32			//表示解码器最大的




//typedef	struct cp_hi3531_sdl_info_s					cp_hi3531_sdl_info_t;
typedef void(*cp_hi3531_sdl_cb)(cp_hi3531_sdl_t* th);



#pragma pack(1)


#define CP_HI3531_SDL_INFO_FIELDS																\
		CP_DEV_INFO_FIELDS																		\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_hi3531_sdl_info_s {
	CP_HI3531_SDL_INFO_FIELDS
};

#pragma pack()




#endif





