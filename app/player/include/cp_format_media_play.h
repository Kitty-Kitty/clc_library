/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2017-04-26

Description:

**************************************************************************/

#ifndef _CP_FORMAT_MEDIA_PLAY_INCLUDE_H_
#define _CP_FORMAT_MEDIA_PLAY_INCLUDE_H_





#include "cp_core.h"
#include "cp_media_play.h"
#include "css_media_info.h"





#define CP_FORMAT_DEFAULT_BUFFER_LENGTH												1024						//��ʾ��ʽ�������С
#define CP_FORMAT_DEFAULT_LONG_BUFFER_LENGTH										1024 * 4					//��ʾ��ʽ���������С



//��ʽ��ý��ͨ����Ϣ
cp_char_t* format_media_channel_info(cp_media_channel_info_t *mci, cp_char_t *buf, cp_int32_t len);

//��ʽ��ý��ͨ����Ϣ
cp_char_t* format_channel_info(cp_channel_info_t *ci, cp_char_t *buf, cp_int32_t len);

//��ʽ��ý����Դ��Ϣ
cp_char_t* format_media_info(cp_media_info_t *mi, cp_char_t *buf, cp_int32_t len);

//��ʽ��λ����Ϣ
cp_char_t* format_position(cp_play_position_t *pp, cp_char_t *buf, cp_int32_t len);

//��ʽ����Ƶ��Ϣ
cp_char_t* format_audio_info(cp_audio_source_info_t *a_info, cp_char_t *buf, cp_int32_t len);

//��ʽ����Ƶ��Ϣ
cp_char_t* format_video_info(cp_video_source_info_t *v_info, cp_char_t *buf, cp_int32_t len);


#endif