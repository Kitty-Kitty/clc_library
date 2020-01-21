/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-08

Description:

**************************************************************************/

#ifndef _CP_DEV_DESCRIPTION_INCLUDE_H_
#define _CP_DEV_DESCRIPTION_INCLUDE_H_

#include "cp_dev_core.h"



//typedef	enum cp_dev_description_type_enum				cp_dev_description_type_e;
//typedef	struct cp_dev_description_s						cp_dev_description_t;
typedef		struct cp_dev_video_description_s				cp_dev_video_description_t;
typedef		struct cp_dev_audio_description_s				cp_dev_audio_description_t;




#pragma pack(1)


/************************************************************************/
/* 表示数据类型                                                          */
/************************************************************************/
typedef enum cp_dev_description_type_enum
{
	cp_dev_description_type_none = 0,
	cp_dev_description_type_general,
	cp_dev_description_type_video,
	cp_dev_description_type_audio,
}cp_dev_description_type_e;


/************************************************************************/
/* 设备描述信息                                                          */
/************************************************************************/
struct cp_dev_description_s
{
	cp_dev_description_type_e				type;											//表示描述信息类型
	cp_int32_t								desc_len;										//设备描述数据长度
	cp_int32_t								dev_type;										//设备类型编号
	cp_char_t								dev_name[CP_APP_DEFAULT_STRING_LENGTH];			//设备解码器名称
};


/************************************************************************/
/* 表示视频描述信息                                                      */
/************************************************************************/
struct cp_dev_video_description_s
{
	cp_dev_description_t					dd;												//设备基本信息
	cp_int32_t								height;											//设备高度
	cp_int32_t								width;											//设备宽度
	cp_int32_t								fps;											//设备帧率
	cp_int32_t								bps;											//设备流的码率信息
};


/************************************************************************/
/* 表示音频描述信息                                                      */
/************************************************************************/
struct cp_dev_audio_description_s
{
	cp_dev_description_t					dd;												//设备基本信息
	cp_int32_t								volume;											//音频音量
	cp_int32_t								bit_rate;										//音频输出码率
	cp_int32_t								sample_rate;									//采样频率，单位（Hz）
	cp_int32_t								channel_layout;									//描述声道类型
	cp_int32_t								sample_format;									//描述声音采样类型
	cp_int32_t								samples;										//样本大小
	cp_int32_t								channels;										//通道数量
};

#pragma pack()





/************************************************************************/
/* 创建描述信息                                                          */
/************************************************************************/
cp_dev_description_t	*create_dev_description(cp_pool_t *pool, cp_dev_description_type_e type);

/************************************************************************/
/* 消毁描述信息                                                          */
/************************************************************************/
cp_int32_t destroy_dev_description(cp_pool_t *pool, cp_dev_description_t *dd);

#endif