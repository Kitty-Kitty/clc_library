/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_AUDIO_FUNC_INCLUDE_H_
#define _CP_AUDIO_FUNC_INCLUDE_H_

#include "cp_audio_func_core.h"



//#define		CP_AUDIO_FILE_DEBUG										1
//#define		CP_AUDIO_FRAME_TIMESTAMP								1
#define		CP_AUDIO_FUNC_MEDIA_ARRAY_SIZE								1024							//配置数组大小


//typedef struct cp_audio_func_s										cp_audio_func_t;
typedef enum cp_audio_func_thread_status_enum							cp_audio_func_thread_status_e;
typedef struct cp_audio_func_media_process_struct						cp_audio_func_media_process_t;


#pragma pack(1)


#define CP_AUDIO_FUNC_FIELDS																			\
		CP_FUNC_FIELDS																					\
		cp_audio_func_configure_t				afc;					/*音频处理的配置信息*/			\
		cp_codec_t								*codec;					/*解码器信息*/					\
		cp_dev_t								*dev;					/*播放设备信息*/					\
		cp_filter_t								*filter;				/*数据过滤器*/					\
		cp_memh_socket_data_t					*msd;					/*表示接收的媒体源数据*/			\
		cp_audio_func_media_process_t			mp_info;				/*媒体处理信息*/					\
		cp_channel_manager_t					cm;						/*通道管理器*/					\
		cp_media_channel_info_t					mci;					/*表示当前播放的媒体信息*/		\
		cp_audio_description_t					decode_md;				/*表示解码后的媒体信息*/			\
		cp_codec_callback_info_t				cc_info;				/*表示解码器回调函数*/			\




/************************************************************************/
/* audio func thread status                                             */
/************************************************************************/
enum cp_audio_func_thread_status_enum
{
	cp_audio_func_thread_status_init = 1,
	cp_audio_func_thread_status_start,
	cp_audio_func_thread_status_stop,
};


/************************************************************************/
/* 媒体处理信息内容                                                      */
/************************************************************************/
struct cp_audio_func_media_process_struct
{
	cp_thread_t								*decode_thread;				/*线程管理器*/
	cp_thread_t								*merge_thread;				/*线程管理器*/
	cp_media_packet_t						*decode_mp;					/*解码媒体数据*/
	cp_media_packet_t						*merge_cache_mp;			/*媒体处理缓存数据*/
	cp_safe_queue_t							*merge_sq;					/*媒体处理使用安全队列*/
	cp_safe_queue_t							*merge_cache_sq;			/*媒体处理使用安全队列*/
	cp_bool_t								is_open_codec;				/*表示是否打开解码器*/
	cp_audio_func_thread_status_e			thread_status;				/*线程状态*/
};


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_audio_func_s {
	CP_AUDIO_FUNC_FIELDS												/*表示时间模块信息*/

#if defined(CP_AUDIO_FILE_DEBUG)
	FILE											*file;				/*媒体文件*/						
#endif

#if defined(CP_AUDIO_FRAME_TIMESTAMP)
	FILE											*timestamp_file;	/*时间戳文件*/
#endif
	
	cp_int32_t										play_flag;
};



#pragma pack()


cp_audio_func_t* create_audio_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_audio_func_info_t *info);
cp_int32_t destroy_audio_func(cp_audio_func_manager_t *manager, cp_audio_func_t* audio_func);


#endif


