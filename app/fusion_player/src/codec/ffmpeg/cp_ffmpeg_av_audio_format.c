/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-21

Description:

**************************************************************************/
#include "cp_ffmpeg_av_audio_format.h"



cp_ffmpeg_av_codec_audio_format_t	cp_ffmpeg_av_codec_audio_format_list[] = {
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_u8, AV_SAMPLE_FMT_U8, "u8 format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_s16, AV_SAMPLE_FMT_S16, "s16 format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_s32, AV_SAMPLE_FMT_S32, "s32 format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_flt, AV_SAMPLE_FMT_FLT, "flt format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_dbl, AV_SAMPLE_FMT_DBL, "dbl format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_u8p, AV_SAMPLE_FMT_U8P, "u8p format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_s16p, AV_SAMPLE_FMT_S16P, "s16p format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_s32p, AV_SAMPLE_FMT_S32P, "s32p format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_fltp, AV_SAMPLE_FMT_FLTP, "fltp format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_dblp, AV_SAMPLE_FMT_DBLP, "dblp format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_s64, AV_SAMPLE_FMT_S64, "s64 format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_s64p, AV_SAMPLE_FMT_S64P, "s64p format")
	CP_FFMPEG_AV_CODEC_AUDIO_FORMAT_REGISTER(cp_audio_format_nb, AV_SAMPLE_FMT_NB, "nb format")
};


/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_ffmpeg_audio_format_info
*
* 函数说明: 获取音频格式信息
*
* 参    数: cp_int32_t cp_audio_format_type						[in]参数说明
*
* 返 回 值: cp_ffmpeg_av_codec_audio_format_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 14:25:58
******************************************************************************************************/
cp_ffmpeg_av_codec_audio_format_t* get_ffmpeg_audio_format_info(cp_int32_t cp_audio_format_type)
{
	cp_int32_t						i = 0;



	for (i = 0; i < cp_ary_size(cp_ffmpeg_av_codec_audio_format_list); i++) {
		if (cp_ffmpeg_av_codec_audio_format_list[i].cp_audio_format_type ==
			cp_audio_format_type) {
			return &cp_ffmpeg_av_codec_audio_format_list[i];
		}
	}
	return CP_NULL;
}



/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_cp_audio_format_info
*
* 函数说明: 描述方法的功能信息
*
* 参    数: cp_int32_t ffmpeg_audio_format_type						[in]参数说明
*
* 返 回 值: cp_ffmpeg_av_codec_audio_format_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 14:28:26
******************************************************************************************************/
cp_ffmpeg_av_codec_audio_format_t* get_cp_audio_format_info(cp_int32_t ffmpeg_audio_format_type)
{
	cp_int32_t						i = 0;



	for (i = 0; i < cp_ary_size(cp_ffmpeg_av_codec_audio_format_list); i++) {
		if (cp_ffmpeg_av_codec_audio_format_list[i].ffmpeg_audio_format_type ==
			ffmpeg_audio_format_type) {
			return &cp_ffmpeg_av_codec_audio_format_list[i];
		}
	}
	return CP_NULL;
}