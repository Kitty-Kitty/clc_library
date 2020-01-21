/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-20

Description:

**************************************************************************/

#ifndef _CP_AUDIO_FUNC_CONF_INCLUDE_H_
#define _CP_AUDIO_FUNC_CONF_INCLUDE_H_


#include "cp_core.h"
#include "cp_module_core.h"
#include "cp_audio_func_conf_string.h"



typedef struct cp_audio_func_configure_s					cp_audio_func_configure_t;


/************************************************************************/
/* 音频处理相关配置                                                      */
/************************************************************************/
struct cp_audio_func_configure_s
{
	cp_int32_t		convert_flag;								//表示是否进行音频重采样，取值：0表示不重采；1表示重采
	cp_int32_t		channel_layout;								//表示输了出声道数，取值：1表示单声道；2表示STEREO立体声
	cp_int32_t		sample_format;								//表示声音采样类型，取值：1表示8位；2表示16位；3表示32位
	cp_int32_t		sample_rate;								//表示声音采样频率，取值：44100/48000等
	cp_int32_t		samples;									//表示声音的采样buffer大小
	cp_int32_t		buffer_size;								//表示当前使用的缓存数量
};

/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	audio_func_parse_configure(cp_module_t *module, cp_audio_func_configure_t *afc);


#endif