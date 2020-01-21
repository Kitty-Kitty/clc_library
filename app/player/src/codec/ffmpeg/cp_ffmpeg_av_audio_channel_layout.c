/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-23

Description:

**************************************************************************/
#include "cp_ffmpeg_av_audio_channel_layout.h"



cp_ffmpeg_av_codec_audio_channel_layout_t	cp_ffmpeg_av_codec_audio_channel_layout_list[] = {
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_mono,			AV_CH_LAYOUT_MONO,				"mono")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_stereo,			AV_CH_LAYOUT_STEREO,			"stereo")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_2point1,			AV_CH_LAYOUT_2POINT1,			"2point1")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_2_1,				AV_CH_LAYOUT_2_1,				"2_1")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_surround,		AV_CH_LAYOUT_SURROUND,			"surround")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_3point1,			AV_CH_LAYOUT_3POINT1,			"3point1")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_4point0,			AV_CH_LAYOUT_4POINT0,			"4point0")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_4point1,			AV_CH_LAYOUT_4POINT1,			"4point1")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_2_2,				AV_CH_LAYOUT_2_2,				"2_2")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_quad,			AV_CH_LAYOUT_2_2,				"quad")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_5point0,			AV_CH_LAYOUT_5POINT0,			"5point0")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_5point1,			AV_CH_LAYOUT_5POINT1,			"5point1")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_5point0_back,	AV_CH_LAYOUT_5POINT0_BACK,		"5point0_back")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_5point1_back,	AV_CH_LAYOUT_5POINT1_BACK,		"5point1_back")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_6point0,			AV_CH_LAYOUT_6POINT0,			"6point0")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_6point0_front,	AV_CH_LAYOUT_6POINT0_FRONT,		"6point0_front")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_hexagonal,		AV_CH_LAYOUT_HEXAGONAL,			"hexagonal")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_6point1,			AV_CH_LAYOUT_6POINT1,			"6point1")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_6point1_back,	AV_CH_LAYOUT_6POINT1_BACK,		"6point1_back")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_6point1_front,	AV_CH_LAYOUT_6POINT1_FRONT,		"6point1_front")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_7point0,			AV_CH_LAYOUT_7POINT0,			"7point0")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_7point0_front,	AV_CH_LAYOUT_7POINT0_FRONT,		"7point0_front")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_7point1,			AV_CH_LAYOUT_7POINT1,			"7point1")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_7point1_wide,	AV_CH_LAYOUT_7POINT1_WIDE,		"7point1_wide")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_7point1_wide_back, AV_CH_LAYOUT_7POINT1_WIDE_BACK, "7point1_wide_back")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_octagonal,		AV_CH_LAYOUT_OCTAGONAL,			"octagonal")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_hexadecagonal,	AV_CH_LAYOUT_HEXADECAGONAL,		"hexadecagonal")
	CP_FFMPEG_AV_CODEC_CHANNEL_LAYOUT_REGISTER(cp_audio_channel_layout_stereo_downmix,	AV_CH_LAYOUT_STEREO_DOWNMIX,	"stereo_downmix")
};


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_ffmpeg_audio_channel_layout_info
*
* 函数说明: 获取音频格式信息
*
* 参    数: cp_int32_t cp_audio_channel_layout_type						[in]参数说明
*
* 返 回 值: cp_ffmpeg_av_codec_audio_channel_layout_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 14:25:58
******************************************************************************************************/
cp_ffmpeg_av_codec_audio_channel_layout_t* get_ffmpeg_audio_channel_layout_info(cp_int32_t cp_audio_channel_layout_type)
{
	cp_int32_t						i = 0;



	for (i = 0; i < cp_ary_size(cp_ffmpeg_av_codec_audio_channel_layout_list); i++) {
		if (cp_ffmpeg_av_codec_audio_channel_layout_list[i].cp_audio_channel_layout_type ==
			cp_audio_channel_layout_type) {
			return &cp_ffmpeg_av_codec_audio_channel_layout_list[i];
		}
	}
	return CP_NULL;
}



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_cp_audio_channel_layout_info
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_int32_t ffmpeg_audio_channel_layout_type						[in]参数说明
*
* 返 回 值: cp_ffmpeg_av_codec_audio_channel_layout_t*
*           0  : 成功
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 14:28:26
******************************************************************************************************/
cp_ffmpeg_av_codec_audio_channel_layout_t* get_cp_audio_channel_layout_info(cp_int32_t ffmpeg_audio_channel_layout_type)
{
	cp_int32_t						i = 0;



	for (i = 0; i < cp_ary_size(cp_ffmpeg_av_codec_audio_channel_layout_list); i++) {
		if (cp_ffmpeg_av_codec_audio_channel_layout_list[i].ffmpeg_audio_channel_layout_type ==
			ffmpeg_audio_channel_layout_type) {
			return &cp_ffmpeg_av_codec_audio_channel_layout_list[i];
		}
	}
	return CP_NULL;
}