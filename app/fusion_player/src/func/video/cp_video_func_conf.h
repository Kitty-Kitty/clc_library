/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_VIDEO_FUNC_CONF_INCLUDE_H_
#define _CP_VIDEO_FUNC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_video_description.h"
#include "cp_video_func_conf_string.h"



#define	CP_VIDEO_SOURCE_URL_LENGTH							512					//视频源地址
#define	CP_VIDEO_SOURCES_MAX_NUMBER							8					//视频源地址


typedef struct cp_video_source_s							cp_video_source_t;
typedef struct cp_video_func_configure_s					cp_video_func_configure_t;



#pragma pack(1)

/************************************************************************/
/* 视频源信息                                                            */
/************************************************************************/
struct cp_video_source_s
{
	cp_char_t						url[CP_VIDEO_SOURCE_URL_LENGTH];			//表示是否进行视频重采样，取值：0表示不重采；1表示重采
	cp_bool_t						is_used;									//标记是否被使用
};

/************************************************************************/
/* 视频处理相关配置                                                      */
/************************************************************************/
struct cp_video_func_configure_s
{
	cp_video_source_t				video_sources[CP_VIDEO_SOURCES_MAX_NUMBER];	//视频源数量
	cp_int32_t						buffer_size;								//表示当前使用的缓存数量
	cp_int32_t						each_buffer_length;							//表示当前使用的每个缓存大小
};

#pragma pack()


/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	video_func_parse_configure(cp_module_t *module, cp_video_func_configure_t *afc);

/************************************************************************/
/* 解析video sources                                                     */
/************************************************************************/
cp_int32_t	video_func_parse_video_sources(const cp_module_t *module, cp_video_func_configure_t *afc);


#endif