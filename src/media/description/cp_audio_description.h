/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-19

Description:

**************************************************************************/

#ifndef _CP_AUDIO_DESCRIPTION_INCLUDE_H_
#define _CP_AUDIO_DESCRIPTION_INCLUDE_H_



#include "cp_media_description.h"


#define		CP_AUDIO_DEFAULT_SAMPLES					1024			//定义默的samples


//typedef		enum cp_audio_format_enum					cp_audio_format_e;
//typedef		enum cp_audio_channel_layout_enum			cp_audio_channel_layout_e;
typedef		struct cp_audio_description_s				cp_audio_description_t;




#pragma pack(1)

/************************************************************************/
/* 表示音频格式                                                          */
/************************************************************************/
typedef	enum cp_audio_format_enum
{
	cp_audio_format_none = 0,
	cp_audio_format_u8,          ///< unsigned 8 bits
	cp_audio_format_s16,         ///< signed 16 bits
	cp_audio_format_s32,         ///< signed 32 bits
	cp_audio_format_flt,         ///< float
	cp_audio_format_dbl,         ///< double

	cp_audio_format_u8p,         ///< unsigned 8 bits, planar
	cp_audio_format_s16p,        ///< signed 16 bits, planar
	cp_audio_format_s32p,        ///< signed 32 bits, planar
	cp_audio_format_fltp,        ///< float, planar
	cp_audio_format_dblp,        ///< double, planar
	cp_audio_format_s64,         ///< signed 64 bits
	cp_audio_format_s64p,        ///< signed 64 bits, planar

	cp_audio_format_nb           ///< number of sample formats. do not use if linking dynamically
}cp_audio_format_e;


/************************************************************************/
/* 表示音频channel_layout                                                */
/************************************************************************/
typedef enum cp_audio_channel_layout_enum
{
	cp_audio_channel_layout_none = 0,
	cp_audio_channel_layout_mono,
	cp_audio_channel_layout_stereo,
	cp_audio_channel_layout_2point1,
	cp_audio_channel_layout_2_1,
	cp_audio_channel_layout_surround,
	cp_audio_channel_layout_3point1,
	cp_audio_channel_layout_4point0,
	cp_audio_channel_layout_4point1,
	cp_audio_channel_layout_2_2,
	cp_audio_channel_layout_quad,
	cp_audio_channel_layout_5point0,
	cp_audio_channel_layout_5point1,
	cp_audio_channel_layout_5point0_back,
	cp_audio_channel_layout_5point1_back,
	cp_audio_channel_layout_6point0,
	cp_audio_channel_layout_6point0_front,
	cp_audio_channel_layout_hexagonal,
	cp_audio_channel_layout_6point1,
	cp_audio_channel_layout_6point1_back,
	cp_audio_channel_layout_6point1_front,
	cp_audio_channel_layout_7point0,
	cp_audio_channel_layout_7point0_front,
	cp_audio_channel_layout_7point1,
	cp_audio_channel_layout_7point1_wide,
	cp_audio_channel_layout_7point1_wide_back,
	cp_audio_channel_layout_octagonal,
	cp_audio_channel_layout_hexadecagonal,
	cp_audio_channel_layout_stereo_downmix
}cp_audio_channel_layout_e;

/************************************************************************/
/* 表示音频描述信息                                                      */
/************************************************************************/
struct cp_audio_description_s
{
	CP_MEDIA_DESCRIPTION_FIELDS																	//媒体基本信息
	cp_int32_t								volume;												//音频音量
	cp_int32_t								bit_rate;											//音频输出码率
	cp_int32_t								sample_rate;										//采样频率，单位（Hz）
	cp_uint16_t								sample_format;										/**< Audio data format */
	cp_uint16_t								channel_layout;										/**< Number of channels: 1 mono, 2 stereo */
	cp_uint16_t								channels;											/**< Number of channels: 1 mono, 2 stereo */
	cp_uint8_t								silence;											/**< Audio buffer silence value (calculated) */
	cp_uint16_t								samples;											/**< Audio buffer size in samples (power of 2) */
	cp_uint32_t								size;												/**< Audio buffer size in bytes (calculated) */
	cp_uint32_t								out_linesize;										/**< Audio out line buffer size in bytes (calculated) */
	cp_uint32_t								samples_buffer_size;								/**< Audio samples buffer size in bytes (calculated) */
};

#pragma pack()



/************************************************************************/
/* 初始化音频信息                                                        */
/************************************************************************/
cp_int32_t init_audio_description(cp_audio_description_t *ad);



#endif