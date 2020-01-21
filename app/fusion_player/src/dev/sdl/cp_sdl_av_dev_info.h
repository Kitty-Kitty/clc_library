/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_SDL_AV_DEV_INFO_INCLUDE_H_
#define _CP_SDL_AV_DEV_INFO_INCLUDE_H_



#include "cp_lockfree_queue.h"
#include "cp_sdl_av_dev_core.h"
#include "SDL.h"





//typedef	struct cp_sdl_av_dev_info_s			cp_sdl_av_dev_info_t;

typedef	struct cp_sdl_av_dev_video_info_s					cp_sdl_av_dev_video_info_t;
typedef	struct cp_sdl_av_dev_audio_info_s					cp_sdl_av_dev_audio_info_t;


typedef void(*cp_sdl_av_dev_cb)(cp_sdl_av_dev_t* th);




#pragma pack(1)


#define CP_SDL_AV_DEV_INFO_FIELDS																						\
		CP_DEV_INFO_FIELDS																								\



/************************************************************************/
/* sdl������Ϣ                                                           */
/************************************************************************/
struct cp_sdl_av_dev_info_s {
	CP_SDL_AV_DEV_INFO_FIELDS
};

/************************************************************************/
/* sdl��Ƶ������Ϣ                                                       */
/************************************************************************/
struct cp_sdl_av_dev_video_info_s
{
	cp_dev_video_description_t			dvd;						/*��ʾ��Ƶ����������Ϣ*/
	cp_video_description_t				vd;							/*��ʾ��Ƶý��������Ϣ*/
	SDL_Window							*window;					/*��ʾ���Ŵ���*/
	SDL_Renderer						*renderer;					/*��ʾ��Ⱦ��*/
	SDL_Texture							*texture;					/*��ʾ����*/
	SDL_Rect							window_rect;				/*��ʾ���ڳ߶�*/
	SDL_Rect							vedio_rect;					/*��ʾ��Ƶ�߶�*/
};


/************************************************************************/
/* sdl��Ƶ������Ϣ                                                       */
/************************************************************************/
struct cp_sdl_av_dev_audio_info_s
{
	cp_dev_audio_description_t			dad;						/*��ʾ��Ƶ����������Ϣ*/
	cp_audio_description_t				ad;							/*��ʾ��Ƶý��������Ϣ*/
	cp_atomic_t							max_buffer_size;			/*��ʾ���Ļ�������*/
	cp_atomic_t							current_buffer_size;		/*��ʾ��ǰ�Ļ�������*/
	cp_int32_t							play_delay_times;			/*��ʾ��ʱ����*/
	cp_int32_t							play_delay_max_times;		/*��ʾ��ʱ�ܴ���*/
	cp_int64_t							play_delay_ns;				/*��ʾ������ʱʱ��*/
	cp_int32_t							play_delay_sample_number;	/*��ʾ��Ƶ������ʱ�������������ڸ���ֵʱ������˫������*/
	SDL_AudioSpec						wanted_spec;				/*��Ƶ������Ϣ*/
	cp_lockfree_queue_t					used_queue;					/*��ʾ��ǰʹ�õ����ݶ���*/
	cp_lockfree_queue_t					free_queue;					/*��ʾ��ǰ�ͷŵĻ������*/
};


#pragma pack()




#endif





