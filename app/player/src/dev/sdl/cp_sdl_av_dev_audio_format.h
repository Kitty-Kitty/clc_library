/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-21

Description:

**************************************************************************/

#ifndef _CP_SDL_AV_DEV_FORMAT_INCLUDE_H_
#define _CP_SDL_AV_DEV_FORMAT_INCLUDE_H_



#include "SDL.h"
#include "cp_media_type.h"
#include "cp_sdl_av_dev_core.h"




typedef struct cp_sdl_av_dev_audio_format_s					cp_sdl_av_dev_audio_format_t;




/************************************************************************/
/*��ʽ��Ӧ��                                                           */
/************************************************************************/
struct cp_sdl_av_dev_audio_format_s
{
	cp_audio_format_e					cp_audio_format_type;
	cp_int32_t							sdl_audio_format_type;
	cp_char_t							description[CP_APP_DEFAULT_LENGTH];
};


/************************************************************************/
/* formatģ��ע�����Ϣ                                                  */
/************************************************************************/
#define CP_SDL_AV_DEV_AUDIO_FORMAT_REGISTER(css_type, format_type, description)			\
	{(css_type), (format_type), (description)},


//��ȡ��Ƶ��ʽ��Ϣ
cp_sdl_av_dev_audio_format_t* get_sdl_audio_format_info(cp_int32_t cp_audio_format_type);


#endif