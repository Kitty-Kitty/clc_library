/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-26

Description:

**************************************************************************/
#include "cp_format_media_play.h"




//格式化媒体通道信息
cp_char_t* format_media_channel_info(cp_media_channel_info_t *mci, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t							tmp_media_buf[CP_FORMAT_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_char_t							tmp_channel_buf[CP_FORMAT_DEFAULT_BUFFER_LENGTH] = { 0, };


	cp_memset(buf, 0, len);

	cp_snprintf(buf, len,
		"%s %s",
		format_media_info(&(mci->media_info), tmp_media_buf, cp_sizeof(tmp_media_buf)),
		format_channel_info(&(mci->channel_info), tmp_channel_buf, cp_sizeof(tmp_channel_buf))
		);

	return buf;
}


//格式化媒体通道信息
cp_char_t* format_channel_info(cp_channel_info_t *ci, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t							tmp_buf[CP_FORMAT_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_memset(buf, 0, len);
	cp_snprintf(buf, len,
		"channel_info[s:%s | c:%d -- l:%d | m:%d | p:%s -- multicast: %s:%d trans_t:%d]",
		//会话信息
		ci->play_session,
		ci->index,
		//媒体信息
		ci->layer,
		ci->mode,
		format_position(&(ci->position), tmp_buf, cp_sizeof(tmp_buf)),
		//网络信息
		ci->multicast_info.ip,
		ci->multicast_info.port,
		ci->stream_description.transport_type
		);

	return buf;
}


//格式化媒体资源信息
cp_char_t* format_media_info(cp_media_info_t *mi, cp_char_t *buf, cp_int32_t len)
{
	cp_char_t							tmp_audio_buf[CP_FORMAT_DEFAULT_BUFFER_LENGTH] = { 0, };
	cp_char_t							tmp_video_buf[CP_FORMAT_DEFAULT_BUFFER_LENGTH] = { 0, };



	cp_memset(buf, 0, len);
	cp_snprintf(buf, len,
		"media_info[id:%s | type:%d | name:%s | addr:%s -- video[%s] -- audio[%s] ]",
		//媒体信息
		mi->id,
		mi->type,
		mi->name,
		mi->addr,
		//视频信息
		format_video_info(&(mi->video_source), tmp_video_buf, cp_sizeof(tmp_video_buf)),
		//音频信息
		format_audio_info(&(mi->audio_source), tmp_audio_buf, cp_sizeof(tmp_audio_buf))
		);

	return buf;
}

//格式化位置信息
cp_char_t* format_position(cp_play_position_t *pp, cp_char_t *buf, cp_int32_t len)
{

	if (!pp || !buf || !len) {
		return CP_NULL;
	}

	cp_memset(buf, 0, len);
	cp_snprintf(buf, len,
		"S[(%d, %d), (%d, %d)] D[(%d, %d), (%d, %d)]",
		//source坐标
		pp->source.left,
		pp->source.top,
		pp->source.right,
		pp->source.bottom,
		//dest坐标
		pp->dest.left,
		pp->dest.top,
		pp->dest.right,
		pp->dest.bottom
		);

	return buf;
}

//格式化音频信息
cp_char_t* format_audio_info(cp_audio_source_info_t *a_info, cp_char_t *buf, cp_int32_t len)
{
	if (!a_info || !buf || !len) {
		return CP_NULL;
	}

	cp_memset(buf, 0, len);
	cp_snprintf(buf, len,
		"enc_name:%s enc_type:%d -- ss_name:%s ss_type:%d sample_rate:%d bit_rate:%d -- volume:%d",
		//音频编码信息
		a_info->encodec_name,
		a_info->encodec_type,
		//音频采集信息
		a_info->sound_channel_name,
		a_info->sound_channel_type,
		a_info->sample_rate,
		a_info->bit_rate,
		//音频揪放信息
		a_info->volume
		);

	return buf;
}

//格式化视频信息
cp_char_t* format_video_info(cp_video_source_info_t *v_info, cp_char_t *buf, cp_int32_t len)
{
	if (!v_info || !buf || !len) {
		return CP_NULL;
	}

	cp_memset(buf, 0, len);
	cp_snprintf(buf, len,
		"enc_name:%s enc_type:%d -- h:%d w:%d fps:%d bps:%d",
		//视频编码信息
		v_info->encodec_name,
		v_info->encodec_type,
		//音频采集信息
		v_info->height,
		v_info->width,
		v_info->fps,
		v_info->bps
		);

	return buf;
}
