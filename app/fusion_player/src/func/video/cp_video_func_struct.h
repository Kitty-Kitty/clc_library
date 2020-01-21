/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_video_func_struct.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/09
*
*Description: create (cp_video_func_struct.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_VIDEO_FUNC_STRUCT_H_
#define _CP_VIDEO_FUNC_STRUCT_H_



#include "cp_core.h"
#include "cp_include.h"
#include "cp_socket.h"
#include "cp_safe_queue.h"



typedef enum cp_video_func_thread_status_enum							cp_video_func_thread_status_e;
typedef struct cp_video_func_media_process_struct						cp_video_func_media_process_t;
typedef struct cp_video_func_codec_process_struct						cp_video_func_codec_process_t;
typedef struct cp_video_func_check_process_struct						cp_video_func_check_process_t;
typedef struct cp_video_func_merge_process_struct						cp_video_func_merge_process_t;



/************************************************************************/
/* video func thread status                                             */
/************************************************************************/
enum cp_video_func_thread_status_enum
{
	cp_video_func_thread_status_init = 1,
	cp_video_func_thread_status_start,
	cp_video_func_thread_status_stop,
};


/************************************************************************/
/* 媒体处理信息内容                                                      */
/************************************************************************/
struct cp_video_func_media_process_struct
{
	cp_thread_t								*thread;					/*线程管理器*/
	cp_media_packet_t						*decode_mp;					/*解码媒体数据*/
	cp_media_packet_t						*cache_mp;					/*媒体处理缓存数据*/
	cp_safe_queue_t							*media_sq;					/*媒体处理使用安全队列*/
	cp_safe_queue_t							*media_cache_sq;			/*媒体处理使用安全队列*/
	cp_video_func_thread_status_e			thread_status;				/*线程状态*/
};


/************************************************************************/
/* 媒体解码处理信息内容                                                      */
/************************************************************************/
struct cp_video_func_codec_process_struct
{
	cp_func_t								*video_func;				/*视频func*/
	cp_codec_t								*codecs;					/*解码器信息*/
	cp_video_description_t					decode_md;					/*表示解码后的媒体信息*/
	cp_codec_callback_info_t				cc_info;					/*表示解码器回调函数*/
	cp_video_func_media_process_t			mp_info;					/*媒体处理信息*/
	cp_bool_t								is_open_codec;				/*表示是否打开解码器*/
};



/************************************************************************/
/* 媒体解码拼接信息内容                                                      */
/************************************************************************/
struct cp_video_func_check_process_struct
{
	cp_func_t								*video_func;				/*视频func*/
	cp_video_func_media_process_t			mp_info;					/*媒体处理信息*/
};


/************************************************************************/
/* 媒体解码拼接信息内容                                                      */
/************************************************************************/
struct cp_video_func_merge_process_struct
{
	cp_func_t								*video_func;				/*视频func*/
	cp_video_func_media_process_t			mp_info;					/*媒体处理信息*/
};



#endif //_CP_VIDEO_FUNC_STRUCT_H_


