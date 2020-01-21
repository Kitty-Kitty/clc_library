/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-19

Description:

**************************************************************************/

#include "cp_audio_description.h"


/************************************************************************/
/* 初始化音频信息                                                        */
/************************************************************************/
cp_int32_t init_audio_description(cp_audio_description_t *ad)
{
	if (!ad) {
		return -1;
	}
	ad->sample_format = cp_audio_format_s16;
	ad->samples = CP_AUDIO_DEFAULT_SAMPLES;
	return 0;
}