/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_SDL_AV_DEV_INCLUDE_H_
#define _CP_SDL_AV_DEV_INCLUDE_H_



#include "cp_lockfree_queue.h"
#include "cp_sdl_av_dev_core.h"
#include "SDL.h"



//typedef struct cp_sdl_av_dev_s					cp_sdl_av_dev_t;



#define CP_SDL_AV_DEV_MAX_BUFFER_SIZE				1024					//�������Ļ����С
#define CP_SDL_AV_DEV_DEFAULT_BUFFER_LENGTH			(8 * 1024)			//����Ĭ�ϵĿ��
#define CP_SDL_AV_DEV_DEFAULT_WIDTH					1920				//����Ĭ�ϵĿ��
#define CP_SDL_AV_DEV_DEFAULT_HEIGHT				1080				//����Ĭ�ϵĸ߶�



#pragma pack(1)

#define CP_SDL_AV_DEV_FIELDS																							\
		CP_FUSION_PLAYER_DEV_FIELDS																							\
		cp_sdl_av_dev_video_info_t			*video_info;				/*��ʾ��Ƶ���������Ϣ*/							\
		cp_sdl_av_dev_audio_info_t			*audio_info;				/*��ʾ��Ƶ���������Ϣ*/							\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_sdl_av_dev_s {
	CP_SDL_AV_DEV_FIELDS								/*��ʾʱ��ģ����Ϣ*/
};

#pragma pack()



cp_sdl_av_dev_t* create_sdl_av_dev(cp_module_register_t *register_info, cp_codec_manager_t *manager, cp_sdl_av_dev_info_t *info);
cp_int32_t destroy_sdl_av_dev(cp_codec_manager_t *manager, cp_sdl_av_dev_t* sdl_av_dev);

#endif


