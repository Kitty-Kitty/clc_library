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
/* sdl设置信息                                                           */
/************************************************************************/
struct cp_sdl_av_dev_info_s {
	CP_SDL_AV_DEV_INFO_FIELDS
};

/************************************************************************/
/* sdl视频描述信息                                                       */
/************************************************************************/
struct cp_sdl_av_dev_video_info_s
{
	cp_dev_video_description_t			dvd;						/*表示视频设置描述信息*/
	cp_video_description_t				vd;							/*表示视频媒体描述信息*/
	SDL_Window							*window;					/*表示播放窗口*/
	SDL_Renderer						*renderer;					/*表示渲染器*/
	SDL_Texture							*texture;					/*表示纹理*/
	SDL_Rect							window_rect;				/*表示窗口尺度*/
	SDL_Rect							vedio_rect;					/*表示视频尺度*/
};


/************************************************************************/
/* sdl音频描述信息                                                       */
/************************************************************************/
struct cp_sdl_av_dev_audio_info_s
{
	cp_dev_audio_description_t			dad;						/*表示音频设置描述信息*/
	cp_audio_description_t				ad;							/*表示音频媒体描述信息*/
	cp_atomic_t							max_buffer_size;			/*表示最大的缓存数量*/
	cp_atomic_t							current_buffer_size;		/*表示当前的缓存数量*/
	cp_int32_t							play_delay_times;			/*表示延时次数*/
	cp_int32_t							play_delay_max_times;		/*表示延时总次数*/
	cp_int64_t							play_delay_ns;				/*表示播放延时时间*/
	cp_int32_t							play_delay_sample_number;	/*表示音频播放延时样本数量，大于该数值时将进行双倍播放*/
	SDL_AudioSpec						wanted_spec;				/*音频描述信息*/
	cp_lockfree_queue_t					used_queue;					/*表示当前使用的数据队列*/
	cp_lockfree_queue_t					free_queue;					/*表示当前释放的缓存队列*/
};


#pragma pack()




#endif





