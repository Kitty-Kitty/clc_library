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
* ��Ȩ����: fz & novigo
*
* ��������: get_sdl_audio_format_info
*
* ����˵��: ��ȡ��Ƶ��ʽ��Ϣ
*
* ��    ��: cp_int32_t cp_audio_format_type						[in]����˵��
*
* �� �� ֵ: cp_sdl_av_dev_audio_format_t*
*           0  : �ɹ� 
*         �� 0  :ʧ��
*
* ��    ע:����˵������
*
* ��    �ߣ�fz
* �������䣺 fangzhenmu@novigo.com.cn
* �������ڣ�2016-12-21 09:45:15
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