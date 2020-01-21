/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-12-01

Description:

**************************************************************************/
#include "cp_ffmpeg_av_codec_conf.h"



cp_ffmpeg_av_codec_conf_t	cp_ffmpeg_av_codec_list[] = {
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_video_h264, AV_CODEC_ID_H264, "h264 codec info")
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_audio_mp2, AV_CODEC_ID_MP2, "mp2 codec info")
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_audio_mp3, AV_CODEC_ID_MP3, "mp3 codec info")
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_audio_aac, AV_CODEC_ID_AAC, "aac codec info")
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_audio_g711_pcm, AV_CODEC_ID_PCM_ALAW, "g711 codec info")
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_audio_g722_1, AV_CODEC_ID_ADPCM_G722, "g722 codec info")
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_audio_g723_1, AV_CODEC_ID_ADPCM_G722, "g723 codec info")
	CP_FFMPEG_AV_CODEC_REGISTER(cp_media_type_audio_g729, AV_CODEC_ID_ADPCM_G722, "g729 codec info")
};


cp_ffmpeg_av_codec_conf_t* get_codec_info(cp_int32_t css_codec_type)
{
	cp_int32_t						i = 0;



	for (i = 0; i < cp_ary_size(cp_ffmpeg_av_codec_list); i++) {
		if (cp_ffmpeg_av_codec_list[i].css_codec_type == css_codec_type) {
			return &cp_ffmpeg_av_codec_list[i];
		}
	}
	return CP_NULL;
}
