/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/

#ifndef	_CP_VIDEO_FUNC_INCLUDE_H_
#define _CP_VIDEO_FUNC_INCLUDE_H_

#include "cp_video_func_core.h"
#include "cp_video_func_proc.h"


//#define		CP_VIDEO_FILE_DEBUG										1
//#define		CP_VIDEO_FRAME_TIMESTAMP								1
#define		CP_VIDEO_FUNC_MEDIA_ARRAY_SIZE								1024							//配置数组大小


//typedef struct cp_video_func_s										cp_video_func_t;


#pragma pack(1)



#define CP_VIDEO_FUNC_FIELDS																			\
		CP_FUNC_FIELDS																					\
		cp_video_func_configure_t				afc;					/*视频处理的配置信息*/			\
		cp_dev_t								*dev;					/*播放设备信息*/					\
		cp_memh_socket_data_t					*msd;					/*表示接收的媒体源数据*/			\
		cp_video_func_codec_process_t			codec_process_info[CP_VIDEO_SOURCES_MAX_NUMBER];				/*媒体解码处理信息*/					\
		cp_video_func_check_process_t			check_process_info;		/*表示处理图像校验数据*/			\
		cp_video_func_merge_process_t			merge_process_info;		/*表示处理图像拼接数据*/			\
		cp_media_channel_info_t					mci;					/*表示当前播放的媒体信息*/		\


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_video_func_s {
	CP_VIDEO_FUNC_FIELDS												/*表示时间模块信息*/

#if defined(CP_VIDEO_FILE_DEBUG)
	FILE											*file;				/*媒体文件*/						
#endif

#if defined(CP_VIDEO_FRAME_TIMESTAMP)
	FILE											*timestamp_file;	/*时间戳文件*/
#endif
	cp_int32_t										play_flag;
};



#pragma pack()


cp_video_func_t* create_video_func(cp_module_register_t *register_info, cp_socket_manager_t *manager, cp_video_func_info_t *info);
cp_int32_t destroy_video_func(cp_video_func_manager_t *manager, cp_video_func_t* video_func);


#endif


