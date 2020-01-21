/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-21

Description:

**************************************************************************/
#include "cp_sdl_av_dev_audio_format.h"



cp_sdl_av_dev_audio_format_t	cp_sdl_av_dev_audio_format_list[] = {
	CP_SDL_AV_DEV_AUDIO_FORMAT_REGISTER(cp_audio_format_u8, AUDIO_U8, "u8 format")
	CP_SDL_AV_DEV_AUDIO_FORMAT_REGISTER(cp_audio_format_s16, AUDIO_S16SYS, "s16 format")
	CP_SDL_AV_DEV_AUDIO_FORMAT_REGISTER(cp_audio_format_s32, AUDIO_S32SYS, "s32 format")
};

/******************************************************************************************************
* 版权所有: fz & novigo
*
* 函数名称: get_sdl_audio_format_info
*
* 函数说明: 获取音频格式信息
*
* 参    数: cp_int32_t cp_audio_format_type						[in]参数说明
*
* 返 回 值: cp_sdl_av_dev_audio_format_t*
*           0  : 成功 
*         非 0  :失败
*
* 备    注:其他说明内容
*
* 作    者：fz
* 电子邮箱： fangzhenmu@novigo.com.cn
* 创建日期：2016-12-21 09:45:15
******************************************************************************************************/
cp_sdl_av_dev_audio_format_t* get_sdl_audio_format_info(cp_int32_t cp_audio_format_type)
{
	cp_int32_t						i = 0;



	for (i = 0; i < cp_ary_size(cp_sdl_av_dev_audio_format_list); i++) {
		if (cp_sdl_av_dev_audio_format_list[i].cp_audio_format_type ==
			cp_audio_format_type) {
			return &cp_sdl_av_dev_audio_format_list[i];
		}
	}
	return CP_NULL;
}