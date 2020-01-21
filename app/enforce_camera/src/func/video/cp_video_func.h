/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VIDEO_FUNC_INCLUDE_H_
#define _CP_VIDEO_FUNC_INCLUDE_H_

#include "cp_video_func_core.h"



#define		CP_VIDEO_FILE_DEBUG									1
#define		CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE						1024					//配置数组大小


//typedef struct cp_video_func_s					cp_video_func_t;
typedef enum cp_video_func_thread_status_enum		cp_video_func_thread_status_e;



#pragma pack(1)


#define CP_VIDEO_FUNC_FIELDS																	\
		CP_FUNC_FIELDS																			\
		cp_codec_t								*codec;			/*解码器信息*/					\
		cp_dev_t								*dev;			/*播放设备信息*/					\
		cp_filter_t								*filter;		/*数据过滤器*/					\
		cp_thread_t								*thread;		/*线程管理器*/					\
		cp_media_packet_t						*decode_mp;		/*解码媒体数据*/					\
		cp_bool_t								is_open_codec;	/*表示是否打开解码器*/			\
		cp_video_func_thread_status_e			thread_status;	/*线程状态*/						\
		cp_channel_manager_t					cm;				/*通道管理器*/					\
		cp_media_channel_info_t					mci;			/*表示当前播放的媒体信息*/		\
		cp_video_description_t					decode_md;		/*表示解码后的媒体信息*/			\
		cp_codec_callback_info_t				cc_info;		/*表示解码器回调函数*/			\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_video_func_s {
	CP_VIDEO_FUNC_FIELDS												/*表示时间模块信息*/
		
#if defined(CP_VIDEO_FILE_DEBUG)
		FILE											*file;			/*媒体文件*/						
#endif
};


enum cp_video_func_thread_status_enum
{
	cp_video_func_thread_status_init = 1,
	cp_video_func_thread_status_start,
	cp_video_func_thread_status_stop,
};


#pragma pack()


cp_video_func_t* create_video_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_video_func_info_t *info);
cp_int32_t destroy_video_func(cp_video_func_manager_t *manager, cp_video_func_t* video_func);


#endif


