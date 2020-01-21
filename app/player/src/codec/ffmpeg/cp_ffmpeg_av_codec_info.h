/**************************************************************************

Copyright:novigo

Author:fangzhenmu@novigo.com.cn

Date:2016-03-18

Description:

**************************************************************************/


#ifndef	_CP_FFMEPG_AV_CODEC_INFO_INCLUDE_H_
#define _CP_FFMEPG_AV_CODEC_INFO_INCLUDE_H_

#include "cp_ffmpeg_av_codec_core.h"




#define		CP_FFMEPG_AV_CODEC_NAME_MAX_LENGTH						32			//��ʾ����������



typedef	struct cp_ffmpeg_av_dev_video_info_s						cp_ffmpeg_av_dev_video_info_t;
typedef	struct cp_ffmpeg_av_dev_audio_info_s						cp_ffmpeg_av_dev_audio_info_t;



//typedef	struct cp_ffmpeg_av_codec_info_s						cp_ffmpeg_av_codec_info_t;
typedef void(*cp_ffmpeg_av_codec_cb)(cp_ffmpeg_av_codec_t* th);




#pragma pack(1)


#define CP_FFMEPG_AV_CODEC_INFO_FIELDS														\
		CP_CODEC_INFO_FIELDS																\
		cp_char_t	av_name[CP_FFMEPG_AV_CODEC_NAME_MAX_LENGTH];	/*��ʾ����������*/		\
		cp_int32_t	av_type;										/*��ʾ����������*/		\
		cp_int32_t	css_type;										/*��ʾcss����������*/	\



/************************************************************************/
/*                                                                      */
/************************************************************************/
struct cp_ffmpeg_av_codec_info_s {
	CP_FFMEPG_AV_CODEC_INFO_FIELDS
};



/************************************************************************/
/*������Ƶ����                                                           */
/************************************************************************/
struct cp_ffmpeg_av_dev_video_info_s
{
	cp_video_description_t			vd;								/*��Ƶ������Ϣ*/
	struct SwsContext				*video_convert_context;			/*��Ƶת������Ϣ*/
};


/************************************************************************/
/*������Ƶ����                                                              */
/************************************************************************/
struct cp_ffmpeg_av_dev_audio_info_s
{
	cp_audio_description_t			ad;								/*��ƵƵ������Ϣ*/
	struct SwrContext				*audio_convert_context;			/*��Ƶת������Ϣ*/
	cp_int32_t						audio_out_linesize;				/*��Ƶת����linesize��Ϣ*/
	cp_int32_t						audio_samples_buffer_size;		/*��Ƶת��������������Ϣ*/
	cp_ffmepg_av_probe_info_t		*probe;							/*ý��̽����*/
	cp_buf_t						*buf;							/*������Ϣ*/
	cp_bool_t						audio_convert;					/*��ʾ��Ƶ�Ƿ��ز���*/
	cp_bool_t						is_async;						/*��ʾ�Ƿ�����첽��ʽ*/
	cp_audio_description_t			cp_convert_ad;					/*��Ƶ�ز���������Ϣ*/
	cp_audio_description_t			ffmpeg_convert_ad;				/*ffmpeg��Ƶ�ز���������Ϣ*/
};



#pragma pack()




#endif





