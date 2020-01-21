/*******************************************************************************
*
*Copyright:novigo
*
*File name: cp_ffmpeg_av_file_conf.h
*
*Author:fangzhenmu@novigo.com.cn
*
*Version: 1.0
*
*Date:2017/08/08
*
*Description: create (cp_ffmpeg_av_file_conf.h)
*
*Others:
*
*History:
*******************************************************************************/

#ifndef _CP_FFMPEG_AV_FILE_CONF_H_
#define _CP_FFMPEG_AV_FILE_CONF_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_ffmpeg_av_file_conf_string.h"



typedef struct cp_ffmpeg_av_file_conf_s						cp_ffmpeg_av_file_conf_t;



#pragma pack(1)

/************************************************************************/
/* 视频源信息                                                            */
/************************************************************************/
struct cp_ffmpeg_av_file_conf_s
{
	cp_int32_t						min_cache_size;								//表示表示最小缓存数量
};


#pragma pack()


/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	ffmpeg_av_file_parse_configure(cp_module_t *module, cp_ffmpeg_av_file_conf_t *fafc);


#endif //_CP_FFMPEG_AV_FILE_CONF_H_


