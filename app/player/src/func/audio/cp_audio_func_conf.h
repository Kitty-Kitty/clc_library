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
#include "cp_audio_description.h"
#include "cp_audio_func_conf_string.h"



typedef struct cp_audio_func_configure_s					cp_audio_func_configure_t;



#pragma pack(1)

/************************************************************************/
/* 音频处理相关配置                                                      */
/************************************************************************/
struct cp_audio_func_configure_s
{
	cp_int32_t						convert_flag;								//表示是否进行音频重采样，取值：0表示不重采；1表示重采
	cp_audio_channel_layout_e		channel_layout;								//表示输了出声道数，取值：1表示单声道；2表示STEREO立体声
	cp_int32_t						sample_format;								//表示声音采样类型，取值：1表示8位；2表示16位；3表示32位
	cp_int32_t						sample_rate;								//表示声音采样频率，取值：44100/48000等
	cp_int32_t						samples;									//表示声音的采样buffer大小
	cp_int32_t						buffer_size;								//表示当前使用的缓存数量
	cp_int32_t						each_buffer_length;							//表示当前使用的每个缓存大小
	cp_int64_t						play_delay_ns;								//表示播放延时时间
	cp_int32_t						play_delay_sample_number;					//表示音频播放延时样本数量，大于该数值时将进行双倍播放
	cp_bool_t						is_used_probe;								//表示是否使用音频嗅探功能，取值[0, 1]; 0 表示不用；1表示使用
};

#pragma pack()


/************************************************************************/
/*解析配置文件                                                           */
/************************************************************************/
cp_int32_t	audio_func_parse_configure(cp_module_t *module, cp_audio_func_configure_t *afc);


#endif