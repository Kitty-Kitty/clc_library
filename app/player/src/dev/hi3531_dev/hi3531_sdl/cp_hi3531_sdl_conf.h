/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_HI3531_SDL_CONF_INCLUDE_H_
#define _CP_HI3531_SDL_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_hi3531_sdl_conf_string.h"





typedef struct	cp_hi3531_sdl_configure_s							cp_hi3531_sdl_configure_t;



/************************************************************************/
/* 音频处理相关配置                                                      */
/************************************************************************/
struct cp_hi3531_sdl_configure_s
{
	cp_int32_t							width;										//表示编码器输出视频宽度
	cp_int32_t							heigth;										//表示编码器输出视频高度
	cp_int32_t							fps;										//表示编码帧率
	cp_int32_t							bitrate;									//表示编码器输出码率，单位kbps
	cp_int32_t							mode;										//表示codec工作模式，1表示vi-venc；2表示vi-fisheye-vpss-venc模式
};



/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	hi3531_sdl_parse_configure(cp_module_t *module, cp_hi3531_sdl_configure_t *hacc);

#endif